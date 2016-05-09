#pragma once
#include "gameNode.h"


class town : public gameNode
{
private:
	image* _town;


public:
	town();
	~town();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

