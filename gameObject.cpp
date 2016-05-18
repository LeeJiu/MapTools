#include "stdafx.h"
#include "gameObject.h"


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

HRESULT gameObject::init(vector<TagTile*> tile)
{
	return S_OK;
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
			if(_isCharacter) _vRoute[_idx]->state = S_ONCHAR;
			else _vRoute[_idx]->state = S_ONENM;
			_characterState = IDLE;
			_idx = 0;
			return;
		}
		else
		{
			_idx++;
		}
	}

	//x축 검사하자

	// 길찾기 다음 벡터의 pivotX의 위치가 케릭터의 왼쪽이라면 [0][0]의 pivotX의 위치를 오른쪽으로 옴기자
	if (_vRoute[_idx]->pivotX < _x)
	{
		_isRight = false;
		_tile[0][0]->pivotX += _moveSpeed * 2;
	}
	// 길찾기 다음 벡터의 pivotX의 위치가 케릭터의 오른쪽이라면 [0][0]의 pivotX의 위치를 왼쪽으로 옴기자
	else if (_vRoute[_idx]->pivotX > _x)
	{
		_isRight = true;
		_tile[0][0]->pivotX -= _moveSpeed * 2;
	}

	//y축 검사하자
	if (_vRoute[_idx]->pivotY - _character->getFrameHeight() / 2 < _y)
	{
		_isUp = true;
		_tile[0][0]->pivotY += _moveSpeed;
	}
	else if (_vRoute[_idx]->pivotY - _character->getFrameHeight() / 2 > _y)
	{
		_isUp = false;
		_tile[0][0]->pivotY -= _moveSpeed;
	}

	// [0][0]번째의 pivot기준으로 렉트 재갱신 하자
	gameObject::setTilePosition(_tile[0][0]->pivotX, _tile[0][0]->pivotY);
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
}

void gameObject::setImage()
{
}

void gameObject::setFrame()
{
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

void gameObject::setCharacterMove(int endX, int endY, vector<TagTile*> vRoute)
{
	if (!_isMove)
	{
		if(_tile[_indexX][_indexY]->state != S_ZEN) _tile[_indexX][_indexY]->state = S_NONE;
		_isMove = true;
		_destX = endX;
		_destY = endY;
		_vRoute = vRoute;
		_characterState = WALK;
	}
}

void gameObject::setTilePosition(float x, float y)
{
	POINT firstPivot = { x, y };

	for (int i = 0; i < TILENUM; i++)		// 세로 ( 열 )
	{
		for (int j = 0; j < TILENUM; j++)	// 가로 ( 행 )
		{
			_tile[j][i]->rc = RectMakeCenter(firstPivot.x + j * _tile[j][i]->width / 2 - i * _tile[j][i]->width / 2,
				firstPivot.y + j * _tile[j][i]->width / 4 + i * _tile[j][i]->width / 4, _tile[j][i]->width, _tile[j][i]->height);
			_tile[j][i]->pivotX = (_tile[j][i]->rc.left + _tile[j][i]->rc.right) / 2;
			_tile[j][i]->pivotY = (_tile[j][i]->rc.top + _tile[j][i]->rc.bottom) / 2;
		}
	}
}

void gameObject::previousState()
{

}

void gameObject::showPossibleMoveTile()
{
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		if (abs(_indexX - _vTile[i]->x) + abs(_indexY - _vTile[i]->y) <= _mv)
		{
			if(_vTile[i]->state == S_NONE)
			IMAGEMANAGER->findImage("walkable")->render(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top);
		}
	}
}

void gameObject::showPossibleAttackTile()
{
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		if (_indexX == _vTile[i]->x && _indexY - 1 == _vTile[i]->y)
		{
			IMAGEMANAGER->findImage("attackable")->render(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top);
		}
		else if (_indexX == _vTile[i]->x && _indexY + 1 == _vTile[i]->y)
		{
			IMAGEMANAGER->findImage("attackable")->render(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top);
		}
		else if (_indexX - 1 == _vTile[i]->x && _indexY == _vTile[i]->y)
		{
			IMAGEMANAGER->findImage("attackable")->render(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top);
		}
		else if (_indexX + 1== _vTile[i]->x && _indexY == _vTile[i]->y)
		{
			IMAGEMANAGER->findImage("attackable")->render(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top);
		}
	}
}
