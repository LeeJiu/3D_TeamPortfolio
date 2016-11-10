#include "stdafx.h"
#include "cStateHandler.h"


cStateHandler::cStateHandler()
{
}


cStateHandler::~cStateHandler()
{
}

cState* cStateHandler::HandleInput(ACTOR_STATE eState)
{
	return m_mState.find(eState)->second;
}

void cStateHandler::AddState(ACTOR_STATE eState, cState * pState)
{
	m_mState.insert(pair<ACTOR_STATE, cState*>(eState, pState));
}

void cStateHandler::EnterState(ACTOR_STATE eState, int nNum)
{
	m_mState.find(eState)->second->Enter(nNum);
}
