#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init()
{
<<<<<<< HEAD
	return E_NOTIMPL;
=======
	
	return S_OK;
>>>>>>> refs/remotes/origin/development
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{
}
<<<<<<< HEAD
=======

void item::setItem(char * imageName, char * itemName, char * itemInfo, 
	int atk, int intel, int def, int spd, int hit, int res, int buy, int sell)
{
	tagItem item;
	ZeroMemory(&item, sizeof(tagItem));
	item.image = IMAGEMANAGER->findImage(imageName);
	item.name = itemName;
	item.info = itemInfo;
	item.atk = atk;
	item.intel = intel;
	item.def = def;
	item.spd = spd;
	item.hit = hit;
	item.res = res;
	item.buyPrice = buy;
	item.sellPrice = sell;

	_vItem.push_back(item);
}
>>>>>>> refs/remotes/origin/development
