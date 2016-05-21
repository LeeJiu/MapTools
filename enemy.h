#pragma once
#include "gameObject.h"

class enemy : public gameObject
{
protected:
	const char* _kind;
	//int _hp, _sp, _atk, _def, _spd, _hit, _res;
	//image* _enemy;
	RECT _rc;
	int _x, _y;

	//int _indexX, _indexY;

	int _idx;														// �̵��� vRoute���� ���� �ε���
	int _moveSpeed;


public:
	enemy();
	~enemy();

	//virtual HRESULT init();
	virtual HRESULT init(int x, int y, vector<TagTile*>& tile);
	virtual HRESULT init(int x, int y, gameObjectManager* gom);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			�Լ� �߰�			*/

	virtual void setMercenary(const char* characterName) = 0;
	virtual void setItem(const char* itemName, bool isWear) = 0;
	virtual void setHell(int hell) = 0;
};

