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
	_volume = 0;
	SOUNDMANAGER->stop("step");
	//SOUNDMANAGER->stop("town_bg");
	SOUNDMANAGER->play("selectStage_bg", _volume);


	_mapListSize = 3;

	IMAGEMANAGER->addImage("selectScene", "image/background/selectScene.bmp", 1280, 720, false, false);
	_imageListTop = IMAGEMANAGER->addImage("dialog_List_top", "image/ui/dialog_List_top.bmp", 300, 18, false, false);
	for (int i = 0; i < _mapListSize; i++)
	{
		image* tempBody;
		tempBody = new image;
		tempBody->init("image/ui/dialog_List_Body.bmp", 300, 30, false, false);
		_imageListBody.push_back(tempBody);
	}
	_imageListBottom = IMAGEMANAGER->addImage("dialog_List_Bottom", "image/ui/dialog_List_Bottom.bmp", 300, 19, false, false);

	_imageTitleBack = IMAGEMANAGER->addImage("title", "image/ui/ui_selectmap.bmp", 162, 65, false, false);
	_imageBottomBack = IMAGEMANAGER->addImage("dialog_bottom", "image/ui/dialog_type_bottom.bmp", 1050, 60, false, false);
	_imageGoingBack = IMAGEMANAGER->addImage("exit", "image/ui/ui_goingmenu.bmp", 254, 115, false, false);
	_imageArrow = IMAGEMANAGER->addImage("arrow", "image/ui/ui_arrow.bmp", 35, 35, true, 0xff00ff);

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

	_selectMapNumber = 0;
	mapListInit();

	return S_OK;
}

void selectStage::release()
{
	SOUNDMANAGER->stop("selectStage_bg");
	for (int i = 0; i < _imageListBody.size(); i++)
	{
		_imageListBody.erase(_imageListBody.begin() + i);
	}
	_imageListBody.clear();
}

void selectStage::update()
{
	if (_volume < 1.f) _volume += 0.005f;
	SOUNDMANAGER->setVolum("selectStage_bg", _volume);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("click", 1.f);

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
			NUMBERDATA->setSElectStageNumber(_selectMapNumber);
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

	_imageListTop->render(getMemDC(), _rcListTop.left, _rcListTop.top);
	for (int i = 0; i < _mapListSize; i++) _imageListBody[i]->render(getMemDC(), _rcListBody[i].left, _rcListBody[i].top);
	_imageListBottom->render(getMemDC(), _rcListBottom.left, _rcListBottom.top);

	_imageTitleBack->render(getMemDC(), _rcTitle.left, _rcTitle.top);
	_imageBottomBack->render(getMemDC(), _rcBottom.left, _rcBottom.top);
	_imageGoingBack->render(getMemDC(), _rcGoing.left, _rcGoing.top);
	_imageArrow->render(getMemDC(), _rcArrow.left, _rcArrow.top);

	HFONT font, oldFont;
	font = CreateFont(20, 0, 0, 0, 1000, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("±¼¸²"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	for (int i = 0; i < _mapListSize; i++) DrawText(getMemDC(), TEXT(_vMapList[i]), -1, &_vRcMapListStr[i], DT_LEFT | DT_VCENTER);


	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

}

void selectStage::mapListInit()
{
	for (int i = 0; i < _mapListSize; i++)
	{
		if (i == 0) _vMapList.push_back("Stage 1");
		if (i == 1) _vMapList.push_back("Stage 2");
		if (i == 2) _vMapList.push_back("Stage 3");
	}
}
