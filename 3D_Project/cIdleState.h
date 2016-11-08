#pragma once
#include "cState.h"


class cIdleState : public cState
{
public:
	cIdleState(cBaseObject* pActor, ACTOR_STATE* pState);
	~cIdleState();

	void Enter(int nNum);
	void Execute();
	void Exit();
};

