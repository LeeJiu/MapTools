#pragma once
#include "character.h"
class player : public character
{
private:


public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

