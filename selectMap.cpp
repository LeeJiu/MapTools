#include "stdafx.h"
#include "selectMap.h"


selectMap::selectMap()
{
}


selectMap::~selectMap()
{
}

HRESULT selectMap::init()
{
	_imageListBack = IMAGEMANAGER->addImage("dialog_type_1", "image/dialog_type_1.bmp", 300, 389, false, false);
	_imageTitleBack = IMAGEMANAGER->addImage("title", "image/dialog_type_title.bmp", 162, 65, false, false);
	_imageBottomBack = IMAGEMANAGER->addImage("dialog_bottom", "image/dialog_type_bottom.bmp", 1050, 60, false, false);
	_imageGoingBack = IMAGEMANAGER->addImage("exit", "image/dialog_type_going.bmp", 254, 115, false, false);


	_rcList = RectMakeCenter(180, CENTERY, _imageListBack->getWidth(), _imageListBack->getHeight());
	_rcTitle = RectMakeCenter(CENTERX, 50, _imageTitleBack->getWidth(), _imageTitleBack->getHeight());
	_rcBottom = RectMakeCenter(CENTERX, WINSIZEY - 60, _imageBottomBack->getWidth(), _imageBottomBack->getHeight());
	_rcGoing = RectMakeCenter(WINSIZEX - 242, _rcBottom.top - 70, _imageGoingBack->getWidth(), _imageGoingBack->getHeight());

	return S_OK;
}

void selectMap::release()
{
}

void selectMap::update()
{
}

void selectMap::render()
{
	Rectangle(getMemDC(), _rcList.left, _rcList.top, _rcList.right, _rcList.bottom);
	Rectangle(getMemDC(), _rcTitle.left, _rcTitle.top, _rcTitle.right, _rcTitle.bottom);
	Rectangle(getMemDC(), _rcBottom.left, _rcBottom.top, _rcBottom.right, _rcBottom.bottom);
	Rectangle(getMemDC(), _rcGoing.left, _rcGoing.top, _rcGoing.right, _rcGoing.bottom);

	_imageListBack->render(getMemDC(), _rcList.left, _rcList.top);
	_imageTitleBack->render(getMemDC(), _rcTitle.left, _rcTitle.top);
	_imageBottomBack->render(getMemDC(), _rcBottom.left, _rcBottom.top);
	_imageGoingBack->render(getMemDC(), _rcGoing.left, _rcGoing.top);
}	