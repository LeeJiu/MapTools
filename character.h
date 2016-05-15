#pragma once
#include "gameObject.h"

enum WEAPON_TYPE
{
	WEAPON_NONE, WEAPON_SWORD, WEAPON_WAND, WEAPON_STAFT, WEAPON_BOW
};

class character : public gameObject
{
protected:
	
	int _next;  //ĳ���� �ɷ�ġ 2
	//bool _isWeaponEquip;		//��� ��������
	bool _isUp, _isRight, _isShow;

	CHARACTER_STATE _characterState;
	CHARACTER_DIRECTION _characterDir;
	//WEAPON_TYPE _weaponType;	//���� ���� Ÿ��
	
	int _curFrameX, _curFrameY, _count;

public:
	character();
	virtual ~character();

	virtual HRESULT init();
	virtual HRESULT init(vector<TagTile*>& tile);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			�Լ� �߰�			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void move(int endX, int endY);
	virtual void setImage();
	virtual void setFrame();
	virtual void previousState();								// �������� ���ư��� �Լ�
	virtual void showPossibleMoveTile();						// �̵������� Ÿ�� �����ִ� �Լ�

	virtual void saveData();
	virtual void loadData();

	virtual void setIsShow(bool isShow) { _isShow = isShow; }
	virtual void setItem(const char* itemName) = 0;
	virtual void setHell(int hell) = 0;

	virtual int getExp() { return _next; }
	virtual RECT getRect() { return _rc; }
	virtual int getHell() = 0;
};

