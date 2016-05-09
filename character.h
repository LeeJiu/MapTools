#pragma once
#include "gameObject.h"
class character : public gameObject
{
private:


public:
	character();
	virtual ~character();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

