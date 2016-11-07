#pragma once
#include "cScene.h"
#include "cPlayer.h"
#include "cTerrain.h"


class cScene_testPlayer : public cScene
{
private:
	cTerrain*					m_pTerrain;
	cPlayer*					m_pPlayer;


public:
	cScene_testPlayer();
	~cScene_testPlayer();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

