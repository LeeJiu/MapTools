#pragma once
#include "gameNode.h"
class item : public gameNode
{
private:


public:
	item();
	~item();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

