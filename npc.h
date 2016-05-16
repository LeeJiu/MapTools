#pragma once
#include "character.h"
class npc : public character
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

