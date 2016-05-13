#pragma once
#include "gameNode.h"
#include "battleUI.h"

class battleScene : public gameNode
{
private:
	battleUI* _battleUI;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

