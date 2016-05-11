#include "stdafx.h"
#include "inventory.h"


inventory::inventory()
{
}


inventory::~inventory()
{
}

HRESULT inventory::init()
{
	_invenOpen = false;

	//인벤토리 이미지 추가
	IMAGEMANAGER->addImage("inven_ch_status", "image/ui/battle_ui_status.bmp", 300, 500, true, 0xff00ff);
	IMAGEMANAGER->addImage("inven_list", "image/ui/inventory_list.bmp", 250, 400, false, false);
	IMAGEMANAGER->addImage("inven_info", "image/ui/inventory_info.bmp", 350, 500, false, false);
	IMAGEMANAGER->addImage("inven_hell", "image/ui/inventory_hell.bmp", 250, 50, false, false);

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{
}

void inventory::render()
{
	Rectangle(getMemDC(), _rcStatus.left, _rcStatus.top, _rcStatus.right, _rcStatus.bottom);
	Rectangle(getMemDC(), _rcItemList.left, _rcItemList.top, _rcItemList.right, _rcItemList.bottom);
	Rectangle(getMemDC(), _rcItemInfo.left, _rcItemInfo.top, _rcItemInfo.right, _rcItemInfo.bottom);
	Rectangle(getMemDC(), _rcExit.left, _rcExit.top, _rcExit.right, _rcExit.bottom);
	Rectangle(getMemDC(), _rcHell.left, _rcHell.top, _rcHell.right, _rcHell.bottom);
	
	for (int i = 0; i < _item.getVItem().size(); ++i)
	{
		RECT rc = _item.getVItem()[i].rc;
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	}

	if (_invenOpen)
	{
		IMAGEMANAGER->findImage("inven_ch_status")->render(getMemDC(), _rcStatus.left, _rcStatus.top);
		IMAGEMANAGER->findImage("inven_list")->render(getMemDC(), _rcItemList.left, _rcItemList.top);
		IMAGEMANAGER->findImage("inven_info")->render(getMemDC(), _rcItemInfo.left, _rcItemInfo.top);
		IMAGEMANAGER->findImage("inven_hell")->render(getMemDC(), _rcHell.left, _rcHell.top);
	}
}

void inventory::showInventory()
{
	_invenOpen = true;

	//show inventory ui
	showUI();

	//update inventory/status
	showCharacterStatus();
	showItemList();
	showItemInfo();
}

void inventory::showCharacterStatus()
{
	//캐릭터 상태 받아오기
}

void inventory::showItemList()
{
	for (int i = 0; i < _item.getVItem().size(); ++i)
	{
		_item.getVItem()[i].rc = RectMake(_rcItemList.left + 20, (_rcItemList.top + 20) + (i * 50), 200, 50);
	}
}

void inventory::showItemInfo()
{
	//아이템 정보 받아오기
}

void inventory::showUI()
{
	/*			rect set			*/
	//ui
	_rcStatus = RectMake(100, 50, 300, 500);
	_rcItemList = RectMake(480, 50, 250, 400);
	_rcItemInfo = RectMake(810, 50, 350, 500);
	_rcExit = RectMake(WINSIZEX - 282, WINSIZEY - 115, 162, 65);
	_rcHell = RectMake(480, WINSIZEY - 220, 250, 50);

	//item list
	
}

void inventory::closeInventory()
{
	_invenOpen = false;

	/*			rect reset			*/
	_rcStatus = RectMake(0, 0, 0, 0);
	_rcItemList = RectMake(0, 0, 0, 0);
	_rcItemInfo = RectMake(0, 0, 0, 0);
	_rcExit = RectMake(0, 0, 0, 0);
	_rcHell = RectMake(0, 0, 0, 0);

	for (int i = 0; i < _item.getVItem().size(); ++i)
	{
		_item.getVItem()[i].rc = RectMake(0, 0, 0, 0);
	}
}

void inventory::setItem(vector<tagItem>& vItem, int arrNum)
{
	tagItem item = vItem[arrNum];
	_item.setItem(item.name, item.name, item.info, 
		item.atk, item.intel, item.def, item.spd, item.hit, item.res, 
		item.buyPrice, item.sellPrice);
}
