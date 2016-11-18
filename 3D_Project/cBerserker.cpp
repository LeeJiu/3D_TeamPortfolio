#include "stdafx.h"
#include "cPlayer.h"
#include "cBerserker.h"
#include "cWeapon.h"
#include "cMonsterManager.h"
#include "cMonster.h"
#include "cCamera.h"

cBerserker::cBerserker()
{
}

cBerserker::~cBerserker()
{
	//SAFE_DELETE(m_pMove);
	SAFE_DELETE(m_Weapon);
}


void cBerserker::BaseObjectEnable()
{
	//무기 관련
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matCorrection = matScale;
	cXMesh_Static* pSTF_Basic = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Weapon/TAX_Basic.X", &matCorrection);
	
	m_Weapon = new cWeapon;
	m_Weapon->SetMesh(pSTF_Basic);
	m_Weapon->SetActive(true);

	m_Weapon->BoundBox.SetBound(&m_Weapon->pTransform->GetWorldPosition(), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
	pSkinned->AddBoneTransform("BN_Weapon_R", m_Weapon->pTransform);

	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);

	m_state = IDLE;
	m_strName = MyUtil::SetAnimation(m_state);

	m_fHP = 1000;
	m_attackLength = 5;
	m_damage = 100;
	m_isAttack = false;

	//sk3
	m_SwingCnt = 0;

	m_vMonster = m_pMonMgr->GetMonsters();
	m_target = NULL;
	
	SetMoveKeys();
	m_pMove->init(pTransform, pTerrain, m_camera, NULL);

	m_atkCnt = 1;
	m_time = 0;
	m_testtime = 0;
}

void cBerserker::BaseObjectUpdate(float timeDelta)
{
	Move(timeDelta);
	Monster_pick();

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

	
	m_time += timeDelta;
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

	//스킬3 - 스윙
	if (!m_isAttack && KEY_MGR->IsOnceDown('3'))
	{
		m_isAttack = true;
		m_time = 0;
		m_SwingCnt++;
		
		RangeCheck(10);

		//카운트 수 전달
		if (m_SwingCnt == 4)
		{
			m_SwingCnt = 0;
		}
		else
		{
			m_state = SK_SWING;
			SKILL03();
			m_strName = MyUtil::SetAnimation(m_state);
			this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
		}
	}

	//스킬5 - 광폭화
	if (!m_isAttack && KEY_MGR->IsOnceDown('5'))
	{
		m_isAttack = true;
		m_time = 0;
	
		m_state = SK_BUFF;
		SKILL04();
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
	}

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
		LOG_MGR->AddLog("%d", m_isMove);
		m_testtime = 0;
	}
}

void cBerserker::BaseObjectRender()
{
	if (m_Weapon)
	{
		m_Weapon->BoundBox.RenderGizmo(m_Weapon->pTransform);

		m_Weapon->Render();
		m_Weapon->pTransform->RenderGimozo();
	}

	this->pSkinned->Render(this->pTransform);
}

void cBerserker::Damage(float damage)
{
	m_fHP -= damage;
	if (m_fHP <= FEPSILON)
	{
		m_fHP = 0.0f;
		m_state = DEAD;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterHold(m_strName);
		return;
	}

	if (m_state != DMG)
	{
		m_state = DMG;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "IDLE", 0.3f);
		m_state = IDLE;
	}
}



void cBerserker::Attack01()
{	
	int damage = m_damage * 1;
	damage = RandomIntRange(damage - 10, damage + 10);
	
	LOG_MGR->AddLog("%d데미지 줌", damage);
	m_target->Damage(damage);
}

void cBerserker::Attack02()
{
	int damage = m_damage * 2;
	damage = RandomIntRange(damage - 10, damage + 10);
	
	LOG_MGR->AddLog("%d데미지 줌", damage);
	m_target->Damage(damage);
}

void cBerserker::Attack03()
{
	int damage = m_damage * 3;
	damage = RandomIntRange(damage - 10, damage + 10);
	
	LOG_MGR->AddLog("%d데미지 줌", damage);
	m_target->Damage(damage);
}

void cBerserker::SKILL01()
{
}

void cBerserker::SKILL02()
{
}

void cBerserker::SKILL03()
{
	int damage = m_damage * 2;
	damage = RandomIntRange(damage - 10, damage + 10);

	//LOG_MGR->AddLog("%d데미지 줌", damage);
	//m_target->TickDamage(damage);


	LOG_MGR->AddLog("때리고잇음");
}

void cBerserker::SKILL04()
{
	LOG_MGR->AddLog("광폭화 시전");
	m_damage += 100;
}

