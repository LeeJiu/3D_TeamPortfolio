#include "stdafx.h"
#include "cScene_LoadingScene.h"


cScene_LoadingScene::cScene_LoadingScene()
{
}


cScene_LoadingScene::~cScene_LoadingScene()
{
}


HRESULT cScene_LoadingScene::Scene_Init()
{
	m_rc = RectMake(0, 0, 1280, 720);
	m_loadingImg = RESOURCE_TEXTURE->GetResource("../Resources/UI/bless_UI.tga");
	
	
	
	
	return S_OK;
}

void cScene_LoadingScene::Scene_Release()
{

}

void cScene_LoadingScene::Scene_Update(float timDelta)
{

}

void cScene_LoadingScene::Scene_Render1()
{

}

void cScene_LoadingScene::Scene_RenderSprite()
{
	SPRITE_MGR->DrawTexture(
		m_loadingImg,
		&m_rc,
		0,0,
		0xffffffff,
		NULL);
}