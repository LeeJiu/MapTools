#pragma once
#include "enemy.h"

class catsaver : public enemy
{
protected:
	bool _isUp, _isRight, _isShow;

	int _curFrameX, _curFrameY, _count;

public:
	catsaver();
	~catsaver();

	HRESULT init(int x, int y, vector<TagTile*>& tile);
	void release();
	void update();
	void render();
	virtual void setImage();
	virtual void setFrame();
	virtual void setMercenary(const char* characterName);

	virtual void setItem(const char* itemName, bool isWear);
	virtual int getHell();
	virtual void setHell(int hell);
};