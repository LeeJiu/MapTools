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

	_battleUI = new battleUI;
	_battleUI->init();

	_battleUI->setObjectManagerMemoryLink(_gameObjMgr);
	_gameObjMgr->setbattleUIMemoryLink(_battleUI);

	_gameObjMgr->setTile();
	_gameObjMgr->setCharacter();

	return S_OK;
}

void battleScene::release()
{
	_gameObjMgr->release();
	_battleUI->release();
}

void battleScene::update()
{
	_gameObjMgr->update();
	_battleUI->update();
}

void battleScene::render()
{
	_gameObjMgr->render();
	_battleUI->render();
}
