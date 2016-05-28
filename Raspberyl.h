#pragma once
#include "character.h"
class raspberyl : public character
{
	float _volume;
public:
	raspberyl();
	~raspberyl();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y, gameObjectManager* gom);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			�Լ� �߰�			*/
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

