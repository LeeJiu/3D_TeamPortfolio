#pragma once
#include "cState.h"


class cStateHandler
{
public:
	cStateHandler();
	~cStateHandler();

	cState* HandleInput(ACTOR_STATE eState);
	void AddState(ACTOR_STATE eState, cState* pState);
	void EnterState(ACTOR_STATE eState, int nNum = 10);

private:
	map<ACTOR_STATE, cState*>				m_mState;
	map<ACTOR_STATE, cState*>::iterator		m_miState;
};

