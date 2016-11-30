#include "stdafx.h"
#include "cMinotauros.h"
#include "cPlayer.h"
#include "cWayPoint.h"


cMinotauros::cMinotauros()
{
	m_fHP = 1000;
	m_fRange = 20;
	m_state = RUN;
	m_strName = MyUtil::SetAnimation(m_state);
	m_bIsOverlap = false;
	m_bHit = false;
	m_bAttacked1 = false;
	m_bAttacked2 = false;
	m_bAlert = false;
	m_fAtkTime = 0;
	m_fDeadTime = 0;
}


cMinotauros::~cMinotauros()
{
	SAFE_DELETE(m_pWayPoint);
}

void cMinotauros::BaseObjectEnable()
{
	pSkinned->Play("RUN");

	m_pWayPoint = new cWayPoint(pTerrain);
	m_pWayPoint->Init(pTransform, 10.0f);
}

void cMinotauros::BaseObjectUpdate(float timeDelta)
{
	if (m_state == DIE)
	{
		m_fDeadTime += timeDelta;
		if (m_fDeadTime > 5.0f)
		{
			m_fDeadTime = 0;
			SetActive(false);
		}
		return;
	}

	float distance = D3DXVec3Length(&(m_pPlayer->pTransform->GetWorldPosition() - pTransform->GetWorldPosition()));


	if (PHYSICS_MGR->intersectSector(pTransform, m_pPlayer->pTransform, 2, 160 * ONE_RAD) == true)
	{
		RangeIn(timeDelta);
	}
	else
	{
		if (distance > m_fRange)
		{
			m_bAlert = false;
			m_fHP = 1000;
		}
		RangeOut();
	}

	SetAniState();
}

void cMinotauros::BaseObjectBoundBox()
{
	pSkinned->AddBoneTransform("BN_Weapon_R", m_pHitTrans);
	m_pHitTrans->MovePositionSelf(0.3f, 0.8f, 0.2f);
	m_pHitBound.SetBound(&m_pHitTrans->GetWorldPosition(), &D3DXVECTOR3(0.7f, 1.5f, 0.25f));

	BoundBox.SetBound(&D3DXVECTOR3(0, 1.5f, 0), &D3DXVECTOR3(1.0f, 1.5f, 1.0f));
}

void cMinotauros::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
	this->pTransform->RenderGimozo();
	this->BoundBox.RenderGizmo(this->pTransform);
	this->m_pHitBound.RenderGizmo(m_pHitTrans);
	m_pHitTrans->RenderGimozo();
}

void cMinotauros::Damage(float fDamage)
{
	if (m_state != DMG && m_state != DIE)
	{
		m_state = DMG;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT");
		m_fHP -= fDamage;
		SOUND_MGR->play("hit_mino", 0.8f);
	}	
	else if (m_state == DIE || m_state == DMG)
	{
		return;
	}

	if (m_fHP <= FEPSILON)
	{
		m_fHP = 0.0f;
		m_state = DIE;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterHold(m_strName);
		m_fDeadTime = 0;
		SOUND_MGR->play("die_mino", 0.8f);
		return;
	}
}

void cMinotauros::Attack01(float timeDelta)
{
	if (m_state != ATK_01)
	{
		m_state = ATK_01;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT");
		pSkinned->SetPlaySpeed(2.0f);

		m_bHit = true;
		m_fAtkTime = 0;
		SOUND_MGR->play("atk_mino", 0.8f);
		return;
	}

	m_fAtkTime += timeDelta;
	if (m_fAtkTime > 0.8f && m_bHit == true)
	{
		//피격 판정 + 플레이어에게 데미지 전달
		if (PHYSICS_MGR->IsOverlap(m_pHitTrans, &m_pHitBound, m_pPlayer->pTransform, &m_pPlayer->BoundBox))
		{
			LOG_MGR->AddLog("때린다");
			m_pPlayer->Damage(100);
			m_fAtkTime = 0;
			m_bHit = false;
			m_bAttacked1 = true;
		}
	}
}

void cMinotauros::Attack02(float timeDelta)
{
	if (m_state != ATK_02)
	{
		m_state = ATK_02;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT");

		m_bHit = true;
		m_fAtkTime = 0;
		SOUND_MGR->play("atk2_mino", 0.8f);
		return;
	}

	m_bAttacked2 = true;

	m_fAtkTime += timeDelta;
	if (m_fAtkTime > 0.8f && m_bHit == true)
	{
		//피격 판정 + 플레이어에게 데미지 전달
		if (PHYSICS_MGR->IsOverlap(m_pHitTrans, &m_pHitBound, m_pPlayer->pTransform, &m_pPlayer->BoundBox))
		{
			LOG_MGR->AddLog("때린다");
			m_pPlayer->Damage(150);
			m_fAtkTime = 0;
			m_bHit = false;
		}
	}
}

void cMinotauros::SetAniState()
{
	string aniName = pSkinned->GetNowPlayingAni();
	if (strcmp(aniName.c_str(), "IDLE") == 0)
	{
		m_state = IDLE;
		m_strName = MyUtil::SetAnimation(m_state);
	}
	else if (strcmp(aniName.c_str(), "WAIT") == 0)
	{
		m_state = WAIT;
		m_strName = MyUtil::SetAnimation(m_state);
		m_fAtkTime = 0;
		m_bHit = false;
		if (m_bAttacked2 == true)
		{
			m_bAttacked1 = false;
			m_bAttacked2 = false;
		}
	}
	else if (strcmp(aniName.c_str(), "RUN") == 0)
	{
		m_state = RUN;
		m_strName = MyUtil::SetAnimation(m_state);
	}
	else if (strcmp(aniName.c_str(), "DMG") == 0)
	{
		m_state = DMG;
		m_strName = MyUtil::SetAnimation(m_state);
		m_fAtkTime = 0;
		m_bHit = false;
		m_bAttacked1 = false;
	}
	else if (strcmp(aniName.c_str(), "ATK_02") == 0)
	{
		m_state = ATK_02;
		m_strName = MyUtil::SetAnimation(m_state);
	}
}

void cMinotauros::RangeIn(float timeDelta)
{
	m_bAlert = true;

	m_bIsOverlap = PHYSICS_MGR->IsOverlap(this, m_pPlayer);

	if (m_state == RUN || m_state == WAIT)
	{
		if (m_bIsOverlap == true)
		{
			if (m_bAttacked1 == false)
			{
				Attack01(timeDelta);
			}
			else
			{
				Attack02(timeDelta);
			}
		}
		else
		{
			MoveToPlayer();
		}
	}
	else if (m_state == ATK_01)
	{
		Attack01(timeDelta);
	}
	else if (m_state == ATK_02)
	{
		Attack02(timeDelta);
	}
}

void cMinotauros::RangeOut()
{
	if (m_bAlert == true)
	{
		if (m_state == RUN)
		{
			m_state = WAIT;
			m_strName = MyUtil::SetAnimation(m_state);
			pSkinned->Play(m_strName);
		}
		else if (m_state == DMG)
		{
			pTransform->LookPosition(m_pPlayer->pTransform->GetWorldPosition());
		}
	}
	else
	{
		if (m_state == RUN)
		{
			m_pWayPoint->Update(pTransform);
		}
		else
		{
			m_state = RUN;
			m_strName = MyUtil::SetAnimation(m_state);
			pSkinned->Play(m_strName);
		}
	}	
}
