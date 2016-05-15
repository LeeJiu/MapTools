#include "stdafx.h"
#include "flonne.h"


flonne::flonne()
{
}


flonne::~flonne()
{
}

HRESULT flonne::init()
{
	return E_NOTIMPL;
}

HRESULT flonne::init(vector<TagTile*>& tile)
{
	_name = "flonne";

	loadData();

	_character = IMAGEMANAGER->findImage("prinny_idle");
	_characterState = IDLE;
	_characterDir = LB;
	_curFrameX = 0;
	_count = 0;

	_aStar = new aStar;
	_aStar->init(tile); //이것은 지현이가 TagTile* 로 변경하면 주석 풀것

	_moveSpeed = 3;

	return S_OK;
}

void flonne::release()
{
}

void flonne::update()
{
}

void flonne::render()
{
}

void flonne::keyControl()
{
}

void flonne::battleKeyControl()
{
}

void flonne::move(int endX, int endY)
{
}

void flonne::setImage()
{
}

void flonne::setFrame()
{
}

void flonne::saveData()
{
}

void flonne::loadData()
{
}

void flonne::setItem(const char * itemName)
{
}
