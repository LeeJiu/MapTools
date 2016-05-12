#pragma once
#include "gameNode.h"


class gameObject : public gameNode
{
protected:
	image* _character;
	RECT _rc;
	int _x, _y;

public:
	gameObject();
	~gameObject();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/
	virtual void keyControl();
	virtual void move();
	virtual void setImage();
	virtual void setFrame();

	virtual RECT getRect() { return _rc; }
};

