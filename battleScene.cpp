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
	_camera = new battleCamera;
	_camera->init();

	_objectMgr = new gameObjectManager;
	_objectMgr->init();
	_objectMgr->setCharacter();
	_objectMgr->setEnemy();
	_objectMgr->setObject();

	_battleMgr = new battleManager;
	_battleMgr->init();
	
	//메모리 링크
	_objectMgr->setCameraMemoryLink(_camera);
	_battleMgr->setCameraMemoryLink(_camera);
	_battleMgr->setObjectMgrMemoryLink(_objectMgr);

	return S_OK;
}

void battleScene::release()
{
	_camera->release();
	_objectMgr->release();
	_battleMgr->release();
	SAFE_DELETE(_camera);
	SAFE_DELETE(_objectMgr);
	SAFE_DELETE(_battleMgr);
}

void battleScene::update()
{

	if (_volume < 0.8f) _volume += 0.005f;
	SOUNDMANAGER->setVolum("battleScene_bg", _volume);

	_camera->update();
	_objectMgr->update();
	_battleMgr->update();
}

void battleScene::render()
{
	_objectMgr->render();
	_battleMgr->render();
}