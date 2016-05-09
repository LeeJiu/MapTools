#pragma once
#include "character.h"
class enemy : public character
{
private:


public:
	enemy();
	~enemy();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

