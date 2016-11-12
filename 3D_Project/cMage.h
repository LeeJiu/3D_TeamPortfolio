#pragma once
#include "cBaseObject.h"
#include "cTestCommand.h"
#include "cTestCommand2.h"
#include "moveClass.h"

class cTerrain;
class cCamera;
class cInputHandler;
class cStateHandler;

class cMage : public cBaseObject
{
private:
	cCamera*			m_camera;
	

	ACTOR_STATE			m_state;
	bool				m_isMove;
	std::string			m_current_Ani;
	std::string			m_Aniname;
	std::vector<int>	m_inputKeys;

	//������Ʈ�� �޾��ش�.
	cInputHandler*		m_pInput;
	moveClass*			m_pMove;

public:
	cMage();
	~cMage();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....

	void SetCamera(cCamera* camera) { m_camera = camera; }
};


