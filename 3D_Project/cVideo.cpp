#include "stdafx.h"
#include "cVideo.h"


cVideo::cVideo()
{
}


cVideo::~cVideo()
{
}

HRESULT cVideo::Init()
{
	hWndVideo = NULL;

	return S_OK;
}

void cVideo::Release()
{
	if (hWndVideo)
	{
		MCIWndClose(hWndVideo);
		MCIWndDestroy(hWndVideo);
		hWndVideo = NULL;
	}
}

bool cVideo::GetIsPlay()
{
	switch (MCIWndGetMode(hWndVideo, NULL, NULL))
	{
	case MCI_MODE_STOP:
		return false;
	case MCI_MODE_PLAY:
		return true;
	}
}

void cVideo::Play(char * pFileName)
{
	if (hWndVideo)
	{
		MCIWndClose(hWndVideo);
		MCIWndDestroy(hWndVideo);
		hWndVideo = NULL;
	}

	// hWndVideo를 생성
	hWndVideo = MCIWndCreate(g_hWnd, g_hInst,
		MCIWNDF_NOTIFYANSI | MCIWNDF_NOMENU |
		MCIWNDF_NOTIFYALL | MCIWNDF_NOPLAYBAR,
		pFileName);
	
	// 사이즈 맞춰서.. 
	if (hWndVideo)
	{
		RECT rt;
		GetClientRect(g_hWnd, &rt);
		SetWindowPos(hWndVideo, NULL, 0, 0, rt.right, rt.bottom, SWP_NOZORDER);
		MCIWndPlay(hWndVideo);
	}
}

void cVideo::Stop()
{
	if (hWndVideo == NULL) return;

	MCIWndStop(hWndVideo);
}

void cVideo::Pause()
{
	if (hWndVideo == NULL) return;

	MCIWndPause(hWndVideo);
}

void cVideo::Resume()
{
	if (hWndVideo == NULL) return;

	MCIWndResume(hWndVideo);
}

void cVideo::Replay()
{
	if (hWndVideo == NULL) return;

	if (GetIsPlay() == FALSE)
	{
		MCIWndPlay(hWndVideo);
	}
}

void cVideo::SetVolume(int nVolume)
{
	MCIWndSetVolume(hWndVideo, nVolume);
}
