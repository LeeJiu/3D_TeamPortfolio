#pragma once
#include "cScene.h"

class cTerrain;
class cPlayer;
class cMonsterManager;

class cScene_Field : public cScene
{
private:
	cTerrain*			m_pTerrain;
	cPlayer*			m_pPlayer;

	cMonsterManager*	m_pMonMgr;

	std::vector<cLight*>		lights;
	std::vector<cBaseObject*>	m_vObject;
	std::vector<cBaseObject*>	m_vBoundBox;


public:
	cScene_Field();
	~cScene_Field();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

	virtual void Scene_RenderFont();

	void SoundInit();
	void ObjectInit();
};

