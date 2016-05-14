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

	//공통으로 사용하는 아이템 이미지 추가
	IMAGEMANAGER->addImage("sword", "image/item/sword.bmp", 256, 256, true, 0xff00ff);
	IMAGEMANAGER->addImage("staff", "image/item/staff.bmp", 256, 256, true, 0xff00ff);
	IMAGEMANAGER->addImage("wand", "image/item/wand.bmp", 256, 256, true, 0xff00ff);
	IMAGEMANAGER->addImage("bow", "image/item/bow.bmp", 256, 256, true, 0xff00ff);

	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->addScene("aStar", new aStar);
	SCENEMANAGER->addScene("store", new store);
	SCENEMANAGER->addScene("town", new town);

	SCENEMANAGER->changeScene("town");

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


