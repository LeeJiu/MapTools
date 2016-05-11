#pragma once
#include "gameObject.h"

class character : public gameObject
{
protected:
	image* _character;
	RECT _rc;
	char* _name;
	int _level, _counter, _mv, _jm;
	int _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next;	//ĳ���� �ɷ�ġ

public:
	character();
	virtual ~character();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/
	virtual void keyControl();
	virtual void move();
};

