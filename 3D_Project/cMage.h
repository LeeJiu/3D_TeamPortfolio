#pragma once
#include "cBaseObject.h"
#include "cTestCommand.h"
#include "cTestCommand2.h"
#include "moveClass.h"
#include "cIdleState.h"
#include "cMoveState.h"

class cTerrain;
class cCamera;
class cInputHandler;
class cStateHandler;

class cMage : public cBaseObject
{
private:
	cCamera*			m_camera;

	ACTOR_STATE			m_state;
	std::string			m_current_Ani;

	//컴포넌트를 달아준다.
	cInputHandler*		m_pInput;
	moveClass*			m_pMove;
	cStateHandler*		m_pState;

public:
	cMage();
	~cMage();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....

	void SetCamera(cCamera* camera) { m_camera = camera; }
};


