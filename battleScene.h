#pragma once
#include "gameNode.h"
#include "aStar.h"

#include "battleUI.h"
#include "gameObjectManager.h"
#include "battleManager.h"


class battleScene : public gameNode
{
private:
	battleUI* _battleUI;
	gameObjectManager* _gameObjMgr;
	battleManager* _battleMgr;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

