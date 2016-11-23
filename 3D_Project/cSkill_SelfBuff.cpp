#include "stdafx.h"
#include "cSkill_SelfBuff.h"


cSkill_SelfBuff::cSkill_SelfBuff()
{
}


cSkill_SelfBuff::~cSkill_SelfBuff()
{
}

void cSkill_SelfBuff::BaseObjectEnable(D3DXVECTOR3  casterWorldPos, int castTime, int buffCount, int coolTime)
{
	m_IsSelect = false;
	m_IsCasting = false;
	m_IsInBuff = false;
	m_IsCoolTime = false;


	m_CasterWorldPos = casterWorldPos;

	pTransform->SetWorldPosition(m_CasterWorldPos);  // 트렌스폼 좌표 


	m_CastTimeCount = 0;
	m_CastTime = castTime;

	m_CoolTimeCount = 0;
	m_CoolTime = coolTime;

	m_BuffCount = 0;
	m_BuffTime = buffCount;


}



void cSkill_SelfBuff::BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos)
{
	m_CasterWorldPos = CasterWorldPos;
	pTransform->SetWorldPosition(m_CasterWorldPos);

	if (m_IsCoolTime) //쿨타임 중이면 
	{
		LOG_MGR->AddLog("쿨타임 중입니다");

		m_CoolTimeCount++; //쿨타임을 계산해주자

		if (m_CoolTimeCount == m_CoolTime)
		{
			m_IsCoolTime = false;
		}

	}
	else //쿨타임 중이 아니면
	{
		if (m_IsSelect)
		{
			

		}
	}




	if (m_IsCasting)
	{
		m_IsSelect = false;
		m_CastTimeCount++;

		if (m_CastTimeCount == m_CastTime) //캐스팅이 끝나면 
		{
			m_IsCasting = false;
			m_IsInBuff = true;
			m_IsCoolTime = true; //쿨타임돌기를 시작합시다

		}

	}

	if (m_IsInBuff)
	{
		m_IsCasting = false;
		m_BuffCount++;

		if (m_BuffCount == m_BuffTime) //시전시간이 끝나면
		{

			m_IsInBuff = false;
			LOG_MGR->AddLog("버프 끝");
		}

	}


}

void cSkill_SelfBuff::SelectSkill()
{
	m_IsSelect = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_BuffCount = 0;

}


void cSkill_SelfBuff::StartCasting()
{
	m_IsCasting = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_BuffCount = 0;

}

