#pragma once
#include "gameNode.h"
class battle : public gameNode
{
private:


public:
	battle();
	~battle();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

