#pragma once
#include "gameNode.h"
#include "item.h"

class store : public gameNode
{
private:
	item _item;

	//아이템 정보를 띄워줄 변수 추가 (atk, def, int, spd ...)


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

	/*			함수 추가			*/
	void showItemInfoAll();		//아이템 정보창 갱신
};

