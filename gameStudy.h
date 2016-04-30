#pragma once

#include "gameNode.h"
#include "mapTool.h"

class gameStudy : public gameNode
{
private:
	mapTool* _mapTool;

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

