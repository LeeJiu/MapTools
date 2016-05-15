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

	//배틀씬에서 사용될 이미지 추가
	IMAGEMANAGER->addImage("walkable", "image/battle/walkable_tile.bmp", 192, 96, true, 0xff00ff);
	IMAGEMANAGER->addImage("attackable", "image/battle/attackable_tile.bmp", 192, 96, true, 0xff00ff);
	
	//씬 추가
	SCENEMANAGER->addScene("town", new town);
	SCENEMANAGER->addScene("selectStage", new selectStage);
	SCENEMANAGER->addScene("battleScene", new battleScene);
	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->addScene("store", new store);


	SCENEMANAGER->changeScene("title");

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


