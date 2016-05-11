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
	_inventory = new inventory;
	_inventory->init();

	return S_OK;
}

void town::release()
{
	SAFE_DELETE(_inventory);
}

void town::update()
{
	keyControl();
}

void town::render()
{
	_inventory->render();
}

void town::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		_inventory->showInventory();
		_invenExit = _inventory->getExit();
	}

	if (PtInRect(&_invenExit, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_inventory->closeInventory();
			_invenExit = RectMake(0, 0, 0, 0);
		}
	}
	
}
