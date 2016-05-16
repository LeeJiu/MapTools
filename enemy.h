#pragma once
#include "gameObject.h"
class enemy : public gameObject
{
private:


public:
	enemy();
	~enemy();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/

	virtual void previousState() = 0;								// 이전으로 돌아가는 함수
	virtual void showPossibleMoveTile() = 0;						// 이동가능한 타일 보여주는 함수

	virtual void setItem(const char* itemName) = 0;
	virtual void setHell(int hell) = 0;
};

