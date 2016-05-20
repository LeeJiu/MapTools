#include "stdafx.h"
#include "catsaver.h"


catsaver::catsaver()
{
}


catsaver::~catsaver()
{
}

HRESULT catsaver::init(int x, int y, vector<TagTile*> tile)
{
	_name = "catsaver";

	_indexX = x;
	_indexY = y;
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		_tile[i % TILENUM][i / TILENUM] = tile[i];
	}

	_pivotY = _tile[_indexX][_indexY]->pivotY;
	_character = new image;
	_character->init("image/character/catsaver_idle.bmp", 612, 500, 6, 4, true, 0xff00ff);
	_characterState = IDLE;
	_characterDir = LB;
	_curFrameX = 0;
	_count = 0;

	_mv = 3;
	_isShow = false;

	_vTile = tile;

	_moveSpeed = 3;

	return S_OK;
}

void catsaver::release()
{

}

void catsaver::update()
{
	if (!_isMove)
	{
		_rc = RectMakeIso(_tile[_indexX][_indexY]->pivotX, _tile[_indexX][_indexY]->pivotY, _character->getFrameWidth(), _character->getFrameHeight());
		_x = (_rc.right + _rc.left) / 2;
		_y = (_rc.top + _rc.bottom) / 2;
	}
	_pivotY = _tile[_indexX][_indexY]->pivotY;
	battleKeyControl();
	gameObject::move();
}

void catsaver::render()
{
	if (_isShowPossibleMoveTile) gameObject::showPossibleMoveTile();
	if (_isShowPossibleAttackTile) gameObject::showPossibleAttackTile();
	{
		//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		_character->frameRender(getMemDC(), _rc.left, _rc.top, _curFrameX, _curFrameY);
	}
}

void catsaver::setMercenary(const char * characterName)
{
}

void catsaver::setItem(const char* itemName, bool isWear)
{

}

int catsaver::getHell()
{
	return 0;
}

void catsaver::setHell(int hell)
{

}
