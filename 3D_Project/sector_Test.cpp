#include "stdafx.h"
#include "sector_Test.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"


sector_Test::sector_Test()
{
}


sector_Test::~sector_Test()
{
}
HRESULT sector_Test::Scene_Init()
{

	m_hitPos = D3DXVECTOR3(0, 0, 0);
	m_bMove = false;

	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMATRIXA16 matScale2;
	D3DXMatrixScaling(&matScale2, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;
	D3DXMATRIXA16 matCorrection2 = matScale2 * matRotate;

	cXMesh_Skinned* pSkinnedDragon = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Boss/SkulDragon/skulDragon_1.X", &matCorrection);
	cXMesh_Skinned*	pSkinnedSurcubus = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Surcubus/surcubus.X", &matCorrection2);

	//위에서 로딩된 SkinnedMesh 인스턴스를 만든다.
	this->pSkinned1 = new cSkinnedAnimation();
	this->pSkinned1->Init(pSkinnedDragon);

	this->pSkinned2 = new cSkinnedAnimation();
	this->pSkinned2->Init(pSkinnedSurcubus);

	this->pSkinnedTrans = new cTransform();
	pSkinnedTrans->SetWorldPosition(0, 0, 0);
	this->pSkinnedTrans2 = new cTransform();
	pSkinnedTrans2->SetWorldPosition(10, 0, 0);


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

	this->m_time = 0;

	this->m_sightLength = 5;
	this->m_sight = 50 * ONE_RAD;

	return S_OK;
}

void sector_Test::Scene_Release()
{
	SAFE_DELETE(this->pSkinnedTrans);
	SAFE_DELETE(this->pSkinnedTrans2);

	this->pSkinned1->Release();
	SAFE_DELETE(this->pSkinned1);
	this->pSkinned2->Release();
	SAFE_DELETE(this->pSkinned2);
}

void sector_Test::Scene_Update(float timeDelta)
{
	this->pSkinned1->Update(timeDelta);
	this->pSkinned2->Update(timeDelta);


	this->pSkinned1->Play("IDLE_C", 0.3f);
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		//Ray ray;
		//POINT ptMousePos = GetMousePos();
		//D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		//this->pMainCamera->ComputeRay(&ray, &screenPos);
		//
		//
		////Terrain 이랑 Ray체크
		//this->m_pTerrain->IsIntersectRay(&m_hitPos, &ray);
		//
		//m_bMove = true;
		////this->pSkinned1->Play("Walk", 0.3f);
	}

	if (KEY_MGR->IsStayDown('W'))
	{
		this->pSkinnedTrans2->MovePositionSelf(0, 0, timeDelta * 5);
	}

	if (KEY_MGR->IsStayDown('S'))
	{
		this->pSkinnedTrans2->MovePositionSelf(0, 0, -timeDelta * 5);
	}

	if (KEY_MGR->IsStayDown('A'))
	{
		this->pSkinnedTrans2->MovePositionSelf(-timeDelta * 5, 0, 0);
	}

	if (KEY_MGR->IsStayDown('D'))
	{
		this->pSkinnedTrans2->MovePositionSelf(timeDelta * 5, 0, 0);
	}
	

	if (KEY_MGR->IsStayDown(VK_LEFT))
	{
		this->pSkinnedTrans->RotateSelf(0,-timeDelta * 50 * ONE_RAD,  0);
	}

	if (KEY_MGR->IsStayDown(VK_RIGHT))
	{
		this->pSkinnedTrans->RotateSelf(0, timeDelta * 50 * ONE_RAD, 0);
	}
	if (KEY_MGR->IsStayDown(VK_UP))
	{
		this->pSkinnedTrans->MovePositionSelf(pSkinnedTrans->GetForward()*timeDelta);
	}

	if (KEY_MGR->IsStayDown(VK_DOWN))
	{
		this->pSkinnedTrans->MovePositionSelf(-pSkinnedTrans->GetForward()*timeDelta);
	}

	
	m_crush = PHYSICS_MGR->intersectSector(this->pSkinnedTrans, this->pSkinnedTrans2, m_sightLength, m_sight);
	
	this->m_time += timeDelta;
	if (m_time > 1.f)
	{
		if (m_crush)
			LOG_MGR->AddLog("충돌중");
		else
			LOG_MGR->AddLog("안충돌중");
		m_time = 0;
	}
}

void sector_Test::Scene_Render1()
{
	//적용되는 LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < this->lights.size(); i++)
		matLights[i] = this->lights[i]->GetLightMatrix();

	//셰이더에 라이팅 셋팅
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

	cXMesh_Skinned::SetCamera(this->pMainCamera);
	this->pSkinned1->Render(pSkinnedTrans);
	this->pSkinnedTrans->RenderGimozo();

	this->pSkinned2->Render(pSkinnedTrans2);
	this->pSkinnedTrans2->RenderGimozo();

	D3DXVECTOR3 axis(0, 1, 0);
	GIZMO_MGR->Circle(this->pSkinnedTrans->GetWorldPosition(), m_sightLength, axis, 0xff00ff00);
	GIZMO_MGR->Sector(this->pSkinnedTrans->GetWorldPosition(), this->pSkinnedTrans->GetForward(), m_sightLength, m_sight);
	
	//D3DXVECTOR3 startPos = this->pSkinnedTrans->GetWorldPosition();
	////============
	//D3DXVECTOR3 dir = pSkinnedTrans->GetForward();
	//float C_tAngle = D3DXVec3Dot(&dir, &D3DXVECTOR3(1,0,0));
	//C_tAngle = acos(C_tAngle);
	//if (dir.z < 0)
	//	C_tAngle = 360* ONE_RAD-C_tAngle;
	////============
	//
	//D3DXVECTOR3 finalPos(startPos.x + m_sightLength * cos(C_tAngle - m_sight), 0, startPos.z + m_sightLength * sin(C_tAngle - m_sight));
	//D3DXVECTOR3 finalPos2(startPos.x + m_sightLength * cos(C_tAngle + m_sight), 0, startPos.z + m_sightLength * sin(C_tAngle + m_sight));
	//
	//GIZMO_MGR->Line(startPos, finalPos, 0xff00ff00);
	//GIZMO_MGR->Line(startPos, finalPos2, 0xff00ff00);
	//Hit 위치에 구
	//GIZMO_MGR->WireSphere(this->m_hitPos, 0.5f, 0xffff0000);

	//셰이더에 라이팅 셋팅
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);
}

//bool sector_Test::intersectSector(const cTransform * Trans1, const cTransform * Trans2, float length, float sight)
//{
//	D3DXVECTOR3 v_distnace = Trans2->GetWorldPosition() - Trans1->GetWorldPosition();
//	float distance = D3DXVec3Length(&v_distnace);
//
//	if (std::fabs(distance) < length)
//	{
//		D3DXVECTOR3 dir = Trans1->GetForward();
//		D3DXVECTOR3 targetDir;
//		D3DXVec3Normalize(&targetDir, &v_distnace);
//
//		float C_tAngle = D3DXVec3Dot(&dir, &targetDir);
//		C_tAngle = acos(C_tAngle);
//
//		if (std::fabs(C_tAngle) <= sight)
//			return true;
//		else return false;
//	}
//	else return false;
//}



