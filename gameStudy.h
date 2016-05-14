#pragma once

#include "gameNode.h"
#include "selectStage.h"
#include "battleScene.h"
#include "town.h"
#include "mapTool.h"
#include "title.h"
<<<<<<< HEAD

class gameStudy : public gameNode
{
private:

=======
#include "store.h"


class gameStudy : public gameNode
{
>>>>>>> refs/remotes/origin/development
public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

