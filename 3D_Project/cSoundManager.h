#pragma once
#include "csingletonbase.h"
#include <map>
#include <string>

//fmod.hpp 추가
#include "inc/fmod.hpp"

//lib 링크
#pragma comment(lib, "lib/fmodex_vc.lib")

//사운드 버퍼(크기)
#define TOTAL_SOUND_CHANNEL 2048

using namespace FMOD;

class cSoundManager : public cSingletonBase<cSoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef arrSounds::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannes;
	typedef arrChannes::iterator arrChannesIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channal;
	arrSounds _mTotalSounds;

public:
	cSoundManager();
	~cSoundManager();

	HRESULT Init();
	void Release();
	void Update();

	//사운드 추가
	void addSound(string keyName, string soundName, bool background, bool loop);
	void play(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);
	bool isPauseSound(string keyNmae);
	bool isPlaySound(string keyName);
	void setVolum(string keyName, float volume);
};

#define SOUND_MGR		cSoundManager::GetInstance()