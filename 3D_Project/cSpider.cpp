#include "stdafx.h"
#include "cSpider.h"
#include "cPlayer.h"


cSpider::cSpider(float fHP, float fRange)
{
	m_fHP = fHP;
	m_fRange = fRange;
	m_state = IDLE;
	m_strName = MyUtil::SetAnimation(m_state);
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
	float distance = D3DXVec3Length(&(m_pPlayer->pTransform->GetWorldPosition() - pTransform->GetWorldPosition()));

	if (distance < m_fRange)
	{
		MoveToPlayer();
	}

	if (KEY_MGR->IsOnceDown('H'))
	{
		Attack01();
	}

	if (KEY_MGR->IsOnceDown('J'))
	{
		Damage(10);
	}

	if (KEY_MGR->IsOnceDown('K'))
	{
		m_pPlayer->Damage();
	}
}

void cSpider::BaseObjectBoundBox()
{
	this->BoundBox.SetBound(&D3DXVECTOR3(0, 2, 0), &D3DXVECTOR3(2.0f, 2.0f, 2.0f));
}

void cSpider::Attack01()
{
	if (m_state != ATK_01)
	{
		m_state = ATK_01;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "IDLE", 0.5f);
		m_state = IDLE;
	}


	//피격 판정 + 플레이어에게 데미지 전달
	//m_pPlayer->Damage(damagePower);
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
		pSkinned->PlayOneShotAfterOther(m_strName, "IDLE", 0.3f);
		m_state = IDLE;
	}
}