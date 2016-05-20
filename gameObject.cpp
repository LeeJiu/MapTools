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

HRESULT gameObject::init(const char* strkey, int x, int y, int imageNum, vector<TagTile*> tile)
{
	return S_OK;
}

HRESULT gameObject::init(int x, int y, vector<TagTile*> tile)
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

	//x�� �˻�����

	// ��ã�� ���� ������ pivotX�� ��ġ�� �ɸ����� �����̶�� [0][0]�� pivotX�� ��ġ�� ���������� �ȱ���
	if (_vRoute[_idx]->pivotX < _x)
	{
		_isRight = false;
		_tile[0][0]->pivotX += _moveSpeed * 2;
	}
	// ��ã�� ���� ������ pivotX�� ��ġ�� �ɸ����� �������̶�� [0][0]�� pivotX�� ��ġ�� �������� �ȱ���
	else if (_vRoute[_idx]->pivotX > _x)
	{
		_isRight = true;
		_tile[0][0]->pivotX -= _moveSpeed * 2;
	}

	//y�� �˻�����
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

	// [0][0]��°�� pivot�������� ��Ʈ �簻�� ����
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
	_character->setFrameX(0);
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

void gameObject::setCharacterMove(int endX, int endY, vector<TagTile*> vRoute)
{
	if (!_isMove)
	{
		if(_tile[_indexX][_indexY]->state != ZEN_POINT) _tile[_indexX][_indexY]->state = S_NONE;
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

	for (int i = 0; i < TILENUM; i++)		// ���� ( �� )
	{
		for (int j = 0; j < TILENUM; j++)	// ���� ( �� )
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
	IMAGEMANAGER->findImage("attackable")->render(getMemDC(), _tile[_indexX + 1][_indexY]->rc.left, _tile[_indexX + 1][_indexY]->rc.top);
	IMAGEMANAGER->findImage("attackable")->render(getMemDC(), _tile[_indexX - 1][_indexY]->rc.left, _tile[_indexX - 1][_indexY]->rc.top);
	IMAGEMANAGER->findImage("attackable")->render(getMemDC(), _tile[_indexX][_indexY + 1]->rc.left, _tile[_indexX][_indexY + 1]->rc.top);
	IMAGEMANAGER->findImage("attackable")->render(getMemDC(), _tile[_indexX][_indexY - 1]->rc.left, _tile[_indexX][_indexY - 1]->rc.top);

}
