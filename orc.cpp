#include "stdafx.h"
#include "orc.h"


orc::orc()
{
}


orc::~orc()
{
}

HRESULT orc::init(int x, int y, vector<TagTile*> tile)
{
	_indexX = x;
	_indexY = y;

	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		_tile[i % TILENUM][i / TILENUM] = tile[i];
	}

	_character = new image;
	_character->init("image/character/orc_idle.bmp", 1008, 668, 6, 4, true, 0xff00ff);
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

void orc::release()
{

}

void orc::update()
{
	if (!_isMove)
	{
		_rc = RectMakeIso(_tile[_indexX][_indexY]->pivotX, _tile[_indexX][_indexY]->pivotY, _character->getFrameWidth(), _character->getFrameHeight());
		_x = (_rc.right + _rc.left) / 2;
		_y = (_rc.top + _rc.bottom) / 2;
	}
	battleKeyControl();
	gameObject::move();
}

void orc::render()
{
	if (_isShowPossibleMoveTile) gameObject::showPossibleMoveTile();
	if (_isShowPossibleAttackTile) gameObject::showPossibleAttackTile();
	_character->frameRender(getMemDC(), _rc.left, _rc.top, _curFrameX, _curFrameY);
}

void orc::setMercenary(const char * characterName)
{
}

<<<<<<< HEAD
void orc::setItem(const char * itemName, bool isWear)
=======
void orc::setItem(const char* itemName, bool isWear)
>>>>>>> refs/remotes/origin/moobin
{
}

int orc::getHell()
{
	return 0;
}

void orc::setHell(int hell)
{

}