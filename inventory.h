#pragma once
#include "gameNode.h"
#include "item.h"

class inventory : public gameNode
{
private:
	item _item;
	bool _invenOpen;

	//ui ��ġ ����
	RECT _rcStatus, _rcItemList, _rcItemInfo, _rcExit, _rcHell;

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/
	void showInventory();
	void showCharacterStatus();
	void showItemList();
	void showItemInfo();
	void showUI();

	void closeInventory();

	void setItem(vector<tagItem>& vItem, int arrNum);

	RECT getExit() { return _rcExit; }
};

