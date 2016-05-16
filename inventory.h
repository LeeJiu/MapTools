#pragma once
#include "gameNode.h"
#include "item.h"

class inventory : public gameNode
{
private:
	item _item;
	bool _invenOpen;

	//캐릭터 정보 세팅
	const char* _name;
	string _hell;
	string _level, _counter, _mv, _jm;
	string _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next;

	//아이템 정보 세팅
	image* _itemImage;
	const char* _itemName;
	string _itmeAtk, _itemInt, _itemDef, _itemSpd, _itemHit, _itemRes, _itemPrice;
	

	//ui 위치 세팅
	RECT _rcStatus, _rcItemList, _rcItemInfo, _rcExit, _rcHell;
	
	//캐릭터 정보 글씨 위치 세팅
	RECT _rcName, _rcLevel, _rcCounter, _rcMv, _rcJm;
	RECT _rcHp, _rcSp, _rcAtk, _rcInt, _rcDef, _rcSpd, _rcHit, _rcRes, _rcExp, _rcNext;

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	void keyControl();
	void updateItemInfo(tagItem item);
	
	void showInventory();
	void showCharacterState();
	void showItemList();
	void showUI();
	void closeInventory();

	void setItem(const char* itemName);
	void setName(const char* name) { _name = name; }
	void setHell(int hell) { _hell = std::to_string(hell); };
	void setClassStates(int level, int counter, int mv, int jm);
	void setCharacterStates(int hp, int sp, int atk, int intel, int def,
		int spd, int hit, int res, int exp, int next);

	RECT getExit() { return _rcExit; }
	item* getItem() { return &_item; }
};

