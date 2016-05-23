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

	if (fabs(_vRoute[_idx]->pivotX - _x) < _moveSpeed * 2 
		&& fabs(_vRoute[_idx]->pivotY - _character->getFrameHeight() / 2 - _y) < _moveSpeed)
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

			if (_targetX != -1 && _targetY != -1 && !_isCharacter)
			{
				attack(_targetX, _targetY);
			}
			else if (_targetX == -1 && _targetY == -1 && !_isCharacter)
			{
				_gameObjMgr->setOrderList(OL_END);
			}
			return;
		}
		else
		{
			_currentMoveCount++;
			_indexX = _vRoute[_idx]->x;
			_indexY = _vRoute[_idx]->y;
			
			if (_currentMoveCount == _mv)
			{
				_isMove = false;

				if (_isCharacter) _vRoute[_idx]->state = S_ONCHAR;
				else _vRoute[_idx]->state = S_ONENM;
				
				_characterState = IDLE;
				_idx = 0;

				_pivotY = _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY;
				
				if (_targetX != -1 && _targetY != -1 && !_isCharacter)
				{
					attack(_targetX, _targetY);
				}
				else if (_targetX == -1 && _targetY == -1 && !_isCharacter)
				{
					_gameObjMgr->setOrderList(OL_END);
				}
				return;
			}
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
		_isRight = false;
		_isUp = true;
	}
	else if (_indexX < targetX && _indexY == targetY)
	{
		_characterDir = RB;
		_isRight = true;
		_isUp = false;
	}
	else if (_indexX == targetX && _indexY > targetY)
	{
		_characterDir = RT;
		_isRight = true;
		_isUp = true;
	}
	else if (_indexX == targetX && _indexY < targetY)
	{
		_characterDir = LB;
		_isRight = false;
		_isUp = false;
	}
	_characterState = ATTACK;
	_cameraX = _x - _sourWidth / 2;
	_cameraY = _y - _sourHeight / 2;
	_character->setFrameX(0);
}

void gameObject::pain(int x, int y, int damage)
{
	if (_indexX > x && _indexY == y)
	{
		_characterDir = LT;
		_isRight = false;
		_isUp = true;
	}
	else if (_indexX < x && _indexY == y)
	{
		_characterDir = RB;
		_isRight = true;
		_isUp = false;
	}
	else if (_indexX == x && _indexY > y)
	{
		_characterDir = RT;
		_isRight = true;
		_isUp = true;
	}
	else if (_indexX == x && _indexY < y)
	{
		_characterDir = LB;
		_isRight = false;
		_isUp = false;
	}
	_characterState = PAIN;
	_hp -= (damage / 10);
	_character->setFrameX(0);
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

void gameObject::setEnemyMove(int targetX, int targetY, int endX, int endY, vector<TagTile*>& vRoute)
{
	if (!_isMove)
	{
		_isMove = true;
		_currentMoveCount = 0;
		_destX = endX;
		_destY = endY;
		_oldX = _indexX;
		_oldY = _indexY;
		_vRoute = vRoute;

		//공격할 캐릭터 위치 저장 (에너미 -> 플레이어)
		_targetX = targetX;
		_targetY = targetY;

		_characterState = WALK;
	}
}

void gameObject::setCharacterMove(int endX, int endY, vector<TagTile*>& vRoute)
{
	if (!_isMove)
	{
		if (_gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->state != ZEN_POINT)
		{
			_gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->state = S_NONE;
		}

		_isMove = true;
		_currentMoveCount = 0;
		_destX = endX;
		_destY = endY;
		_oldX = _indexX;
		_oldY = _indexY;
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
		if (abs(_oldX - _gameObjMgr->getVTile()[i]->x) + abs(_oldY - _gameObjMgr->getVTile()[i]->y) < _mv)
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
		if ((abs(_indexX - _gameObjMgr->getVTile()[i]->x) == 0 && abs(_indexY - _gameObjMgr->getVTile()[i]->y) == 1)
			|| (abs(_indexX - _gameObjMgr->getVTile()[i]->x) == 1 && abs(_indexY - _gameObjMgr->getVTile()[i]->y) == 0))
		{
			IMAGEMANAGER->findImage("walkable")->render(getMemDC(), _gameObjMgr->getVTile()[i]->rc.left, _gameObjMgr->getVTile()[i]->rc.top);
		}
	}
}