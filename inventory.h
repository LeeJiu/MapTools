#pragma once
#include "gameNode.h"
#include "item.h"

class inventory : public gameNode
{
private:
	item _item;

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	
};

