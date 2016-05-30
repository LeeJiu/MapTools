#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(int x, int y, gameObjectManager * gom, battleCamera* cam)
{
	return E_NOTIMPL;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
}