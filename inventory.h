#pragma once
#include "gameNode.h"
class inventory : public gameNode
{
private:


public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

