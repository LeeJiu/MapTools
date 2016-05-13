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

	/*			함수 추가			*/
	virtual void keyControl();
	virtual void move();
	virtual void setImage();
	virtual void setFrame();

	virtual void setItem(tagItem item) = 0;
	virtual void setHell(int hell) = 0;

	virtual RECT getRect() { return _rc; }
	virtual int getHell() = 0;
};

