#include "stdafx.h"
#include "character.h"


character::character()
{
}


character::~character()
{
}

HRESULT character::init()
{
<<<<<<< HEAD
	return E_NOTIMPL;
=======
	return S_OK;
}

HRESULT character::init(vector<TagTile*> tile)
{
	return S_OK;
>>>>>>> refs/remotes/origin/development
}

void character::release()
{
}

void character::update()
<<<<<<< HEAD
{
=======
{	
>>>>>>> refs/remotes/origin/development
}

void character::render()
{
	if(_isShowPossibleMoveTile) showPossibleMoveTile();
}
<<<<<<< HEAD
=======

void character::keyControl()
{
}

void character::battleKeyControl()
{

}

void character::move(int endX, int endY)
{

}

void character::setImage()
{
}

void character::setFrame()
{
}

void character::previousState()
{
}

void character::showPossibleMoveTile()
{
	for (int i = 0; i < 100; i++)
	{
		if (abs(_indexX - _vTile[i]->x) <= _mv && abs(_indexY - _vTile[i]->y) <= _mv)
		{
			IMAGEMANAGER->findImage("walkable")->render(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top);
		}
	}
}

void character::saveData()
{
}

void character::loadData()
{
}
>>>>>>> refs/remotes/origin/development
