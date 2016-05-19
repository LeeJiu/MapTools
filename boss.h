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

	virtual void previousState();							// �������� ���ư��� �Լ�
	virtual void showPossibleMoveTile();				// �̵������� Ÿ�� �����ִ� �Լ�

	virtual void setItem(const char* itemName);
	virtual int getHell();
	virtual void setHell(int hell);
};
