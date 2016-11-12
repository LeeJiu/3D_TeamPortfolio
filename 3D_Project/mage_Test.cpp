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
#include "cMage.h"

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
		"../Resources/Textures/MyHeight512.bmp",
		"../Resources/Textures/terrain1.jpg",
		"../Resources/Textures/terrain2.png",
		"../Resources/Textures/terrain3.png",
		"../Resources/Textures/terrain4.png",
		"../Resources/Textures/Splat.png",
		1.0f,
		100.0f,
		3,
		100);

	m_hitPos = D3DXVECTOR3(0, 0, 0);

	m_bMove = false;

	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Elf/Elf_Master.X", &matCorrection);


	//+++애니메이션 체크 관련+++++

	D3DXMatrixScaling(&matScale, 1, 1, 1);
	matCorrection = matScale * matRotate;
	m_Land = new cBaseObject;
	m_Land->SetMesh(RESOURCE_STATICXMESH->GetResource(
		"../Resources/Meshes/TestMesh/boundMesh.X", &matCorrection));
	m_Land->SetActive(true);

	//m_Land->pTransform->SetWorldPosition(0, this->m_pTerrain->GetHeight(0, 0) - 18, 0);
	m_Land->pTransform->SetWorldPosition(0, 0, 0);

	this->pMage = new cMage;
	this->pMage->SetMesh(pSkinned);
	this->pMage->SetTerrain(m_pTerrain);
	this->pMage->SetCamera(this->pMainCamera);
	this->pMage->SetActive(true);
	
	//캐릭터가 그려질 위치 트랜스폼
	//this->pMage->pTransform = new cTransform();
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
	//================레이 추가. 아래 방향 바뀌지 않음 .
	cRay.direction = D3DXVECTOR3(0, -1, 0);
	cRay.origin = pMage->pTransform->GetWorldPosition();
	//=============== 레이 초기화 끝.
	pMainCamera->SetWorldPosition(2, 5, 2);
	isClick = false;



	return S_OK;
}

void mage_Test::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(this->pMage);
	SAFE_DELETE(this->pTransForCamera);


}

void mage_Test::Scene_Update(float timeDelta)
{

	// 레이 업데이트
	m_currentPos = pMage->pTransform->GetWorldPosition(); // 현재 위치.
														  //cRay.direction = D3DXVECTOR3(0, -1, 0);
	cRay.origin.y = pMage->pTransform->GetWorldPosition().y + 5; // 머리위에 붙일예정

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

	this->pMage->Update(timeDelta);
	

	if (KEY_MGR->IsOnceDown(VK_SPACE))

	{
		LOG_MGR->AddLog("%d %d %s", KEY_MGR->IsOnceUp('W'), current_State, current_Ani.c_str());
	}


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
	this->pMage->Render();

	//Hit 위치에 구
	GIZMO_MGR->WireSphere(this->m_mousePos, 0.5f, 0xffff0000);

	//셰이더에 라이팅 셋팅
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

	m_Land->Render();
	//========== 레이 기지모
	GIZMO_MGR->Line(this->cRay.origin, this->cRay.origin + this->cRay.direction * 100, 0xffffff00);

}


void mage_Test::Scene_RenderSprite()
{
}
