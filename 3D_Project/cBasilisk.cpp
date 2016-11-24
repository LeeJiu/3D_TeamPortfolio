#include "stdafx.h"
#include "cBasilisk.h"
#include "cPlayer.h"
#include "cWayPoint.h"


cBasilisk::cBasilisk()
{
	m_fHP = 1000;
	m_fRange = 20;
	m_state = IDLE;
	m_strName = MyUtil::SetAnimation(m_state);
	m_bIsOverlap = false;
	m_bHit = false;
	m_fAtkTime = 0;
	m_fDeadTime = 0;
}


cBasilisk::~cBasilisk()
{
}

void cBasilisk::BaseObjectEnable()
{
	pSkinned->Play("IDLE");

	m_pWayPoint = new cWayPoint(pTerrain);
	m_pWayPoint->Init(pTransform, 10.0f);
}

void cBasilisk::BaseObjectUpdate(float timeDelta)
{
	m_pWayPoint->Update(pTransform);
	float distance = D3DXVec3Length(&(m_pPlayer->pTransform->GetWorldPosition() - pTransform->GetWorldPosition()));

	if (distance < m_fRange)
	{
		MoveToPlayer();
	}
	else
	{
		m_pWayPoint->Update(pTransform);
	}
}

void cBasilisk::BaseObjectBoundBox()
{
}

void cBasilisk::Damage(float fDamage)
{
}

void cBasilisk::Attack01(float timeDelta)
{
}

void cBasilisk::SetAniState()
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
	}
	else if (strcmp(aniName.c_str(), "RUN") == 0)
	{
		m_state = RUN;
		m_strName = MyUtil::SetAnimation(m_state);
	}
}
