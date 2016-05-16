#pragma once
#include "gameNode.h"
class selectStage : public gameNode
{
private:


public:
	selectStage();
	~selectStage();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

