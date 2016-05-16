#pragma once

#include "gameNode.h"
#include "mapTool.h"
#include "title.h"

class gameStudy : public gameNode
{
private:

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

