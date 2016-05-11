#pragma once
#include "gameNode.h"
#include "inventory.h"

class town : public gameNode
{
private:
	image* _town;		//마을 맵 이미지 (통짜 맵)
	inventory* _inventory;

	RECT _invenExit;

public:
	town();
	~town();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	void keyControl();
};

