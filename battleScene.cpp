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
	_battleMapLoad = new battleMapLoad;
	_battleMapLoad->init();

	_aStar = new aStar;
	//_aStar->init(_battleMapLoad->getTileVector());

	_gameObjMgr = new gameObjectManager;
	_gameObjMgr->init();

	_battleUI = new battleUI;
	_battleUI->init();

	_battleUI->setObjectManagerMemoryLink(_gameObjMgr);
	_gameObjMgr->setbattleUIMemoryLink(_battleUI);

	return S_OK;
}

void battleScene::release()
{
	_battleMapLoad->release();
	_gameObjMgr->release();
	_battleUI->release();
}

void battleScene::update()
{
	_battleMapLoad->update();
	_gameObjMgr->update();
	_battleUI->update();
}

void battleScene::render()
{
	_battleMapLoad->render();
	_gameObjMgr->render();
	_battleUI->render();
}
