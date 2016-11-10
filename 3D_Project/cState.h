#pragma once

class cSkinnedAnimation;
class cBaseObject;

class cState
{
protected:
	ACTOR_STATE*		m_pState;

	cBaseObject*		m_pActor;
	cSkinnedAnimation*	m_pAnim;

public:
	cState();
	virtual ~cState();

	virtual void Enter(int nNum = 10) = 0;
	virtual void Execute() = 0;
	virtual void Exit() = 0;

	ACTOR_STATE GetCurrentState() { return *m_pState; }
};

