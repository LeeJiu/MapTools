#pragma once
#include "gameNode.h"
#include "battleManager.h"
#include "gameObjectManager.h"

class battleScene : public gameNode
{
private:
	gameObjectManager* _objectMgr;
	battleManager* _battleMgr;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

