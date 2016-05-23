#include "stdafx.h"
#include "orc.h"
#include "gameObjectManager.h"

orc::orc()
{
}


orc::~orc()
{
}


HRESULT orc::init(int x, int y, gameObjectManager * gom)
{
	_name = "orc";

	_indexX = x;
	_indexY = y;
	
	_targetX = -1;
	_targetY = -1;

	_gameObjMgr = gom;
	_shadow = IMAGEMANAGER->findImage("shadow");
	_character = new image;
	_character->init("image/character/orc_idle.bmp", 1008, 668, 6, 4, true, 0xff00ff);
	_characterState = IDLE;
	_characterDir = LB;
	_curFrameX = 0;

	_mv = 5;
	_isShow = false;
	_moveSpeed = 3;

	_moveSpeed = 3;

	_rc = RectMakeIso(_gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotX, _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY, 
		_character->getFrameWidth(), _character->getFrameHeight());
	_x = (_rc.right + _rc.left) / 2;
	_y = (_rc.top + _rc.bottom) / 2;

	_maxHp = _hp = 100;

	_hpBar = new progressBar;
	_hpBar->init(_x, _rc.top - 10, 120, 10);
	_hpBar->gauge(_hp, _maxHp);

	_pivotY = _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY;

	return S_OK;
}

void orc::release()
{
	SAFE_DELETE(_character);
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void orc::update()
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
	else
	{
		gameObject::move();
	}
	_pivotY = _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY;
}

void orc::render()
{
	if (_isShowPossibleMoveTile) gameObject::showPossibleMoveTile();
	if (_isShowPossibleAttackTile) gameObject::showPossibleAttackTile();
	
	if (_x > _cameraX && _x < _cameraX + WINSIZEX && _y > _cameraY && _y < _cameraY + WINSIZEY)
	{
		_shadow->render(getMemDC(), _rc.left + 15, _rc.bottom - _shadow->getFrameHeight() / 2);
		_character->frameRender(getMemDC(), _rc.left, _rc.top, _curFrameX, _curFrameY);
		_hpBar->render();
	}
}

void orc::setImage()
{
	switch (_characterState)
	{
	case IDLE:
		_character->init("image/character/orc_idle.bmp", 1008, 668, 6, 4, true, 0xff00ff);
		break;
	case WALK:
		_character->init("image/character/orc_walk.bmp", 534, 668, 6, 4, true, 0xff00ff);
		break;
	case ATTACK:
		_character->init("image/character/orc_attack.bmp", 1764, 668, 7, 4, true, 0xff00ff);
		break;
	case PAIN:
		_character->init("image/character/orc_pain.bmp", 189, 596, 1, 4, true, 0xff00ff);
		break;
	}
}

void orc::setFrame()
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

	if (_count % 10 == 0)
	{
		_curFrameX++;
		if (_curFrameX > _character->getMaxFrameX())
		{
			_curFrameX = 0;
			if (_characterState == ATTACK)
			{
				_characterState = IDLE;
				_gameObjMgr->setOrderList(OL_END);
				return;
			}
			else if (_characterState == PAIN)
			{
				_characterState = IDLE;
				return;
			}
		}
		_character->setFrameX(_curFrameX);
	}
}

void orc::setMercenary(const char * characterName)
{
}


void orc::setItem(const char* itemName, bool isWear)
{
}

int orc::getHell()
{
	return 0;
}

void orc::setHell(int hell)
{

}
