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
	SOUNDMANAGER->play("town_bg", 1.f);

	IMAGEMANAGER->addImage("town_background", "image/background/town_background.bmp", 4155, 1704, true, 0xff00ff);
	IMAGEMANAGER->addImage("town_background_pixel", "image/background/town_background_pixel.bmp", 4155, 1704, false, false);

	IMAGEMANAGER->addFrameImage("entrance_battle", "image/background/entrance_battle.bmp", 2695, 266, 11, 1, false, false);
	IMAGEMANAGER->addFrameImage("entrance_store", "image/background/entrance_store.bmp", 3969, 220, 27, 1, false, false);
	IMAGEMANAGER->addFrameImage("entrance_etc", "image/background/entrance_etc.bmp", 1694, 279, 7, 1, false, false);
	IMAGEMANAGER->addFrameImage("mercenary", "image/character/mercenary_idle.bmp", 498, 616, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("store", "image/character/store_idle.bmp", 498, 305, 6, 2, true, 0xff00ff);

	_town = IMAGEMANAGER->findImage("town_background");
	_townPixel = IMAGEMANAGER->findImage("town_background_pixel");
	_storeNPC = IMAGEMANAGER->findImage("store");
	_mercenaryNPC = IMAGEMANAGER->findImage("mercenary");
	_mercenaryNPC->setFrameY(1);

	_mercenaryShadow = IMAGEMANAGER->findImage("shadow");
	_storeShadow = IMAGEMANAGER->findImage("shadow");

	_battlePortal = IMAGEMANAGER->findImage("entrance_battle");
	_storePortal = IMAGEMANAGER->findImage("entrance_store");
	_etcPortal = IMAGEMANAGER->findImage("entrance_etc");

	_prinny = new prinny;
	_prinny->init();

	_sourX = 1790;
	_sourY = 490;
	
	//���� �Ա� ��ǥ
	//_sourX = 2600;
	//_sourY = 60;

	return S_OK;
}

void town::release()
{
	SAFE_DELETE(_prinny);

	SOUNDMANAGER->stop("town_bg");
}

void town::update()
{
	_prinny->update();

	keyControl();
	pixelCollision(_prinny->getRect());
	setFrame();

	enterEntrance();
}

void town::render()
{
	_town->render(getMemDC(), 0, 0, _sourX, _sourY, WINSIZEX, WINSIZEY);
	//_townPixel->render(getMemDC(), 0, 0, _sourX, _sourY, WINSIZEX, WINSIZEY);
	
	//��Ż �̹��� ������
	_battlePortal->frameRender(getMemDC(), 2061 - _sourX, 1012 - _sourY,
		_battlePortal->getFrameX(), _battlePortal->getFrameY());

	_storePortal->frameRender(getMemDC(), 1595 - _sourX, 371 - _sourY,
		_storePortal->getFrameX(), _storePortal->getFrameY());

	_etcPortal->frameRender(getMemDC(), 1134 - _sourX, 478 - _sourY,
		_etcPortal->getFrameX(), _etcPortal->getFrameY());

	_mercenaryShadow->render(getMemDC(), 1208 - _sourX - 15, 535 - _sourY + 120);
	_storeShadow->render(getMemDC(), 1628 - _sourX - 15, 405 - _sourY + 120);

	_mercenaryNPC->frameRender(getMemDC(), 1208 - _sourX, 535 - _sourY, _mercenaryNPC->getFrameX(), _mercenaryNPC->getFrameY());
	_storeNPC->frameRender(getMemDC(), 1628 - _sourX, 405 - _sourY, _storeNPC->getFrameX(), _storeNPC->getFrameY());

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
	//���ʺ��� �ȼ� �˻�
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

	//������ �ȼ� �˻�
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

	//���� �ȼ� �˻�
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

	//�Ʒ��� �ȼ� �˻�
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
	_rcMercenary = RectMake(1134 - _sourX, 478 - _sourY, _etcPortal->getFrameWidth() / 2, _etcPortal->getFrameHeight() / 2);

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

	if (IntersectRect(&RectMake(0, 0, 0, 0), &_prinny->getRect(), &_rcMercenary))
	{
		_prinny->saveData();
		SCENEMANAGER->changeScene("mercenaryStore");
		return;
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

	if (_count % 8 == 0)
	{
		_mercenaryNPC->setFrameX(_mercenaryNPC->getFrameX() + 1);

		if (_mercenaryNPC->getFrameX() >= _mercenaryNPC->getMaxFrameX())
		{
			_mercenaryNPC->setFrameX(0);
		}
	}

	if (_count % 8 == 0)
	{
		_storeNPC->setFrameX(_storeNPC->getFrameX() + 1);

		if (_storeNPC->getFrameX() >= _storeNPC->getMaxFrameX())
		{
			_storeNPC->setFrameX(0);
		}
	}
}
