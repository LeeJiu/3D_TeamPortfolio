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

	m_camera->AttachTo(pTransform);
	m_camera->SetLocalPosition(0, 3, -5);

	//SetMoveKeys();
	m_pMove->init(pTransform, pTerrain, m_camera, NULL);


}

void cMage::BaseObjectUpdate(float timeDelta)
{
	CamControl(timeDelta);

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
	
		//캐스팅 120초
		//시전시간 200초
		m_pSkill_FlameRoad->Effect_Init();
		m_pSkill_FlameRoad->StartCasting();
	}


	if (KEY_MGR->IsOnceDown('3'))
	{
		m_state = STF_TYFUNG;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
		m_pSkill_SnowStorm->Effect_Init();
		m_pSkill_SnowStorm->StartCasting();
	}

	if (KEY_MGR->IsOnceDown('4'))
	{
		m_pSkill_DarkRain->Effect_Init();
		m_pSkill_DarkRain->SelectSkill();
	}

	if (m_pSkill_DarkRain->GetCastCount() == 1) //캐스팅 시작시에 모션을 바꿔주기 위해서
	{
		m_state = STF_BUMB;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
	}


	if (KEY_MGR->IsOnceDown('5'))
	{
		m_state = STF_BUFF;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
		m_pSkill_magicShild->Effect_Init();
		m_pSkill_magicShild->StartCasting();

	}

	if (KEY_MGR->IsOnceDown('7'))
	{
		m_state = STF_BLINK;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
		m_pSkill_Escape->StartCasting();
	}

	if (KEY_MGR->IsOnceDown('8'))
	{
		m_pSurroundSkill->StartCasting();
		LOG_MGR->AddLog("캐스팅중");
	}

	if (KEY_MGR->IsOnceDown('9'))
	{
		m_pSkill_Front->SelectSkill();

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

	m_pSkill_Front->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), pTransform->GetForward());

	m_pSurroundSkill->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition());

	m_pSkill_magicShild->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition());
	m_pSkill_magicShild->Effect_Update(timeDelta);

	m_pSkill_Escape->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), pTransform->GetForward(0));
	
	m_pSkill_FlameRoad->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), pTransform->GetForward());
	m_pSkill_FlameRoad->Effect_Update(timeDelta);


	if (m_pSkill_Escape->GetBuffCount() == 100)
	{
		pTransform->SetWorldPosition(D3DXVECTOR3(m_pSkill_Escape->GetEscapePos().x, pTransform->GetWorldPosition().y, m_pSkill_Escape->GetEscapePos().z));
	}

	if (m_pSkill_DarkRain->GetIsAttacking())
	{
		//m_camera->ShakePos(0.3f, 0.4f);
		//m_camera->SetShakePosFlag(SHAKE_);
		//m_camera->ShakeUpdate(timeDelta);
	}
	//스킬 사용 관련

	if (m_aniCount == 120)
	{
		m_magicATK->StopEmission();
		m_isAttack = false;
	}

	
	if (m_isAttack)
	{
		m_aniCount++;
		m_magicATK->Update(timeDelta);
		m_magicATK->pTransform->SetWorldPosition(this->m_ATKBox->pTransform->GetWorldPosition());
	}

	MonsterUpdate(timeDelta);

}


void cMage::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);

	m_ATKBox->BoundBox.RenderGizmo(m_ATKBox->pTransform);

	//this->m_Weapon->Render();

	MonsterRender();


	m_pSurroundSkill->BaseObjectRender();
	m_pRoundSkill->BaseObjectRender();
	m_pSkill_SnowStorm->BaseObjectRender();
	m_pSkill_SnowStorm->Effect_Render();
	m_pSkill_DarkRain->BaseObjectRender();
	m_pSkill_DarkRain->Effect_Render();
	m_pSkill_Front->BaseObjectRender();
	m_pSkill_magicShild->Effect_Render();
	m_pSkill_Escape->BaseObjectRender();
	m_pSkill_FlameRoad->BaseObjectRender();
	m_pSkill_FlameRoad->Effect_Render();

	if (m_isAttack)
	{
		m_magicATK->Render();
	}


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
	m_pSkill_DarkRain->BaseObjectEnable(pTransform->GetWorldPosition(), 6.0f, 40, 100, 200, 300);

	m_pSkill_Front = new cSkill_Front;
	m_pSkill_Front->SetActive(true);
	m_pSkill_Front->BaseObjectEnable(pTransform->GetWorldPosition(), 20.0f, 3.0f, 1, 400, 300);

	m_pSkill_magicShild = new cSkill_MagicShild;
	m_pSkill_magicShild->SetActive(true);
	m_pSkill_magicShild->BaseObjectEnable(pTransform->GetWorldPosition(), 1, 600, 300);

	m_pSkill_Escape = new cSkill_Escape;
	m_pSkill_Escape->SetActive(true);
	m_pSkill_Escape->BaseObjectEnable(pTransform->GetWorldPosition(), 25.0f, 1, 200, 100);


	m_pSkill_FlameRoad = new cSkill_FlameRoad;
	m_pSkill_FlameRoad->SetActive(true);
	m_pSkill_FlameRoad->BaseObjectEnable(pTransform->GetWorldPosition(), 20.0f, 3.0f, 130, 250, 100);

	m_aniCount = 0;
	

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