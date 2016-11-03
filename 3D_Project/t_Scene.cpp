#include "StdAfx.h"
#include "t_Scene.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"

t_Scene::t_Scene(void)
{
}

t_Scene::~t_Scene(void)
{
}

HRESULT t_Scene::Scene_Init()
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

	//위에서 로딩된 SkinnedMesh 인스턴스를 만든다.
	this->pSkinned1 = new cSkinnedAnimation();
	this->pSkinned1->Init(pSkinned);

	//캐릭터가 그려질 위치 트랜스폼
	this->pSkinnedTrans = new cTransform();

	//라이트 푸쉬
	cLight_Direction* pLight1 = new cLight_Direction();
	pLight1->Color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->Intensity = 1.0f;
	pLight1->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);

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

	return S_OK;
}

void t_Scene::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(this->pSkinnedTrans);

	this->pSkinned1->Release();
	SAFE_DELETE(this->pSkinned1);
}

void t_Scene::Scene_Update(float timeDelta)
{
	this->pSkinned1->Update(timeDelta);

	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);


		//Terrain 이랑 Ray체크
		this->m_pTerrain->IsIntersectRay(&m_hitPos, &ray);

		m_bMove = true;
		this->pSkinned1->Play("Walk", 0.3f);
	}

	if (KEY_MGR->IsStayDown(VK_LCONTROL))
	{

		if (KEY_MGR->IsOnceDown('1'))
			this->pSkinned1->Play("Idle_01", 0.3f);

		if (KEY_MGR->IsOnceDown('2'))
			this->pSkinned1->Play("Idle_02", 0.3f);

		if (KEY_MGR->IsOnceDown('3'))
			this->pSkinned1->PlayOneShot("Walk", 0.3f);

	}


	if (m_bMove == true)
	{
		//거리를 구한다.
		D3DXVECTOR3 dirToTarget = this->m_hitPos - this->pSkinnedTrans->GetWorldPosition();
		float dist = D3DXVec3Length(&dirToTarget);

		//히트 포인트에 위치하게 되면 lookdirection을 하지 않는다.
		//자신이 자신의 위치를 보게 되면 모델이 사라져버린다.
		if (dist <= 0.001)
		{
			m_bMove = false;
			this->pSkinned1->Play("Idle_01", 0.3f);
			return;
		}

		D3DXVec3Normalize(&dirToTarget, &dirToTarget);

		//방향을 구한다.
		this->pSkinnedTrans->LookDirection(dirToTarget);

		//이동량
		float deltaMove = 5.0f * timeDelta;
		float t = Clamp01(deltaMove / dist);

		//현재 위치에서 히트 포인트로
		D3DXVECTOR3 pos = VecLerp(this->pSkinnedTrans->GetWorldPosition(), this->m_hitPos, t);

		//높이 얻는다. / 터레인의 높이
		pos.y = this->m_pTerrain->GetHeight(pos.x, pos.z);

		this->pSkinnedTrans->SetWorldPosition(pos);
	}

	LOG_MGR->AddLog("x: %.2f, y : %.2f, z : %.2f",
		this->pSkinnedTrans->GetWorldPosition().x,
		this->pSkinnedTrans->GetWorldPosition().y,
		this->pSkinnedTrans->GetWorldPosition().z);
}

void t_Scene::Scene_Render1()
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

	//Hit 위치에 구
	GIZMO_MGR->WireSphere(this->m_hitPos, 0.5f, 0xffff0000);
}


void t_Scene::Scene_RenderSprite()
{
}

