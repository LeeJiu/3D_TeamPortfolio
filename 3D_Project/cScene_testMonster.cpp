#include "stdafx.h"
#include "cScene_testMonster.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cCamera.h"


cScene_testMonster::cScene_testMonster()
{
}


cScene_testMonster::~cScene_testMonster()
{
}

HRESULT cScene_testMonster::Scene_Init()
{
	//
	//파일 로드
	//
	LOAD_MGR->LoadObjects(m_vObject);
	LOAD_MGR->LoadBoundBox(m_vBoundBox);

	//
	//터레인 세팅
	//
	m_pTerrain = new cTerrain;
	m_pTerrain->Init(
		"../Resources/Textures/MyHeight256.bmp",
		"../Resources/Textures/terrain1.png",
		"../Resources/Textures/terrain2.png",
		"../Resources/Textures/terrain3.png",
		"../Resources/Textures/terrain4.png",
		"../Resources/Textures/Splat2.png",
		1.0f,
		100.0f,
		3,
		100);

	//캐릭터 보정 행렬 세팅
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;


	//
	//플레이어 세팅
	//
	m_pPlayer = new cBerserker;
	m_pPlayer->SetTerrain(m_pTerrain);
	m_pPlayer->SetCamera(pMainCamera);
	m_pPlayer->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Pant/Pant_Master.X", &matCorrection));


	//
	//몬스터 매니저 세팅
	//
	m_pMonMgr = new cMonsterManager;
	m_pMonMgr->SetTerrain(m_pTerrain);
	m_pMonMgr->SetPlayer(m_pPlayer);
	m_pMonMgr->Init();


	m_pPlayer->SetMonsterManager(m_pMonMgr);
	m_pPlayer->SetActive(true);

	//
	//라이트 세팅
	//

	//라이트 푸쉬
	cLight_Direction* pLight1 = new cLight_Direction();
	pLight1->Color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->Intensity = 1.0f;
	pLight1->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);

	/*cLight_Point* pLight2 = new cLight_Point();
	pLight2->Color = D3DXCOLOR(1, 1, 1, 0);
	pLight2->minRange = 5.0f;
	pLight2->maxRange = 10.0f;
	pLight2->distancePow = 10.0f;

	cLight_Point* pLight3 = new cLight_Point();
	pLight3->Color = D3DXCOLOR(1, 1, 1, 0);
	pLight3->minRange = 5.0f;
	pLight3->maxRange = 10.0f;
	pLight3->distancePow = 10.0f;
	pLight3->pTransform->SetWorldPosition(3, 3, 0);
	pLight3->Intensity = 0.5f;*/

	this->lights.push_back(pLight1);
	/*this->lights.push_back(pLight2);
	this->lights.push_back(pLight3);*/


	int size = m_vObject.size();
	for (int i = 0; i < size; ++i)
	{
		m_vRender.push_back(m_vObject[i]);
	}

	m_vRender.push_back(dynamic_cast<cBaseObject*>(m_pPlayer));

	size = m_pMonMgr->GetMonsters().size();
	for (int i = 0; i < size; ++i)
	{
		m_vRender.push_back(dynamic_cast<cBaseObject*>(m_pMonMgr->GetMonsters()[i]));
	}

	return S_OK;
}

void cScene_testMonster::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);
	SAFE_DELETE(m_pPlayer);

	m_pMonMgr->Release();
	SAFE_DELETE(m_pMonMgr);
}

void cScene_testMonster::Scene_Update(float timeDelta)
{
	int size = m_vRender.size();
	for (int i = 0; i < size; ++i)
	{
		m_vRender[i]->Update(timeDelta);
	}
}

void cScene_testMonster::Scene_Render1()
{
	m_pTerrain->Render(this->pMainCamera, dynamic_cast<cLight_Direction*>(lights[0]));

	m_vCulling.clear();
	int size = m_vRender.size();
	for (int i = 0; i < size; i++) 
	{
		if (this->pMainCamera->Frustum.IsInFrustum(m_vRender[i]))
		{
			m_vCulling.push_back(m_vRender[i]);
		}
	}

	//적용되는 LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < this->lights.size(); i++)
		matLights[i] = this->lights[i]->GetLightMatrix();

	//셰이더에 라이팅 셋팅
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	//cXMesh_Static::SetTechniqueName("ReciveShadow");
	cXMesh_Static::SetBaseLight(dynamic_cast<cLight_Direction*>(lights[0]));

	//셰이더에 라이팅 셋팅
	//cXMesh_Skinned::SetTechniqueName("ReciveShadow");
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

	cXMesh_Skinned::SetCamera(this->pMainCamera);

	size = m_vCulling.size();
	for (int i = 0; i < size; i++)
	{
		m_vCulling[i]->Render();
	}
}