#pragma once
#include "cBaseObject.h"
#include "cTestCommand.h"
#include "cTestCommand2.h"


class cTerrain;
class cCamera;
class cMonsterManager;

class cPlayer : public cBaseObject 
{
private:
	cCamera*			m_camera;

	cMonsterManager*	m_pMonMgr;

public:
	cPlayer();
	~cPlayer();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....
	void BaseObjectRender();

	void Damage() { LOG_MGR->AddLog("�÷��̾� ����"); }

	void SetCamera(cCamera* camera) { m_camera = camera; }
	void SetMonsterManager(cMonsterManager* pMonMgr) { m_pMonMgr = pMonMgr; }
};

