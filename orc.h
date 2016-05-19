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

	HRESULT init(int x, int y, vector<TagTile*> tile);
	void release();
	void update();
	void render();

	virtual void setMercenary(const char* characterName);

	virtual void setItem(const char* itemName);
	virtual int getHell();
	virtual void setHell(int hell);
};

