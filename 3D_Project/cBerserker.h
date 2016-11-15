#pragma once
#include "cBaseObject.h"
#include "cBerserKer_Attack.h"
#include "cBerserKer_Attack2.h"
#include "cBerserKer_Attack3.h"
#include "moveClass.h"

#define CONTROL_KEY 5

class cTerrain;
class cCamera;
class cInputHandler;

class cBerserker : public cBaseObject
{
private:
		cCamera*			m_camera;
		ACTOR_STATE			m_state;
		std::string			m_Aniname;
		std::map<int, bool> m_InputKeys;
		bool				m_isMove;
		bool				m_isAttack;

		int					m_atkCnt;		//평타단계 수
		float				m_time;			//커맨드체크할 타이머
		float				m_fadeOut;		//애니 끝나는시간
		
		float				m_testtime;		//로그찎는용 타이머
		
		//컴포넌트를 달아준다.
		cInputHandler*		m_pInput;
		moveClass*			m_pMove;
		
		//스킬
		cBerserKer_Attack*	m_attak1;
		cBerserKer_Attack2*	m_attak2;
		cBerserKer_Attack3*	m_attak3;

	public:
		cBerserker();
		~cBerserker();

		void BaseObjectEnable();
		void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....

		void SetCamera(cCamera* camera) { m_camera = camera; }
	};

