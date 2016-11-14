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

		int					m_atkCnt;		//��Ÿ�ܰ� ��
		float				m_time;			//Ŀ�ǵ�üũ�� Ÿ�̸�
		float				m_fadeOut;		//�ִ� �����½ð�
		
		float				m_testtime;		//�αש��¿� Ÿ�̸�
		
		//������Ʈ�� �޾��ش�.
		cInputHandler*		m_pInput;
		moveClass*			m_pMove;
		
		//��ų
		cBerserKer_Attack*	m_attak1;
		cBerserKer_Attack2*	m_attak2;
		cBerserKer_Attack3*	m_attak3;

	public:
		cBerserker();
		~cBerserker();

		void BaseObjectEnable();
		void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....

		void SetCamera(cCamera* camera) { m_camera = camera; }
	};

