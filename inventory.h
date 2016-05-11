#pragma once
#include "gameNode.h"
#include "item.h"

class inventory : public gameNode
{
private:
	item _item;
	bool _invenOpen;

	//ui 위치 세팅
	RECT _rcStatus, _rcItemList, _rcItemInfo, _rcExit, _rcHell;

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	void showInventory();
	void showCharacterStatus();
	void showItemList();
	void showItemInfo();
	void showUI();

	void closeInventory();

	void setItem(vector<tagItem>& vItem, int arrNum);

	RECT getExit() { return _rcExit; }
};

