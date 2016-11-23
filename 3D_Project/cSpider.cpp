#include "stdafx.h"
#include "cSpider.h"
#include "cPlayer.h"


cSpider::cSpider(float fHP, float fRange)
{
	m_fHP = fHP;
	m_fRange = fRange;
	m_fRange2 = 10;
	m_state = IDLE;
	m_strName = MyUtil::SetAnimation(m_state);
	m_bIsOverlap = false;
	m_bHit = false;
	m_fAtkTime = 0;

	time = 0;
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
	//SetAniState();

	float distance = D3DXVec3Length(&(m_pPlayer->pTransform->GetWorldPosition() - pTransform->GetWorldPosition()));

	//인식 범위에 들어왔을 때
	if (distance > m_fRange2 && distance < m_fRange)
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
	//공격 범위에 들어왔을 때
	else if (distance < m_fRange2)
	{
		m_bIsOverlap = PHYSICS_MGR->IsOverlap(this, m_pPlayer);

		if (m_bIsOverlap == true)
		{
			Attack01(timeDelta);
		}
		else
		{
			if (m_state == WAIT)
			{
				m_state = RUN;
				m_strName = MyUtil::SetAnimation(m_state);
				pSkinned->Stop();
				pSkinned->Play(m_strName);
			}
			else if (m_state == RUN)
			{
				LOG_MGR->AddLog("RUN : %s", m_strName.c_str());
				MoveToPlayer();
			}
		}
	}
	//범위 밖
	else
	{
		if (m_state == RUN)
		{
			m_state = WAIT;
			m_strName = MyUtil::SetAnimation(m_state);
			pSkinned->Play(m_strName, 0.3f);
		}
	}

	SetAniState();
}

void cSpider::BaseObjectBoundBox()
{
	this->BoundBox.SetBound(&D3DXVECTOR3(0, 1, 2), &D3DXVECTOR3(1.2f, 1.0f, 1.5f));
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
	}

	m_fAtkTime += timeDelta;
	if (m_fAtkTime > 1.8f && m_bHit == true)
	{
		//피격 판정 + 플레이어에게 데미지 전달
		if (PHYSICS_MGR->IsBlocking(this, m_pPlayer))
		{
			LOG_MGR->AddLog("때린다");
			m_pPlayer->Damage(100);
		}
		m_fAtkTime = 0;
		m_bHit = false;
	}
}

void cSpider::Damage(float fDamage)
{
	m_fHP -= fDamage;
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
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3f);
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
}
