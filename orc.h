#pragma once
#include "enemy.h"
class orc : public enemy
{
protected:
	bool _isUp, _isRight, _isShow;

	int _curFrameX, _curFrameY, _count;

public:
	orc();
	~orc();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void previousState();							// �������� ���ư��� �Լ�
	virtual void showPossibleMoveTile();				// �̵������� Ÿ�� �����ִ� �Լ�

	virtual void setItem(const char* itemName);
	virtual int getHell();
	virtual void setHell(int hell);
};

