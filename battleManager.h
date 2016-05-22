#pragma once
#include "gameNode.h"
#include "battleUI.h"

class gameObjectManager;

class battleManager : public gameNode
{
private:
	gameObjectManager* _objectMgr;
	battleUI* _ui;

	bool _onCharacterList, _onSummary, _onStatus, _onOrder, _onAction;


public:
	battleManager();
	~battleManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();

	void setObjectMgrMemoryLink(gameObjectManager* objectMgr) { _objectMgr = objectMgr; }
};

