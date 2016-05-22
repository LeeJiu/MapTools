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
	IMAGEMANAGER->addImage("inven_ch_status", "image/ui/ui_status.bmp", 300, 500, true, 0xff00ff);
	IMAGEMANAGER->addImage("inven_list", "image/ui/inventory_list.bmp", 250, 400, false, false);
	IMAGEMANAGER->addImage("inven_info", "image/ui/inventory_info.bmp", 350, 556, false, false);
	IMAGEMANAGER->addImage("inven_hell", "image/ui/inventory_hell.bmp", 250, 50, false, false);
	IMAGEMANAGER->addImage("inven_exit", "image/ui/store_exit.bmp", 162, 65, false, false);
	IMAGEMANAGER->addImage("inven_next", "image/ui/inventory_next.bmp", 162, 65, false, false);
	IMAGEMANAGER->addImage("inven_equip", "image/ui/inventory_equip.bmp", 162, 65, false, false);
	IMAGEMANAGER->addImage("inven_takeoff", "image/ui/inventory_takeoff.bmp", 162, 65, false, false);
	IMAGEMANAGER->addImage("none", "image/item/none.bmp", 256, 256, true, 0xff00ff);

	_itemImage = IMAGEMANAGER->findImage("none");
	_equip = IMAGEMANAGER->findImage("none");
	_icon = IMAGEMANAGER->findImage("prinny_icon");

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
		_icon->render(getMemDC(), _rcStatus.left + 5, _rcStatus.top + 67);

		IMAGEMANAGER->findImage("inven_ch_status")->render(getMemDC(), _rcStatus.left, _rcStatus.top);
		IMAGEMANAGER->findImage("inven_list")->render(getMemDC(), _rcItemList.left, _rcItemList.top);
		IMAGEMANAGER->findImage("inven_info")->render(getMemDC(), _rcItemInfo.left, _rcItemInfo.top);
		IMAGEMANAGER->findImage("inven_hell")->render(getMemDC(), _rcHell.left, _rcHell.top);
		IMAGEMANAGER->findImage("inven_exit")->render(getMemDC(), _rcExit.left, _rcExit.top);
		IMAGEMANAGER->findImage("inven_next")->render(getMemDC(), _rcNext.left, _rcNext.top);

		if (_onItemButton)
			_equip->render(getMemDC(), _rcEquip.left, _rcEquip.top);
		
		_itemImage->render(getMemDC(), _rcItemInfo.left + 47, _rcItemInfo.bottom - 256);

		HFONT font, oldFont;
		font = CreateFont(25, 0, 0, 0, 800, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
		oldFont = (HFONT)SelectObject(getMemDC(), font);

		//캐릭터 정보
		DrawText(getMemDC(), _name, -1, 
			&RectMake(_rcStatus.left + 20, _rcStatus.top + 20, 200, 30), DT_LEFT | DT_VCENTER);
		DrawText(getMemDC(), _level.c_str(), -1, 
			&RectMake(_rcStatus.left + 160, _rcStatus.top + 95, 100, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _counter.c_str(), -1, 
			&RectMake(_rcStatus.left + 210, _rcStatus.top + 120, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _mv.c_str(), -1, 
			&RectMake(_rcStatus.left + 160, _rcStatus.top + 145, 30, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _jm.c_str(), -1, 
			&RectMake(_rcStatus.left + 230, _rcStatus.top + 145, 30, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _hp.c_str(), -1, 
			&RectMake(_rcStatus.left + 70, _rcStatus.top + 190, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _sp.c_str(), -1, 
			&RectMake(_rcStatus.left + 70, _rcStatus.top + 215, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _atk.c_str(), -1, 
			&RectMake(_rcStatus.left + 70, _rcStatus.top + 235, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _int.c_str(), -1, 
			&RectMake(_rcStatus.left + 200, _rcStatus.top + 235, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _def.c_str(), -1, 
			&RectMake(_rcStatus.left + 70, _rcStatus.top + 257, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _spd.c_str(), -1, 
			&RectMake(_rcStatus.left + 200, _rcStatus.top + 257, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _hit.c_str(), -1, 
			&RectMake(_rcStatus.left + 70, _rcStatus.top + 280, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _res.c_str(), -1, 
			&RectMake(_rcStatus.left + 200, _rcStatus.top + 280, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _exp.c_str(), -1, 
			&RectMake(_rcStatus.left + 70, _rcStatus.top + 300, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _next.c_str(), -1, 
			&RectMake(_rcStatus.left + 70, _rcStatus.top + 323, 50, 30), DT_RIGHT | DT_VCENTER);
		DrawText(getMemDC(), _weapon.c_str(), -1,
			&_rcWeapon, DT_LEFT | DT_VCENTER);
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
		DrawText(getMemDC(), _itemAtk.c_str(), -1,
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
				if (!_item.getVItem()[i].isWear && !_isWear)
				{
					SOUNDMANAGER->play("click", 1.f);

					_onItemButton = true;		//버튼 그린다.
					_equip = IMAGEMANAGER->findImage("inven_equip");

					_selectItemNum = i;
					updateItemInfo(_item.getVItem()[_selectItemNum]);
					break;
				}
			}
		}
	}

	if (PtInRect(&_rcEquip, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (!_isWear && _onItemButton)
			{
				//장착 불가능 하면 아무것도 안 한다.
				if (!checkEquip())
				{
					SOUNDMANAGER->play("ban", 1.f);
					return;
				}

				_onItemButton = false;		//버튼 안 그린다.
				
				_item.getVItem()[_selectItemNum].isWear = true;
				_isWear = _item.getVItem()[_selectItemNum].isWear;
				//현재 캐릭터의 장비 상태를 변경한다.

				SOUNDMANAGER->play("equip", 1.f);

				setEquip(_isWear);
				//착용한 아이템을 목록에서 삭제한다.
				_item.removeItem(_selectItemNum);
				if (_item.getVItem().size() <= 0) return;

				updateItemInfo(_item.getVItem().front());
			}
			else if (_isWear && _onItemButton)
			{
				_onItemButton = false;		//버튼 안 그린다.

				//착용했던 장비를 아이템 목록에 추가한다.
				_item.setItem(_weapon.c_str(), false);

				SOUNDMANAGER->play("equip", 1.f);

				_isWear = _item.getVItem().back().isWear;

				//현재 캐릭터의 장비 상태를 변경한다.
				setEquip(_isWear);
				updateItemInfo(_item.getVItem().back());
			}
		}
	}

	if (PtInRect(&_rcWeapon, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_isWear && !_onItemButton)
			{
				if (strcmp(_weapon.c_str(), "nothing") == 0) return;

				_onItemButton = true;		//버튼 그린다.
				_equip = IMAGEMANAGER->findImage("inven_takeoff");
			}
		}
	}
}

void inventory::showInventory()
{
	_invenOpen = true;

	/*			 ui rect set			*/
	_rcStatus = RectMake(100, 50, 300, 500);
	_rcItemList = RectMake(480, 50, 250, 400);
	_rcItemInfo = RectMake(810, 50, 350, 556);
	_rcExit = RectMake(WINSIZEX - 282, WINSIZEY - 110, 162, 65);
	_rcHell = RectMake(480, WINSIZEY - 220, 250, 50);
	_rcNext = RectMake(100, WINSIZEY - 110, 162, 65);
	_rcEquip = RectMake(CENTERX - 81, WINSIZEY - 110, 162, 65);
	_rcWeapon = RectMake(120, 430, 200, 30);

	/*			item list rect set			*/
	int size = _item.getVItem().size();
	for (int i = 0; i < size; ++i)
	{
		_item.getVItem()[i].rc = RectMake(_rcItemList.left + 20, (_rcItemList.top + 40) + (i * 50), 200, 50);
	}
}

void inventory::updateItemInfo(tagItem item)
{
	//아이템 정보 갱신
	_itemName = item.name;
	_itemAtk = std::to_string(item.atk);
	_itemInt = std::to_string(item.intel);
	_itemDef = std::to_string(item.def);
	_itemSpd = std::to_string(item.spd);
	_itemHit = std::to_string(item.hit);
	_itemRes = std::to_string(item.res);
	_itemPrice = std::to_string(item.sellPrice);
	
	/*			item list rect set			*/
	int size = _item.getVItem().size();
	for (int i = 0; i < size; ++i)
	{
		_item.getVItem()[i].rc = RectMake(_rcItemList.left + 20, (_rcItemList.top + 40) + (i * 50), 200, 50);
	}

	_itemImage = IMAGEMANAGER->findImage(_itemName);
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
	_rcNext = RectMake(0, 0, 0, 0);
	_rcEquip = RectMake(0, 0, 0, 0);
	_rcWeapon = RectMake(0, 0, 0, 0);

	int size = _item.getVItem().size();
	for (int i = 0; i < size; ++i)
	{
		_item.getVItem()[i].rc = RectMake(0, 0, 0, 0);
	}
}

bool inventory::checkEquip()
{
	if (strcmp(_item.getVItem()[_selectItemNum].name, "sword") == 0)
	{
		if (strcmp(_name, "prinny") == 0)
			return true;
		else
			return false;
	}
	else if (strcmp(_item.getVItem()[_selectItemNum].name, "staff") == 0)
	{
		if (strcmp(_name, "flonne") == 0)
			return true;
		else
			return false;
	}
	else if (strcmp(_item.getVItem()[_selectItemNum].name, "wand") == 0)
	{
		if (strcmp(_name, "raspberyl") == 0)
			return true;
		else
			return false;
	}
	else if (strcmp(_item.getVItem()[_selectItemNum].name, "bow") == 0)
	{
		if (strcmp(_name, "etna") == 0)
			return true;
		else
			return false;
	}
}

void inventory::setItem(const char* itemName, bool isWear)
{
	_item.setItem(itemName, isWear);
}

void inventory::setName(const char * name)
{
	_name = name;

	if (strcmp(_name, "prinny") == 0)
	{
		_icon = IMAGEMANAGER->findImage("prinny_icon");
	}
	else if (strcmp(_name, "etna") == 0)
	{
		_icon = IMAGEMANAGER->findImage("etna_icon");
	}
	else if (strcmp(_name, "flonne") == 0)
	{
		_icon = IMAGEMANAGER->findImage("flonne_icon");
	}
	else if (strcmp(_name, "raspberyl") == 0)
	{
		_icon = IMAGEMANAGER->findImage("raspberyl_icon");
	}
}

void inventory::setClassStates(int level, int counter, int mv, int jm)
{
	_level = std::to_string(level);
	_counter = std::to_string(counter);
	_mv = std::to_string(mv);
	_jm = std::to_string(jm);
}

void inventory::setCharacterStates(int hp, int sp, int atk, int intel, 
	int def, int spd, int hit, int res, int exp, int next, WEAPON_TYPE weapon)
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

	switch (weapon)
	{
	case NONE:
		_weapon = "nothing";
		_isWear = false;
		break;
	case SWORD:
		_weapon = "sword";
		_isWear = true;
		break;
	case WAND:
		_weapon = "wand";
		_isWear = true;
		break;
	case STAFF:
		_weapon = "staff";
		_isWear = true;
		break;
	case BOW:
		_weapon = "bow";
		_isWear = true;
		break;
	}
}

void inventory::setEquip(bool isWear)
{
	if (isWear)
	{
		_atk = std::to_string(atoi(_atk.c_str()) + _item.getVItem()[_selectItemNum].atk);
		_int = std::to_string(atoi(_int.c_str()) + _item.getVItem()[_selectItemNum].intel);
		_def = std::to_string(atoi(_def.c_str()) + _item.getVItem()[_selectItemNum].def);
		_spd = std::to_string(atoi(_spd.c_str()) + _item.getVItem()[_selectItemNum].spd);
		_hit = std::to_string(atoi(_hit.c_str()) + _item.getVItem()[_selectItemNum].hit);
		_res = std::to_string(atoi(_res.c_str()) + _item.getVItem()[_selectItemNum].res);
		_weapon = _item.getVItem()[_selectItemNum].name;
	}
	else
	{
		_atk = std::to_string(atoi(_atk.c_str()) - _item.getVItem().back().atk);
		_int = std::to_string(atoi(_int.c_str()) - _item.getVItem().back().intel);
		_def = std::to_string(atoi(_def.c_str()) - _item.getVItem().back().def);
		_spd = std::to_string(atoi(_spd.c_str()) - _item.getVItem().back().spd);
		_hit = std::to_string(atoi(_hit.c_str()) - _item.getVItem().back().hit);
		_res = std::to_string(atoi(_res.c_str()) - _item.getVItem().back().res);
		_weapon = "nothing";
	}
}
