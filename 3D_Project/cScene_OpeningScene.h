#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;

class cScene_OpeningScene : public cScene
{

	cBaseObject*  m_pMainCharacter;
	cBaseObject*  m_pStage;

	std::vector<cLight*>	lights;


public:
	cScene_OpeningScene();
	~cScene_OpeningScene();


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();
};

