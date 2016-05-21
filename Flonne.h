#pragma once
#include "character.h"
class flonne : public character
{
public:
	flonne();
	~flonne();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y, vector<TagTile*>& tile);
	virtual HRESULT init(int x, int y, gameObjectManager* gom);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			함수 추가			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void setImage();

	virtual void saveData();
	virtual void loadData();

	virtual void setItem(const char* itemName, bool isWear);
	virtual void setMercenary(const char* characterName);
	virtual void setHell(int hell);
	virtual int getHell();

	virtual RECT getRect() { return _rc; }
};

