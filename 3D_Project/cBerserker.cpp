#include "stdafx.h"
#include "cPlayer.h"
#include "cBerserker.h"
#include "cMonsterManager.h"
#include "cMonster.h"
#include "cCamera.h"
#include "cInven.h"
#include "cTrailRender.h"
#include "cShowDamage.h"

//#include "cViewDamage.h"

cBerserker::cBerserker()
{
}

cBerserker::~cBerserker()
{
	//SAFE_DELETE(m_ViewDamage);
	SAFE_DELETE(m_ShowDamage);
}

void cBerserker::BaseObjectEnable()
{
	m_UIContainer = new cUI_Container;
	m_UIContainer->UI_Init();


	SetBassClass();
	
	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
	BaseObjectBoundBox();

	BasixWeaponSet();

	m_state = IDLE;
	m_strName = MyUtil::SetAnimation(m_state);

	m_botton = false;

	m_fHP = 3000;					//신상정보
	m_currentHp = 3000;			//신상정보
	m_attackLength = 5;				//신상정보
	m_damage = 100;					//신상정보
	m_isAttack = false;				//신상정보
	m_invenOn = false;				//신상정보

	m_vMonster = m_pMonMgr->GetMonsters();	//받아온 몬스터정보들
	m_target = NULL;			//타겟팅된 몬스터
	
	m_pMove->init(pTransform, pTerrain, m_camera, NULL);

	m_camera->AttachTo(pTransform);			//카메라붙임
	m_camera->SetLocalPosition(0, 2, -5);

	m_atkCnt = 1;			//평타 진행도
	m_time = 0;				//평타 글쿨
	m_testtime = 0;			//테스트용 로그찎는시간
	m_Invintime = 0;		//무적시간체ㅔ크

	//skill
	SkillInit();
	SetTickCount();
	
	//m_ViewDamage = new cViewDamage;					//init
	//m_ViewDamage->Init();
	m_ShowDamage = new cShowDamage;
}

void cBerserker::BaseObjectUpdate(float timeDelta)
{
	m_UIContainer->UI_Update();

	//m_ViewDamage->Update(timeDelta, m_camera);
	m_ShowDamage->Update(timeDelta);
	CamControl(timeDelta);
	Move(timeDelta);

	//틱업데이트
	//for (int i = 0; i < TICKMAX; i++)
	//{
	//	m_tick[i]->tickUpdate(TIME_MGR->GetFrameDeltaSec());
	//}

	if (!m_invenOn)
	{
		Monster_pick();
	}
	UiUpdate(timeDelta, m_camera);
	if (this->pTrailRender != NULL)
		this->pTrailRender->Update(timeDelta);

	/*
	//======================테스트용 애니 확인==================================
	if (KEY_MGR->IsOnceDown(VK_NUMPAD1))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_BUFF", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD2))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_ATKUP", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD3))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_CRASH", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD4))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_SWING", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD5))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_HOWL", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD6))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_ACCEL", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD7))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_JUMPATK", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD8))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_ESCAPE", 0.3, 0.15);
	
	//==============================================================
	*/
	
	m_time += timeDelta;
	m_Invintime += timeDelta;
	m_testtime += timeDelta;

	//
	//=================평타=================
	//
	
	if (LengthCheck() && !m_isAttack && KEY_MGR->IsOnceDown('1'))
	{
		m_isAttack = true;
		m_time = 0;
		switch (m_atkCnt)
		{
			case 1 : 
				m_state = ATK_01;
				Attack01();
				m_atkCnt++;
				break;
			case 2: 
				m_state = ATK_02;
				Attack02();
				m_atkCnt++;
				break;
			case 3: 
				pSkinned->ChangeBoneTransform("BN_Weapon_R", "BN_Weapon_L");// 막타를 칠때 BN_Weapon_L로
				m_state = ATK_03;
				Attack03();
				m_atkCnt = 1;
				break;
		}
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
	}

	//스킬2 - 하울링
	if (!m_isAttack && KEY_MGR->IsOnceDown('2'))
	{
		m_isAttack = true;
		m_time = 0;

		RangeCheck(10);

		m_state = SK_HOWL;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
		m_state = IDLE;
		m_Howling->Effect_Init();
		m_Howling->StartCasting();
	}

	//스킬3 - 스윙
	if (!m_isAttack && KEY_MGR->IsOnceDown('3'))
	{
		m_isAttack = true;
		m_time = 0;
	
		m_state = SK_SWING;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
		m_state = IDLE;
		m_Swing->Effect_Init();
		m_Swing->StartCasting();
	}

	//스킬4 - ?
	if (!m_isAttack && KEY_MGR->IsOnceDown('4'))
	{
		
	}

	//스킬5 - 버서크
	if (!m_isAttack && KEY_MGR->IsOnceDown('5'))
	{
		m_isAttack = true;
		m_time = 0;

		LOG_MGR->AddLog("광폭화 시전");
		m_damage += 100;

		m_state = SK_BUFF;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
		m_state = IDLE;
		m_Burserk->Effect_Init();
		m_Burserk->StartCasting();
	}

	SKILL01();			//하울링
	SKILL02();			//스윙
	SKILL03();			//
	SKILL04();			//버프

	
	m_Swing->BaseObjectUpdate(timeDelta, this->pTransform->GetWorldPosition());
	m_Swing->Effect_Update(timeDelta);

	

	//글쿨 막타만 1.5초
	if (m_time > 1)
	{
		if (m_atkCnt != 1)
		{
			m_isAttack = false;
			m_state = IDLE;
		}
		else if (m_atkCnt == 1)
		{
			if (m_time > 1.5)
			{
				m_isAttack = false;
				m_state = IDLE;
			}
		}
	}

	if (pSkinned->GetTime() > 0.7)
	{
		if (pSkinned->IsCurrentBone("BN_Weapon_L"))
			pSkinned->ChangeBoneTransform("BN_Weapon_L", "BN_Weapon_R");
	}

	//평타 초기화시간
	if (m_time > 5)
		m_atkCnt = 1;

	//test용 로그 출려꾸 
	if (m_testtime > 1)
	{
		LOG_MGR->AddLog("hp : %d", m_currentHp);
		m_testtime = 0;
	}

	m_camera->ShakeUpdate(timeDelta);

	if (m_isHeat && m_Invintime > 1)
	{
		m_state = IDLE;
	}
}

void cBerserker::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
	this->BoundBox.RenderGizmo(this->pTransform);

	m_Weapon->Render();
	if (this->pTrailRender != NULL)
	{
		this->pTrailRender->RenderDistort(this->m_camera);
	}

	m_Swing->BaseObjectRender();
	m_Swing->Effect_Render();
	//m_ViewDamage->Render();
}

void cBerserker::BaseSpriteRender()
{
	UiURender();
	m_ShowDamage->Render();
	m_UIContainer->UI_Render();

	//char temp[32];
	//sprintf_s(temp, "../Resources/Textures/num_%d.tga", 2);
	//
	//RECT rc = RectMake(WINSIZE_X / 2, WINSIZE_Y / 2, 32, 32);
	//
	//SPRITE_MGR->DrawTexture(
	//	RESOURCE_TEXTURE->GetResource(temp),
	//	&rc,
	//	rc.left,
	//	rc.top,
	//	0xffffffff,
	//	NULL
	//);
}

void cBerserker::BaseObjectBoundBox()
{
	BoundBox.SetBound(&D3DXVECTOR3(0, 1.5f, 0), &D3DXVECTOR3(0.5f, 1.5f, 0.5f));
}

void cBerserker::Damage(float damage)
{
	m_Invintime = 0;
	m_isHeat = true;

	m_currentHp -= damage;
	if (m_currentHp <= FEPSILON)
	{
		m_currentHp = 0.0f;
		m_state = DEAD;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterHold(m_strName);
		return;
	}

	if (m_state == DMG || m_state == DEAD)
	{
		return;
	}

	if (m_state != DMG)
	{
		
		m_state = DMG;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "IDLE", 0.3f);
	}
}



void cBerserker::Attack01()
{	
	int damage = m_damage * 1;
	damage = 2; 
	//damage = RandomIntRange(damage - 10, damage + 10);

	m_ShowDamage->SetNumber(damage, m_target->pTransform);
	//m_ViewDamage->SetNumber(damage, m_target->pTransform);//여기서 트랜스폼넘겨줘야지 .

	LOG_MGR->AddLog("%d데미지 줌", damage);
	m_target->Damage(damage);
}

void cBerserker::Attack02()
{
	int damage = m_damage * 2;
	damage = 5;
	//damage = RandomIntRange(damage - 10, damage + 10);

	m_ShowDamage->SetNumber(damage, m_target->pTransform);
	//m_ViewDamage->SetNumber(damage, m_target->pTransform);

	LOG_MGR->AddLog("%d데미지 줌", damage);
	m_target->Damage(damage);
}

void cBerserker::Attack03()
{
	int damage = m_damage * 3;
	damage = 8;
	//damage = RandomIntRange(damage - 10, damage + 10);
	
	m_ShowDamage->SetNumber(damage, m_target->pTransform);
	//m_ViewDamage->SetNumber(damage, m_target->pTransform);

	LOG_MGR->AddLog("%d데미지 줌", damage);
	m_target->Damage(damage);
}


void  cBerserker::SkillInit()
{
	m_Swing = new cSkill_Swing;
	m_Swing->SetActive(true);
	m_Swing->BaseObjectEnable(pTransform->GetWorldPosition(), 10.f, 1, 200, 50);	//즉시시전은 캐스터 카운트 1

	m_Howling = new cSkill_Howling;
	m_Howling->SetActive(true);
	m_Howling->BaseObjectEnable(pTransform->GetWorldPosition(), 10.f, 1, 5, 60);
	
	m_Burserk = new cSkill_Burserk;
	m_Burserk->SetActive(true);
	m_Burserk->BaseObjectEnable(pTransform->GetWorldPosition(), 1, 200, 20);

	m_aniCount = 0;
}


void cBerserker::SKILL01()
{
}

void cBerserker::SKILL02()
{
	int damage = m_damage * 2;

	if (m_Swing->GetIsAttacking())
	{
		RangeCheck(10);
		int size = m_vMonster.size();

		for (int i = 0; i < size; i++)
		{
			if (!m_vMonster[i]->GetInRange()) continue;
			damage = RandomIntRange(damage - 10, damage + 10);

			if (m_tick[BK_SWING]->tickStart())
			{
				//이거 틱데미지로바꿔
				//if (PHYSICS_MGR->IsOverlap(m_Weapon->pTransform, &m_inven->GetWeapon()->BoundBox, m_vMonster[i]->pTransform, &m_vMonster[i]->BoundBox))
				if (PHYSICS_MGR->IsOverlap(m_Weapon, m_vMonster[i]))
				{
					LOG_MGR->AddLog("%d 데미지줌", damage);
					//m_ShowDamage->SetNumber(damage, m_vMonster[i]->pTransform);
					//m_ViewDamage->SetNumber(damage, m_vMonster[i]->pTransform);
					m_vMonster[i]->Damage(damage);
				}
			}
		}
	}
}

void cBerserker::SKILL03()
{
	
}

void cBerserker::SKILL04()
{
	//if (m_Burserk->GetIsInBuff())
	//{
	//	if (m_Burserk->m_AttackingCount > m_Burserk->m_AttackingTime)
	//	{
	//		m_damage -= 100;
	//		LOG_MGR->AddLog("버프 끗");
	//	}
	//}
}

void cBerserker::BasixWeaponSet()
{
	//베이직무기 셋팅해줄거
	m_Weapon = new cItem;

	m_Weapon = ITEM_MGR->getItem(2);
	m_Weapon->BoundBox.SetBound(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
	pSkinned->AddBoneTransform("BN_Weapon_R", m_Weapon->pTransform);

	//트레일렌더그려줄거
	this->pTrailRender->Transform.AttachTo(m_Weapon->pTransform);
	this->pTrailRender->Transform.SetLocalPosition(0, 1, 0);
	this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 90 * ONE_RAD, 0);

}

void cBerserker::SetTickCount()
{
	for (int i = 0; i < TICKMAX; i++)
	{
		m_tick[i] = new cTickFunc;
		m_tick[i]->init(0.3f);
	}

	m_tick[BK_HOWL]->init(0.5f);
	m_tick[BK_SWING]->init(0.5f);
	m_tick[BK_ACCEL]->init(0.3f); //넌아직모르겟엄
}

void cBerserker::UiUpdate(float timeDelta, cCamera* camera)
{
	if (m_inven->GetWeapon() == NULL &&m_botton == true)
	{
		if (pTrailRender != NULL)
		{
			this->pTrailRender->Transform.ReleaseParent();
			pSkinned->RemoveBoneTransform("BN_Weapon_R");
		}

		pSkinned->RemoveBoneTransform("BN_Weapon_R");
		m_Weapon = ITEM_MGR->getItem(2);
		m_Weapon->BoundBox.SetBound(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
		pSkinned->AddBoneTransform("BN_Weapon_R", m_Weapon->pTransform);

		//트레일렌더그려줄거
		this->pTrailRender->Transform.AttachTo(m_Weapon->pTransform);
		this->pTrailRender->Transform.SetLocalPosition(0, 1, 0);
		this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 90 * ONE_RAD, 0);
		
		m_botton = false;
	}
	else if (m_inven->GetWeapon() != NULL&& m_botton == false)
	{
		if (pTrailRender != NULL)
		{
			this->pTrailRender->Transform.ReleaseParent();
			pSkinned->RemoveBoneTransform("BN_Weapon_R");
		}

		m_Weapon = m_inven->GetWeapon();
		m_Weapon->BoundBox.SetBound(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
		pSkinned->AddBoneTransform("BN_Weapon_R", m_Weapon->pTransform);
		m_botton = true;

		//트레일렌더그려줄거
		this->pTrailRender->Transform.AttachTo(m_Weapon->pTransform);
		this->pTrailRender->Transform.SetLocalPosition(0, 1, 0);
		this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 90 * ONE_RAD, 0);
		
		
		//this->pTrailRender->Transform.AttachTo(m_inven->GetWeapon()->pTransform);
		//this->pTrailRender->Transform.SetLocalPosition(0, 1, 0);
		//this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 90 * ONE_RAD, 0);
	}


	if (KEY_MGR->IsOnceDown('I'))
	{
		m_invenOn = !m_invenOn;
		m_inven->SetInvenOn(m_invenOn);
	}

	if (m_invenOn)
	{
		m_inven->update(timeDelta, m_camera, this->pTransform->GetWorldPosition());
		ITEM_MGR->update(timeDelta);
	}

}
