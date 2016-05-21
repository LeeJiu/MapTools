#pragma once
#include "enemy.h"

class orc : public enemy
{
private:
	int _curFrameX, _curFrameY;

public:
	orc();
	~orc();

	virtual HRESULT init(int x, int y, vector<TagTile*>& tile);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void setImage();
	virtual void setFrame();
	virtual void setMercenary(const char* characterName);
	virtual void setItem(const char* itemName, bool isWear);
	virtual int getHell();
	virtual void setHell(int hell);
};

