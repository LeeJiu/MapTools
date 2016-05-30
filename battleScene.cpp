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
	_volume = 0;
	SOUNDMANAGER->play("battleScene_bg", _volume);

	_camera = new battleCamera;
	_camera->init();

	_objectMgr = new gameObjectManager;
	_objectMgr->init();

	_battleMgr = new battleManager;
	_battleMgr->init();
	
	//�޸� ��ũ
	_objectMgr->setCameraMemoryLink(_camera);
	_objectMgr->setbattleMgrMemoryLink(_battleMgr);
	_battleMgr->setCameraMemoryLink(_camera);
	_battleMgr->setObjectMgrMemoryLink(_objectMgr);

	_objectMgr->setObject();
	_objectMgr->setCharacter();
	_objectMgr->setEnemy();

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

	SOUNDMANAGER->stop("battleScene_bg");
}

void battleScene::update()
{

	if (_volume < 1.f) _volume += 0.005f;
	SOUNDMANAGER->setVolum("battleScene_bg", _volume);

	_camera->update();
	_objectMgr->update();
	_battleMgr->update();
}

void battleScene::render()
{
	_objectMgr->tileRender();
	_battleMgr->selectTileRender();
	_objectMgr->render();
	_battleMgr->render();
}