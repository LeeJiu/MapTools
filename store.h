#pragma once
#include "gameNode.h"
#include "item.h"

class store : public gameNode
{
private:
	item _item;

	//������ ������ ����� ���� �߰� (atk, def, int, spd ...)


	//ui rect
	RECT _rcStoreTitle, _rcListTitle;
	RECT _rcItemList;
	RECT _rcItemStatus;
	RECT _rcItemInfo;
	RECT _rcItemImage;

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

