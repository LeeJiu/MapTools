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
	IMAGEMANAGER->addImage("inven_info", "image/ui/inventory_info.bmp", 350, 556, false, false);
	IMAGEMANAGER->addImage("inven_hell", "image/ui/inventory_hell.bmp", 250, 50, false, false);
	IMAGEMANAGER->addImage("inven_exit", "image/ui/store_exit.bmp", 162, 65, false, false);
	IMAGEMANAGER->addImage("none", "image/item/none.bmp", 256, 256, true, 0xff00ff);

	_itemImage = IMAGEMANAGER->findImage("none");

	return S_OK;
}

void inventory::release()
{
	_item.getVItem().clear();
}

void inventory::update()
{
	keyControl();
}

void inventory::render()
{
	if (_invenOpen)
	{
		IMAGEMANAGER->findImage("inven_ch_status")->render(getMemDC(), _rcStatus.left, _rcStatus.top);
		IMAGEMANAGER->findImage("inven_list")->render(getMemDC(), _rcItemList.left, _rcItemList.top);
		IMAGEMANAGER->findImage("inven_info")->render(getMemDC(), _rcItemInfo.left, _rcItemInfo.top);
		IMAGEMANAGER->findImage("inven_hell")->render(getMemDC(), _rcHell.left, _rcHell.top);
		IMAGEMANAGER->findImage("inven_exit")->render(getMemDC(), _rcExit.left, _rcExit.top);

		_itemImage->render(getMemDC(), _rcItemInfo.left + 47, _rcItemInfo.bottom - 256);

		HFONT font, oldFont;
		font = CreateFont(25, 0, 0, 0, 800, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
		oldFont = (HFONT)SelectObject(getMemDC(), font);

		//캐릭터 정보
		DrawText(getMemDC(), _name, -1, &_rcName, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _level.c_str(), -1, &_rcLevel, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _counter.c_str(), -1, &_rcCounter, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _mv.c_str(), -1, &_rcMv, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _jm.c_str(), -1, &_rcJm, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _hp.c_str(), -1, &_rcHp, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _sp.c_str(), -1, &_rcSp, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _atk.c_str(), -1, &_rcAtk, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _int.c_str(), -1, &_rcInt, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _def.c_str(), -1, &_rcDef, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _spd.c_str(), -1, &_rcSpd, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _hit.c_str(), -1, &_rcHit, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _res.c_str(), -1, &_rcRes, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _exp.c_str(), -1, &_rcExp, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _next.c_str(), -1, &_rcNext, DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _hell.c_str(), -1, 
			&RectMake(_rcHell.left + 20, _rcHell.top + 10, 180, 50), DT_RIGHT | DT_VCENTER);

		//아이템 목록
		int size = _item.getVItem().size();
		for (int i = 0; i < size; ++i)
		{
			RECT rc = _item.getVItem()[i].rc;
			DrawText(getMemDC(), _item.getVItem()[i].name, -1, &rc, DT_LEFT | DT_VCENTER);
		}

		//아이템 정보
		DrawText(getMemDC(), _itemName, -1, 
			&RectMake(_rcItemInfo.left + 25, _rcItemInfo.top + 20, 100, 30), DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _itmeAtk.c_str(), -1, 
			&RectMake(_rcItemInfo.left + 100, _rcItemInfo.top + 75, 100, 30), DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _itemInt.c_str(), -1, 
			&RectMake(_rcItemInfo.left + 100, _rcItemInfo.top + 110, 100, 30), DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _itemDef.c_str(), -1, 
			&RectMake(_rcItemInfo.left + 100, _rcItemInfo.top + 140, 100, 30), DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _itemSpd.c_str(), -1, 
			&RectMake(_rcItemInfo.left + 100, _rcItemInfo.top + 175, 100, 30), DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _itemHit.c_str(), -1, 
			&RectMake(_rcItemInfo.left + 100, _rcItemInfo.top + 205, 100, 30), DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _itemRes.c_str(), -1, 
			&RectMake(_rcItemInfo.left + 100, _rcItemInfo.top + 235, 100, 30), DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _itemPrice.c_str(), -1, 
			&RectMake(_rcItemInfo.left + 100, _rcItemInfo.top + 267, 100, 30), DT_LEFT | DT_VCENTER);

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
	}
}

void inventory::keyControl()
{
	int size = _item.getVItem().size();
	for (int i = 0; i < size; ++i)
	{
		RECT rc = _item.getVItem()[i].rc;
		if (PtInRect(&rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				updateItemInfo(_item.getVItem()[i]);
				break;
			}
		}
	}
}

void inventory::showInventory()
{
	_invenOpen = true;

	//show inventory ui
	showUI();
	//showCharacterState();
	//showItemList();
}

void inventory::showCharacterState()
{
	
}

void inventory::showItemList()
{
	

}

void inventory::updateItemInfo(tagItem item)
{
	//아이템 정보 갱신
	_itemName = item.name;
	_itmeAtk = std::to_string(item.atk);
	_itemInt = std::to_string(item.intel);
	_itemDef = std::to_string(item.def);
	_itemSpd = std::to_string(item.spd);
	_itemHit = std::to_string(item.hit);
	_itemRes = std::to_string(item.res);
	_itemPrice = std::to_string(item.sellPrice);

	_itemImage = IMAGEMANAGER->findImage(_itemName);
}

void inventory::showUI()
{
	/*			 ui rect set			*/
	_rcStatus = RectMake(100, 50, 300, 500);
	_rcItemList = RectMake(480, 50, 250, 400);
	_rcItemInfo = RectMake(810, 50, 350, 556);
	_rcExit = RectMake(WINSIZEX - 282, WINSIZEY - 110, 162, 65);
	_rcHell = RectMake(480, WINSIZEY - 220, 250, 50);

	/*			character states rect set			*/
	_rcName = RectMake(120, 70, 200, 30);
	_rcLevel = RectMake(260, 145, 100, 30);
	_rcCounter = RectMake(310, 170, 50, 30);
	_rcMv = RectMake(260, 195, 50, 30);
	_rcJm = RectMake(330, 195, 50, 30);
	_rcHp = RectMake(170, 240, 50, 30);
	_rcSp = RectMake(170, 265, 50, 30);
	_rcAtk = RectMake(170, 285, 50, 30);
	_rcInt = RectMake(300, 285, 50, 30);
	_rcDef = RectMake(170, 307, 50, 30);
	_rcSpd = RectMake(300, 307, 50, 30);
	_rcHit = RectMake(170, 330, 50, 30);
	_rcRes = RectMake(300, 330, 50, 30);
	_rcExp = RectMake(170, 350, 50, 30);
	_rcNext = RectMake(170, 373, 50, 30);

	/*			item list rect set			*/
	int size = _item.getVItem().size();
	for (int i = 0; i < size; ++i)
	{
		_item.getVItem()[i].rc = RectMake(_rcItemList.left + 20, (_rcItemList.top + 40) + (i * 50), 200, 50);
	}
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

	int size = _item.getVItem().size();
	for (int i = 0; i < size; ++i)
	{
		_item.getVItem()[i].rc = RectMake(0, 0, 0, 0);
	}
}

void inventory::setItem(const char* itemName)
{
	_item.setItem(itemName);
}

void inventory::setClassStates(int level, int counter, int mv, int jm)
{
	_level = std::to_string(level);
	_counter = std::to_string(counter);
	_mv = std::to_string(mv);
	_jm = std::to_string(jm);
}

void inventory::setCharacterStates(int hp, int sp, int atk, int intel, int def, int spd, int hit, int res, int exp, int next)
{
	_hp = std::to_string(hp);
	_sp = std::to_string(sp);
	_atk = std::to_string(atk);
	_int = std::to_string(intel);
	_def = std::to_string(def);
	_spd = std::to_string(spd);
	_hit = std::to_string(hit);
	_res = std::to_string(res);
	_exp = std::to_string(exp);
	_next = std::to_string(next);
}
