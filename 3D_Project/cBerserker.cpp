#include "stdafx.h"
#include "cPlayer.h"
#include "cBerserker.h"
#include "cMonsterManager.h"
#include "cMonster.h"
#include "cCamera.h"
#include "cInven.h"
#include "cTrailRender.h"
#include "cShowDamage.h"

cBerserker::cBerserker()
{
}

cBerserker::~cBerserker()
{
	SAFE_DELETE(m_ShowDamage);
	SAFE_DELETE(m_Swing);
	SAFE_DELETE(m_Burserk);
	SAFE_DELETE(m_ArmorCrash);
}

void cBerserker::BaseObjectEnable()
{
	m_fHP = 3000;					//최대체력
	m_currentHp = 3000;				//hp
	m_fSP = 1000;					//최대스킬포인트
	m_currentSp = 1000;				//sp

	m_attackLength = 5;				//공격범위
	m_damage = 100;					//기본 데미지
	m_isAttack = false;				//공격중
	m_invenOn = false;				//인벤
	m_isBurserk = false;			//버서크 모드
	m_isAutoWalk = false;

	m_UIContainer = new cUI_Container;
	m_UIContainer->UI_Init(m_fHP, m_fSP, BERSERKER);

	SetBassClass();
	
	//캐릭터의 그려진 위치를 세팅
	//pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
	BaseObjectBoundBox();

	BasicWeaponSet();

	m_state = IDLE;
	m_strName = MyUtil::SetAnimation(m_state);

	m_botton = false;

	m_vMonster = m_pMonMgr->GetMonsters();	//받아온 몬스터정보들
	m_target = NULL;						//타겟팅된 몬스터
	
	m_pMove->init(pTransform, pTerrain, m_camera, NULL);

	m_camera->AttachTo(pTransform);			//카메라붙임
	m_camera->SetLocalPosition(0, 4, -10);

	m_atkCnt = 1;			//평타 진행도
	m_time = 0;				//평타 글쿨
	m_testtime = 0;			//테스트용 로그찎는시간
	m_TextTime = 0;

	//skill
	SkillInit();
	SetTickCount();

	m_ShowDamage = new cShowDamage;
}

void cBerserker::BaseObjectUpdate(float timeDelta)
{
	m_ShowDamage->Update(timeDelta);
	CamControl(timeDelta);
	Move(timeDelta);
	
	//틱업데이트
	for (int i = 0; i < BK_TICKMAX; i++)
	{
		m_tick[i]->tickUpdate(TIME_MGR->GetFrameDeltaSec());
	}

	if (m_invenOn || m_ArmorCrash->GetIsSelecting())
	{
	}
	else	Monster_pick();

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
	m_TextTime += timeDelta;
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

	//스킬2 - 차지
	if (!m_ArmorCrash->GetIsCool() && !m_isAttack && KEY_MGR->IsOnceDown('2'))
	{
		SOUND_MGR->play("bk_charge_voice", 0.8);

		m_currentSp -= 100;
		m_time = 0;
		RangeCheck(10);
		
		m_state = SK_CHARGE;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->Play(m_strName, 0.3);
		m_state = IDLE;
		m_ArmorCrash->SelectSkill();
		m_ArmorCrash->Effect_Init();
	}
	else if (m_ArmorCrash->GetIsCool() && KEY_MGR->IsOnceDown('2'))
	{
		SOUND_MGR->play("ban", 0.5);
		if (!m_textOn)
		{
			m_TextTime = 0;
			m_textOn = true;
		}
	}

	if (m_ArmorCrash->GetAtkCount() == 1)
	{
		SOUND_MGR->stop("bk_charge_voice");
		SOUND_MGR->play("bk_atk3_voice", 0.8);
		SOUND_MGR->play("charge_boom", 0.8);
		m_state = SK_CHARGE_ATK;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
	}


	//스킬3 - 스윙
	if (!m_Swing->GetIsCool() && !m_isAttack && KEY_MGR->IsOnceDown('3'))
	{
		SOUND_MGR->play("bk_swing_voice", 0.8);
		m_currentSp -= 80;
		m_time = 0;
		m_state = SK_SWING;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
		m_state = IDLE;
		m_Swing->Effect_Init();
		m_Swing->StartCasting();
	}
	else if (m_Swing->GetIsCool() && KEY_MGR->IsOnceDown('3'))
	{
		SOUND_MGR->play("ban", 0.5);
		if (!m_textOn)
		{
			m_TextTime = 0;
			m_textOn = true;
		}
	}

	//스킬5 - 버서크
	if (!m_Burserk->GetIsCool() && !m_isAttack && KEY_MGR->IsOnceDown('5'))
	{
		SOUND_MGR->play("bk_burserk_voice", 0.8);

		m_currentSp -= 50;
		m_time = 0;
		LOG_MGR->AddLog("광폭화 시전");
	
		m_state = SK_BUFF;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
		m_state = IDLE;
		m_Burserk->Effect_Init();
		m_Burserk->StartCasting();
	}
	else if (m_Burserk->GetIsCool() && KEY_MGR->IsOnceDown('5'))
	{
		SOUND_MGR->play("ban", 0.5);
		if (!m_textOn)
		{
			m_TextTime = 0;
			m_textOn = true;
		}
	}

	SKILL01();			//차징
	SKILL02();			//스윙
	SKILL03();			//
	SKILL04();			//버프
	
	m_Swing->BaseObjectUpdate(timeDelta, this->pTransform->GetWorldPosition());
	m_Swing->Effect_Update(timeDelta);
	m_Burserk->BaseObjectUpdate(timeDelta, this->pTransform->GetWorldPosition());
	m_Burserk->Effect_Update(timeDelta);

	Ray ray;
	POINT ptMousePos = GetMousePos();
	D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
	m_camera->ComputeRay(&ray, &screenPos);
	D3DXVECTOR3		mousePos;
	pTerrain->IsIntersectRay(&mousePos, &ray);

	m_ArmorCrash->BaseObjectUpdate(timeDelta, this->pTransform->GetWorldPosition(), mousePos);
	m_ArmorCrash->Effect_Update(timeDelta);

	//텍스트사라줘
	if (m_textOn && m_TextTime > 1)
		m_textOn = false;

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
		m_testtime = 0;
	}

	m_camera->ShakeUpdate(timeDelta);
	m_UIContainer->UI_Update(m_currentHp, m_currentSp, this->pTransform->GetWorldPosition());

	if (m_target)
	{
		if (!m_target->IsActive())
			m_target = NULL;
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
	m_Burserk->Effect_Render();
	m_ArmorCrash->BaseObjectRender();
	m_ArmorCrash->Effect_Render();
}

void cBerserker::BaseSpriteRender()
{
	UiURender();
	m_ShowDamage->Render();//바운드박스 xy받아와
	m_UIContainer->UI_Render();
}

void cBerserker::BaseFontRender()
{
	m_UIContainer->UI_fontRender();

	if (m_textOn)
	{
		DXFONT_MGR->PrintTextOutline("스킬 쿨타임 입니다", WINSIZE_X/2 - 80, WINSIZE_Y/2 - 200, 0xffffffff, 0xff000000);
	}
}

void cBerserker::BaseObjectBoundBox()
{
	BoundBox.SetBound(&D3DXVECTOR3(0, 1.5f, 0), &D3DXVECTOR3(0.5f, 1.5f, 0.5f));
}

void cBerserker::Damage(float damage)
{
	m_currentHp -= damage;

	if (m_currentHp <= FEPSILON)
	{
		SOUND_MGR->play("bk_dead", 0.8);
		m_currentHp = 0.0f;
		m_state = DEAD;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterHold(m_strName);
		return;
	}

	if (m_state == DMG || m_state == DEAD 
		|| m_ArmorCrash->GetIsSelecting()
		|| m_ArmorCrash->GetIsAttacking()
		|| m_Swing->GetIsAttacking())
	{
		return;
	}

	if (m_state != DMG)
	{
		SOUND_MGR->play("bk_heat", 0.8);
		m_state = DMG;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "IDLE", 0.3f);
	}
}



void cBerserker::Attack01()
{	
	SOUND_MGR->play("bk_atk1_voice", 0.8);
	SOUND_MGR->play("bk_atk1", 0.8);

	int damage = (m_damage + m_Weapon->getDmg()) * 1;
	damage = RandomIntRange(damage - 10, damage + 10);

	m_ShowDamage->SetNumber(damage, m_target->pTransform, m_camera);

	LOG_MGR->AddLog("%d데미지 줌", damage);
	m_target->Damage(damage);
}

void cBerserker::Attack02()
{
	SOUND_MGR->play("bk_atk2_voice", 0.8);
	SOUND_MGR->play("bk_atk2", 0.8);

	int damage = (m_damage + m_Weapon->getDmg()) * 2;
	damage = RandomIntRange(damage - 10, damage + 10);

	m_ShowDamage->SetNumber(damage, m_target->pTransform, m_camera);

	LOG_MGR->AddLog("%d데미지 줌", damage);
	m_target->Damage(damage);
}

void cBerserker::Attack03()
{
	SOUND_MGR->play("bk_atk3_voice", 0.8);
	SOUND_MGR->play("bk_atk3", 0.8);

	int damage = (m_damage + m_Weapon->getDmg()) * 3;
	damage = RandomIntRange(damage - 10, damage + 10);
	
	m_ShowDamage->SetNumber(damage, m_target->pTransform, m_camera);

	LOG_MGR->AddLog("%d데미지 줌", damage);
	m_target->Damage(damage);
}


void  cBerserker::SkillInit()
{
	m_Swing = new cSkill_Swing;
	m_Swing->SetActive(true);
	m_Swing->BaseObjectEnable(pTransform->GetWorldPosition(), 10.f, 1, 200, 150);	//즉시시전은 캐스터 카운트 1
	
	m_Burserk = new cSkill_Burserk;
	m_Burserk->SetActive(true);
	m_Burserk->BaseObjectEnable(pTransform->GetWorldPosition(), 70, 600, 500);

	m_ArmorCrash = new cSkill_AmorCrash;
	m_ArmorCrash->SetActive(true);
	m_ArmorCrash->BaseObjectEnable(pTransform->GetWorldPosition(), 2, 10, 1, 100, 1000);

	m_aniCount = 0;
}


void cBerserker::SKILL01()
{
	int damage = (m_damage + m_Weapon->getDmg()) * 5;

	if (m_ArmorCrash->GetIsAttacking())
	{
		m_isAttack = true;

		RangeCircleCheck(m_ArmorCrash->GetAttackPos(), 4);
		int size = m_vMonster.size();

		if (m_tick[BK_SWING]->tickStart())
		{
			for (int i = 0; i < size; i++)
			{
				if (m_vMonster[i]->GetInRange())
				{
					if (!m_vMonster[i]->IsActive()) continue;

					LOG_MGR->AddLog("m_vMonster[%d] = %d", m_vMonster[i]->GetInRange());
					damage = RandomIntRange(damage - 10, damage + 10);
					m_ShowDamage->SetNumber(damage, m_vMonster[i]->pTransform, m_camera);
					m_vMonster[i]->Damage(damage);
				}
				else if (!m_vMonster[i]->GetInRange()) continue;
			}
		}
	}
}

void cBerserker::SKILL02()
{
	int damage = (m_damage + m_Weapon->getDmg()) * 2;

	if (m_Swing->GetIsAttacking())
	{
		m_isAttack = true;

		RangeCheck(10);
		int size = m_vMonster.size();

		if (m_tick[BK_SWING]->tickStart())
		{
			for (int i = 0; i < size; i++)
			{
				if (m_vMonster[i]->GetInRange())
				{
					if (!m_vMonster[i]->IsActive()) continue;

					LOG_MGR->AddLog("m_vMonster[%d] = %d", i, m_vMonster[i]->GetInRange());
					damage = RandomIntRange(damage - 10, damage + 10);
					m_ShowDamage->SetNumber(damage, m_vMonster[i]->pTransform, m_camera);
					m_vMonster[i]->Damage(damage);
				}
				else if (!m_vMonster[i]->GetInRange()) continue;
			}
		}
	}
}

void cBerserker::SKILL03()
{
	
}

void cBerserker::SKILL04()
{
	if (m_Burserk->GetIsInBuff())
	{
		LOG_MGR->AddLog("버서크모드임");
		m_isBurserk = true;
		m_damage = 200;
	}
	else
	{
		m_isBurserk = false;
		m_damage = 100;
	}
}

void cBerserker::BasicWeaponSet()
{
	//베이직무기 셋팅해줄거
	m_Weapon = new cItem;

	//TrailRenderSet
	this->pTrailRender = new cTrailRender();
	this->pTrailRender->Init(
		1.0f,					//꼬리 라이브 타임 ( 이게 크면 환영큐 사이즈가 커지고 꼬리가 오랬동안 남아있다 )
		1.0f,					//폭
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/TrailTest.png"),	//메인 Texture
		D3DXCOLOR(0.5f, 0, 0, 0.8),												//메인 Texture 로 그릴때 컬러
		NULL
	);

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

	m_tick[BK_CHARGE]->init(1.f);
	m_tick[BK_SWING]->init(0.8f);
	m_tick[BK_ACCEL]->init(0.3f); //넌아직모르겟엄
}

void cBerserker::UiUpdate(float timeDelta, cCamera* camera)
{
	if (m_inven->GetWeapon() == NULL &&m_botton == true)
	{
		SOUND_MGR->play("offWeapon", 0.8);
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
		this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 0 * ONE_RAD, 90 * ONE_RAD);
		
		m_botton = false;
	}
	else if (m_inven->GetWeapon() != NULL&& m_botton == false)
	{
		SOUND_MGR->play("setWeapon", 0.8);
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
