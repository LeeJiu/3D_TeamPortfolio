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

	m_IsShot = false;           // ��ų �߻����̴�?
	m_IsInRange = false;        // �߻��� ��ų�� ��Ÿ� ���̴�?
	m_IsAttacking = false;      // ��ų�� ��Ҵ�?

	m_AttackingCount = 0;   //���� �����ð��� ���
	m_AttackingTime = attackingTime; //

	m_MaxDistance = maxDistance;   //��Ÿ�

	m_CasterWorldPos = casterWorldPos;   //�������� ��ġ
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