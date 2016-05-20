#pragma once
#include "enemy.h"
class orc : public enemy
{
private:
	int _curFrameX, _curFrameY, _count;

public:
	orc();
	~orc();

	HRESULT init(int x, int y, vector<TagTile*> tile);
	void release();
	void update();
	void render();

	virtual void setMercenary(const char* characterName);

	virtual void setItem(const char* itemName, bool isWear);
	virtual int getHell();
	virtual void setHell(int hell);
};

