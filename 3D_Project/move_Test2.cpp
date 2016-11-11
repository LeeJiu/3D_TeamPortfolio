#include "StdAfx.h"
#include "move_Test2.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"

move_Test2::move_Test2(void)
{
}

move_Test2::~move_Test2(void)
{
}

HRESULT move_Test2::Scene_Init()
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

	cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Queen/Queen.X", &matCorrection);

	//=================== 스태틱 렌더 그림.
	D3DXMatrixScaling(&matScale, 1, 1, 1);

	matCorrection = matScale * matRotate;
	m_Land = new cBaseObject;
	m_Land->SetMesh(RESOURCE_STATICXMESH->GetResource(
		"../Resources/Meshes/TestMesh/boundMesh.X", &matCorrection));
	m_Land->SetActive(true);

	//m_Land->pTransform->SetWorldPosition(0, this->m_pTerrain->GetHeight(0, 0) - 18, 0);
	m_Land->pTransform->SetWorldPosition(0, 0, 0);


	//위에서 로딩된 SkinnedMesh 인스턴스를 만든다.
	this->pSkinned1 = new cSkinnedAnimation();
	this->pSkinned1->Init(pSkinned);


	//캐릭터가 그려질 위치 트랜스폼
	this->pSkinnedTrans = new cTransform();
	pSkinnedTrans->SetWorldPosition(0, m_pTerrain->GetHeight(0,0)+3.f, 0);
	
	pSkinnedBound = new cBoundBox;
	pSkinnedBound->Init(D3DXVECTOR3(-2, -2, -2), D3DXVECTOR3(2, 2, 2));

	move = new moveClass;
	move->init(pSkinned1, pSkinnedTrans, m_pTerrain,pMainCamera,pSkinnedBound);

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


	collTrans = new cTransform;
	collTrans->SetWorldPosition(3, m_pTerrain->GetHeight(3, 3) + 2.f, 3);


	collBox = new cBoundBox;
	collBox->Init(D3DXVECTOR3(-2, -2, -2), D3DXVECTOR3(2, 2, 2));
	//================레이 추가. 아래 방향 바뀌지 않음 .
	//=============== 레이 초기화 끝.
	pMainCamera->SetWorldPosition(2, 5, 2);
	return S_OK;
}

void move_Test2::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(this->pSkinnedTrans);

	this->pSkinned1->Release();
	SAFE_DELETE(this->pSkinned1);
}

void move_Test2::Scene_Update(float timeDelta)
{
	move->update(timeDelta, m_Land,collBox,collTrans);

	this->pSkinned1->Update(timeDelta);


	if (KEY_MGR->IsOnceDown(VK_SPACE))
	{
		LOG_MGR->AddLog("T:%.2f,P:%.2f",
			m_pTerrain->GetHeight(0, 0), pSkinnedTrans->GetWorldPosition().y);

	}


}

void move_Test2::Scene_Render1()
{
	m_pTerrain->Render(this->pMainCamera, dynamic_cast<cLight_Direction*>(lights[0]));

	//적용되는 LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < this->lights.size(); i++)
		matLights[i] = this->lights[i]->GetLightMatrix();

	//셰이더에 라이팅 셋팅
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

	//SkinnedEffect CameraMatrix 적용
	//D3DXMATRIXA16 matViewProjection = pCamera->GetViewProjectionMatrix();
	//m_pSkinnedEffect->SetMatrix( "matViewProjection", &matViewProjection );

	cXMesh_Skinned::SetCamera(this->pMainCamera);

	this->pSkinned1->Render(pSkinnedTrans);

	//가지고 있는 Animation 을출력해보자..
	RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Queen/Queen.X")->ShowAnimationName(0, 100);

	//Hit 위move_Test2치에 구
	//GIZMO_MGR->WireSphere(this->m_mousePos, 0.5f, 0xffff0000);

	//셰이더에 라이팅 셋팅
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

	m_Land->Render();
	//========== 레이 기지모
	move->render();

	collBox->RenderGizmo(collTrans);

	//GIZMO_MGR->WireSphere(pSkinnedTrans->GetWorldPosition()
	//	, pSkinnedBox->radius, 0xffff0000);
	//
	pSkinnedBound->RenderGizmo(pSkinnedTrans);

}


void move_Test2::Scene_RenderSprite()
{
}

