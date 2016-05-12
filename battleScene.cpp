#include "stdafx.h"
#include "battleScene.h"


battleScene::battleScene()
{
}


battleScene::~battleScene()
{
}

HRESULT battleScene::init()
{	
	_vOrderList.push_back("공격개시");
	_vOrderList.push_back("턴 종료");
	_vOrderList.push_back("보너스 표");
	_vOrderList.push_back("캐릭터 명단");
	_vOrderList.push_back("전투지식");
	_vOrderList.push_back("포기");
	_vOrderList.push_back("설정");
	_orderListSize = _vOrderList.size();

	_imageStatusBack = IMAGEMANAGER->addImage("character_status", "image/ui_characterstatus_back.bmp", 300, 500, true, 0xff00ff);
	_imageBottomStatusBack = IMAGEMANAGER->addImage("bottom_status", "image/ui_battle_bottom_status.bmp", 314, 110, true, 0xff00ff);
	_imageSkillTitleBack = IMAGEMANAGER->addImage("skill_title", "image/dialog_type_title.bmp", 162, 65, false, false);
	_imageCharacterListBack = IMAGEMANAGER->addImage("character_list", "image/ui_battle_summon.bmp", 250, 300, true, 0xff00ff);
	_imageIconCharacter = IMAGEMANAGER->addImage("icon_character", "image/icon_character_fuka.bmp", 96, 96, false, false);

	_imageOrderListTop = IMAGEMANAGER->addImage("orderlist_top", "image/ui_orderlist_top.bmp", 254, 29, false, false);
	for (int i = 0; i < _vOrderList.size(); i++)
	{
		image* tempBody = new image;
		tempBody->init("image/ui_orderlist_body.bmp", 254, 30, false, false);
		_imageOrderListBody.push_back(tempBody);
	}
	_imageOrderListBottom = IMAGEMANAGER->addImage("orderlist_bottom", "image/ui_orderlist_bottom.bmp", 254, 30, false, false);

	_rcStatus = RectMake(50, 100, _imageStatusBack->getWidth(), _imageStatusBack->getHeight());
	_rcBottomStatus = RectMake(50, WINSIZEY - 250, _imageBottomStatusBack->getWidth(), _imageBottomStatusBack->getHeight());
	_rcSkillTitle = RectMakeCenter(CENTERX, 50, _imageSkillTitleBack->getWidth(), _imageSkillTitleBack->getHeight());
	_rcCharacterList = RectMake(WINSIZEX - 400, 100, _imageCharacterListBack->getWidth(), _imageCharacterListBack->getHeight());
	_rcIconCharacter = RectMake(_rcBottomStatus.left + 7, _rcBottomStatus.top + 7, 96, 96);

	_rcOrderListTop = RectMake(WINSIZEX - 300, 100, _imageOrderListTop->getWidth(), _imageOrderListTop->getHeight());
	for (int i = 0; i < _orderListSize; i++)
	{
		RECT tempBody = RectMake(_rcOrderListTop.left, _rcOrderListTop.bottom + (30 * i), 254, 30);
		_rcOrderListBody.push_back(tempBody);

		RECT tempRect = RectMake(_rcOrderListBody[i].left + 20, _rcOrderListBody[i].top + 5, _imageOrderListTop->getWidth(), _imageOrderListTop->getHeight());
		_rcOrderListStr.push_back(tempRect);
	}
	_rcOrderListBottom = RectMake(WINSIZEX - 300, _rcOrderListBody[_orderListSize - 1].bottom, _imageOrderListBottom->getWidth(), _imageOrderListBottom->getHeight());
	

	return S_OK;
}

void battleScene::release()
{
}

void battleScene::update()
{
}

void battleScene::render()
{
	Rectangle(getMemDC(), _rcStatus.left, _rcStatus.top, _rcStatus.right, _rcStatus.bottom);
	Rectangle(getMemDC(), _rcBottomStatus.left, _rcBottomStatus.top, _rcBottomStatus.right, _rcBottomStatus.bottom);
	Rectangle(getMemDC(), _rcSkillTitle.left, _rcSkillTitle.top, _rcSkillTitle.right, _rcSkillTitle.bottom);

	Rectangle(getMemDC(), _rcOrderListTop.left, _rcOrderListTop.top, _rcOrderListTop.right, _rcOrderListTop.bottom);
	for (int i = 0; i < _orderListSize; i++) Rectangle(getMemDC(), _rcOrderListBody[i].left, _rcOrderListBody[i].top, _rcOrderListBody[i].right, _rcOrderListBody[i].bottom);
	Rectangle(getMemDC(), _rcOrderListBottom.left, _rcOrderListBottom.top, _rcOrderListBottom.right, _rcOrderListBottom.bottom);
	Rectangle(getMemDC(), _rcIconCharacter.left, _rcIconCharacter.top, _rcIconCharacter.right, _rcIconCharacter.bottom);

	_imageStatusBack ->render(getMemDC(), _rcStatus.left, _rcStatus.top);
	_imageBottomStatusBack ->render(getMemDC(), _rcBottomStatus.left, _rcBottomStatus.top);
	_imageSkillTitleBack->render(getMemDC(), _rcSkillTitle.left, _rcSkillTitle.top);
	_imageCharacterListBack->render(getMemDC(), _rcCharacterList.left, _rcCharacterList.top);
	_imageIconCharacter->render(getMemDC(), _rcIconCharacter.left, _rcIconCharacter.top);

	_imageOrderListTop ->render(getMemDC(), _rcOrderListTop.left, _rcOrderListTop.top);
	for (int i = 0; i < _orderListSize; i++) _imageOrderListBody[i]->render(getMemDC(), _rcOrderListBody[i].left, _rcOrderListBody[i].top);
	_imageOrderListBottom->render(getMemDC(), _rcOrderListBottom.left, _rcOrderListBottom.top);

	HFONT font, oldFont;
	font = CreateFont(20, 0, 0, 0, 800, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	for (int i = 0; i < _orderListSize; i++) DrawText(getMemDC(), TEXT(_vOrderList[i]), -1, &_rcOrderListStr[i], DT_LEFT | DT_VCENTER);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}
