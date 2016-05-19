#pragma once
#include "gameObject.h"
class enemy : public gameObject
{
private:

protected:
	const char* _kind;
	int _hp, _sp, _atk, _def, _spd, _hit, _res;

	image* _enemy;
	RECT _rc;
	int _x, _y;
	int _indexX, _indexY;

	int _idx;														// 이동시 vRoute에서 사용될 인덱스
	int _moveSpeed;


public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	/*			함수 추가			*/

	virtual void previousState() = 0;								// 이전으로 돌아가는 함수
	virtual void showPossibleMoveTile() = 0;						// 이동가능한 타일 보여주는 함수

	virtual void setItem(const char* itemName) = 0;
	virtual void setHell(int hell) = 0;
};

