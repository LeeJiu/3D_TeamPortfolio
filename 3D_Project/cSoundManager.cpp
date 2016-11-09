#include "stdafx.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager() : _system(NULL), _channal(NULL), _sound(NULL)
{
}


cSoundManager::~cSoundManager()
{
}

HRESULT cSoundManager::Init()
{
	System_Create(&_system);
	_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTAL_SOUND_CHANNEL];
	_channal = new Channel*[TOTAL_SOUND_CHANNEL];

	memset(_sound, 0, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
	memset(_channal, 0, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));

	return S_OK;
}

void cSoundManager::Release()
{
	if (_channal != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTAL_SOUND_CHANNEL; i++)
		{
			if (_channal != NULL)
			{
				if (_channal[i]) _channal[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	SAFE_DELETE_ARR(_channal);
	SAFE_DELETE_ARR(_sound);

	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void cSoundManager::Update()
{
	_system->update();
}

void cSoundManager::addSound(string keyName, string soundName, bool background, bool loop)
{
	if (loop)
	{
		if (background)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void cSoundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channal[count]);
			_channal[count]->setVolume(volume);
			break;
		}
	}
}

void cSoundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channal[count]->stop();
			break;
		}
	}
}

void cSoundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channal[count]->setPaused(true);
			break;
		}
	}
}

void cSoundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channal[count]->setPaused(false);
			break;
		}
	}
}

bool cSoundManager::isPauseSound(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	bool isPause = false;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channal[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}

bool cSoundManager::isPlaySound(string keyName)
{
	bool isPlay = false;
	int count = 0;

	arrSoundsIter iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channal[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}


void cSoundManager::setVolum(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channal[count]->setVolume(volume);
			break;
		}
	}
}
