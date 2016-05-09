#pragma once
#include "gameNode.h"
class store : public gameNode
{
private:


public:
	store();
	~store();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

