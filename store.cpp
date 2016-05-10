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
	//스토어 배경 이미지 추가
	IMAGEMANAGER->addImage("store_background", "image/background/store_background.bmp", WINSIZEX, WINSIZEY, false, false);

	//아이템 이미지 추가
	IMAGEMANAGER->addImage("sword", "image/item/sword.bmp", 256, 256, true, 0xff00ff);
	IMAGEMANAGER->addImage("staff", "image/item/staff.bmp", 256, 256, true, 0xff00ff);
	IMAGEMANAGER->addImage("wand", "image/item/wand.bmp", 256, 256, true, 0xff00ff);
	IMAGEMANAGER->addImage("bow", "image/item/bow.bmp", 256, 256, true, 0xff00ff);

	//판매할 아이템을 세팅
	_item.setItem("sword", "sword", "검이다.", 100, 0, 0, 0, 0, 0, 100, 10);
	_item.setItem("staff", "staff", "스태프다.", 0, 100, 0, 0, 0, 0, 150, 15);
	_item.setItem("wand", "wand", "완드다.", 0, 100, 0, 0, 0, 160, 0, 16);
	_item.setItem("bow", "bow", "활이다.", 0, 0, 0, 0, 100, 130, 0, 13);
	
	/*			store ui			*/
	
	//이미지
	IMAGEMANAGER->addImage("store_title", "image/ui/store_title.bmp", 162, 65, false, false);
	IMAGEMANAGER->addImage("store_list_title", "image/ui/store_list_title.bmp", 100, 50, true, 0xff00ff);
	IMAGEMANAGER->addImage("store_list", "image/ui/dialog_type_List.bmp", 300, 389, false, false);
	IMAGEMANAGER->addImage("store_status", "image/ui/store_ui_item_status.bmp", 700, 389, false, false);
	IMAGEMANAGER->addImage("store_info", "image/ui/dialog_type_bottom.bmp", 1182, 65, false, false);
	
	//렉트
	_rcStoreTitle = RectMake(30, 30, 162, 65);
	_rcListTitle = RectMake(80, 120, 100, 50);
	_rcItemList = RectMake(79, 150, 300, 389);
	_rcItemStatus = RectMake(499, 150, 700, 389);
	_rcItemInfo = RectMake(49, WINSIZEY - 115, 1182, 65);
	_rcItemImage = RectMake(918, 210, 256, 256);

	for (int i = 0; i < _item.getVItem().size(); ++i)
	{
		_item.getVItem()[i].rc = RectMake(_rcItemList.left, (_rcItemList.top + 20) + (i * 50) , 300, 50);
	}

	return S_OK;
}

void store::release()
{
}

void store::update()
{
}

void store::render()
{
	IMAGEMANAGER->findImage("store_background")->render(getMemDC(), 0, 0);

	//HFONT font, oldFont;
	//font = CreateFont(20, 0, 0, 0, 800, true, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("궁서체"));
	//oldFont = (HFONT)SelectObject(getMemDC(), font);
	
	//DrawText(getMemDC(), TEXT("Select Map"), -1, &_rcTitleStr, DT_LEFT | DT_VCENTER);
	//DrawText(getMemDC(), TEXT("Start"), -1, &_rcGoingStart, DT_LEFT | DT_VCENTER);
	//DrawText(getMemDC(), TEXT("Skip Story"), -1, &_rcGoingSkip, DT_LEFT | DT_VCENTER);
	//DrawText(getMemDC(), TEXT("Exit"), -1, &_rcGoingExit, DT_LEFT | DT_VCENTER);

	Rectangle(getMemDC(), _rcStoreTitle.left, _rcStoreTitle.top, _rcStoreTitle.right, _rcStoreTitle.bottom);
	Rectangle(getMemDC(), _rcItemList.left, _rcItemList.top, _rcItemList.right, _rcItemList.bottom);
	Rectangle(getMemDC(), _rcItemStatus.left, _rcItemStatus.top, _rcItemStatus.right, _rcItemStatus.bottom);
	Rectangle(getMemDC(), _rcItemInfo.left, _rcItemInfo.top, _rcItemInfo.right, _rcItemInfo.bottom);

	IMAGEMANAGER->findImage("store_title")->render(getMemDC(), _rcStoreTitle.left, _rcStoreTitle.top);
	IMAGEMANAGER->findImage("store_list")->render(getMemDC(), _rcItemList.left, _rcItemList.top);
	IMAGEMANAGER->findImage("store_list_title")->render(getMemDC(), _rcListTitle.left, _rcListTitle.top);
	IMAGEMANAGER->findImage("store_status")->render(getMemDC(), _rcItemStatus.left, _rcItemStatus.top);
	IMAGEMANAGER->findImage("store_info")->render(getMemDC(), _rcItemInfo.left, _rcItemInfo.top);

	Rectangle(getMemDC(), _rcItemImage.left, _rcItemImage.top, _rcItemImage.right, _rcItemImage.bottom);

	for (int i = 0; i < _item.getVItem().size(); ++i)
	{
		RECT rc = _item.getVItem()[i].rc;
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	}
}

void store::showItemInfoAll()
{
}
