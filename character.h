#pragma once
#include "gameObject.h"


class character : public gameObject
{
protected:
	/*image* _character;
	RECT _rc;
	int _x, _y;*/
	const char* _name;				//ĳ���� �̸�
	int _level, _counter, _mv, _jm;									//ĳ���� �ɷ�ġ 1
	int _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next;  //ĳ���� �ɷ�ġ 2
	//bool _isWeaponEquip;		//��� ��������
	bool _isUp, _isRight, isShow;

	CHARACTER_STATE _characterState;
	CHARACTER_DIRECTION _characterDir;
	//WEAPON_TYPE _weaponType;	//���� ���� Ÿ��
	
	int _curFrameX, _curFrameY, _count;

public:
	character();
	virtual ~character();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/
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

