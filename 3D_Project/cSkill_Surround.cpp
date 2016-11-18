#include "stdafx.h"
#include "cSkill_Surround.h"


cSkill_Surround::cSkill_Surround()
{
}


cSkill_Surround::~cSkill_Surround()
{
}

void cSkill_Surround::BaseObjectEnable()
{


}

void cSkill_Surround::SkillInit(D3DXVECTOR3 casterWorldPos, float surroundRadius, int hitMax, int  damage, int  useSP,
int   coolTime, int  castTime, int actionTime)
{
	
	m_CasterWorldPos = casterWorldPos;
	
	pTransform->SetWorldPosition(m_CasterWorldPos);  // Æ®·»½ºÆû ÁÂÇ¥ 

	//m_CasterPos->SetWorldPosition(m_CasterWorldPos);
	//m_SurroundRadius = surroundRadius;
	//m_BoundSphere->radius = m_SurroundRadius;
	//m_HitMax = hitMax;
	
	m_Damage = damage;
	m_UseSP = useSP;


	m_CoolTime = coolTime;
	m_CastTime = castTime;
	m_ActionTime = actionTime;


	m_UseSkill = false;
	m_IsCasting = false;
	m_IsAction  = false;

	m_IsHit = false;		

	//

	m_tickTime = 0.5f;
	m_timeTemp = 0;
}

void cSkill_Surround::SkillUpdate(float timeDelta)
{
	if (m_timeTemp < m_tickTime)
	{
		m_timeTemp += timeDelta;

	}
	else if (m_timeTemp > m_tickTime)
	{
		//
		m_timeTemp = 0;
	}


	m_CasterPos->SetWorldPosition(m_CasterWorldPos);

}