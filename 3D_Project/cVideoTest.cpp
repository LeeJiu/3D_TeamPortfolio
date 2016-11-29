#include "stdafx.h"
#include "cVideoTest.h"


cVideoTest::cVideoTest()
{
}


cVideoTest::~cVideoTest()
{
}

HRESULT cVideoTest::Scene_Init()
{
	m_pVideo = new cVideo;
	m_pVideo->Init();
	g_bDXRender = false;

	return S_OK;
}

void cVideoTest::Scene_Release()
{
	m_pVideo->Release();
	SAFE_DELETE(m_pVideo);
}

void cVideoTest::Scene_Update(float timeDelta)
{
	if (KEY_MGR->IsOnceDown(VK_RETURN))
	{
		m_pVideo->Play("../Video/trailer.wmv");
	}
	if (KEY_MGR->IsOnceDown('1'))
	{
		m_pVideo->Stop();
	}
	if (KEY_MGR->IsOnceDown('2'))
	{
		m_pVideo->Replay();
	}
	if (KEY_MGR->IsOnceDown('3'))
	{
		g_bDXRender = true;
		SCENE_MGR->ChangeScene("cScene_testMonster");
	}
}

void cVideoTest::Scene_Render1()
{
}
