#include "stdafx.h"
#include "DragonTest.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"

DragonTest::DragonTest(void)
{
}

DragonTest::~DragonTest(void)
{
}

HRESULT DragonTest::Scene_Init()
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
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Pant/Pant_Master.X", &matCorrection);

	//+++애니메이션 체크 관련+++++

	D3DXMatrixScaling(&matScale, 1, 1, 1);
	matCorrection = matScale * matRotate;
	m_Land = new cBaseObject;
	m_Land->SetMesh(RESOURCE_STATICXMESH->GetResource(
		"../Resources/Meshes/TestMesh/boundMesh.X", &matCorrection));
	m_Land->SetActive(true);

	//m_Land->pTransform->SetWorldPosition(0, this->m_pTerrain->GetHeight(0, 0) - 18, 0);
	m_Land->pTransform->SetWorldPosition(0, 0, 0);

	//몬스터
	this->m_pMonMgr = new cMonsterManager;
	this->pBerserker = new cBerserker;

	this->m_pMonMgr->SetTerrain(this->m_pTerrain);
	this->m_pMonMgr->SetPlayer(this->pBerserker);
	this->m_pMonMgr->Init();

	this->pBerserker->SetMesh(pSkinned);
	this->pBerserker->SetTerrain(m_pTerrain);
	this->pBerserker->SetCamera(this->pMainCamera);
	this->pBerserker->SetMonsterManager(this->m_pMonMgr);
	this->pBerserker->SetActive(true);

	//캐릭터가 그려질 위치 트랜스폼
	this->pBerserker->pTransform->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);



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

	isClick = false;

	m_CharacterBar = new cUI_CharacterBar;
	m_CharacterBar->init();
	//

	//라이트 추가
	//cLight_Point* pL = new cLight_Point();
	//pL->Color = D3DXCOLOR(0, 0, 1, 1);
	//pL->distancePow = 10.0f;
	//pL->maxRange = 10.0f;
	//pL->minRange = 3.0f;
	//pL->Intensity = 1.0f;
	//pL->pTransform->SetWorldPosition(pos2);
	//
	//this->extraLights.push_back(pL);

	return S_OK;
}

void DragonTest::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(this->pBerserker);
	m_pMonMgr->Release();
	SAFE_DELETE(m_pMonMgr);

	for (int i = 0; i < lights.size(); i++)
	{
		SAFE_DELETE(lights[i]);
	}
	lights.clear();

	SAFE_DELETE(m_CharacterBar);
}

void DragonTest::Scene_Update(float timeDelta)
{
	//this->pTransForCamera->SetWorldPosition(this->pBerserker->pTransform->GetWorldPosition());
	m_CharacterBar->update();

	if (KEY_MGR->IsOnceUp('T'))
	{
		ITEM_MGR->createItem(1, D3DXVECTOR3(0, 7, 0));

	}
	if (KEY_MGR->IsOnceUp('Y'))
	{
		ITEM_MGR->createItem(0, D3DXVECTOR3(0, 7, 0));

	}


	this->pBerserker->Update(timeDelta);
	m_pMonMgr->Update(timeDelta);
	showUpdate();
	//this->ReadyShadowMap(&m_pMonMgr->MonToBasic());
}

void DragonTest::Scene_Render1()
{
	m_pTerrain->Render(this->pMainCamera, dynamic_cast<cLight_Direction*>(lights[0]));

	//적용되는 LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < this->lights.size(); i++)
		matLights[i] = this->lights[i]->GetLightMatrix();

	//셰이더에 라이팅 셋팅
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());
	//cXMesh_Skinned::SetLighting(&this->extraLights);
	
	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::SetTechniqueName("ReciveShadow");
	cXMesh_Skinned::sSkinnedMeshEffect->SetTexture("Ramp_Tex", RESOURCE_TEXTURE->GetResource("../Resources/Textures/Ramp_1.png"));
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);
	//

	//
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("ReciveShadow");		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

	//cXMesh_Skinned::SetTechniqueName("ReciveShadow");


	this->pBerserker->Render();
	this->m_pMonMgr->Render();
	//RenderEnvironment(pBerserker->pTransform);
	//m_Land->Render();
}


void DragonTest::Scene_RenderSprite()
{
	this->pBerserker->BaseSpriteRender();
	m_CharacterBar->uiRender();


}
void DragonTest::showUpdate()
{
	//방향성광원에 붙은 카메라의 Frustum 업데이트
	this->pDirectionLightCamera->UpdateMatrix();
	this->pDirectionLightCamera->UpdateFrustum();

	//쉐도우 맵 그린다.
	this->pDirectionLightCamera->RenderTextureBegin(0xffffffff);

	cXMesh_Static::SetCamera(this->pDirectionLightCamera);
	cXMesh_Static::SetTechniqueName("CreateShadow");

	cXMesh_Skinned::SetCamera(this->pDirectionLightCamera);
	cXMesh_Skinned::SetTechniqueName("CreateShadow");


	//만약 Terrain 도 쉐도우 맵을 그려야한다면...
	// if (m_pTerrain != NULL)
	// {
	// 	m_pTerrain->RenderShadow(this->pDirectionLightCamera);
	// }
	//

	this->pDirectionLightCamera->RenderTextureEnd();


	// //만약 Terrain 도 쉐도우 맵을 셋팅한다면...
	// if (m_pTerrain != NULL)
	// {
	// 	m_pTerrain->m_pTerrainEffect->SetTexture("Shadow_Tex",
	// 		this->pDirectionLightCamera->GetRenderTexture());
	// 
	// 	m_pTerrain->m_pTerrainEffect->SetMatrix("matLightViewProjection",
	// 		&this->pDirectionLightCamera->GetViewProjectionMatrix());
	// }



	//쉐도우 Texture
	cXMesh_Static::sStaticMeshEffect->SetTexture("Shadow_Tex",
		this->pDirectionLightCamera->GetRenderTexture());

	//쉐도우 행렬
	cXMesh_Static::sStaticMeshEffect->SetMatrix("matLightViewProjection",
		&this->pDirectionLightCamera->GetViewProjectionMatrix());


	//쉐도우 Texture
	cXMesh_Skinned::sSkinnedMeshEffect->SetTexture("Shadow_Tex",
		this->pDirectionLightCamera->GetRenderTexture());

	//쉐도우 행렬
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrix("matLightViewProjection",
		&this->pDirectionLightCamera->GetViewProjectionMatrix());
}