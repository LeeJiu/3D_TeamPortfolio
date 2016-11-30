#include "stdafx.h"
#include "cScene_OpeningScene.h"

#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cCamera.h"

#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"

#include "cTerrain.h"
#include "cSkinnedAnimation.h"


cScene_OpeningScene::cScene_OpeningScene()
{
}


cScene_OpeningScene::~cScene_OpeningScene()
{
}



HRESULT cScene_OpeningScene::Scene_Init()
{

	//캐릭터 보정 행렬 세팅
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;


	cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Elf/Elf_Master.X", &matCorrection);
	cXMesh_Skinned* pPet_Elephant = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Elephant/pet_Elephant.X", &matCorrection);
	//cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Pant/Pant_Master.X", &matCorrection);

	m_pMainCharacter = new cBaseObject;
	m_pMainCharacter->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Elf/Elf_Master.X", &matCorrection));
	m_pMainCharacter->SetActive(true);
	m_pMainCharacter->pTransform->SetWorldPosition(D3DXVECTOR3(0, 0, 0));

	m_pStage = new cBaseObject;
	m_pStage->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/OpenObject/openObj.X", &matCorrection));
	m_pStage->SetActive(true);
	m_pStage->pTransform->SetWorldPosition(D3DXVECTOR3(0, +100, 0));



	//라이트 푸쉬
	cLight_Direction* pLight1 = new cLight_Direction();
	pLight1->Color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->Intensity = 1.0f;
	pLight1->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);

	this->lights.push_back(pLight1);

	return S_OK;
}

void cScene_OpeningScene::Scene_Release()
{

}

void cScene_OpeningScene::Scene_Update(float timDelta)
{

	m_pMainCharacter->Update(timDelta);
	m_pMainCharacter->pSkinned->Play("HELLO", 0.3f);

	//m_state = STF_FROZEN;
	//m_strName = MyUtil::SetAnimation(m_state);
	//this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);


}

void cScene_OpeningScene::Scene_Render1()
{

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

	m_pMainCharacter->Render();
	m_pStage->Render();
}

void cScene_OpeningScene::Scene_RenderSprite()
{

}