#pragma once

#include "gameNode.h"
#include "selectMap.h"

class gameStudy : public gameNode
{
private:
	selectMap* _selectMap;

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

