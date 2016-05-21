#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager() : _system(NULL), _channal(NULL), _sound(NULL)
{
}


soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	// 사운드 시스템 생성
	System_Create(&_system);
	_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTAL_SOUND_CHANNEL];
	_channal = new Channel*[TOTAL_SOUND_CHANNEL];

	//memset byte 단위로 초기화 시켜준다.
	memset(_sound, 0, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
	memset(_channal, 0, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));
	
	return S_OK;
}

void soundManager::release()
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
	// 메모리 해제해주자
	SAFE_DELETE_ARRAY(_channal);
	SAFE_DELETE_ARRAY(_sound);

	//시스템 닫기
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void soundManager::update()
{
	_system->update();
}

void soundManager::addSound(string keyName, string soundName, bool background, bool loop)
{
	//돌림 노래 유무
	if (loop)
	{
		// 배경음식 유무
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
		//한번만 플레이 하자
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	// 맵에 사운드를 키값과 함께 넣자
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void soundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// 사운드 플레이 해라 
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channal[count]);

			// 볼륨 설정
			_channal[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// 사운드 정지
			_channal[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// 사운드 일시정지
			_channal[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// 사운드 다시재생
			_channal[count]->setPaused(false);
			break;
		}
	}
}

bool soundManager::isPauseSound(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	bool isPause = false;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// 사운드 다시재생
			_channal[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}

bool soundManager::isPlaySound(string keyName)
{
	bool isPlay = false;
	int count = 0;

	arrSoundsIter iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// 사운드 다시재생
			_channal[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}


void soundManager::setVolum(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// 볼륨 설정
			_channal[count]->setVolume(volume);
			break;
		}
	}
}