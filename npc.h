#pragma once
<<<<<<< HEAD
#include "character.h"
class npc : public character
=======
#include "gameObject.h"

class npc : public gameObject
>>>>>>> refs/remotes/origin/development
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

