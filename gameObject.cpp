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
	_mapLoad = new battleMapLoad;
	_mapLoad->init();

	_aStar = new aStar;
	//_aStar->init(_mapLoad->getTileVector()); 이것은 지현이가 TagTile* 로 변경하면 주석 풀것

	_moveSpeed = 3;

	return S_OK;
}

void gameObject::release()
{
	SAFE_DELETE(_mapLoad);
	SAFE_DELETE(_aStar);
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
	if (abs(_tile[_vRoute[_idx]->x][_vRoute[_idx]->y].pivotX - _x) < 3
		&& abs(_tile[_vRoute[_idx]->x][_vRoute[_idx]->y].pivotY - _character->getFrameHeight() / 2 - _y) < 3)
	{
		if (_vRoute[_idx]->x == _destX && _vRoute[_idx]->y == _destY)
		{
			_idxX = _destX;
			_idxY = _destY;
			_isMove = false;
			_idx = 0;
			_aStar->reset();
			return;
		}
		else _idx++;
	}

	//x축 검사하자
	if (abs(_tile[_vRoute[_idx]->x][_vRoute[_idx]->y].pivotX - _x) < _moveSpeed * 2)
	{
		_x = _tile[_vRoute[_idx]->x][_vRoute[_idx]->y].pivotX;
	}
	else if (_tile[_vRoute[_idx]->x][_vRoute[_idx]->y].pivotX < _x)
	{
		_x -= _moveSpeed * 2;
	}
	else if (_tile[_vRoute[_idx]->x][_vRoute[_idx]->y].pivotX > _x)
	{
		_x += _moveSpeed * 2;
	}

	//y축 검사하자
	if (abs(_tile[_vRoute[_idx]->x][_vRoute[_idx]->y].pivotY - _character->getFrameHeight() / 2 - _y) < _moveSpeed)
	{
		_y = _tile[_vRoute[_idx]->x][_vRoute[_idx]->y].pivotY - _character->getFrameHeight() / 2;
	}
	else if (_tile[_vRoute[_idx]->x][_vRoute[_idx]->y].pivotY - _character->getFrameHeight() / 2 < _y)
	{
		_y -= _moveSpeed;
	}
	else if (_tile[_vRoute[_idx]->x][_vRoute[_idx]->y].pivotY - _character->getFrameHeight() / 2 > _y)
	{
		_y += _moveSpeed;
	}

	_rc = RectMakeCenter(_x, _y, _character->getFrameWidth(), _character->getFrameHeight());
}

void gameObject::attack()
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
