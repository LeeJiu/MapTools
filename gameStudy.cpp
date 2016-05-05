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

	_mapTool = new mapTool;
	_mapTool->init();
=======
	_map = new mapTool;
	_map->init();
>>>>>>> refs/remotes/origin/master

	return S_OK;
}

void gameStudy::release()
{
<<<<<<< HEAD
	_mapTool->release();
	SAFE_DELETE(_mapTool);

=======
	_map->release();
>>>>>>> refs/remotes/origin/master
	gameNode::release();
}

void gameStudy::update()
{
<<<<<<< HEAD
	_mapTool->update();

=======
	_map->update();
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

<<<<<<< HEAD
	_mapTool->render();

=======
	_map->render();
>>>>>>> refs/remotes/origin/master
	//======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);
}


