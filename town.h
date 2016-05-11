#pragma once
#include "gameNode.h"
#include "inventory.h"

class town : public gameNode
{
private:
	image* _town;		//���� �� �̹��� (��¥ ��)
	inventory* _inventory;

	RECT _invenExit;

public:
	town();
	~town();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/
	void keyControl();
};

