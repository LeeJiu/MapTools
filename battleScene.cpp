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
	_gameObjMgr = new gameObjectManager;
	_gameObjMgr->init();

	_battleMgr = new battleManager;
	_battleMgr->init();
	
	_gameObjMgr->setTile();
	_gameObjMgr->setCharacter();
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


	return S_OK;
}

void battleScene::release()
{
	_gameObjMgr->release();
	_battleMgr->release();
	_battleUI->release();
}

void battleScene::update()
{
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
