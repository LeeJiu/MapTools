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
	// ���� �ý��� ����
	System_Create(&_system);
	_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTAL_SOUND_CHANNEL];
	_channal = new Channel*[TOTAL_SOUND_CHANNEL];

	//memset byte ������ �ʱ�ȭ �����ش�.
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
	// �޸� ����������
	SAFE_DELETE_ARRAY(_channal);
	SAFE_DELETE_ARRAY(_sound);

	//�ý��� �ݱ�
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
	//���� �뷡 ����
	if (loop)
	{
		// ������� ����
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
		//�ѹ��� �÷��� ����
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	// �ʿ� ���带 Ű���� �Բ� ����
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
			// ���� �÷��� �ض� 
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channal[count]);

			// ���� ����
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
			// ���� ����
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
			// ���� �Ͻ�����
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
			// ���� �ٽ����
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
			// ���� �ٽ����
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
			// ���� �ٽ����
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
			// ���� ����
			_channal[count]->setVolume(volume);
			break;
		}
	}
}