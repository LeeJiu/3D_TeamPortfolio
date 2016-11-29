#pragma once

class cVideo
{
private:
	HWND	hWndVideo;

public:
	cVideo();
	~cVideo();
	
	HRESULT Init();
	void Release();

	bool GetIsPlay();
	void Play(char * pFileName);
	void Stop();
	void Pause();
	void Resume();
	void Replay();
	void SetVolume(int nVolume);
};

