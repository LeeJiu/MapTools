#pragma once
#include "gameObject.h"

enum WEAPON_TYPE
{
	WEAPON_NONE, WEAPON_SWORD, WEAPON_WAND, WEAPON_STAFT, WEAPON_BOW
};

class character : public gameObject
{
protected:
	int _next;  //캐릭터 능력치 2
	//bool _isWeaponEquip;		//장비 장착여부
	bool _isUp, _isRight, _isShow;

	CHARACTER_STATE _characterState;
	CHARACTER_DIRECTION _characterDir;
	//WEAPON_TYPE _weaponType;	//장착 무기 타입
	
	int _curFrameX, _curFrameY, _count;

public:
	character();
	virtual ~character();

	virtual HRESULT init();
	virtual HRESULT init(vector<TagTile*> tile);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			함수 추가			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void move(int endX, int endY);
	virtual void setImage();
	virtual void setFrame();
	virtual void previousState();								// 이전으로 돌아가는 함수
	virtual void showPossibleMoveTile();						// 이동가능한 타일 보여주는 함수

	virtual void saveData();
	virtual void loadData();

	virtual void setIsShow(bool isShow) { _isShow = isShow; }
	virtual void setItem(const char* itemName) = 0;
	virtual void setMercenary(const char* characterName) = 0;
	virtual void setHell(int hell) = 0;

	virtual int getExp() { return _next; }
	virtual RECT getRect() { return _rc; }
	virtual int getHell() = 0;
};

