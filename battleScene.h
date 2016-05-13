#pragma once
#include "gameNode.h"
#include "battleUI.h"
#include "battleMapLoad.h"
#include "aStar.h"

class battleScene : public gameNode
{
private:
	battleUI* _battleUI;
	battleMapLoad* _battleMapLoad;
	aStar* _aStar;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

