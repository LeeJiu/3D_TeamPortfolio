#pragma once
#include "cBaseObject.h"
#include "cTestCommand.h"
#include "cTestCommand2.h"
#include "moveClass.h"

#define CONTROL_KEY 5

class cTerrain;
class cCamera;
class cInputHandler;
class cStateHandler;

class cBerserker : public cBaseObject
{
private:
		cCamera*			m_camera;
		ACTOR_STATE			m_state;
		std::string			m_Aniname;
		std::map<int, bool> m_InputKeys;
		bool				m_isMove;

		//컴포넌트를 달아준다.
		cInputHandler*		m_pInput;
		moveClass*			m_pMove;

	public:
		cBerserker();
		~cBerserker();

		void BaseObjectEnable();
		void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....

		void SetCamera(cCamera* camera) { m_camera = camera; }
	};

