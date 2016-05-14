#pragma once
#include "gameObject.h"


class character : public gameObject
{
protected:
	/*image* _character;
	RECT _rc;
	int _x, _y;*/
	const char* _name;				//캐릭터 이름
	int _level, _counter, _mv, _jm;									//캐릭터 능력치 1
	int _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next;  //캐릭터 능력치 2
	//bool _isWeaponEquip;		//장비 장착여부
	bool _isUp, _isRight, isShow;

	CHARACTER_STATE _characterState;
	CHARACTER_DIRECTION _characterDir;
	//WEAPON_TYPE _weaponType;	//장착 무기 타입
	
	int _curFrameX, _curFrameY, _count;

public:
	character();
	virtual ~character();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void move(int endX, int endY);
	virtual void setImage();
	virtual void setFrame();

	virtual void saveData();
	virtual void loadData();

	virtual void setItem(const char* itemName) = 0;
	virtual void setHell(int hell) = 0;

	virtual RECT getRect() { return _rc; }
	virtual int getHell() = 0;
};

