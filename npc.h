#pragma once
#include "gameObject.h"

class npc : public gameObject
{
private:


public:
	npc();
	~npc();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

};

