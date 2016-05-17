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

void gameObject::move(int endX, int endY)
{
	// 목적지의 도착했을때
	if (abs(_tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotX - _x) < 3
		&& abs(_tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotY - _character->getFrameHeight() / 2 - _y) < 3)
	{
		if (_vRoute[_idx]->x == endX && _vRoute[_idx]->y == endY)
		{
			_indexX = _destX;
			_indexY = _destY;
			_isMove = false;
			_idx = 0;
			return;
		}
		else _idx++;
	}

	//x축 검사하자
	if (abs(_tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotX - _x) < _moveSpeed * 2)
	{
		if (_vRoute[_idx]->x == _vRoute[_idx]->y)
		{
			_tile[0][0]->pivotX = _tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotX;
		}
		else if (_vRoute[_idx]->x > _vRoute[_idx]->y)
		{
			_tile[0][0]->pivotX = _tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotX + WIDTH / 2 * (_vRoute[_idx]->y - _vRoute[_idx]->x);
		}
		else if (_vRoute[_idx]->x < _vRoute[_idx]->y)
		{
			_tile[0][0]->pivotX = _tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotX - WIDTH / 2 * (_vRoute[_idx]->y - _vRoute[_idx]->x);
		}
	}
	else if (_tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotX < _x)
	{
		_tile[0][0]->pivotX += _moveSpeed * 2;
	}
	else if (_tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotX > _x)
	{
		_tile[0][0]->pivotX -= _moveSpeed * 2;
	}

	//y축 검사하자
	if (abs(_tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotY - _character->getFrameHeight() / 2 - _y) < _moveSpeed)
	{
		if (_vRoute[_idx]->x == _vRoute[_idx]->y)
		{
			_tile[0][0]->pivotY = _tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotY - WIDTH * _vRoute[_idx]->y;
		}
		else if (_vRoute[_idx]->x > _vRoute[_idx]->y)
		{
			_tile[0][0]->pivotY = _tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotY - WIDTH / 2 * (_vRoute[_idx]->y + _vRoute[_idx]->x);
		}
		else if (_vRoute[_idx]->x < _vRoute[_idx]->y)
		{
			_tile[0][0]->pivotY = _tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotY - WIDTH / 2 * (_vRoute[_idx]->y + _vRoute[_idx]->x);
		}
	}
	else if (_tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotY - _character->getFrameHeight() / 2 < _y)
	{
		_tile[0][0]->pivotY -= _moveSpeed * 2;
	}
	else if (_tile[_vRoute[_idx]->x][_vRoute[_idx]->y]->pivotY - _character->getFrameHeight() / 2 > _y)
	{
		_tile[0][0]->pivotY += _moveSpeed * 2;
	}

	// [0][0]번째의 pivot기준으로 렉트 재갱신 하자
	setTilePosition(_tile[0][0]->pivotX, _tile[0][0]->pivotY);
}

void gameObject::attack(int targetX, int targetY)
{
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
	for (int i = 0; i < 100; i++)
	{
		if (abs(_indexX - _vTile[i]->x) + abs(_indexY - _vTile[i]->y) <= _mv)
		{
			IMAGEMANAGER->findImage("walkable")->render(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top);
		}
	}
}
