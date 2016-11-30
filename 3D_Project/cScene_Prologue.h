#pragma once
#include "cScene.h"
#include "cVideo.h"

class cScene_Prologue : public cScene
{
private:
	cVideo*		m_pVideo;
	bool		m_bStart;

public:
	cScene_Prologue();
	~cScene_Prologue();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

