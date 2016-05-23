#pragma once
#include "gameObject.h"

class enemy : public gameObject
{
public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y, gameObjectManager* gom);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			함수 추가			*/

	virtual void setMercenary(const char* characterName) = 0;
	virtual void setItem(const char* itemName, bool isWear) = 0;
	virtual void setHell(int hell) = 0;
};

