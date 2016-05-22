#pragma once
#include "gameNode.h"


class battleManager : public gameNode
{
private:


public:
	battleManager();
	~battleManager();

	HRESULT init();
	void release();
	void update();
	void render();

};

