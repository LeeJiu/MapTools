#include "stdafx.h"
#include "selectStage.h"

selectStage::selectStage()
{
}


selectStage::~selectStage()
{
}

HRESULT selectStage::init()
{
	SOUNDMANAGER->stop("step");
	SOUNDMANAGER->stop("town_bg");

	_mapListSize = 5;

	IMAGEMANAGER->addImage("selectScene", "image/battleUI/selectScene.bmp", 1280, 720, false, false);
	_imageListTop = IMAGEMANAGER->addImage("dialog_List_top", "image/battleUI/dialog_List_top.bmp", 300, 18, false, false);
	for (int i = 0; i < _mapListSize; i++)
	{
		image* tempBody;
		tempBody = new image;
		tempBody->init("image/battleUI/dialog_List_Body.bmp", 300, 30, false, false);
		_imageListBody.push_back(tempBody);
	}
	_imageListBottom = IMAGEMANAGER->addImage("dialog_List_Bottom", "image/battleUI/dialog_List_Bottom.bmp", 300, 19, false, false);

	_imageTitleBack = IMAGEMANAGER->addImage("title", "image/battleUI/ui_selectmap.bmp", 162, 65, false, false);
	_imageBottomBack = IMAGEMANAGER->addImage("dialog_bottom", "image/battleUI/dialog_type_bottom.bmp", 1050, 60, false, false);
	_imageGoingBack = IMAGEMANAGER->addImage("exit", "image/battleUI/ui_goingmenu.bmp", 254, 115, false, false);
	_imageArrow = IMAGEMANAGER->addImage("arrow", "image/battleUI/ui_arrow.bmp", 35, 35, true, 0xff00ff);

	_rcListTop = RectMakeCenter(180, 200, _imageListTop->getWidth(), _imageListTop->getHeight());
	for (int i = 0; i < _mapListSize; i++)
	{
		RECT tempBody = RectMakeCenter(180, _rcListTop.bottom + (30 * i) + _imageListBody[0]->getHeight() / 2, _imageListBody[0]->getWidth(), _imageListBody[0]->getHeight());
		_rcListBody.push_back(tempBody);

		RECT tempRect = RectMake(_rcListBody[i].left + 20, _rcListBody[i].top + 5, _imageListBody[0]->getWidth(), _imageListBody[0]->getHeight());
		_vRcMapListStr.push_back(tempRect);
	}
	int listBodyEnd = _mapListSize - 1;
	_rcListBottom = RectMakeCenter(180, _rcListBody[listBodyEnd].bottom + _imageListBottom->getHeight() / 2, _imageListBottom->getWidth(), _imageListBottom->getHeight());
	_rcTitle = RectMakeCenter(CENTERX, 50, _imageTitleBack->getWidth(), _imageTitleBack->getHeight());
	_rcBottom = RectMakeCenter(CENTERX, WINSIZEY - 60, _imageBottomBack->getWidth(), _imageBottomBack->getHeight());
	_rcGoing = RectMakeCenter(WINSIZEX - 242, _rcBottom.top - 70, _imageGoingBack->getWidth(), _imageGoingBack->getHeight());
	_rcArrow = RectMakeCenter(_rcListBody[0].left, _rcListBody[0].top + _imageArrow->getHeight() / 2, _imageArrow->getWidth(), _imageArrow->getHeight());

	//_rcTitleStr = RectMakeCenter(CENTERX + 25, _rcTitle.top + (_rcTitle.bottom - _rcTitle.top) / 2, _imageTitleBack->getWidth(), 20);
	_rcGoingStart = RectMakeCenter(WINSIZEX - 195, _rcBottom.top - 90, _imageGoingBack->getWidth(), _imageGoingBack->getHeight() / 3);
	_rcGoingSkip = RectMakeCenter(WINSIZEX - 195, _rcBottom.top - 60, _imageGoingBack->getWidth(), _imageGoingBack->getHeight() / 3);
	_rcGoingExit = RectMakeCenter(WINSIZEX - 195, _rcBottom.top - 30, _imageGoingBack->getWidth(), _imageGoingBack->getHeight() / 3);

	_imageShortcutStart = IMAGEMANAGER->addImage("shortcut_start", "image/battleUI/shortcut_key_1.bmp", 30, 30, true, 0xff00ff);
	_imageShortcutSkip = IMAGEMANAGER->addImage("shortcut_skip", "image/battleUI/shortcut_key_2.bmp", 30, 30, true, 0xff00ff);
	_imageShortcutExit = IMAGEMANAGER->addImage("shortcut_exit", "image/battleUI/shortcut_key_Q.bmp", 30, 30, true, 0xff00ff);

	_selectMapNumber = 0;
	mapListInit();

	return S_OK;
}

void selectStage::release()
{
	for (int i = 0; i < _imageListBody.size(); i++)
	{
		_imageListBody.erase(_imageListBody.begin() + i);
	}
	_imageListBody.clear();
}

void selectStage::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//CHECK MAPLIST SELECT
		for (int i = 0; i < _mapListSize; i++)
		{
			if (PtInRect(&_rcListBody[i], _ptMouse))
			{
				_selectMapNumber = i;
				_rcArrow = RectMakeCenter(_rcListBody[i].left, _rcListBody[i].top + _imageArrow->getHeight() / 2, _imageArrow->getWidth(), _imageArrow->getHeight());
			}
		}

		//START BUTTON
		if (PtInRect(&_rcGoingStart, _ptMouse))
		{
			STAGEDATA->setSElectStageNumber(_selectMapNumber);
			SCENEMANAGER->changeScene("battleScene");
		}

		//SKIP STORY BUTTON
		if (PtInRect(&_rcGoingSkip, _ptMouse))
		{

		}

		//EXIT BUTTON
		if (PtInRect(&_rcGoingExit, _ptMouse))
		{
			SCENEMANAGER->changeScene("town");
		}
	}
}

void selectStage::render()
{
	IMAGEMANAGER->findImage("selectScene")->render(getMemDC());

	//Rectangle(getMemDC(), _rcListTop.left, _rcListTop.top, _rcListTop.right, _rcListTop.bottom);
	//for (int i = 0; i < _mapListSize; i++) Rectangle(getMemDC(), _rcListBody[i].left, _rcListBody[i].top, _rcListBody[i].right, _rcListBody[i].bottom);
	//Rectangle(getMemDC(), _rcListBottom.left, _rcListBottom.top, _rcListBottom.right, _rcListBottom.bottom);

	//Rectangle(getMemDC(), _rcTitle.left, _rcTitle.top, _rcTitle.right, _rcTitle.bottom);
	//Rectangle(getMemDC(), _rcBottom.left, _rcBottom.top, _rcBottom.right, _rcBottom.bottom);
	//Rectangle(getMemDC(), _rcGoing.left, _rcGoing.top, _rcGoing.right, _rcGoing.bottom);
	//Rectangle(getMemDC(), _rcArrow.left, _rcArrow.top, _rcArrow.right, _rcArrow.bottom);

	//Rectangle(getMemDC(), _rcGoingStart.left, _rcGoingStart.top, _rcGoingStart.right, _rcGoingStart.bottom);
	//Rectangle(getMemDC(), _rcGoingSkip.left, _rcGoingSkip.top, _rcGoingSkip.right, _rcGoingSkip.bottom);
	//Rectangle(getMemDC(), _rcGoingExit.left, _rcGoingExit.top, _rcGoingExit.right, _rcGoingExit.bottom);

	_imageListTop->render(getMemDC(), _rcListTop.left, _rcListTop.top);
	for (int i = 0; i < _mapListSize; i++) _imageListBody[i]->render(getMemDC(), _rcListBody[i].left, _rcListBody[i].top);
	_imageListBottom->render(getMemDC(), _rcListBottom.left, _rcListBottom.top);

	_imageTitleBack->render(getMemDC(), _rcTitle.left, _rcTitle.top);
	_imageBottomBack->render(getMemDC(), _rcBottom.left, _rcBottom.top);
	_imageGoingBack->render(getMemDC(), _rcGoing.left, _rcGoing.top);
	_imageArrow->render(getMemDC(), _rcArrow.left, _rcArrow.top);

	HFONT font, oldFont;
	font = CreateFont(20, 0, 0, 0, 1000, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	//DrawText(getMemDC(), TEXT("Select Map"), -1, &_rcTitleStr, DT_LEFT | DT_VCENTER);
	//DrawText(getMemDC(), TEXT("Start"), -1, &_rcGoingStart, DT_LEFT | DT_VCENTER);
	//DrawText(getMemDC(), TEXT("Skip Story"), -1, &_rcGoingSkip, DT_LEFT | DT_VCENTER);
	//DrawText(getMemDC(), TEXT("Exit"), -1, &_rcGoingExit, DT_LEFT | DT_VCENTER);

	//_imageShortcutStart->render(getMemDC(), _rcGoingStart.left - 35, _rcGoingStart.top - 3);
	//_imageShortcutSkip->render(getMemDC(), _rcGoingSkip.left - 35, _rcGoingSkip.top - 3);
	//_imageShortcutExit->render(getMemDC(), _rcGoingExit.left - 35, _rcGoingExit.top - 3);

	for (int i = 0; i < _mapListSize; i++) DrawText(getMemDC(), TEXT(_vMapList[i]), -1, &_vRcMapListStr[i], DT_LEFT | DT_VCENTER);


	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

}

void selectStage::mapListInit()
{
	for (int i = 0; i < _mapListSize; i++)
	{
		if (i == 0) _vMapList.push_back("서울게임 아카데미 4층");
		if (i == 1) _vMapList.push_back("서울게임 아카데미 5층");
		if (i == 2) _vMapList.push_back("서울게임 아카데미 6층");
		if (i == 3) _vMapList.push_back("보스 방 : 장명호");
		if (i == 4) _vMapList.push_back("보스 방 : 양호성");
		if (i == 5) _vMapList.push_back("BASIC BATTLE 6");
		if (i == 6) _vMapList.push_back("BASIC BATTLE 7");
		if (i == 7) _vMapList.push_back("BASIC BATTLE 8");
		if (i == 8) _vMapList.push_back("BASIC BATTLE 9");
		if (i == 9) _vMapList.push_back("BASIC BATTLE 10");
		if (i == 10) _vMapList.push_back("BASIC BATTLE 11");
		if (i == 11) _vMapList.push_back("BASIC BATTLE 12");
	}
}
