#pragma once
#include "character.h"
#include "inventory.h"

class prinny : public character
{
private:
	inventory* _inventory;

	RECT _invenExit;

public:
	prinny();
	~prinny();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/
	void keyControl();
	void move();
	void setImage();
	void setFrame();
};

