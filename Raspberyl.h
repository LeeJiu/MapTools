#pragma once
#include "character.h"
class Raspberyl : public character
{
public:
	Raspberyl();
	~Raspberyl();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void move(int endX, int endY);
	virtual void setImage();
	virtual void setFrame();
};

