#pragma once
#include "cScene.h"
#include "cMonster.h"
#include "cMage.h"
#include "cSetBoundObject.h"


class cScene_testMonster : public cScene
{
private:
	cTerrain*					m_pTerrain;
	cMonster*					m_pMonster;
	cMage*						m_pMage;

	std::vector<cLight*>		lights;

public:
	cScene_testMonster();
	~cScene_testMonster();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
	
	
	std::vector<cBaseObject*>		objects;
};

