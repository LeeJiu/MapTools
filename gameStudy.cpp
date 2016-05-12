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
<<<<<<< HEAD
=======
>>>>>>> refs/remotes/origin/backup-Jaejun
	
	SCENEMANAGER->addScene("town", new town);
	SCENEMANAGER->addScene("selectStage", new selectStage);
	SCENEMANAGER->addScene("battleScene", new battleScene);
	SCENEMANAGER->changeScene("battleScene");
<<<<<<< HEAD
=======
=======
>>>>>>> refs/remotes/origin/backup-Jaejun

	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->addScene("aStar", new aStar);

	SCENEMANAGER->changeScene("title");
<<<<<<< HEAD
>>>>>>> refs/remotes/origin/development
=======
>>>>>>> refs/remotes/origin/backup-Jaejun

	return S_OK;
}

void gameStudy::release()
{
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> refs/remotes/origin/development
=======
>>>>>>> refs/remotes/origin/backup-Jaejun
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


