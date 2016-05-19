#pragma once
#include "character.h"
class raspberyl : public character
{
public:
	raspberyl();
	~raspberyl();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y, vector<TagTile*> tile);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			함수 추가			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void setImage();
	virtual void setFrame();

	virtual void saveData();
	virtual void loadData();

	virtual void setItem(const char* itemName, bool isWear);
	virtual void setMercenary(const char* characterName);
	virtual void setHell(int hell);
	virtual int getHell();

	virtual RECT getRect() { return _rc; }
};

