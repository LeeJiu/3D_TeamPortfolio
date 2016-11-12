#include "StdAfx.h"
#include "monster_Test.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"



monster_Test::monster_Test()
{
}


monster_Test::~monster_Test()
{
}

HRESULT monster_Test::Scene_Init()
{
	Terrain_Init();

	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	Player_Init();
	TestLand_Init();
	Monster_Init();
	Player_ATK_Init();

	Light_Push();


	for (int i = 0; i < 10; i++)
	{
		aniCount[i] = 0;
	}


	//=============== 레이 초기화 끝.
	pMainCamera->SetWorldPosition(2, 5, 2);

	
	return S_OK;
}


void monster_Test::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(this->pSkinnedTrans);
		this->pSkinned1->Release();
	SAFE_DELETE(this->pSkinned1);
}


void monster_Test::Scene_Update(float timeDelta)
{
	Player_Update(timeDelta);
	Monster_Update(timeDelta);



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


void monster_Test::Scene_Render1()
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
	Monster_Render();
	pATK->RenderGizmo(pATKTrans);


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


void monster_Test::Scene_RenderSprite()
{
}


void monster_Test::Light_Push()
{



	//라이트 푸쉬
	cLight_Direction* pLight1 = new cLight_Direction();
	pLight1->Color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->Intensity = 1.0f;
	pLight1->pTransform->SetRotateWorld(45 * ONE_RAD, 90 * ONE_RAD, 45 * ONE_RAD);

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


}

void monster_Test::Terrain_Init()
{
	m_pTerrain = new cTerrain;
	m_pTerrain->Init(
		"../Resources/Textures/MyHeight512.bmp",
		"../Resources/Textures/terrain1.png",
		"../Resources/Textures/terrain2.png",
		"../Resources/Textures/terrain3.png",
		"../Resources/Textures/terrain4.png",
		"../Resources/Textures/Splat.png",
		1.0f,
		100.0f,
		3,
		100);
}

void monster_Test::TestLand_Init()
{
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;


	//=================== 스태틱 렌드 그림.
	D3DXMatrixScaling(&matScale, 1, 1, 1);

	m_Land = new cBaseObject;
	m_Land->SetMesh(RESOURCE_STATICXMESH->GetResource(
		"../Resources/Meshes/TestMesh/boundMesh.X", &m_matCorrection));
	m_Land->SetActive(true);

	//m_Land->pTransform->SetWorldPosition(0, this->m_pTerrain->GetHeight(0, 0) - 18, 0);
	m_Land->pTransform->SetWorldPosition(0, 0, 0);
}

void monster_Test::Player_Init()
{

	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Elf/Elf_Master.X", &matCorrection);

	pPlayerSpeed = 0.3f;


	m_hitPos = D3DXVECTOR3(0, 0, 0);

	m_bMove = false;


	//위에서 로딩된 SkinnedMesh 인스턴스를 만든다.
	this->pSkinned1 = new cSkinnedAnimation();
	this->pSkinned1->Init(pSkinned);

	//캐릭터가 그려질 위치 트랜스폼
	this->pSkinnedTrans = new cTransform();
	pSkinnedTrans->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);


	isMove = false;

	isClick = false;


	//================레이 추가. 아래 방향 바뀌지 않음 .
	cRay.direction = D3DXVECTOR3(0, -1, 0);
	cRay.origin = pSkinnedTrans->GetWorldPosition();
}


void monster_Test::Player_Update(float timeDelta)
{

	// 레이 업데이트
	m_currentPos = pSkinnedTrans->GetWorldPosition(); // 현재 위치.
	//cRay.direction = D3DXVECTOR3(0, -1, 0);
	cRay.origin.y = pSkinnedTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정

	this->pSkinned1->Update(timeDelta);

	//this->pTransForCamera->SetWorldPosition(this->pSkinnedTrans->GetWorldPosition());


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
		D3DXVECTOR3 dir = m_mousePos - cRay.origin;	// 방향 및 mousePos의 원점 이동.	
		dir.y = 0;


		if (D3DXVec3Length(&dir) > 0.5f)
		{
			isMove = true;
			D3DXVec3Normalize(&dir, &dir);
			D3DXVECTOR3 lerp = pSkinnedTrans->GetForward();
			D3DXVec3Lerp(&lerp, &lerp, &dir, 0.2);
			pSkinnedTrans->LookDirection(lerp, D3DXVECTOR3(0, 1, 0));

			cRay.origin += dir*pPlayerSpeed;
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


	Player_ATK_Update(timeDelta);

	pSkinned1->Play(current_Ani, 0.3f);

}


void monster_Test::Monster_Init()
{
	for (int i = 0; i < 10; i++)
	{


		this->pMonster[i] = new cSkinnedAnimation();
		this->pMonsterTrans[i] = new cTransform();

		m_mob_Speed[i] = 0.2f;


	}

	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;


	cXMesh_Skinned* pGriff = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Griff/MOB_HipGriff.X", &matCorrection);
	cXMesh_Skinned* pElephant = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Elephant/pet_Elephant.X", &matCorrection);
	cXMesh_Skinned* pBashil = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Bashil/MOB_Bashil.X", &matCorrection);
	cXMesh_Skinned* pSpiderQ = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_SpiderQueen.X", &matCorrection);
	cXMesh_Skinned* pSpider = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_Spider.X", &matCorrection);
	cXMesh_Skinned* pMinho = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Minho/MOB_Minho.X", &matCorrection);
	cXMesh_Skinned* pGriffBaby = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Griff/MOB_GriffBaby.X", &matCorrection);


	this->pMonster[0]->Init(pGriff);
	this->pMonster[1]->Init(pElephant);
	this->pMonster[2]->Init(pBashil);
	this->pMonster[3]->Init(pSpiderQ);
	this->pMonster[4]->Init(pSpider);
	this->pMonster[5]->Init(pMinho);
	this->pMonster[6]->Init(pGriffBaby);
	this->pMonster[7]->Init(pGriff);
	this->pMonster[8]->Init(pGriff);
	this->pMonster[9]->Init(pGriff);



	pMonsterTrans[0]->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);
	pMonsterTrans[1]->SetWorldPosition(5, m_pTerrain->GetHeight(0, 0), 0);
	pMonsterTrans[2]->SetWorldPosition(10, m_pTerrain->GetHeight(0, 0), 0);
	pMonsterTrans[3]->SetWorldPosition(15, m_pTerrain->GetHeight(0, 0), 0);
	pMonsterTrans[4]->SetWorldPosition(20, m_pTerrain->GetHeight(0, 0), 0);
	pMonsterTrans[5]->SetWorldPosition(25, m_pTerrain->GetHeight(0, 0), 0);
	pMonsterTrans[6]->SetWorldPosition(30, m_pTerrain->GetHeight(0, 0), 0);
	pMonsterTrans[7]->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);
	pMonsterTrans[8]->SetWorldPosition(0, m_pTerrain->GetHeight(0, 0), 0);
	pMonsterTrans[9]->SetWorldPosition(30, m_pTerrain->GetHeight(0, 0), 20);

	for (int i = 0; i < 10; i++)
	{
		//================레이 추가. 아래 방향 바뀌지 않음 .
		cMobRay[i].direction = D3DXVECTOR3(0, -1, 0);
		cMobRay[i].origin = pMonsterTrans[i]->GetWorldPosition();

		m_mob_firstPos[0] = pMonsterTrans[0]->GetWorldPosition();
		m_mob_firstPos[1] = pMonsterTrans[1]->GetWorldPosition();
		m_mob_firstPos[2] = pMonsterTrans[2]->GetWorldPosition();
		m_mob_firstPos[3] = pMonsterTrans[3]->GetWorldPosition();
		m_mob_firstPos[4] = pMonsterTrans[4]->GetWorldPosition();
		m_mob_firstPos[5] = pMonsterTrans[5]->GetWorldPosition();
		m_mob_firstPos[6] = pMonsterTrans[6]->GetWorldPosition();
		m_mob_firstPos[7] = pMonsterTrans[7]->GetWorldPosition();
		m_mob_firstPos[8] = pMonsterTrans[8]->GetWorldPosition();
		m_mob_firstPos[9] = pMonsterTrans[9]->GetWorldPosition();

	}


}

void monster_Test::Monster_Update(float timeDelta)
{

	for (int i = 0; i < 10; i++)
	{



		m_mob_currentPos[i] = pMonsterTrans[i]->GetWorldPosition();
		D3DXVECTOR3 searchLenght = pMonsterTrans[i]->GetWorldPosition() - pSkinnedTrans->GetWorldPosition();

		if (D3DXVec3Length(&searchLenght) < 10.0f)
		{
			aniCount[i] = 0;
			D3DXVECTOR3 mobDir = pSkinnedTrans->GetWorldPosition() - cMobRay[i].origin;
			mobDir.y = 0;


			if (D3DXVec3Length(&mobDir) > 0.5f)
			{

				isMobMove[i] = true;
				D3DXVec3Normalize(&mobDir, &mobDir);
				D3DXVECTOR3 mobLerp = pMonsterTrans[i]->GetForward();
				D3DXVec3Lerp(&mobLerp, &mobLerp, &mobDir, 0.2);
				pMonsterTrans[i]->LookDirection(mobLerp, D3DXVECTOR3(0, 1, 0));

				cMobRay[i].origin += mobDir*m_mob_Speed[i];
			}
			else
			{
				isMobMove[i] = false;
				aniCount[i] = 1;
			}


		}
		else
		{
			D3DXVECTOR3 mobReturnDir = m_mob_firstPos[i] - cMobRay[i].origin;
			mobReturnDir.y = 0;

			if (D3DXVec3Length(&mobReturnDir) > 0.5f)
			{
				aniCount[i] = 1;
				isMobMove[i] = true;
				D3DXVec3Normalize(&mobReturnDir, &mobReturnDir);
				D3DXVECTOR3 mobLerp = pMonsterTrans[i]->GetForward();
				D3DXVec3Lerp(&mobLerp, &mobLerp, &mobReturnDir, 0.2);
				pMonsterTrans[i]->LookDirection(mobLerp, D3DXVECTOR3(0, 1, 0));

				cMobRay[i].origin += mobReturnDir*m_mob_Speed[i];

			}
			else
			{
				isMobMove[i] = false;
				aniCount[i] = 1;
			}

		}

		// 터레인과 충돌 했다면. 
		if (this->m_pTerrain->IsIntersectRay(&m_mob_prePos[i], &cMobRay[i]) == true)
		{
			if (m_mob_lastPos[i].y > m_mob_prePos[i].y)
			{
				m_mob_prePos[i] = m_mob_lastPos[i];
			}
		}


		this->pMonsterTrans[i]->SetWorldPosition(m_mob_prePos[i]);
		m_mob_currentPos[i] = m_mob_prePos[i];

		if (fabs(m_mob_prePos[i].y - m_mob_currentPos[i].y) < 0.5f && isMobMove[i] == true) // 숫자는 넘어갈 수 있는 높이. ( 아래에서 위로 갈떄. )
		{
			this->pMonsterTrans[i]->SetWorldPosition(m_mob_prePos[i]);
			m_mob_currentPos[i] = m_mob_prePos[i]; // 좌표 갱신

		}

			// 레이랑 케릭터 거리가 멀어지면 레이가 더이상 넘어가지 못하게 만든다.
			float mob_rayCheckDis = D3DXVec3Length(&(cMobRay[i].origin - pMonsterTrans[i]->GetWorldPosition()));
			if (mob_rayCheckDis > 0.25f) // 상수 값은 속력 보다 조금 높은 값.
			{
				cMobRay[i].origin = pMonsterTrans[i]->GetWorldPosition();
				cMobRay[i].origin.y = pMonsterTrans[i]->GetWorldPosition().y + 5; // 머리위에 붙일예정

			}



			pMonster[i]->Update(timeDelta);


			switch (aniCount[i])
			{
			case 0: pMonster[i]->Play("IDLE", 0.3);
				break;
			case 1: pMonster[i]->Play("RUN", 0.3);
				break;
			case 2: pMonster[i]->Play("ATK_01", 0.3);
				break;
			case 3: pMonster[i]->Play("DMG", 0.3);
				break;
			default: pMonster[i]->Play("IDLE", 0.3);
				break;
			}

		}
	}



void monster_Test::Monster_Render()
{
	for (int i = 0; i < 10; i++)
	{

		this->pMonster[i]->Render(pMonsterTrans[i]);

	}

}

void monster_Test::Player_ATK_Init()
{
	pATK = new cBoundBox();
	D3DXVECTOR3 maxPos(0.5f, 0.5f, 0.5f);
	D3DXVECTOR3 minPos(-0.5f, -0.5f, -0.5f);
	pATK->localMaxPos = maxPos;
	pATK->localMinPos = minPos;
	pATKTrans = new cTransform();
	pATKTrans->AttachTo(pSkinnedTrans);
	pATKTrans->SetLocalPosition(D3DXVECTOR3(0, 2.5f, 0));




	isATK = false;
}

void monster_Test::Player_ATK_Update(float timeDelta)
{
	for (int i = 0; i < 10; i++)
	{
		D3DXVECTOR3 atkLength = m_mousePos - pMonsterTrans[i]->GetWorldPosition();

		//if (D3DXVec3Length(&atkLength) < 0.5f)
		//{
		//	isTarget = true;
		//	LOG_MGR->AddLog("타겟팅중");
		//}

	}

	if (KEY_MGR->IsOnceDown(VK_SPACE))
	{
		isATK = true;
		pSkinned1->Play("STF_ATK1", 0.3);
	}

	if (isATK)
	{
	
		pATKTrans->MovePositionSelf(D3DXVECTOR3(0, 0, 0.3f * 1.0f));

		
	}
	
	D3DXVECTOR3 atkLength1 = pSkinnedTrans->GetWorldPosition() - pATKTrans->GetWorldPosition();
	if (D3DXVec3Length(&atkLength1) > 20.0f)
	{
		
		pATKTrans->SetLocalPosition(D3DXVECTOR3(0, 2.5f, 0));
		isATK = false;
	}

	for (int i = 0; i < 10; i++)
	{
		D3DXVECTOR3 hitLength = pMonsterTrans[i]->GetWorldPosition() - pATKTrans->GetWorldPosition();

		if (D3DXVec3Length(&hitLength) < 10.0f)
		{
			aniCount[i] = 3;

		}
	

	}


	isMove = true;

}
