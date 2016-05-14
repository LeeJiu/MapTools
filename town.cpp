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
<<<<<<< HEAD
	return E_NOTIMPL;
=======
	IMAGEMANAGER->addImage("town_background", "image/background/town_background.bmp", 4155, 1704, true, 0xff00ff);
	IMAGEMANAGER->addImage("town_background_pixel", "image/background/town_background_pixel.bmp", 4155, 1704, false, false);

	IMAGEMANAGER->addFrameImage("entrance_battle", "image/background/entrance_battle.bmp", 2695, 266, 11, 1, false, false);
	IMAGEMANAGER->addFrameImage("entrance_store", "image/background/entrance_store.bmp", 3969, 220, 27, 1, false, false);
	IMAGEMANAGER->addFrameImage("entrance_etc", "image/background/entrance_etc.bmp", 1694, 279, 7, 1, false, false);

	_town = IMAGEMANAGER->findImage("town_background");
	_townPixel = IMAGEMANAGER->findImage("town_background_pixel");

	_battlePortal = IMAGEMANAGER->findImage("entrance_battle");
	_storePortal = IMAGEMANAGER->findImage("entrance_store");
	_etcPortal = IMAGEMANAGER->findImage("entrance_etc");

	_prinny = new prinny;
	_prinny->init();

	_sourX = 1790;
	_sourY = 490;
	
	//마을 입구 좌표
	//_sourX = 2600;
	//_sourY = 60;

	return S_OK;
>>>>>>> refs/remotes/origin/development
}

void town::release()
{
<<<<<<< HEAD

=======
	SAFE_DELETE(_prinny);
>>>>>>> refs/remotes/origin/development
}

void town::update()
{
<<<<<<< HEAD

=======
	_prinny->update();

	keyControl();
	pixelCollision(_prinny->getRect());
	setFrame();

	enterEntrance();
>>>>>>> refs/remotes/origin/development
}

void town::render()
{
<<<<<<< HEAD

=======
	_town->render(getMemDC(), 0, 0, _sourX, _sourY, WINSIZEX, WINSIZEY);
	//_townPixel->render(getMemDC(), 0, 0, _sourX, _sourY, WINSIZEX, WINSIZEY);
	
	//포탈 이미지 프레임
	_battlePortal->frameRender(getMemDC(), 2061 - _sourX, 1012 - _sourY,
		_battlePortal->getFrameX(), _battlePortal->getFrameY());

	_storePortal->frameRender(getMemDC(), 1595 - _sourX, 371 - _sourY,
		_storePortal->getFrameX(), _storePortal->getFrameY());

	_etcPortal->frameRender(getMemDC(), 1134 - _sourX, 478 - _sourY,
		_etcPortal->getFrameX(), _etcPortal->getFrameY());

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

void town::enterEntrance()
{
	_rcBattle = RectMake(2061 - _sourX, 1012 - _sourY, _battlePortal->getFrameWidth(), _battlePortal->getFrameHeight());
	_rcStore = RectMake(1595 - _sourX, 371 - _sourY, _storePortal->getFrameWidth(), _storePortal->getFrameHeight());

	if (IntersectRect(&RectMake(0, 0, 0, 0), &_prinny->getRect(), &_rcBattle))
	{
		if (_prinny->getRect().bottom > (_rcBattle.top + _rcBattle.bottom) / 2)
		{
			_prinny->saveData();
			SCENEMANAGER->changeScene("selectStage");
			return;
		}
	}

	if (IntersectRect(&RectMake(0, 0, 0, 0), &_prinny->getRect(), &_rcStore))
	{
		if (_prinny->getRect().top < (_rcStore.top + _rcStore.bottom) / 2 + 30)
		{
			_prinny->saveData();
			SCENEMANAGER->changeScene("store");
			return;
		}
	}
}

void town::setFrame()
{
	_count++;
	if (_count % 5 == 0)
	{
		_battlePortal->setFrameX(_battlePortal->getFrameX() + 1);

		if (_battlePortal->getFrameX() >= _battlePortal->getMaxFrameX())
		{
			_battlePortal->setFrameX(0);
		}
	}

	if (_count % 3 == 0)
	{
		_storePortal->setFrameX(_storePortal->getFrameX() + 1);

		if (_storePortal->getFrameX() >= _storePortal->getMaxFrameX())
		{
			_storePortal->setFrameX(0);
		}
	}

	if (_count % 5 == 0)
	{
		_etcPortal->setFrameX(_etcPortal->getFrameX() + 1);

		if (_etcPortal->getFrameX() >= _etcPortal->getMaxFrameX())
		{
			_etcPortal->setFrameX(0);
		}
	}
>>>>>>> refs/remotes/origin/development
}
