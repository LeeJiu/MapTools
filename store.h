#pragma once
#include "gameNode.h"
#include "item.h"

class store : public gameNode
{
private:
	item _item;

	//������ ������ ����� ���� �߰� (atk, def, int, spd ...)


public:
	store();
	~store();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/
	void showItemInfoAll();		//������ ����â ����
};

