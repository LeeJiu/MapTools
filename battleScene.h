#pragma once
#include "gameNode.h"
#include "battleUI.h"

class battleScene : public gameNode
{
private:
	battleUI* _ui;

	bool _onCharacterList, _onSummary, _onStatus, _onOrder, _onAction;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
};

