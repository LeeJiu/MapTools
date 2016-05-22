#pragma once
#include "gameObject.h"

class enemy : public gameObject
{
protected:
	const char* _kind;
	RECT _rc;
	int _x, _y;

	int _idx;														// �̵��� vRoute���� ���� �ε���
	int _moveSpeed;


public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y, gameObjectManager* gom);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			�Լ� �߰�			*/

	virtual void setMercenary(const char* characterName) = 0;
	virtual void setItem(const char* itemName, bool isWear) = 0;
	virtual void setHell(int hell) = 0;
};

