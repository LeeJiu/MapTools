#pragma once
#include "enemy.h"

class boss : public enemy
{
public:
	boss();
	~boss();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void previousState();							// 이전으로 돌아가는 함수
	virtual void showPossibleMoveTile();				// 이동가능한 타일 보여주는 함수

	virtual void setItem(const char* itemName, bool isWear);
	virtual int getHell();
	virtual void setHell(int hell);
};

