#include "stdafx.h"
#include "town.h"


town::town()
{
}


town::~town()
{
}

HRESULT town::init()
{
	_prinny = new prinny;
	_prinny->init();


	return S_OK;
}

void town::release()
{
	SAFE_DELETE(_prinny);
}

void town::update()
{
	_prinny->update();
}

void town::render()
{
	_prinny->render();
}
