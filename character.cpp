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
	return S_OK;
}

HRESULT character::init(vector<TagTile*>& tile)
{
	return E_NOTIMPL;
}

void character::release()
{
}

void character::update()
{	
}

void character::render()
{
}

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

	}
}

void character::saveData()
{
}

void character::loadData()
{
}