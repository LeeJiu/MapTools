#pragma once
#include "gameNode.h"

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
	void setItem(const char* imageName);
	vector<tagItem>& getVItem() { return _vItem; }
};

