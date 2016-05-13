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
	_battleUI = new battleUI;
	_battleUI->init();

	return S_OK;
}

void battleScene::release()
{
	_battleUI->release();
}

void battleScene::update()
{
	_battleUI->update();
}

void battleScene::render()
{
<<<<<<< HEAD
	_battleUI->render();
=======
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
	font = CreateFont(20, 0, 0, 0, 800, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("±¼¸²"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	for (int i = 0; i < _orderListSize; i++) DrawText(getMemDC(), TEXT(_vOrderList[i]), -1, &_rcOrderListStr[i], DT_LEFT | DT_VCENTER);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);


>>>>>>> origin/Jaejun
}
