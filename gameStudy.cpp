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
<<<<<<< HEAD

	//IMAGEMANAGER->addImage("mapTile", "image/mapTile.bmp", 208, 156, false, false);// 타일맵 큰이미지!....

=======
>>>>>>> refs/remotes/origin/master
	_map = new mapTool;
	_map->init();

	return S_OK;
}

void gameStudy::release()
{
	_map->release();
<<<<<<< HEAD

=======
>>>>>>> refs/remotes/origin/master
	gameNode::release();
}

void gameStudy::update()
{
	_map->update();
<<<<<<< HEAD

=======
>>>>>>> refs/remotes/origin/master
	gameNode::update();
}

void gameStudy::render()
{
	//백버퍼에서 뿌려준다
	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//IMAGEMANAGER->findImage("background")->render(getMemDC());
	//======================
	//이 사이에서 그려주면 됨.

	_map->render();
<<<<<<< HEAD

=======
>>>>>>> refs/remotes/origin/master
	//======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);
}


