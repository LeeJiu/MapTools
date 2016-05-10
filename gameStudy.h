#pragma once

#include "gameNode.h"
#include "mapTool.h"
<<<<<<< HEAD
#include "store.h"

class gameStudy : public gameNode
{
=======
#include "title.h"
#include "aStar.h"

class gameStudy : public gameNode
{
private:

>>>>>>> refs/remotes/origin/development
public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

