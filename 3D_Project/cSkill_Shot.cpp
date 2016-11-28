#include "stdafx.h"
#include "cSkill_Shot.h"


cSkill_Shot::cSkill_Shot()
{
}


cSkill_Shot::~cSkill_Shot()
{
}


void cSkill_Shot::BaseObjectEnable(D3DXVECTOR3 casterWorldPos, float maxDistance, int attackingTime)
{

	m_IsShot = false;           // 스킬 발사중이니?
	m_IsInRange = false;        // 발사할 스킬이 사거리 안이니?
	m_IsAttacking = false;      // 스킬이 닿았니?

	m_AttackingCount = 0;   //공격 시전시간을 잰다
	m_AttackingTime = attackingTime; //

	m_MaxDistance = maxDistance;   //사거리

	m_CasterWorldPos = casterWorldPos;   //시전자의 위치
	m_BoundBox.SetBound(&m_CasterWorldPos, &D3DXVECTOR3(0.3f, 0.3f, 0.3f));

	pTransform->SetWorldPosition(m_CasterWorldPos);



}

void cSkill_Shot::BaseObjectUpdate(float timeDelta, D3DXVECTOR3 casterWorldPos, D3DXVECTOR3 lookDir)
{

	m_CasterWorldPos = casterWorldPos;



	if (m_IsShot)
	{
		pTransform->SetWorldPosition(m_CasterWorldPos);

	}

	
	if (m_IsAttacking)
	{
		m_IsShot = false;
		m_AttackingCount++;
		pTransform->SetWorldPosition(m_CasterWorldPos);

	}

	if (m_AttackingCount == m_AttackingTime)
	{
		m_IsAttacking = false;
	}


}

void  cSkill_Shot::BaseObjectRender()
{

}

void cSkill_Shot::ShotSkill()
{
     m_IsShot = true;
     m_AttackingCount = 0;
}

void cSkill_Shot::MakeAtk()
{
	m_IsAttacking = true;
	m_AttackingCount = 0;

}