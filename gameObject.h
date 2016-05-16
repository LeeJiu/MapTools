#pragma once
#include "gameNode.h"
class gameObject : public gameNode
{
private:


public:
	gameObject();
	~gameObject();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

