#pragma once
#include "cScene.h"

class cTerrain;
class cMonster;
class cLight;

class cScene_BoundBoxTool : public cScene
{
private:
	cTerrain*			m_pTerrain;
	cMonster*			m_pMonster;

	cLight*				testLight;

	std::vector<cLight*>	lights;

public:
	cScene_BoundBoxTool();
	~cScene_BoundBoxTool();

	HRESULT Scene_Init();

	void Scene_Release();

	void Scene_Update(float timeDelta);

	void Scene_Render1();
};

