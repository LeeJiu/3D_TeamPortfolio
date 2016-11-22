#include "stdafx.h"
#include "cPlayer.h"
#include "cMage.h"
#include "cMonsterManager.h"
#include "cMonster.h"
#include "cCamera.h"
#include "cInven.h"

//파티클
#include "cPartcleEmitter.h"
#include "cParticleQuad.h""
#include "cParticle.h"
#include "cQuadParticleEmitter.h"

//스킬

cMage::cMage()
{

}


cMage::~cMage()
{
	SAFE_DELETE(m_ATKBox);
	SAFE_DELETE(m_Weapon);
}



void cMage::BaseObjectEnable()
{

	//몬스터 관련
	MonsterInit();

	SetBassClass();

	m_pMonsterMgr = new cMonsterManager;
	

	//무기 관련

	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Static* pSTF_Basic = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Weapon/STF_Master.X", &matCorrection);


	//m_Weapon = new cWeapon;
	//m_Weapon->SetMesh(pSTF_Basic);
	//m_Weapon->SetActive(true);

	//pSkinned->AddBoneTransform("Bip01-R-Hand", m_Weapon->pTransform);


	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);


	m_isPetOn = false;

	//스킬 관련
	SkillInit();



	//평타 박스
	m_ATKBox = new cBaseObject;
	m_ATKBox->BoundBox.Init(D3DXVECTOR3(-0.3f, -0.3f, -0.3f), D3DXVECTOR3(0.3f, 0.3f, 0.3f));


	m_ATKBox->BoundBox.SetBound(&m_ATKBox->pTransform->GetWorldPosition(), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
	pSkinned->AddBoneTransform("Bip01-L-Hand", m_ATKBox->pTransform);


	//캐릭터의 그려진 위치를 세팅
	//D3DXVECTOR3	minPos(-1, 0, -1);
	//D3DXVECTOR3	maxPos(1, 3, 1);
	//BoundBox.Init(minPos, maxPos);

	m_state = IDLE;
	m_strName = MyUtil::SetAnimation(m_state);

	m_fHP = 1000;
	m_attackLength = 5;
	m_damage = 100;
	m_isAttack = false;

	
	//SetMoveKeys();
	m_pMove->init(pTransform, pTerrain, m_camera, NULL);


}

void cMage::BaseObjectUpdate(float timeDelta)
{

	Move(timeDelta);
	Monster_pick();
	UiUpdate(timeDelta, m_camera);

	//펫에 타고 있냐
	//if (KEY_MGR->IsOnceDown('9'))
	//{
	//	if (m_isPetOn) m_isPetOn = false;
	//	else
	//	{
	//		m_state = PET_RUN;
	//		m_strName = SetAnimation(m_state);
	//		this->pSkinned->Play(m_strName, 0.3);
	//		m_isPetOn = true;
	//	}
	//}
	//
	//
	//if (m_isPetOn)
	//{
	//
	//}
	//else
	//{




	if (KEY_MGR->IsOnceDown('1'))
	{
		m_isAttack = true;
		m_state = ATK_01;
		MagicATKInit();
		m_magicATK->StartEmission();
		m_aniCount = 0;


		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
	}

	if (KEY_MGR->IsOnceDown('2'))
	{
		m_state = STF_FROZEN;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
		FlameRoadInit();
		m_flameRoad_cast = true;
		m_flameRoad_cast_count = 0;
		m_aniCount = 0;
	}

	if (KEY_MGR->IsOnceDown('3'))
	{
		m_state = STF_STORM;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
	}

	if (KEY_MGR->IsOnceDown('4'))
	{
		m_state = STF_TYFUNG;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
		m_pSkill_SnowStorm->Effect_Init();
		m_pSkill_SnowStorm->StartCasting();
	}


	if (KEY_MGR->IsOnceDown('5'))
	{
		m_state = STF_BUFF;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
		m_magicShild->StartEmission();
		m_isMagicShild = true;
		m_aniCount = 0;
	}

	if (KEY_MGR->IsOnceDown('7'))
	{
		m_pSurroundSkill->SelectSkill();


	}

	if (KEY_MGR->IsOnceDown('8'))
	{
		m_pSurroundSkill->StartCasting();
		LOG_MGR->AddLog("캐스팅중");
	}

	if (KEY_MGR->IsOnceDown('9'))
	{
		m_pSkill_DarkRain->Effect_Init();
		m_pSkill_DarkRain->SelectSkill();
	
	}


	Ray ray;
	POINT ptMousePos = GetMousePos();
	D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
	m_camera->ComputeRay(&ray, &screenPos);
	D3DXVECTOR3		mousePos;
	pTerrain->IsIntersectRay(&mousePos, &ray);
	//mousePos = PHYSICS_MGR->getLastHeight(enemy, &ray, m_pTerrain, &m_mousePos);


	m_pRoundSkill->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), mousePos);

	m_pSkill_SnowStorm->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition());
	m_pSkill_SnowStorm->Effect_Update(timeDelta);
	m_pSkill_DarkRain->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), mousePos);
	m_pSkill_DarkRain->Effect_Update(timeDelta);


	//스킬 사용 관련



	if (m_aniCount == 120)
	{
		m_magicATK->StopEmission();
		m_isAttack = false;
	}

	if (m_aniCount == 600)
	{
		m_magicShild->StopEmission();

	}


	if (m_flameRoad_cast)
	{
		m_flameRoad_cast_count++;
	}

	if (m_flameRoad_cast_count == 120)
	{
		m_flameRoad->StartEmission();
		m_flameRoad2->StartEmission();
		m_flameRoad3->StartEmission();
		m_isFlameRoad = true;
		m_aniCount = 0;
	}

	if (m_aniCount == 200)
	{
		m_flameRoad->StopEmission();
		m_flameRoad2->StopEmission();
		m_flameRoad3->StopEmission();
		m_flameRoad_cast_count = 0;
		m_isFlameRoad = false;
		m_flameRoad_cast = false;
	}



	if (m_isAttack)
	{
		m_aniCount++;
		m_magicATK->Update(timeDelta);
		m_magicATK->pTransform->SetWorldPosition(this->m_ATKBox->pTransform->GetWorldPosition());
	}



	if (m_isFlameRoad)
	{
		m_aniCount++;
		m_flameRoad->Update(timeDelta);
		m_flameRoad2->Update(timeDelta);
		m_flameRoad3->Update(timeDelta);
		m_flameRoad->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_flameRoad->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
		m_flameRoad2->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_flameRoad2->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
		m_flameRoad3->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_flameRoad3->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
	}





	if (m_isMagicShild)
	{
		m_aniCount++;
		m_magicShild->Update(timeDelta);
		m_magicShild->pTransform->SetWorldPosition(this->pTransform->GetWorldPosition());

	}



	MonsterUpdate(timeDelta);

	m_pSurroundSkill->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition());


}


void cMage::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);

	m_ATKBox->BoundBox.RenderGizmo(m_ATKBox->pTransform);

	//this->m_Weapon->Render();

	MonsterRender();

	SkillRender();

	m_pSurroundSkill->BaseObjectRender();
	m_pRoundSkill->BaseObjectRender();
	m_pSkill_SnowStorm->BaseObjectRender();
	m_pSkill_SnowStorm->Effect_Render();
	m_pSkill_DarkRain->BaseObjectRender();
	m_pSkill_DarkRain->Effect_Render();
	

}

void  cMage::SkillInit()
{

	m_pSkill_SnowStorm = new cSkill_SnowStorm;
	m_pSkill_SnowStorm->SetActive(true);
	m_pSkill_SnowStorm->BaseObjectEnable(pTransform->GetWorldPosition(), 5.0f, 1, 400, 300);

	m_pSurroundSkill = new cSkill_Surround;
	m_pSurroundSkill->BaseObjectEnable(pTransform->GetWorldPosition(), 6.0f, 100, 20, 20);

	m_pRoundSkill = new cSkill_Round;
	m_pRoundSkill->BaseObjectEnable(pTransform->GetWorldPosition(), 6.0f, 20, 20, 100, 30);

	m_pSkill_DarkRain = new cSkill_DarkRain;
	m_pSkill_DarkRain->SetActive(true);
	m_pSkill_DarkRain->BaseObjectEnable(pTransform->GetWorldPosition(), 6.0f, 20, 1, 400, 300);


	m_aniCount = 0;
	


	MagicShildInit();

	
	m_isAttack = false;
	m_isMagicShild = false;
	m_isFlameRoad = false;
	m_flameRoad_cast = false;
}


void  cMage::SkillRender()
{
	

	if (m_isAttack)
	{
		m_magicATK->Render();
	}

	if (m_isMagicShild)
	{
		m_magicShild->Render();
	}

	if (m_isFlameRoad)
	{
		m_flameRoad->Render();
		m_flameRoad2->Render();
		m_flameRoad3->Render();
	}

}


//평타
void cMage::MagicATKInit()
{

	m_magicATK = new cQuadParticleEmitter;
	m_magicATK->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.5f);  //초반 크기
	scales.push_back(2.5f);

	m_magicATK->Init(
		100,
		50.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 1, -1),
		D3DXVECTOR3(0, 1, -1),     //회전량
		D3DXVECTOR3(1, 1, 1),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(90 * ONE_RAD, 90 * ONE_RAD, 0),	//초기시작시 회전 min
		D3DXVECTOR3(180 * ONE_RAD, 180 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		1.0f, 2.5f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK.tga"),
		true);

	m_magicATK->StartEmission();




}


void cMage::FlameRoadInit()
{
	m_flameRoad = new cQuadParticleEmitter();
	m_flameRoad->SetActive(true);


	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.0f);  //초반 크기
	scales.push_back(6.0f);

	m_flameRoad->Init(
		101,
		50.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		3.0f,
		D3DXVECTOR3(0, 1, 10),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 1, 20),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(150 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(150 * ONE_RAD, 90 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		1.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/flame.tga"),
		true);


	m_flameRoad2 = new cQuadParticleEmitter();
	m_flameRoad2->SetActive(true);


	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(1.0f);  //초반 크기
	scales2.push_back(4.0f);

	m_flameRoad2->Init(
		102,
		50.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		3.0f,
		D3DXVECTOR3(0, 1, 10),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 1, 20),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(150 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(150 * ONE_RAD, 90 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors2, scales2,
		1.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/flame2.tga"),
		true);

	m_flameRoad3 = new cPartcleEmitter();
	m_flameRoad3->SetActive(true);

	//배열을 2 개이상 
	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales3;
	scales3.push_back(0.1f);
	scales3.push_back(0.1f);

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
		"../Resources/Textures/Effects/flame3.tga");

	//파티클 랜더러 셋팅
	m_flameRoad3->Init(
		50,				//최대 파티클 수
		5.0f,				//초당 파티클 발생 량
		7,					//하나의 파티클 입자 라이프 최소값
		10,					//하나의 파티클 입자 라이프 최대값
		D3DXVECTOR3(0, 5, 10),	//파티클 입자 속도 최소값 ( 로컬기준 )
		D3DXVECTOR3(0, 10, 20),	//파티클 입자 속도 최대값 ( 로컬기준 )
		D3DXVECTOR3(0, 0, 0),	//파티클 입자 가속 최소값 ( 로컬기준 )
		D3DXVECTOR3(0, 0, 0), //파티클 입자 가속 최대값 ( 로컬기준 )
		colors3,				//컬러 배열
		scales3,				//스케일 배열
		1.1f,				//입자크기 최소값
		5.2f,				//최대값
		pTex,				//텍스쳐
		false);


	m_flameRoad3->EmissionType = PATICLE_EMISSION_TYPE::SPHERE_OUTLINE;
	m_flameRoad3->SphereEmissionRange = 3.0f;

}





//매직 실드

void cMage::MagicShildInit()
{
	m_magicShild = new cQuadParticleEmitter();
	m_magicShild->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(5.0f);  //초반 크기
	scales.push_back(5.0f);

	m_magicShild->Init(
		10,
		30.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		5.0f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		2.0f, 2.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicShild.tga"),
		true);

}


//스노우 스톰 



void cMage::MonsterInit()
{
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Skinned* pMonster = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Minho/MOB_Minho.X", &matCorrection);

	//무기 관련
	m_pMonster = new cBaseObject;
	m_pMonster->SetMesh(pMonster);
	m_pMonster->SetActive(true);

	m_pMonster->BoundBox.Init(D3DXVECTOR3(-0.5, -0.5, -0.5), D3DXVECTOR3(0.5, 5.5, 0.5));
	m_pMonster->pTransform->SetWorldPosition(D3DXVECTOR3(0, 8, 0));


	m_isTarget = false;
	m_MobCollision = false;




}


void cMage::MonsterUpdate(float timeDelta)
{

	m_pMonster->pSkinned->Update(timeDelta);



	MonsterCollision(timeDelta);



}


void cMage::MonsterCollision(float timeDelta)
{

  //D3DXVECTOR3 magicATKLegth = pTransform->GetWorldPosition() - m_pMonster->pTransform->GetWorldPosition();
  //
  //if (KEY_MGR->IsOnceDown(VK_LBUTTON))
  //{
  //	Ray ray;
  //	POINT ptMousePos = GetMousePos();
  //	D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
  //	this->m_camera->ComputeRay(&ray, &screenPos);
  //
  //	if (PHYSICS_MGR->IsRayHitBound(&ray, &m_pMonMgr->GetMonsters().size, m_pMonster->pTransform, NULL, NULL))
  //	{
  //		m_isTarget = true;
  //		//m_pMonster->pSkinned->PlayOneShot("WAIT", 0.3f);
  //
  //	}
  //	else
  //	{
  //		m_isTarget = false;
  //		m_pMonster->pSkinned->Play("IDLE", 0.3f);
  //	}
  //
  //
  //	if (m_isTarget &&D3DXVec3Length(&magicATKLegth) > 20)
  //	{
  //		m_state = RUN;
  //		m_strName = MyUtil::SetAnimation(m_state);
  //		this->pSkinned->Play(m_strName, 0.3);
  //	}
  //
  //
  //}
  //
  //
  //
  //if (m_isTarget && D3DXVec3Length(&magicATKLegth) > 20)
  //{
  //	pTransform->LookPosition(m_pMonster->pTransform->GetWorldPosition(), 90.0f * ONE_RAD);
  //	pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 10.0f * timeDelta));
  //	m_StateCount = 0;
  //	//사거리 밖이면 이동해라
  //}
  //else
  //{
  //
  //	m_StateCount++;
  //	if (m_StateCount == 1)
  //	{
  //		m_state = WAIT;
  //		m_strName = MyUtil::SetAnimation(m_state);
  //		this->pSkinned->Play(m_strName, 0.3);
  //	}
  //
  //}
  //
  //
  //
  //
  //if (m_isTarget && D3DXVec3Length(&magicATKLegth) < 20);
  //{
  //
  //
  //	if (m_isAttack)
  //	{
  //		pSkinned->RemoveBoneTransform("Bip01-L-Hand");
  //		m_ATKBox->pTransform->LookPosition(m_pMonster->pTransform->GetWorldPosition() + D3DXVECTOR3(0, 2, 0));
  //		m_ATKBox->pTransform->MovePositionSelf(0, 0, 30.0f * timeDelta);
  //	}
  //	else
  //	{
  //		pSkinned->AddBoneTransform("Bip01-L-Hand", m_ATKBox->pTransform);
  //	}
  //
  //}
  //
  //if (PHYSICS_MGR->IsOverlap(m_ATKBox, m_pMonster))
  //{
  //
  //}
  //
  //
  


}


void cMage::MonsterRender()
{

	m_pMonster->Render();
	m_pMonster->BoundBox.RenderGizmo(m_pMonster->pTransform);

}



void  cMage::Damage(float damage)
{

}

void cMage::Attack01()
{

}
void cMage::Attack02()
{

}
void cMage::Attack03()
{

}

void cMage::SKILL01()
{

}
void cMage::SKILL02()
{

}
void cMage::SKILL03()
{

}
void cMage::SKILL04()
{

}