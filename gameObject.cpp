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
		//_x = _vRoute[_idx]->x;
		//_y = _vRoute[_idx]->y;
		//_x = CENTERX;
		//_y = CENTERY - _prinny.image->getFrameHeight() / 2;
		//_prinny.rc = RectMakeIso(_tile[_x][_y]->pivotX, _tile[_x][_y]->pivotY, _prinny.image->getFrameWidth(), _prinny.image->getFrameHeight());
		if (_vRoute[_idx]->x == _destX && _vRoute[_idx]->y == _destY)
		{
			_indexX = _destX;
			_indexY = _destY;
			_isMove = false;
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
		_tile[0][0]->pivotX += _moveSpeed * 2;
	}
	// 길찾기 다음 벡터의 pivotX의 위치가 케릭터의 오른쪽이라면 [0][0]의 pivotX의 위치를 왼쪽으로 옴기자
	else if (_vRoute[_idx]->pivotX > _x)
	{
		_tile[0][0]->pivotX -= _moveSpeed * 2;
	}

	//y축 검사하자
	if (_vRoute[_idx]->pivotY - _character->getFrameHeight() / 2 < _y)
	{
		_tile[0][0]->pivotY += _moveSpeed;
	}
	else if (_vRoute[_idx]->pivotY - _character->getFrameHeight() / 2 > _y)
	{
		_tile[0][0]->pivotY -= _moveSpeed;
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

void gameObject::setCharacterMove(int endX, int endY, vector<TagTile*> vRoute)
{
	if (!_isMove)
	{
		_isMove = true;
		_destX = endX;
		_destY = endY;
		_vRoute = vRoute;
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
	for (int i = 0; i < 100; i++)
	{
		if (abs(_indexX - _vTile[i]->x) + abs(_indexY - _vTile[i]->y) <= _mv)
		{
			IMAGEMANAGER->findImage("walkable")->render(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top);
		}
	}
}
