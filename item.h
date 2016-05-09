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
	int buyPrice;	//�÷��̾ �� �� ����
	int sellPrice;	//�÷��̾ �� �� ����
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

	/*			�Լ� �߰�			*/
	void setItem(char* imageName, char* itemName, char* itemInfo, int atk, int intel, int def, int spd, int hit, int buy, int sell);
	vector<tagItem>& getVItem() { return _vItem; }
};

