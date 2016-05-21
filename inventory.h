#pragma once
#include "gameNode.h"
#include "item.h"

class inventory : public gameNode
{
private:
	item _item;
	bool _invenOpen;
	bool _isWear;
	bool _onItemButton;

	int _selectItemNum;

	//캐릭터 정보 세팅
	image* _icon;
	const char* _name;
	string _hell;
	string _level, _counter, _mv, _jm;
	string _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next, _weapon;

	//아이템 정보 세팅
	image* _itemImage;
	const char* _itemName;
	string _itemAtk, _itemInt, _itemDef, _itemSpd, _itemHit, _itemRes, _itemPrice;
	
	//ui 위치 세팅
	RECT _rcStatus, _rcItemList, _rcItemInfo, _rcExit, _rcHell, _rcNext, _rcEquip, _rcWeapon;

	//ui 변경되는 이미지
	image* _equip;
	
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
	void closeInventory();
	bool checkEquip();

	void setItem(const char* itemName, bool isWear);
	void setName(const char* name);
	void setHell(int hell) { _hell = std::to_string(hell); };
	void setClassStates(int level, int counter, int mv, int jm);
	void setCharacterStates(int hp, int sp, int atk, int intel, int def,
		int spd, int hit, int res, int exp, int next, WEAPON_TYPE weapon);
	void setEquip(bool isWear);

	RECT getExit() { return _rcExit; }
	RECT getNext() { return _rcNext; }
	item* getItem() { return &_item; }
	string getAtk() { return _atk; }
	string getInt() { return _int; }
	string getDef() { return _def; }
	string getSpd() { return _spd; }
	string getHit() { return _hit; }
	string getRes() { return _res; }
	string getWeapon() { return _weapon; }
};

