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

	_battleUI = new battleUI;
	_battleUI->init();

	_aStar = new aStar;
	//_aStar->init(_battleMapLoad->getTileVector());

	return S_OK;
}

void battleScene::release()
{
	_battleMapLoad->release();
	_battleUI->release();
}

void battleScene::update()
{
	_battleMapLoad->update();
	_battleUI->update();
}

void battleScene::render()
{
	_battleMapLoad->render();
	_battleUI->render();
}
