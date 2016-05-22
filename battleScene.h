#pragma once
#include "gameNode.h"
#include "battleManager.h"
#include "battleCamera.h"
#include "gameObjectManager.h"

class battleScene : public gameNode
{
private:
<<<<<<< HEAD
	float _volume;
	battleUI* _ui;

	bool _onCharacterList, _onSummary, _onStatus, _onOrder, _onAction;
=======
	gameObjectManager* _objectMgr;
	battleManager* _battleMgr;
	battleCamera* _camera;
>>>>>>> refs/remotes/origin/development

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

