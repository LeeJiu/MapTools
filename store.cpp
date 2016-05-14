#include "stdafx.h"
#include "store.h"


store::store()
{
}


store::~store()
{
}

HRESULT store::init()
{
<<<<<<< HEAD
	return E_NOTIMPL;
=======
	//스토어 배경 이미지 추가
	IMAGEMANAGER->addImage("store_background", "image/background/store_background.bmp", WINSIZEX, WINSIZEY, false, false);

	//판매할 아이템을 세팅
	_item.setItem("sword");
	_item.setItem("staff");
	_item.setItem("wand");
	_item.setItem("bow");
	
	/*			store ui			*/
	
	//이미지
	IMAGEMANAGER->addImage("store_title", "image/ui/store_title.bmp", 162, 65, false, false);
	IMAGEMANAGER->addImage("store_exit", "image/ui/store_exit.bmp", 162, 65, false, false);
	IMAGEMANAGER->addImage("store_list_title", "image/ui/store_list_title.bmp", 100, 50, true, 0xff00ff);
	IMAGEMANAGER->addImage("store_list", "image/ui/dialog_type_List.bmp", 300, 389, false, false);
	IMAGEMANAGER->addImage("store_status", "image/ui/store_ui_item_status.bmp", 700, 389, false, false);
	IMAGEMANAGER->addImage("store_info", "image/ui/dialog_type_bottom.bmp", 1182, 65, false, false);
	IMAGEMANAGER->addImage("store_hell", "image/ui/store_hell.bmp", 300, 50, false, false);
	IMAGEMANAGER->addImage("store_buy", "image/ui/store_buy.bmp", 200, 50, false, false);
	
	//렉트
	//틀
	_rcStoreTitle = RectMake(30, 30, 162, 65);
	_rcExit = RectMake(WINSIZEX - 202, 30, 162, 65);
	_rcListTitle = RectMake(80, 120, 100, 50);
	_rcItemList = RectMake(79, 150, 300, 389);
	_rcItemStatus = RectMake(499, 150, 700, 389);
	_rcItemInfo = RectMake(49, WINSIZEY - 115, 1182, 65);
	_rcItemImage = RectMake(918, 210, 256, 256);
	_rcHell = RectMake(650, 545, 300, 50);
	_rcBuy = RectMake(1000, 545, 200, 50);
	
	//글씨 위치
	_rcName = RectMake(540, 180, 200, 35);
	_rcAtk = RectMake(615, 250, 200, 35);
	_rcInt = RectMake(615, 285, 200, 35);
	_rcDef = RectMake(615, 325, 200, 35);
	_rcSpd = RectMake(615, 365, 200, 35);
	_rcHit = RectMake(615, 405, 200, 35);
	_rcRes = RectMake(615, 445, 200, 35);
	_rcPrice = RectMake(615, 485, 200, 35);
	_rcInfo = RectMake(80, WINSIZEY - 100, 1100, 35);

	for (int i = 0; i < _item.getVItem().size(); ++i)
	{
		_item.getVItem()[i].rc = RectMake(_rcItemList.left + 20, (_rcItemList.top + 20) + (i * 50) , 200, 50);
	}

	//플레이어를 정보를 받아온다.
	_prinny = new prinny;
	_prinny->init();

	_itemImage = IMAGEMANAGER->findImage("sword");
	_name = _item.getVItem().begin()->name;
	_info = _item.getVItem().begin()->info;
	_atk = std::to_string(_item.getVItem().begin()->atk);
	_int = std::to_string(_item.getVItem().begin()->intel);
	_def = std::to_string(_item.getVItem().begin()->def);
	_spd = std::to_string(_item.getVItem().begin()->spd);
	_hit = std::to_string(_item.getVItem().begin()->hit);
	_res = std::to_string(_item.getVItem().begin()->res);
	_price = std::to_string(_item.getVItem().begin()->buyPrice);
	_hell = std::to_string(_prinny->getHell());

	return S_OK;
>>>>>>> refs/remotes/origin/development
}

void store::release()
{
<<<<<<< HEAD
=======
	_item.getVItem().clear();
>>>>>>> refs/remotes/origin/development
}

void store::update()
{
<<<<<<< HEAD
=======
	_prinny->update();

	keyControl();
>>>>>>> refs/remotes/origin/development
}

void store::render()
{
<<<<<<< HEAD
=======
	IMAGEMANAGER->findImage("store_background")->render(getMemDC(), 0, 0);

	Rectangle(getMemDC(), _rcExit.left, _rcExit.top, _rcExit.right, _rcExit.bottom);

	IMAGEMANAGER->findImage("store_title")->render(getMemDC(), _rcStoreTitle.left, _rcStoreTitle.top);
	IMAGEMANAGER->findImage("store_exit")->render(getMemDC(), _rcExit.left, _rcExit.top);
	IMAGEMANAGER->findImage("store_list")->render(getMemDC(), _rcItemList.left, _rcItemList.top);
	IMAGEMANAGER->findImage("store_list_title")->render(getMemDC(), _rcListTitle.left, _rcListTitle.top);
	IMAGEMANAGER->findImage("store_status")->render(getMemDC(), _rcItemStatus.left, _rcItemStatus.top);
	IMAGEMANAGER->findImage("store_info")->render(getMemDC(), _rcItemInfo.left, _rcItemInfo.top);
	IMAGEMANAGER->findImage("store_hell")->render(getMemDC(), _rcHell.left, _rcHell.top);
	IMAGEMANAGER->findImage("store_buy")->render(getMemDC(), _rcBuy.left, _rcBuy.top);

	_itemImage->render(getMemDC(), _rcItemImage.left, _rcItemImage.top);

	HFONT font, oldFont;
	font = CreateFont(30, 0, 0, 0, 800, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	for (int i = 0; i < _item.getVItem().size(); ++i)
	{
		RECT rc = _item.getVItem()[i].rc;
		DrawText(getMemDC(), _item.getVItem()[i].name, -1, &rc, DT_LEFT | DT_VCENTER);
	}

	DrawText(getMemDC(), _name, -1, &_rcName, DT_LEFT | DT_VCENTER);
	DrawText(getMemDC(), _info, -1, &_rcInfo, DT_LEFT | DT_VCENTER);
	DrawText(getMemDC(), _atk.c_str(), -1, &_rcAtk, DT_LEFT | DT_VCENTER);
	DrawText(getMemDC(), _int.c_str(), -1, &_rcInt, DT_LEFT | DT_VCENTER);
	DrawText(getMemDC(), _def.c_str(), -1, &_rcDef, DT_LEFT | DT_VCENTER);
	DrawText(getMemDC(), _spd.c_str(), -1, &_rcSpd, DT_LEFT | DT_VCENTER);
	DrawText(getMemDC(), _hit.c_str(), -1, &_rcHit, DT_LEFT | DT_VCENTER);
	DrawText(getMemDC(), _res.c_str(), -1, &_rcRes, DT_LEFT | DT_VCENTER);
	DrawText(getMemDC(), _price.c_str(), -1, &_rcPrice, DT_LEFT | DT_VCENTER);
	DrawText(getMemDC(), _hell.c_str(), -1,
		&RectMake(_rcHell.left + 20, _rcHell.top + 10, 220, 50), DT_RIGHT | DT_VCENTER);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	_prinny->render();
}

void store::buyItem(const char* itemName)
{
	int remainHell = atoi(_hell.c_str()) - atoi(_price.c_str());
	if (remainHell >= 0)
	{
		_prinny->setHell(remainHell);
		_prinny->setItem(itemName);
		_hell = std::to_string(remainHell);
	}
}

void store::keyControl()
{
	for (int i = 0; i < _item.getVItem().size(); ++i)
	{
		RECT rc = _item.getVItem()[i].rc;
		if (PtInRect(&rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				showItemInfoAll(i);
				_buyItemIdx = i;
				break;
			}
		}
	}
	if (PtInRect(&_rcBuy, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			buyItem(_item.getVItem()[_buyItemIdx].name);
		}
	}
	if (PtInRect(&_rcExit, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_prinny->saveData();
			SCENEMANAGER->changeScene("town");
		}
	}
}

void store::showItemInfoAll(int arrNum)
{
	_itemImage = IMAGEMANAGER->findImage(_item.getVItem()[arrNum].name);
	_name = _item.getVItem()[arrNum].name;
	_info = _item.getVItem()[arrNum].info;
	_atk = std::to_string(_item.getVItem()[arrNum].atk);
	_int = std::to_string(_item.getVItem()[arrNum].intel);
	_def = std::to_string(_item.getVItem()[arrNum].def);
	_spd = std::to_string(_item.getVItem()[arrNum].spd);
	_hit = std::to_string(_item.getVItem()[arrNum].hit);
	_res = std::to_string(_item.getVItem()[arrNum].res);
	_price = std::to_string(_item.getVItem()[arrNum].buyPrice);
>>>>>>> refs/remotes/origin/development
}
