#pragma once
#include "gameNode.h"


class town : public gameNode
{
private:
	image* _town;		//마을 맵 이미지 (통짜 맵)


public:
	town();
	~town();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

