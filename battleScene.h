#pragma once
#include "gameNode.h"
#include "battleManager.h"
#include "battleCamera.h"
#include "gameObjectManager.h"

class battleScene : public gameNode
{
private:
	float _volume;

	gameObjectManager* _objectMgr;
	battleManager* _battleMgr;
	battleCamera* _camera;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

