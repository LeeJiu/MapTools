#pragma once
#include "gameNode.h"
#include "battleMapLoad.h"
#include "aStar.h"

#include "battleUI.h"
#include "gameObjectManager.h"


class battleScene : public gameNode
{
private:
	battleUI* _battleUI;
	battleMapLoad* _battleMapLoad;
	aStar* _aStar;
	gameObjectManager* _gameObjMgr;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

