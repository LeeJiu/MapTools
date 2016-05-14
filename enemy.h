#pragma once
<<<<<<< HEAD
#include "character.h"
class enemy : public character
=======
#include "gameObject.h"
class enemy : public gameObject
>>>>>>> refs/remotes/origin/development
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

