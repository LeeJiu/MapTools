#pragma once

#include "gameNode.h"
#include "mapTool.h"
#include "store.h"

class gameStudy : public gameNode
{
public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

