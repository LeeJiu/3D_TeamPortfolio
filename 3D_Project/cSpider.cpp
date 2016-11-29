#include "stdafx.h"
#include "cSpider.h"
#include "cPlayer.h"


cSpider::cSpider()
{
	m_fHP = 1000;
	m_fRange = 20;
	m_fRange2 = 10;
	m_state = IDLE;
	m_strName = MyUtil::SetAnimation(m_state);
	m_bIsOverlap = false;
	m_bHit = false;
	m_fAtkTime = 0;
	m_fDeadTime = 0;
}


cSpider::~cSpider()
{
	
}

void cSpider::BaseObjectEnable()
{
	pSkinned->Play("IDLE");
}

void cSpider::BaseObjectUpdate(float timeDelta)
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

	//인식 범위에 들어왔을 때
	if (distance > m_fRange2 && distance < m_fRange)
	{
		Alert();
	}
	//공격 범위에 들어왔을 때
	else if (distance < m_fRange2)
	{
		RangeIn(timeDelta);
	}
	//범위 밖
	else
	{
		RangeOut();
	}

	SetAniState();
}

void cSpider::BaseObjectBoundBox()
{
	pSkinned->AddBoneTransform("BN_hand_L_04", m_pHitTrans);
	m_pHitTrans->MovePositionSelf(0, -0.5f, 0);
	m_pHitBound.SetBound(&m_pHitTrans->GetWorldPosition(), &D3DXVECTOR3(1.5f, 1.5f, 1.0f));

	BoundBox.SetBound(&D3DXVECTOR3(0, 1.5f, 0), &D3DXVECTOR3(1.5f, 1.5f, 1.5f));
}

void cSpider::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
	this->pTransform->RenderGimozo();
	this->BoundBox.RenderGizmo(this->pTransform);
	this->m_pHitBound.RenderGizmo(m_pHitTrans);
	m_pHitTrans->RenderGimozo();
}

void cSpider::Attack01(float timeDelta)
{
	if (m_state != ATK_01)
	{
		m_state = ATK_01;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT");

		m_bHit = true;
		m_fAtkTime = 0;
		return;
	}

	m_fAtkTime += timeDelta;
	if (m_fAtkTime > 1.8f && m_bHit == true)
	{
		//피격 판정 + 플레이어에게 데미지 전달
		if (PHYSICS_MGR->IsOverlap(m_pHitTrans, &m_pHitBound, m_pPlayer->pTransform, &m_pPlayer->BoundBox))
		{
			m_pPlayer->Damage(100);
			LOG_MGR->AddLog("때린다 %d",100);
			m_fAtkTime = 0;
			m_bHit = false;
		}
	}
}

void cSpider::Damage(float fDamage)
{
	LOG_MGR->AddLog("데미지들어옴!!!아파!! %.1f", fDamage);
	if (m_state != DMG && m_state != DIE)
	{
		m_state = DMG;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT");
		m_fHP -= fDamage;
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
		return;
	}
}

void cSpider::SetAniState()
{
	string aniName = pSkinned->GetNowPlayingAni();
	if (strcmp(aniName.c_str(), "IDLE") == 0)
	{
		m_state = IDLE;
		m_strName = MyUtil::SetAnimation(m_state);
	}
	else if (strcmp(aniName.c_str(), "GET_UP") == 0)
	{
		m_state = GET_UP;
		m_strName = MyUtil::SetAnimation(m_state);
	}
	else if (strcmp(aniName.c_str(), "WAIT") == 0)
	{
		m_state = WAIT;
		m_strName = MyUtil::SetAnimation(m_state);
		m_fAtkTime = 0;
		m_bHit = false;
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
	}
}

void cSpider::Alert()
{
	if (m_state == IDLE)
	{
		m_state = GET_UP;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3f);
	}
	else if (m_state == RUN)
	{
		m_state = WAIT;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->Play(m_strName, 0.3f);
	}
}

void cSpider::RangeIn(float timeDelta)
{
	m_bIsOverlap = PHYSICS_MGR->IsOverlap(this, m_pPlayer);

	if (m_state == WAIT || m_state == GET_UP)
	{
		if (m_bIsOverlap == true)
		{
			Attack01(timeDelta);
		}
		else
		{
			m_state = RUN;
			m_strName = MyUtil::SetAnimation(m_state);
			pSkinned->Stop();
			pSkinned->Play(m_strName);
		}
	}
	else if (m_state == RUN)
	{
		if (m_bIsOverlap == true)
		{
			Attack01(timeDelta);
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
}

void cSpider::RangeOut()
{
	if (m_state == RUN)
	{
		m_state = WAIT;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->Play(m_strName, 0.3f);
	}
}
