#pragma once
#include "cscene.h"



class cScene_LoadingScene : public cScene
{
	RECT                    m_rc;
	LPDIRECT3DTEXTURE9      m_loadingImg;



public:
	cScene_LoadingScene();
	~cScene_LoadingScene();


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();
};

