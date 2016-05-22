#include "stdafx.h"
#include "battleScene.h"


battleScene::battleScene()
{
}


battleScene::~battleScene()
{
}

HRESULT battleScene::init()
{
	_ui = new battleUI;
	_ui->init();

	return S_OK;
}

void battleScene::release()
{
}

void battleScene::update()
{
	if (_volume < 0.8f) _volume += 0.005f;
	SOUNDMANAGER->setVolum("battleScene_bg", _volume);
	


	_ui->update();
	
	keyControl();
}

void battleScene::render()
{
	_ui->render();
}

void battleScene::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_onCharacterList = !_onCharacterList;
		_ui->onCharacterList(_onCharacterList);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_onSummary = !_onSummary;
		_ui->onSummary(_onSummary);
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_onStatus = !_onStatus;
		_ui->onStatus(_onStatus);
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_onOrder = !_onOrder;
		_ui->onOrder(_onOrder);
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_onAction = !_onAction;
		_ui->onAction(_onAction);
	}
}
