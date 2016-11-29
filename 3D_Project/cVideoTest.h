#pragma once
#include "cScene.h"
#include "cVideo.h"

class cVideoTest :public cScene
{
private:
	cVideo* m_pVideo;

public:
	cVideoTest();
	~cVideoTest();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

