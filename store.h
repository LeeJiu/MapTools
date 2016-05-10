#pragma once
#include "gameNode.h"
#include "item.h"

class store : public gameNode
{
private:
	item _item;

	//������ ������ ����� ���� �߰� (atk, def, int, spd ...)
	image* _itemImage;
	string _atk, _int, _def, _spd, _hit, _res, _price;
	char* _name;
	char* _info;

	//������ ���� rect
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

	/*			�Լ� �߰�			*/
	void keyControl();
	void showItemInfoAll(int arrNum);		//������ ����â ����
};

