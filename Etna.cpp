#include "stdafx.h"
#include "etna.h"


etna::etna()
{
}


etna::~etna()
{
}

HRESULT etna::init()
{
	return E_NOTIMPL;
}

HRESULT etna::init(vector<TagTile*>& tile)
{
	_name = "etna";

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

void etna::release()
{
}

void etna::update()
{
}

void etna::render()
{
}

void etna::keyControl()
{
}

void etna::battleKeyControl()
{
}

void etna::move(int endX, int endY)
{
}

void etna::setImage()
{
}

void etna::setFrame()
{
}

void etna::saveData()
{
}

void etna::loadData()
{
}
