#include "StdAfx.h"
#include "move_Test.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"

move_Test::move_Test(void)
{
}

move_Test::~move_Test(void)
{
}

HRESULT move_Test::Scene_Init()
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
	//
	pSkinnedBox = new cBoundBox;
	pSkinnedBox->Init(D3DXVECTOR3(-1, -1, -1), D3DXVECTOR3(1, 1, 1));
	//pSkinnedBox->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(2, 2, 2));

	// pSkinnedBox->localCenter = D3DXVECTOR3(0, 0, 0);
	// pSkinnedBox->localMaxPos = D3DXVECTOR3(2, 2, 2);
	// pSkinnedBox->localMinPos = D3DXVECTOR3(-2, -2, -2);
	// pSkinnedBox->halfSize = D3DXVECTOR3(2, 2, 2);
	// pSkinnedBox->radius = 3.f;

	//캐릭터가 그려질 위치 트랜스폼
	this->pSkinnedTrans = new cTransform();
	pSkinnedTrans->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);
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
	pMainCamera->SetWorldPosition(2, 5, 2);
	isClick = false;
	//
	colliTest = new cTransform;
	colliTest->SetWorldPosition(3, m_pTerrain->GetHeight(3, 3) + 2, 3);

	testBox = new cBoundBox;
	//testBox->Init(D3DXVECTOR3(-2, -2, -2), D3DXVECTOR3(2, 2, 2));
	testBox->Init(D3DXVECTOR3(-1, -2, -1), D3DXVECTOR3(3, 2, 3));

	//testBox->localCenter = D3DXVECTOR3(0, 0, 0);
	//testBox->localMaxPos = D3DXVECTOR3(3, 3, 3);
	//testBox->localMinPos = D3DXVECTOR3(-3, -3, -3);
	//testBox->halfSize = D3DXVECTOR3(3, 3, 3);
	//
	//testBox->radius = 3.f;
	//
	quad[0] = D3DXVECTOR3(-3, 0, 3);
	quad[1] = D3DXVECTOR3(3, 0, 3);
	quad[2] = D3DXVECTOR3(-3, 0, -3);
	quad[3] = D3DXVECTOR3(3, 0, -3);

	boundHit = false;

	skill = new cSkillUi;
	skill->init();
	//====================== 매니져
	D3DXVECTOR3 itmePos = D3DXVECTOR3(0, m_pTerrain->GetHeight(0, 0),0);
	ITEM_MGR->createItem(0, itmePos);
	//======================
	m_inven = new cInven;
	m_inven->init();
	return S_OK;
}

void move_Test::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(this->pSkinnedTrans);

	this->pSkinned1->Release();
	SAFE_DELETE(this->pSkinned1);

	m_inven->release();
	//SAFE_DELETE(this->m_inven);

}

void move_Test::Scene_Update(float timeDelta)
{
	// 레이 업데이트 
	m_currentPos = pSkinnedTrans->GetWorldPosition(); // 현재 위치. 
	//cRay.direction = D3DXVECTOR3(0, -1, 0);
	cRay.origin.y = pSkinnedTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정

	//PHYSICS_MRG->



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
		cRay.origin -= pSkinnedTrans->GetRight()*0.2f;

	}
	if (KEY_MGR->IsStayDown('E'))
	{
		isMove = true;
		cRay.origin += pSkinnedTrans->GetRight()*0.2f;
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
	if (KEY_MGR->IsOnceDown('T')) // 쿼드 테스트용.
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);

		this->m_pTerrain->IsIntersectRay(&m_mousePos, &ray);
	}
	if (KEY_MGR->IsOnceDown('O'))
	{
		ITEM_MGR->createItem(1, D3DXVECTOR3(0, MyUtil::RandomFloatRange(3,10), 0));

	}
	//=========================
	//if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	//{
	//	Ray ray;
	//	POINT ptMousePos = GetMousePos();
	//	D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
	//	this->pMainCamera->ComputeRay(&ray, &screenPos);

	//	this->m_pTerrain->IsIntersectRay(&m_mousePos, &ray);
	//	isClick = true;
	//}

	if (isClick == true)
	{
		D3DXVECTOR3 dir = m_mousePos - cRay.origin;	// 방향 및 mousePos의 원점 이동.	
		dir.y = 0;


		if (D3DXVec3Length(&dir) > 0.5f)
		{
			isMove = true;
			D3DXVec3Normalize(&dir, &dir);
			D3DXVECTOR3 lerp = pSkinnedTrans->GetForward();
			D3DXVec3Lerp(&lerp, &lerp, &dir, 0.2);
			pSkinnedTrans->LookDirection(lerp, D3DXVECTOR3(0, 1, 0));

			cRay.origin += dir*0.2f;
		}
		else
		{
			isMove = false;
			isClick = false;

			LOG_MGR->AddLog("Tx: %.2f, Ty : %.2f, Tz : %.2f",
				cRay.origin.x,
				cRay.origin.y,
				cRay.origin.z);
		}
	}

	// PHYSICS_MRG->IsOverlap();
	frontRay.origin = pSkinnedTrans->GetWorldPosition();
	frontRay.origin.y = pSkinnedTrans->GetWorldPosition().y+2;
	frontRay.direction = cRay.direction;


	//if (PHYSICS_MGR->IsOverlap(pSkinnedTrans, pSkinnedBox, colliTest, testBox))
	//{
	//	boundHit = true;
	//	if (PHYSICS_MGR->IsRayHitBound(&cRay, testBox, colliTest, NULL, NULL))
	//	{
	//		LOG_MGR->AddLog("충돌1");

	//	}
		if(PHYSICS_MGR->IsBlocking(
			pSkinnedTrans, 
			pSkinnedBox, 
			colliTest, testBox, 1.f))
		{
			cRay.origin = pSkinnedTrans->GetWorldPosition();
			cRay.origin.y = pSkinnedTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정
			LOG_MGR->AddLog("충돌2");
		}
	

	

	//if (
	//	PHYSICS_MGR->IsRayHitBound(
	//	&cRay,				//레이
	//	testBox,			//바운드
	//	colliTest,	//바운드의 Transform
	//	NULL,     //Hit 위치 ( NULL 이면 대입 안됨 )
	//	NULL	  //Hit 의 노말 ( NULL 이면 대입 안됨 )
	//	))
	//{
	//	LOG_MGR->AddLog("츙돌");
	//}

	//D3DXIntersectTri()

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

	// 터레인과 충돌 했다면. / 캐릭터 위치에서 쏘는 레이와 터레인을 충돌 체크
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
	skill->update();




	//if (KEY_MGR->IsStayDown(VK_LCONTROL))
	//{

	//	if (KEY_MGR->IsOnceDown('1'))
	//		this->pSkinned1->Play("Idle_01", 0.3f);

	//	if (KEY_MGR->IsOnceDown('2'))
	//		this->pSkinned1->Play("Idle_02", 0.3f);

	//	if (KEY_MGR->IsOnceDown('3'))
	//		this->pSkinned1->PlayOneShot("Walk", 0.3f);

	//}



	//if (m_bMove == true)
	//{
	//	//거리를 구한다.
	//	D3DXVECTOR3 dirToTarget = this->m_hitPos - this->pSkinnedTrans->GetWorldPosition();
	//	float dist = D3DXVec3Length(&dirToTarget);

	//	//히트 포인트에 위치하게 되면 lookdirection을 하지 않는다.
	//	//자신이 자신의 위치를 보게 되면 모델이 사라져버린다.
	//	if (dist <= 0.001)
	//	{
	//		m_bMove = false;
	//		this->pSkinned1->Play("Idle_01", 0.3f);
	//		return;
	//	}

	//	D3DXVec3Normalize(&dirToTarget, &dirToTarget);

	//	//방향을 구한다.
	//	this->pSkinnedTrans->LookDirection(dirToTarget);

	//	//이동량
	//	float deltaMove = 5.0f * timeDelta;
	//	float t = Clamp01(deltaMove / dist);

	//	//현재 위치에서 히트 포인트로
	//	D3DXVECTOR3 pos = VecLerp(this->pSkinnedTrans->GetWorldPosition(), this->m_hitPos, t);

	//	//높이 얻는다. / 터레인의 높이
	//	pos.y = this->m_pTerrain->GetHeight(pos.x, pos.z);

	//	this->pSkinnedTrans->SetWorldPosition(pos);
	//}

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
	PHYSICS_MGR->IsPointSphere(pSkinnedTrans, 3.f, colliTest);
	
	m_inven->update(timeDelta,pMainCamera);
	ITEM_MGR->update(timeDelta);
}

void move_Test::Scene_Render1()
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
	GIZMO_MGR->Line(this->frontRay.origin, this->frontRay.origin + this->frontRay.direction * 100, 0xffff0000);

	//
	pSkinnedBox->RenderGizmo(pSkinnedTrans);

	//GIZMO_MGR->WireSphere(pSkinnedTrans->GetWorldPosition()
	//	, pSkinnedBox->radius, 0xffff0000);
	//
	testBox->RenderGizmo(colliTest);
	//GIZMO_MGR->WireSphere(colliTest->GetWorldPosition()
	//	, testBox->radius, 0xff0000ff);
	QuadRender();
	//if(PHYSICS_MGR->IsOverlap(pSkinnedTrans, pSkinnedBox, colliTest, testBox))
	//{
	//	LOG_MGR->AddLog("충돌1");
	//}
	ITEM_MGR->render();
}


void move_Test::Scene_RenderSprite()
{
	m_inven->render();
	skill->uiRender();

}


void move_Test::QuadRender()
{
	//  원점 기준
	// 0----1
	//
	// 2----3
	//float x, z;
	//x = z = 10.f;
	//
	//quad[0] = D3DXVECTOR3(-x, 0, z);
	//quad[1] = D3DXVECTOR3(x, 0, z);
	//quad[2] = D3DXVECTOR3(-x, 0, -z);
	//quad[3] = D3DXVECTOR3(x, 0, -z);
	//
	//for (int i = 0; i < 4; i++)
	//{
	//	D3DXVec3TransformCoord(&quad[i], &quad[i], &pSkinnedTrans->GetWorldRotateMatrix() );
	//}
	//
	//quad[0] += D3DXVECTOR3( m_mousePos.x, 0 + m_mousePos.y + 0.5f,  m_mousePos.z);
	//quad[1] += D3DXVECTOR3(m_mousePos.x, 0 + m_mousePos.y + 0.5f,  m_mousePos.z);
	//quad[2] += D3DXVECTOR3( m_mousePos.x, 0 + m_mousePos.y + 0.5f,  m_mousePos.z);
	//quad[3] += D3DXVECTOR3( m_mousePos.x, 0 + m_mousePos.y + 0.5f,  m_mousePos.z);

	MyUtil::createQuad(quad, 5, 5, pSkinnedTrans, &m_mousePos);
	//createQuad(quad, 5, 5, pSkinnedTrans, &m_mousePos);
	PHYSICS_MGR->IsPointQuad(quad, &cRay);


	//0    1
	//
	//2    3

	//GIZMO_MGR->Quad(*quad);

	//
	//GIZMO_MGR->Line(quad[0], quad[1], 0xff00ff00);
	//GIZMO_MGR->Line(quad[1], quad[3], 0xff00ff00);
	//GIZMO_MGR->Line(quad[3], quad[0], 0xff00ff00);
	//
	//GIZMO_MGR->Line(quad[0], quad[3], 0xffff0000);
	//GIZMO_MGR->Line(quad[3], quad[2], 0xffff0000);
	//GIZMO_MGR->Line(quad[2], quad[0], 0xffff0000);



}

void move_Test::createQuad(D3DXVECTOR3* quad, float row, float col, cTransform* myTrans, D3DXVECTOR3* createPos)
{
	//  원점 기준
	// 0----1
	//
	// 2----3

	quad[0] = D3DXVECTOR3(-row, 0, col);
	quad[1] = D3DXVECTOR3(row, 0, col);
	quad[2] = D3DXVECTOR3(-row, 0, -col);
	quad[3] = D3DXVECTOR3(row, 0, -col);

	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i], &quad[i], &myTrans->GetWorldRotateMatrix());
	}

	quad[0] += D3DXVECTOR3(createPos->x, 0 + createPos->y + 0.5f, createPos->z);
	quad[1] += D3DXVECTOR3(createPos->x, 0 + createPos->y + 0.5f, createPos->z);
	quad[2] += D3DXVECTOR3(createPos->x, 0 + createPos->y + 0.5f, createPos->z);
	quad[3] += D3DXVECTOR3(createPos->x, 0 + createPos->y + 0.5f, createPos->z);

	GIZMO_MGR->Line(quad[0], quad[1], 0xff00ff00);
	GIZMO_MGR->Line(quad[1], quad[3], 0xff00ff00);
	GIZMO_MGR->Line(quad[3], quad[0], 0xff00ff00);

	GIZMO_MGR->Line(quad[0], quad[3], 0xffff0000);
	GIZMO_MGR->Line(quad[3], quad[2], 0xffff0000);
	GIZMO_MGR->Line(quad[2], quad[0], 0xffff0000);

}
