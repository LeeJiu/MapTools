#pragma once

#include "gameNode.h"
#include "selectStage.h"
#include "battleScene.h"
#include "town.h"
#include "mapTool.h"
#include "title.h"
<<<<<<< HEAD
#include "aStar.h"
#include "store.h"

#include "town.h"
=======
>>>>>>> refs/remotes/origin/backup-Jaejun

class gameStudy : public gameNode
{
private:
<<<<<<< HEAD


=======
>>>>>>> refs/remotes/origin/backup-Jaejun
public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

