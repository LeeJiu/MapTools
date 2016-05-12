#include "stdafx.h"
#include "town.h"


town::town()
{
}


town::~town()
{
}

HRESULT town::init()
{
	IMAGEMANAGER->addImage("town_background", "image/background/town_background.bmp", 4155, 1704, true, 0xff00ff);
	IMAGEMANAGER->addImage("town_background_pixel", "image/background/town_background_pixel.bmp", 4155, 1704, false, false);

	_town = IMAGEMANAGER->findImage("town_background");
	_townPixel = IMAGEMANAGER->findImage("town_background_pixel");

	_prinny = new prinny;
	_prinny->init();

	_sourX = 1790;
	_sourY = 490;

	return S_OK;
}

void town::release()
{
	SAFE_DELETE(_prinny);
}

void town::update()
{
	keyControl();
	pixelCollision(_prinny->getRect());

	_prinny->update();
}

void town::render()
{
	_town->render(getMemDC(), 0, 0, _sourX, _sourY, WINSIZEX, WINSIZEY);
	//_townPixel->render(getMemDC(), 0, 0, _sourX, _sourY, WINSIZEX, WINSIZEY);
	_prinny->render();
}

void town::keyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_sourX -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_sourX += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_sourY -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_sourY += 3;
	}
}

void town::pixelCollision(RECT rc)
{
	//왼쪽부터 픽셀 검사
	_proveX = rc.left;
	_proveY = (rc.top + rc.bottom) / 2;
	for (int i = _proveX; i < _proveX + 5; ++i)
	{
		COLORREF color = GetPixel(_townPixel->getMemDC(), i + _sourX, _proveY + _sourY);
		if (color == 0xff00ff)
		{
			_sourX += 3;
			break;
		}
	}

	//오른쪽 픽셀 검사
	_proveX = rc.right;
	_proveY = (rc.top + rc.bottom) / 2;
	for (int i = _proveX; i > _proveX - 5; --i)
	{
		COLORREF color = GetPixel(_townPixel->getMemDC(), i + _sourX, _proveY + _sourY);
		if (color == 0xff00ff)
		{
			_sourX -= 3;
			break;
		}
	}

	//위쪽 픽셀 검사
	_proveX = (rc.left + rc.right) / 2;
	_proveY = (rc.top + rc.bottom) / 2;
	for (int i = _proveY; i < _proveY + 5; ++i)
	{
		COLORREF color = GetPixel(_townPixel->getMemDC(), _proveX + _sourX, i + _sourY);
		if (color == 0xff00ff)
		{
			_sourY += 3;
			break;
		}
	}

	//아래쪽 픽셀 검사
	_proveX = (rc.left + rc.right) / 2;
	_proveY = rc.bottom;
	for (int i = _proveY; i > _proveY - 5; --i)
	{
		COLORREF color = GetPixel(_townPixel->getMemDC(), _proveX + _sourX, i + _sourY);
		if (color == 0xff00ff)
		{
			_sourY -= 3;
			break;
		}
	}
}
