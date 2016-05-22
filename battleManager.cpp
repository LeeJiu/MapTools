#include "stdafx.h"
#include "battleManager.h"
#include "gameObjectManager.h"

battleManager::battleManager()
{
}

battleManager::~battleManager()
{
}

HRESULT battleManager::init()
{
	_ui = new battleUI;
	_ui->init();

	return S_OK;
}

void battleManager::release()
{
	_ui->release();
	SAFE_DELETE(_ui);
}

void battleManager::update()
{
	_ui->update();

	keyControl();
}

void battleManager::render()
{
	_ui->render();
}

void battleManager::keyControl()
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
