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
	return S_OK;
}

void item::release()
{
	_vItem.clear();
}

void item::update()
{
}

void item::render()
{
}

void item::setItem(const char * imageName, bool isWear)
{
	tagItem item;
	if (strcmp(imageName, "sword") == 0)
	{
		ZeroMemory(&item, sizeof(tagItem));
		item.image = IMAGEMANAGER->findImage("sword");
		item.name = "sword";
		item.info = "검이다";
		item.atk = 100;
		item.intel = 0;
		item.def = 0;
		item.spd = 0;
		item.hit = 0;
		item.res = 0;
		item.buyPrice = 100;
		item.sellPrice = 10;
		item.isWear = isWear;
		item.type = SWORD;
	}
	else if (strcmp(imageName, "staff") == 0)
	{
		ZeroMemory(&item, sizeof(tagItem));
		item.image = IMAGEMANAGER->findImage("staff");
		item.name = "staff";
		item.info = "스태프다";
		item.atk = 0;
		item.intel = 100;
		item.def = 0;
		item.spd = 0;
		item.hit = 0;
		item.res = 0;
		item.buyPrice = 150;
		item.sellPrice = 15;
		item.isWear = isWear;
		item.type = STAFF;
	}
	else if (strcmp(imageName, "wand") == 0)
	{
		ZeroMemory(&item, sizeof(tagItem));
		item.image = IMAGEMANAGER->findImage("wand");
		item.name = "wand";
		item.info = "완드다";
		item.atk = 0;
		item.intel = 100;
		item.def = 0;
		item.spd = 0;
		item.hit = 50;
		item.res = 0;
		item.buyPrice = 160;
		item.sellPrice = 16;
		item.isWear = isWear;
		item.type = WAND;
	}
	else if (strcmp(imageName, "bow") == 0)
	{
		ZeroMemory(&item, sizeof(tagItem));
		item.image = IMAGEMANAGER->findImage("bow");
		item.name = "bow";
		item.info = "활이다";
		item.atk = 0;
		item.intel = 0;
		item.def = 0;
		item.spd = 50;
		item.hit = 130;
		item.res = 0;
		item.buyPrice = 130;
		item.sellPrice = 13;
		item.isWear = isWear;
		item.type = BOW;
	}

	_vItem.push_back(item);
}

void item::removeItem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}
