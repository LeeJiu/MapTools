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

	/*			�Լ� �߰�			*/

	virtual void previousState() = 0;								// �������� ���ư��� �Լ�
	virtual void showPossibleMoveTile() = 0;						// �̵������� Ÿ�� �����ִ� �Լ�

	virtual void setItem(const char* itemName) = 0;
	virtual void setHell(int hell) = 0;
};

