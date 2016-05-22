#pragma once
#include "gameObject.h"



class character : public gameObject
{
protected:
	int _next;				//ĳ���� �ɷ�ġ 2
	bool _isWeaponEquip;	//��� ��������

	WEAPON_TYPE _equipWeapon;	//���� ���� Ÿ��
	
	float _pivotY;

public:
	character();
	virtual ~character();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y, gameObjectManager* gom);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			�Լ� �߰�			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void move(int endX, int endY);
	virtual void setImage();
	virtual void previousState();								// �������� ���ư��� �Լ�

	virtual void saveData();
	virtual void loadData();

	virtual void setItem(const char* itemName, bool isWear) = 0;
	virtual void setMercenary(const char* characterName) = 0;
	virtual void setHell(int hell) = 0;

	virtual int getExp() { return _next; }
	virtual RECT getRect() { return _rc; }
	virtual int getHell() = 0;
};

