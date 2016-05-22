#include "stdafx.h"
#include "gameObject.h"
#include "gameObjectManager.h"

gameObject::gameObject()
{
}


gameObject::~gameObject()
{
}

HRESULT gameObject::init()
{
	return S_OK;
}

HRESULT gameObject::init(int x, int y, gameObjectManager * gom)
{
	return E_NOTIMPL;
}

HRESULT gameObject::init(const char * strkey, int x, int y, int imageNum, gameObjectManager * gom)
{
	return E_NOTIMPL;
}

void gameObject::release()
{
}

void gameObject::update()
{
}

void gameObject::render()
{
}

void gameObject::keyControl()
{
}

void gameObject::battleKeyControl()
{
}

void gameObject::move()
{
	if (!_isMove) return;

	if (fabs(_vRoute[_idx]->pivotX - _x) < _moveSpeed * 2 && fabs(_vRoute[_idx]->pivotY - _character->getFrameHeight() / 2 - _y) < _moveSpeed)
	{
		if (_vRoute[_idx]->x == _destX && _vRoute[_idx]->y == _destY)
		{
			_indexX = _destX;
			_indexY = _destY;
			_isMove = false;

			if (_isCharacter) _vRoute[_idx]->state = S_ONCHAR;
			else _vRoute[_idx]->state = S_ONENM;

			_characterState = IDLE;
			_idx = 0;

			_pivotY = _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY;
			return;
		}
		else
		{
			_indexX = _vRoute[_idx]->x;
			_indexY = _vRoute[_idx]->y;
			_idx++;
		}
	}

	//x축 검사하자

	// 길찾기 다음 벡터의 pivotX의 위치가 케릭터의 왼쪽이라면 [0][0]의 pivotX의 위치를 오른쪽으로 옴기자
	if (abs(_vRoute[_idx]->pivotX - _x) < _moveSpeed * 2)
	{
		_x = _vRoute[_idx]->pivotX;
	}
	else if (_vRoute[_idx]->pivotX < _x)
	{
		_cameraX -= _moveSpeed * 2;
		_x -= _moveSpeed * 2;
		_isRight = false;
	}
	// 길찾기 다음 벡터의 pivotX의 위치가 케릭터의 오른쪽이라면 [0][0]의 pivotX의 위치를 왼쪽으로 옴기자
	else if (_vRoute[_idx]->pivotX > _x)
	{
		_cameraX += _moveSpeed * 2;
		_x += _moveSpeed * 2;
		_isRight = true;
	}

	//y축 검사하자
	if (abs(_vRoute[_idx]->pivotY - _character->getFrameHeight() / 2 - _y) < _moveSpeed)
	{
		_y = _vRoute[_idx]->pivotY - _character->getFrameHeight() / 2;
	}
	else if (_vRoute[_idx]->pivotY - _character->getFrameHeight() / 2 < _y)
	{
		_cameraY -= _moveSpeed;
		_y -= _moveSpeed;
		_isUp = true;
	}
	else if (_vRoute[_idx]->pivotY - _character->getFrameHeight() / 2 > _y)
	{
		_cameraY += _moveSpeed;
		_y += _moveSpeed;
		_isUp = false;
	}

	_rc = RectMakeCenter(_x, _y, _character->getFrameWidth(), _character->getFrameHeight());
}

void gameObject::attack(int targetX, int targetY)
{
	if (_indexX > targetX && _indexY == targetY)
	{
		_characterDir = LT;
	}
	else if (_indexX < targetX && _indexY == targetY)
	{
		_characterDir = RB;
	}
	else if (_indexX == targetX && _indexY > targetY)
	{
		_characterDir = RT;
	}
	else if (_indexX == targetX && _indexY < targetY)
	{
		_characterDir = LB;
	}
	_characterState = ATTACK;
	_character->setFrameX(0);
	_isOrdering = true;
}

void gameObject::pain(int x, int y, int damage)
{
	if (_indexX > x && _indexY == y)
	{
		_characterDir = LT;
	}
	else if (_indexX < x && _indexY == y)
	{
		_characterDir = RB;
	}
	else if (_indexX == x && _indexY > y)
	{
		_characterDir = RT;
	}
	else if (_indexX == x && _indexY < y)
	{
		_characterDir = LB;
	}
	_characterState = PAIN;
	_character->setFrameX(0);
	_character->setFrameY(2);
	_isOrdering = true;
}

void gameObject::setImage()
{
}

void gameObject::setFrame()
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
				_isOrdering = false;
				return;
			}
		}
		_character->setFrameX(_curFrameX);
	}
}

void gameObject::saveData()
{
}

void gameObject::loadData()
{
}

void gameObject::setDirectionImage()
{
	if (_isRight)
	{
		if (_isUp)
		{
			_characterDir = RT;
		}
		else _characterDir = RB;
	}
	else
	{
		if (_isUp)
		{
			_characterDir = LT;
		}
		else _characterDir = LB;
	}
}

void gameObject::setCharacterMove(int endX, int endY, vector<TagTile*>& vRoute)
{
	if (!_isMove)
	{
		if (_gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->state != ZEN_POINT) _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->state = S_NONE;
		_isMove = true;
		_destX = endX;
		_destY = endY;
		_vRoute = vRoute;
		_characterState = WALK;
	}
}

void gameObject::previousState()
{

}

void gameObject::showPossibleMoveTile()
{
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		if (abs(_oldX - _gameObjMgr->getVTile()[i]->x) + abs(_oldY - _gameObjMgr->getVTile()[i]->y) <= _mv)
		{
			if (_gameObjMgr->getVTile()[i]->state == S_NONE)
				IMAGEMANAGER->findImage("walkable")->render(getMemDC(), _gameObjMgr->getVTile()[i]->rc.left, _gameObjMgr->getVTile()[i]->rc.top);
		}
	}
}

void gameObject::showPossibleAttackTile()
{
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		if (abs(_indexX + _indexY - _gameObjMgr->getVTile()[i]->x - _gameObjMgr->getVTile()[i]->y) == 1)
		{
			IMAGEMANAGER->findImage("walkable")->render(getMemDC(), _gameObjMgr->getVTile()[i]->rc.left, _gameObjMgr->getVTile()[i]->rc.top);
		}
	}
}
