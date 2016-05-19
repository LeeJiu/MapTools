#include "stdafx.h"
#include "objects.h"


objects::objects()
{
}


objects::~objects()
{
}

HRESULT objects::init(const char* strkey, int x, int y, int imageNum, vector<TagTile*> tile)
{
	_name = strkey;

	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		_tile[i] = tile[i]; //기본타일과 같느니라.
	}

	_imageNum = imageNum;
	
	//_character = new image;
	_character = IMAGEMANAGER->findImage(_name);
	_x = x;
	_y = y;

	//렉트생성용.
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

	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		if (_x == _tile[i]->x && _y == _tile[i]->y)
		{
			if (_height < TILESIZE / 2)
				_rcSommon = RectMake(_tile[i]->pivotX - _width / 2, _tile[i]->pivotY + TILESIZE / 4 - _height / 2, _width, _height);
			else if (_height > TILESIZE / 2)
				_rcSommon = RectMake(_tile[i]->pivotX - _width / 2, _tile[i]->rc.bottom - _height, _width, _height);
		}
	}

	_isFrame = false;
	if (_imageNum == 4) _isFrame = true;



	_count = 0;
	_curFrameX = 0;

	return S_OK;
}

void objects::release()
{

}

void objects::update()
{
	_count++;

	//렉트셋팅
	_rcSommon = RectMake(_rcSommon.left, _rcSommon.top, _rcSommon.right, _rcSommon.bottom);

	//프레임셋팅
	if (_count % 5 == 0)
	{
		_curFrameX++;
		if (_curFrameX > _character->getMaxFrameX())
		{
			_curFrameX = 0;
		}
		_character->setFrameX(_curFrameX);
	}
}

void objects::render()
{
	if (_isFrame)
		_character->frameRender(getMemDC(), _rcSommon.left, _rcSommon.top);
	else
		_character->render(getMemDC(), _rcSommon.left, _rcSommon.top);
}

void objects::previousState()
{

}

void objects::showPossibleMoveTile()
{

}

void objects::setItem(const char* itemName)
{

}

int objects::getHell()
{

	return 0;
}
void objects::setHell(int hell)
{

}

void objects::setMercenary(const char* characterName)
{

}