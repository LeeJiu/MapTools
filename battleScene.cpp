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


	_count = 0;
	_volume = 0.2f;
	_Prinny_voluem = 0;
	SOUNDMANAGER->play("step", _Prinny_voluem);
	SOUNDMANAGER->play("battleScene_bg", _volume);

	_gameObjMgr = new gameObjectManager;
	_gameObjMgr->init();

	_battleMgr = new battleManager;
	_battleMgr->init();
	
	_gameObjMgr->setTile();
	_gameObjMgr->setObject();
	_gameObjMgr->setCharacter();
	_gameObjMgr->setEnemy();
	_gameObjMgr->setAstar();

	_battleUI = new battleUI;
	_battleUI->init();


	_gameObjMgr->setBattleUIMemoryLink(_battleUI);
	_gameObjMgr->setBattleManagerMemoryLink(_battleMgr);
	_battleMgr->setBattleUIMemoryLink(_battleUI);
	_battleMgr->setGameObjectManagerMemoryLink(_gameObjMgr);

	_battleUI->setObjectManagerMemoryLink(_gameObjMgr);
	_battleUI->setBattleManagerMemoryLink(_battleMgr);
	_battleUI->setCharacterList();

	_battleUI->setGameObjectSize();
	_battleUI->setCamera();

	return S_OK;
}

void battleScene::release()
{
	_gameObjMgr->release();
	_battleMgr->release();
	_battleUI->release();

	SOUNDMANAGER->stop("battleScene_bg");
}

void battleScene::update()
{
	if (_volume < 0.8f) _volume += 0.005f;
	SOUNDMANAGER->setVolum("battleScene_bg", _volume);
	SOUNDMANAGER->setVolum("step", _Prinny_voluem);

	//_Prinny_voluem = 

	_gameObjMgr->update();
	_battleMgr->update();
	_battleUI->update();
}

void battleScene::render()
{
	_gameObjMgr->render();
	_battleMgr->render();
	_battleUI->render();
}
