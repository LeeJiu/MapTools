#pragma once
#include "character.h"

//const char* _character;
//RECT _rc;
//char _name[128];
//int _level, _counter, _mv, _jm;
//int _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next;
//bool _isWeaponEquip, _isArmorEquip, _isArtifactEquip, _isEtcEquip;

class characterDatabase : public singletonBase<database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	typedef map<string, character*> arrElement;
	typedef map<string, character*>::iterator iterElement;

private:
	arrElement _mTotalElement;

public:
	characterDatabase();
	~characterDatabase();

	HRESULT init();
	void release();

	void loadDatabase(string name);

	character* getElementData(string str) { return _mTotalElement.find(str)->second; }

	void setElementDataNumber(string str, int number);
	void setElementDataState(string str, int state);
	void setElementDataDrawX(string str, int drawX);
	void setElementDataDrawY(string str, int drawY);
	void setElementDataImageNum(string str, int imageNum);

};

