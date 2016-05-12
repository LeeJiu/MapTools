#pragma once

#include "gameNode.h"
<<<<<<< HEAD
#include "selectStage.h"
#include "battleScene.h"
#include "town.h"
=======
#include "mapTool.h"
#include "title.h"
#include "aStar.h"
>>>>>>> refs/remotes/origin/development

class gameStudy : public gameNode
{
private:
<<<<<<< HEAD

=======
>>>>>>> refs/remotes/origin/development

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

