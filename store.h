#pragma once
#include "gameNode.h"
#include "item.h"
#include "prinny.h"

class store : public gameNode
{
private:
	item _item;

	//�÷��̾�
	gameObject* _prinny;

	//������ ������ ����� ���� �߰� (atk, def, int, spd ...)
	image* _itemImage;
	string _atk, _int, _def, _spd, _hit, _res, _price, _hell;
	const char* _name;
	char* _info;
	int _buyItemIdx;

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
	void buyItem(const char* itemName);
	void keyControl();
	void showItemInfoAll(int arrNum);		//������ ����â ����
};

