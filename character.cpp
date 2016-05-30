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

HRESULT character::init(int x, int y, gameObjectManager * gom, battleCamera* cam)
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

void character::previousState()
{
}

void character::saveData()
{
}

void character::loadData()
{
}