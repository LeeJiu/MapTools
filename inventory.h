#pragma once
#include "gameNode.h"
<<<<<<< HEAD
class inventory : public gameNode
{
private:

=======
#include "item.h"

class inventory : public gameNode
{
private:
	item _item;
	bool _invenOpen;

	//ĳ���� ���� ����
	char* _name;
	string _hell;
	string _level, _counter, _mv, _jm;
	string _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next;

	//������ ���� ����
	image* _itemImage;
	char* _itemName;
	string _itmeAtk, _itemInt, _itemDef, _itemSpd, _itemHit, _itemRes, _itemPrice;
	

	//ui ��ġ ����
	RECT _rcStatus, _rcItemList, _rcItemInfo, _rcExit, _rcHell;
	
	//ĳ���� ���� �۾� ��ġ ����
	RECT _rcName, _rcLevel, _rcCounter, _rcMv, _rcJm;
	RECT _rcHp, _rcSp, _rcAtk, _rcInt, _rcDef, _rcSpd, _rcHit, _rcRes, _rcExp, _rcNext;

	
>>>>>>> refs/remotes/origin/development

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/
<<<<<<< HEAD

=======
	void keyControl();
	void updateItemInfo(tagItem item);
	
	void showInventory();
	void showCharacterState();
	void showItemList();
	void showUI();
	void closeInventory();

	void setItem(tagItem item);
	void setName(char* name) { _name = name; }
	void setHell(int hell) { _hell = std::to_string(hell); };
	void setClassStates(int level, int counter, int mv, int jm);
	void setCharacterStates(int hp, int sp, int atk, int intel, int def,
		int spd, int hit, int res, int exp, int next);

	RECT getExit() { return _rcExit; }
>>>>>>> refs/remotes/origin/development
};

