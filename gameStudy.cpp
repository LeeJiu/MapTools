#include "stdafx.h"
#include "gameStudy.h"


gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::init()
{
	gameNode::init(true);

	//IMAGEMANAGER->addImage("mapTile", "image/mapTile.bmp", 208, 156, false, false);// 타일맵 큰이미지!....

	//_map = new mapTool;
	//_map->init();

	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->addScene("aStar", new aStar);

	SCENEMANAGER->changeScene("aStar");

	return S_OK;
}

void gameStudy::release()
{
	SCENEMANAGER->release();

	gameNode::release();
}

void gameStudy::update()
{
	SCENEMANAGER->update();

	gameNode::update();
}

void gameStudy::render()
{
	//백버퍼에서 뿌려준다
	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//======================
	//이 사이에서 그려주면 됨.

	SCENEMANAGER->render();

	//======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);
}


