#include "stdafx.h"
#include "catsaver.h"
#include "gameObjectManager.h"

catsaver::catsaver()
{
}


catsaver::~catsaver()
{
}


HRESULT catsaver::init(int x, int y, gameObjectManager * gom)
{
	_name = "catsaver";

	_indexX = x;
	_indexY = y;

	_gameObjMgr = gom;
	_shadow = IMAGEMANAGER->findImage("shadow");
	_character = new image;
	_character->init("image/character/catsaver_idle.bmp", 612, 500, 6, 4, true, 0xff00ff);
	_characterState = IDLE;
	_characterDir = LB;
	_curFrameX = 0;
	_count = 0;

	_mv = 3;
	_isShow = false;

	_moveSpeed = 3;

	_rc = RectMakeIso(_gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotX, _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY,
		_character->getFrameWidth(), _character->getFrameHeight());
	_x = (_rc.right + _rc.left) / 2;
	_y = (_rc.top + _rc.bottom) / 2;

	_maxHp = _hp = 100;

	_hpBar = new progressBar;
	_hpBar->init(_x, _rc.top - 10, 120, 10);
	_hpBar->gauge(_hp, _maxHp);

	return S_OK;
}

void catsaver::release()
{
	SAFE_DELETE(_character);
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void catsaver::update()
{
	_hpBar->setX(_x);
	_hpBar->setY(_rc.top - 10);
	_hpBar->update();

	gameObject::setDirectionImage();
	setImage();
	setFrame();

	if (!_isMove)
	{
		_rc = RectMakeIso(_gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotX, _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY, 
			_character->getFrameWidth(), _character->getFrameHeight());
		_x = (_rc.right + _rc.left) / 2;
		_y = (_rc.top + _rc.bottom) / 2;
	}
	_pivotY = _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY;
	battleKeyControl();
	gameObject::move();
}

void catsaver::render()
{
	if (_isShowPossibleMoveTile) gameObject::showPossibleMoveTile();
	if (_isShowPossibleAttackTile) gameObject::showPossibleAttackTile();

	if (_x > _cameraX && _x < _cameraX + WINSIZEX && _y > _cameraY && _y < _cameraY + WINSIZEY)
	{
		_shadow->render(getMemDC(), _rc.left - 15, _rc.bottom - _shadow->getFrameHeight() / 2);
		//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		_character->frameRender(getMemDC(), _rc.left, _rc.top, _curFrameX, _curFrameY);
		_hpBar->render();

	}
}

void catsaver::setImage()
{
	switch (_characterState)
	{
	case IDLE:
		_character->init("image/character/catsaver_idle.bmp", 612, 500, 6, 4, true, 0xff00ff);
		break;
	case WALK:
		_character->init("image/character/catsaver_idle.bmp", 744, 528, 6, 4, true, 0xff00ff);
		break;
	case ATTACK:
		_character->init("image/character/catsaver_attack.bmp", 1295, 856, 5, 4, true, 0xff00ff);
		break;
	case PAIN:
		_character->init("image/character/catsaver_pain.bmp", 101, 416, 1, 1, true, 0xff00ff);
	}
}

void catsaver::setFrame()
{
	_count++;

	switch (_characterDir)
	{
	case LB:
		_curFrameY = 0;
		_character->setFrameY(_curFrameY);
		break;

	case RB:
		_curFrameY = 1;
		_character->setFrameY(_curFrameY);
		break;

	case RT:
		_curFrameY = 2;
		_character->setFrameY(_curFrameY);
		break;

	case LT:
		_curFrameY = 3;
		_character->setFrameY(_curFrameY);
		break;
	}

	if (_count % 7 == 0)
	{
		_curFrameX++;
		if (_curFrameX > _character->getMaxFrameX())
		{
			_curFrameX = 0;
			/*if (_characterState == ATTACK)
			{
			_characterState = IDLE;
			_isOrdering = false;
			return;
			}*/
		}
		_character->setFrameX(_curFrameX);
	}
}
void catsaver::setMercenary(const char * characterName)
{
}

void catsaver::setItem(const char* itemName, bool isWear)
{

}

int catsaver::getHell()
{
	return 0;
}

void catsaver::setHell(int hell)
{

}
