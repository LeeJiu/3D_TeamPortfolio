#include "stdafx.h"
#include "mage_Test.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cCamera.h"

#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"

#include "cTerrain.h"
#include "cSkinnedAnimation.h"



#include "cPet.h"


mage_Test::mage_Test(void)
{
}

mage_Test::~mage_Test(void)
{

	//SAFE_RELEASE(pSky);
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

	//캐릭터 보정 행렬 세팅
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;


	cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Elf/Elf_Master.X", &matCorrection);
	cXMesh_Skinned* pPet_Elephant = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Elephant/pet_Elephant.X", &matCorrection);

	//
	//플레이어 세팅
	//
	m_pPlayer = new cMage;
	m_pPlayer->SetTerrain(m_pTerrain);
	m_pPlayer->SetCamera(pMainCamera);
	m_pPlayer->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Elf/Elf_Master.X", &matCorrection));

	//
	//몬스터 매니저 세팅
	//
	m_pMonMgr = new cMonsterManager;
	m_pMonMgr->SetTerrain(m_pTerrain);
	m_pMonMgr->SetPlayer(m_pPlayer);
	m_pMonMgr->Init();

	m_pPlayer->SetMonsterManager(m_pMonMgr);
	m_pPlayer->SetActive(true);



	//펫 관련
	//this->pPet = new cPet;
	//this->pPet->SetMesh(pPet_Elephant);
	//this->pPet->SetTerrain(m_pTerrain);
	//this->pPet->SetActive(true);
	//this->pPet->pTransform->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);
	//this->pPet->pTransform->LookDirection(this->pMage->pTransform->GetForward(), 90.0f*ONE_RAD);

	//라이트 세팅
	//

	//라이트 푸쉬
	cLight_Direction* pLight1 = new cLight_Direction();
	pLight1->Color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->Intensity = 1.0f;
	pLight1->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);

	/*testLight = new cLight_Direction();
	testLight->Color = D3DXCOLOR(1, 1, 1, 1);
	testLight->Intensity = 1.0f;
	testLight->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);*/

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


	return S_OK;
}

void mage_Test::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);
	SAFE_DELETE(m_pPlayer);
	m_pMonMgr->Release();
	SAFE_DELETE(m_pMonMgr);

	for (int i = 0; i < lights.size(); i++)
	{
		SAFE_DELETE(lights[i]);
	}
	lights.clear();
}

void mage_Test::Scene_Update(float timeDelta)
{

	if (KEY_MGR->IsOnceUp('T'))
	{
		ITEM_MGR->createItem(1, D3DXVECTOR3(0, 7, 0));

	}
	if (KEY_MGR->IsOnceUp('Y'))
	{
		ITEM_MGR->createItem(0, D3DXVECTOR3(0, 7, 0));

	}


	m_pPlayer->Update(timeDelta);

	m_pMonMgr->Update(timeDelta);

	

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

	//this->pMage->Update(timeDelta);
	//m_pMonMgr->Update(timeDelta);

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

	m_pMonMgr->Render();
	m_pPlayer->Render();

}

void mage_Test ::Scene_RenderSprite()
{
	m_pPlayer->BaseSpriteRender();
}

void mage_Test::Scene_RenderFont()
{
	this->m_pPlayer->BaseFontRender();
}

	//if (pMage->GetIsPetOn())
	//{
	//	this->pPet->Render();
	//}

