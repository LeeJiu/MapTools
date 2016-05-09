#pragma once
#include "gameNode.h"
class title : public gameNode
{
private:


public:
	title();
	~title();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

