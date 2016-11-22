#include "stdafx.h"
#include "mage_Test.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"


#include "cPet.h"


mage_Test::mage_Test(void)
{
}

mage_Test::~mage_Test(void)
{
}

HRESULT mage_Test::Scene_Init()
{
	m_pTerrain = new cTerrain;
	m_pTerrain->Init(
		"../Resources/Textures/MyHeight256.bmp",
		"../Resources/Textures/terrain1.png",
		"../Resources/Textures/terrain2.png",
		"../Resources/Textures/terrain3.png",
		"../Resources/Textures/terrain4.png",
		"../Resources/Textures/Splat.png",
		1.0f,
		100.0f,
		3,
		100);

	m_bMove = false;

	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Elf/Elf_Master.X", &matCorrection);
	cXMesh_Skinned* pPet_Elephant = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Elephant/pet_Elephant.X", &matCorrection);


	//+++애니메이션 체크 관련+++++

	D3DXMatrixScaling(&matScale, 1, 1, 1);
	matCorrection = matScale * matRotate;
	m_Land = new cBaseObject;
	m_Land->SetMesh(RESOURCE_STATICXMESH->GetResource(
		"../Resources/Meshes/TestMesh/boundMesh.X", &matCorrection));
	m_Land->SetActive(true);

	//m_Land->pTransform->SetWorldPosition(0, this->m_pTerrain->GetHeight(0, 0) - 18, 0);
	m_Land->pTransform->SetWorldPosition(0, 0, 0);

	//몬스터 & 플레이어
	this->m_pMonMgr = new cMonsterManager;
	this->pMage = new cMage;

	this->m_pMonMgr->SetTerrain(this->m_pTerrain);
	this->m_pMonMgr->SetPlayer(this->pMage);
	this->m_pMonMgr->Init();


	this->pMage->SetMesh(pSkinned);
	this->pMage->SetTerrain(m_pTerrain);
	this->pMage->SetCamera(this->pMainCamera);
	this->pMage->SetMonsterManager(this->m_pMonMgr);
	this->pMage->SetActive(true);


	//펫 관련
	//this->pPet = new cPet;
	//this->pPet->SetMesh(pPet_Elephant);
	//this->pPet->SetTerrain(m_pTerrain);
	//this->pPet->SetActive(true);
	//this->pPet->pTransform->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);
	//this->pPet->pTransform->LookDirection(this->pMage->pTransform->GetForward(), 90.0f*ONE_RAD);


	//캐릭터가 그려질 위치 트랜스폼
	this->pMage->pTransform->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);
	this->pTransForCamera = new cTransform();


	this->pMage->pTransform->AddChild(this->pMainCamera);
	this->pMainCamera->SetLocalPosition(0, 5, -10);
	isCharView = true;
	isAltView = false;


	//라이트 푸쉬
	cLight_Direction* pLight1 = new cLight_Direction();
	pLight1->Color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->Intensity = 1.0f;
	pLight1->pTransform->SetRotateWorld(45 * ONE_RAD, 45 * ONE_RAD, 45 * ONE_RAD);

	cLight_Point* pLight2 = new cLight_Point();
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
	pLight3->Intensity = 0.5f;

	this->lights.push_back(pLight1);
	this->lights.push_back(pLight2);
	this->lights.push_back(pLight3);

	isMove = false;

	pMainCamera->SetWorldPosition(2, 5, 2);
	isClick = false;



	return S_OK;
}

void mage_Test::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(this->pMage);
	m_pMonMgr->Release();
	SAFE_DELETE(m_pMonMgr);
	SAFE_DELETE(this->pTransForCamera);


	for (int i = 0; i < lights.size(); i++)
	{
		SAFE_DELETE(lights[i]);
	}
	lights.clear();
}

void mage_Test::Scene_Update(float timeDelta)
{
	this->pTransForCamera->SetWorldPosition(this->pMage->pTransform->GetWorldPosition());

	if (isCharView && KEY_MGR->IsStayDown(VK_MENU))
	{
		isAltView = true;
		isCharView = false;
		this->pMainCamera->ReleaseParent();
		this->pTransForCamera->AddChild(this->pMainCamera);
	}
	if (isAltView && KEY_MGR->IsOnceUp(VK_MENU))
	{
		this->pMainCamera->Reset();
		this->pTransForCamera->Reset();
		this->pTransForCamera->SetWorldMatrix(this->pMage->pTransform->GetFinalMatrix());

		this->pMage->pTransform->AddChild(this->pMainCamera);
		this->pMainCamera->SetLocalPosition(0, 5, -10);
		isCharView = true;
		isAltView = false;
	}


	if (isCharView)
	{
		pMainCamera->DefaultControl3(timeDelta, this->pMage->pTransform);
	}
	else if (isAltView)
	{
		pMainCamera->DefaultControl3(timeDelta, this->pTransForCamera);
	}



	//if (pMage->GetIsPetOn())
	//{
	//	this->pPet->Update(timeDelta);
	//	D3DXVECTOR3 petSpace(0, 6, 0);
	//	this->pPet->pTransform->AddChild(this->pMage->pTransform);
	//	this->pMage->pTransform->SetLocalPosition(petSpace);
	//	
	//}
	//else
	//{
	//	this->pMage->pTransform->ReleaseParent();
	//	this->pPet->pTransform->LookDirection(this->pMage->pTransform->GetForward(), 90.0f*ONE_RAD);
	//	this->pPet->pTransform->SetWorldPosition(this->pMage->pTransform->GetWorldPosition().x, m_pTerrain->GetHeight(0, 0), this->pMage->pTransform->GetWorldPosition().z);
	//}
	//


	this->pMage->Update(timeDelta);

	m_pMonMgr->Update(timeDelta);



}

void mage_Test::Scene_Render1()
{
	m_pTerrain->Render(this->pMainCamera, dynamic_cast<cLight_Direction*>(lights[0]));

	//적용되는 LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < this->lights.size(); i++)
		matLights[i] = this->lights[i]->GetLightMatrix();

	//셰이더에 라이팅 셋팅
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

	cXMesh_Skinned::SetCamera(this->pMainCamera);

	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);


	this->pMage->Render();

	this->m_pMonMgr->Render();


	//if (pMage->GetIsPetOn())
	//{
	//	this->pPet->Render();
	//}





	m_Land->Render();

}


void mage_Test::Scene_RenderSprite()
{
}
