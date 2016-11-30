#include "stdafx.h"
#include "cScene_Prologue.h"


cScene_Prologue::cScene_Prologue()
{
}


cScene_Prologue::~cScene_Prologue()
{
}

HRESULT cScene_Prologue::Scene_Init()
{
	m_pVideo = new cVideo;
	m_pVideo->Init();
	m_bStart = false;
	g_bDXRender = false;

	return S_OK;
}

void cScene_Prologue::Scene_Release()
{
	m_pVideo->Release();
	SAFE_DELETE(m_pVideo);
}

void cScene_Prologue::Scene_Update(float timeDelta)
{
	if (m_bStart == false)
	{
		m_pVideo->Play("../Resources/Video/BLESS_movie.wmv");
		m_bStart = true;
	}

	if (m_pVideo->GetIsPlay() == false)
	{
		m_pVideo->Stop();
		SCENE_MGR->ChangeScene("Field", 1);
	}

	if (KEY_MGR->IsOnceDown(VK_RETURN))
	{
		SCENE_MGR->ChangeScene("Field", 1);
	}
}

void cScene_Prologue::Scene_Render1()
{
}