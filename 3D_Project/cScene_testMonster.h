#pragma once
#include "cScene.h"
#include "cSetBoundObject.h"
#include "cBerserker.h"
#include "cMonsterManager.h"


class cScene_testMonster : public cScene
{
private:
	cTerrain*			m_pTerrain;
	cPlayer*			m_pPlayer;

	cMonsterManager*	m_pMonMgr;

	std::vector<cLight*>		lights;
	std::vector<cBaseObject*>	m_vObject;
	std::vector<cBaseObject*>	m_vBoundBox;

public:
	cScene_testMonster();
	~cScene_testMonster();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

