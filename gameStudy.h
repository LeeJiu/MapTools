#pragma once

#include "gameNode.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "selectStage.h"
#include "battleScene.h"
#include "town.h"
=======
#include "mapTool.h"
#include "title.h"
#include "aStar.h"
>>>>>>> refs/remotes/origin/development
=======
#include "selectStage.h"
#include "battleScene.h"
#include "town.h"
#include "mapTool.h"
#include "title.h"
#include "aStar.h"
>>>>>>> refs/remotes/origin/backup-Jaejun

class gameStudy : public gameNode
{
private:
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> refs/remotes/origin/development

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

