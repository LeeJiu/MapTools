#pragma once
#include "gameNode.h"
#include "item.h"
#include "prinny.h"

class store : public gameNode
{
private:
	item _item;

	//플레이어
	gameObject* _prinny;

	//아이템 정보를 띄워줄 변수 추가 (atk, def, int, spd ...)
	image* _itemImage;
	string _atk, _int, _def, _spd, _hit, _res, _price, _hell;
	const char* _name;
	char* _info;
	int _buyItemIdx;

	//아이템 정보 rect
	RECT _rcName, _rcAtk, _rcInt, _rcDef, _rcSpd, _rcHit, _rcRes, _rcPrice, _rcInfo, _rcHell;

	//ui rect
	RECT _rcStoreTitle, _rcListTitle, _rcExit;
	RECT _rcItemList;
	RECT _rcItemStatus;
	RECT _rcItemInfo;
	RECT _rcItemImage;
	RECT _rcBuy;

public:
	store();
	~store();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	void buyItem(const char* itemName);
	void keyControl();
	void showItemInfoAll(int arrNum);		//아이템 정보창 갱신
};

