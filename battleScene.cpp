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
	_battleUI = new battleUI;
	_battleUI->init();

	return S_OK;
}

void battleScene::release()
{
	_battleUI->release();
}

void battleScene::update()
{
	_battleUI->update();
}

void battleScene::render()
{
	_battleUI->render();
}
