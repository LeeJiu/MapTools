#pragma once
#include "character.h"
#include "inventory.h"

class prinny : public character
{
private:
	int _hell;

	inventory* _inventory;

	RECT _invenExit;

public:
	prinny();
	~prinny();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	void keyControl();
	void move();
	void setImage();
	void setFrame();

	void setItem(tagItem item);
	void setHell(int hell) { _hell = hell; }

	int getHell() { return _hell; }
};

