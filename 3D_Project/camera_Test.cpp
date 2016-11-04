#include "stdafx.h"
#include "camera_Test.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"

camera_Test::camera_Test()
{
}
camera_Test::~camera_Test()
{
}

HRESULT camera_Test::Scene_Init()
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
	pSkinnedTrans->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);


	this->pSkinnedTrans->AddChild(this->pMainCamera);
	this->pMainCamera->SetLocalPosition(0, 5, -10);


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
	cRay.origin = pSkinnedTrans->GetWorldPosition();
	//=============== 레이 초기화 끝.
	//pMainCamera->SetWorldPosition(2, 5, 2);
	isClick = false;
	return S_OK;
}

void camera_Test::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(this->pSkinnedTrans);

	this->pSkinned1->Release();
	SAFE_DELETE(this->pSkinned1);
}

void camera_Test::Scene_Update(float timeDelta)
{
	pMainCamera->DefaultControl3(timeDelta, this->pSkinnedTrans);

	// 레이 업데이트 
	m_currentPos = pSkinnedTrans->GetWorldPosition(); // 현재 위치. 
													  //cRay.direction = D3DXVECTOR3(0, -1, 0);
	cRay.origin.y = pSkinnedTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정

	if (KEY_MGR->IsStayDown('W'))
	{
		isMove = true;
		cRay.origin += pSkinnedTrans->GetForward()*0.2f;
	}
	if (KEY_MGR->IsStayDown('S'))
	{
		isMove = true;
		cRay.origin -= pSkinnedTrans->GetForward()*0.2f;

	}
	if (KEY_MGR->IsStayDown('Q'))
	{
		isMove = true;
		cRay.origin += pSkinnedTrans->GetRight()*0.2f;

	}
	if (KEY_MGR->IsStayDown('E'))
	{
		isMove = true;
		cRay.origin -= pSkinnedTrans->GetRight()*0.2f;
	}
	if (KEY_MGR->IsStayDown('A'))
	{
		pSkinnedTrans->RotateSelf(0, -2 * ONE_RAD, 0);
	}

	if (KEY_MGR->IsStayDown('D'))
	{
		pSkinnedTrans->RotateSelf(0, 2 * ONE_RAD, 0);
	}
	//=========================
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);

		this->m_pTerrain->IsIntersectRay(&m_mousePos, &ray);
		isClick = true;
	}

	if (isClick == true)
	{
		//D3DXVECTOR3 dir = m_mousePos - cRay.origin;
		//D3DXVec3Normalize(&dir, &dir);

		D3DXVECTOR3 dir(0, 0, 1);
		cRay.origin += dir*timeDelta;

	//	LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
	//		cRay.origin.x,
	//		cRay.origin.y,
	//		cRay.origin.z);
	}




	// 오브젝트와 충돌했다면. ( 걸러 낼려면 반지름 값을 넣어놔야 한다. )

	//m_lastPos = this->pSkinnedTrans->GetWorldPosition();
	//m_lastPos.y = -1000;
	// 추후에 거리 값을 이용해서 2,3번째 인자 값을 걸러 낼꺼임.
	if ((
		PHYSICS_MGR->IsRayHitStaticMeshObject(
			&this->cRay,
			this->m_Land,
			this->m_Land->pTransform,
			&this->m_prePos,
			NULL)) == true)
	{
		m_lastPos = m_prePos; // 오브젝트 충돌 값이 더 클 경우 Last 값을 갱신한다. 
	}
	else
	{
		m_lastPos.y = pSkinnedTrans->GetWorldPosition().y - 10;
	}

	// 터레인과 충돌 했다면. 
	if (this->m_pTerrain->IsIntersectRay(&m_prePos, &cRay) == true)
	{
		if (m_lastPos.y > m_prePos.y)
		{
			m_prePos = m_lastPos;
		}
	}



	//=================================== 케릭터를 최종적으로 움직이게 하는 부분 
	if (fabs(m_prePos.y - m_currentPos.y) < 0.5f && isMove == true) // 숫자는 넘어갈 수 있는 높이. ( 아래에서 위로 갈떄. )
	{
		this->pSkinnedTrans->SetWorldPosition(m_prePos);
		m_currentPos = m_prePos; // 좌표 갱신
	}
	// 레이랑 케릭터 거리가 멀어지면 레이가 더이상 넘어가지 못하게 만든다.
	float rayCheckDis = D3DXVec3Length(&(cRay.origin - pSkinnedTrans->GetWorldPosition()));
	if (rayCheckDis > 0.25f) // 상수 값은 속력 보다 조금 높은 값.
	{
		cRay.origin = pSkinnedTrans->GetWorldPosition();
		cRay.origin.y = pSkinnedTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정

	}

	isMove = false;
	//=================================== 케릭터를 최종적으로 움직이게 하는 부분  끗.

	this->pSkinned1->Update(timeDelta);


	if (KEY_MGR->IsOnceDown(VK_SPACE))
	{
		LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
			this->pSkinnedTrans->GetWorldPosition().x,
			this->pSkinnedTrans->GetWorldPosition().y,
			this->pSkinnedTrans->GetWorldPosition().z);

		LOG_MGR->AddLog("Rx: %.2f, Ry : %.2f, Rz : %.2f",
			m_prePos.x,
			m_prePos.y,
			m_prePos.z);

	}


}

void camera_Test::Scene_Render1()
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
	GIZMO_MGR->WireSphere(this->m_mousePos, 0.5f, 0xffff0000);

	//셰이더에 라이팅 셋팅
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

	m_Land->Render();
	//========== 레이 기지모
	GIZMO_MGR->Line(this->cRay.origin, this->cRay.origin + this->cRay.direction * 100, 0xffffff00);

}


void camera_Test::Scene_RenderSprite()
{
}

