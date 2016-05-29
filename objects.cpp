#include "stdafx.h"
#include "objects.h"
#include "gameObjectManager.h"

objects::objects()
{
}


objects::~objects()
{
}


HRESULT objects::init(const char * strkey, int x, int y, int imageNum, gameObjectManager * gom, battleCamera* cam)
{
	_name = strkey;

	_imageNum = imageNum;

	//_character = new image;
	_character = IMAGEMANAGER->findImage(_name);
	_indexX = x;
	_indexY = y;

	//��Ʈ������.
	if (_imageNum == 4)
	{
		_width = _character->getFrameWidth();
		_height = _character->getFrameHeight();
	}
	else
	{
		_width = _character->getWidth();
		_height = _character->getHeight();
	}

	_gameObjMgr = gom;

	if (_height < WIDTH / 2)
		_rc = RectMake(_gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotX - _width / 2, _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY + WIDTH / 4 - _height / 2, _width, _height);
	else if (_height > WIDTH / 2)
		_rc = RectMake(_gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotX - _width / 2, _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->rc.bottom - _height, _width, _height);


	_isFrame = false;
	if (_imageNum == 4) _isFrame = true;

	_count = 0;
	_curFrameX = 0;

	_pivotY = _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY;

	return S_OK;
}

void objects::release()
{

}

void objects::update()
{
	_count++;

	//�����Ӽ���
	if (_count % 5 == 0)
	{
		_curFrameX++;
		if (_curFrameX > _character->getMaxFrameX())
		{
			_curFrameX = 0;
		}
		_character->setFrameX(_curFrameX); 
		
	}


	if (_height < WIDTH / 2)
		_rc = RectMake(_gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotX - _width / 2, _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotY + WIDTH / 4 - _height / 2, _width, _height);
	else if (_height > WIDTH / 2)
		_rc = RectMake(_gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->pivotX - _width / 2, _gameObjMgr->getVTile()[_indexY * TILENUM + _indexX]->rc.bottom - _height, _width, _height);

	_x = (_rc.right + _rc.left) / 2;
	_y = (_rc.top + _rc.bottom) / 2;
}

void objects::render()
{
	if (_x > _cameraX && _x < _cameraX + WINSIZEX && _y > _cameraY && _y < _cameraY + WINSIZEY)
	{
		if (_isFrame)
			_character->frameRender(getMemDC(), _rc.left, _rc.top);
		else
		{
			//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
			_character->render(getMemDC(), _rc.left, _rc.top);
		}
	}
}

void objects::previousState()
{

}

void objects::showPossibleMoveTile()
{

}

int objects::getHell()
{

	return 0;
}
void objects::setHell(int hell)
{

}

void objects::setItem(const char * itemName, bool isWear)
{
}

void objects::setMercenary(const char* characterName)
{

}