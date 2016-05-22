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
	_objectMgr = new gameObjectManager;
	_objectMgr->init();

	_battleMgr = new battleManager;
	_battleMgr->init();
	
	//메모리 링크
	_battleMgr->setObjectMgrMemoryLink(_objectMgr);

	return S_OK;
}

void battleScene::release()
{
	_objectMgr->release();
	_battleMgr->release();
	SAFE_DELETE(_objectMgr);
	SAFE_DELETE(_battleMgr);
}

void battleScene::update()
{
	_objectMgr->update();
	_battleMgr->update();
}

void battleScene::render()
{
<<<<<<< HEAD
	_objectMgr->render();
	_battleMgr->render();
}
=======
	
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
>>>>>>> refs/remotes/origin/development
