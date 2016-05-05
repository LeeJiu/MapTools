#pragma once

#include "gameNode.h"
#include "mapTool.h"

class gameStudy : public gameNode
{
private:
<<<<<<< HEAD
	mapTool* _mapTool;
=======
	mapTool* _map;
>>>>>>> refs/remotes/origin/master

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

