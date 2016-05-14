#pragma once
#include "gameObject.h"
class enemy : public gameObject
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

