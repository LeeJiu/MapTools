#pragma once
#include "gameNode.h"
<<<<<<< HEAD
class item : public gameNode
{
private:
=======

class item : public gameNode
{
private:
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;
>>>>>>> refs/remotes/origin/development


public:
	item();
	~item();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
<<<<<<< HEAD

=======
	void setItem(const char* imageName/*, char* itemName, char* itemInfo, 
		int atk, int intel, int def, int spd, int hit, int res, int buy, int sell*/);
	vector<tagItem>& getVItem() { return _vItem; }
>>>>>>> refs/remotes/origin/development
};

