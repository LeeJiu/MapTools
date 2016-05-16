#include "stdafx.h"
#include "raspberyl.h"


raspberyl::raspberyl()
{
}


raspberyl::~raspberyl()
{
}

HRESULT raspberyl::init()
{
	return E_NOTIMPL;
}

HRESULT raspberyl::init(vector<TagTile*> tile)
{
	for (int i = 0; i < 100; i++)
	{
		_tile[i % TILENUM][i / TILENUM] = tile[i];
	}

	_name = "raspberyl";

	loadData();

	_character = IMAGEMANAGER->findImage("prinny_idle");
	_characterState = IDLE;
	_characterDir = LB;
	_curFrameX = 0;
	_count = 0;

	_moveSpeed = 3;

	return S_OK;
}

void raspberyl::release()
{
}

void raspberyl::update()
{
}

void raspberyl::render()
{
}

void raspberyl::keyControl()
{
}

void raspberyl::battleKeyControl()
{
}

void raspberyl::move(int endX, int endY)
{
}

void raspberyl::setImage()
{
}

void raspberyl::setFrame()
{
}

void raspberyl::saveData()
{
}

void raspberyl::loadData()
{
}

void raspberyl::setItem(const char * itemName)
{
}
