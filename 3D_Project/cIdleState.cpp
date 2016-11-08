#include "stdafx.h"
#include "cIdleState.h"


cIdleState::cIdleState(cBaseObject* pActor, ACTOR_STATE* pState)
{
	m_pActor = pActor;
	m_pAnim = pActor->GetSkinnedAnim();
	m_pState = pState;
}


cIdleState::~cIdleState()
{
}

void cIdleState::Enter(int nNum)
{
	if(nNum == 1)
	{ 
		m_pAnim->Play("Idle_01", 0.3f);
	}
	else if(nNum == 2)
	{
		m_pAnim->Play("Idle_02", 0.3f);
	}
	else
	{
		m_pAnim->Play("Idle_01", 0.3f);
	}
}

void cIdleState::Execute()
{
	
}

void cIdleState::Exit()
{
}
