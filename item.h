#pragma once
#include "gameNode.h"

struct tagItem
{
	image* image;
	RECT rc;
	char* name;
	char* info;
	int atk;
	int intel;
	int def;
	int spd;
	int hit;
	int buyPrice;	//플레이어가 살 때 가격
	int sellPrice;	//플레이어가 팔 때 가격
};


class item : public gameNode
{
private:
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

public:
	item();
	~item();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	void setItem(char* imageName, char* itemName, char* itemInfo, int atk, int intel, int def, int spd, int hit, int buy, int sell);
	vector<tagItem>& getVItem() { return _vItem; }
};

