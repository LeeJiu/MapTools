#include "stdafx.h"
#include "gameObjectManager.h"

gameObjectManager::gameObjectManager()
{
}


gameObjectManager::~gameObjectManager()
{
}

HRESULT gameObjectManager::init()
{
	_turnCount = 0;	
	_turnType = true;	//Turn Type = PLAYER(TRUE) || ENEMY(FALSE)
	
	

	return S_OK;
}

void gameObjectManager::release()
{
}

void gameObjectManager::update()
{
}

void gameObjectManager::render()
{
}

void gameObjectManager::setActionAttack()
{

}

void gameObjectManager::setChangeTurn()
{
	if (_turnType == TRUE) _turnType = FALSE;
	if (_turnType == FALSE) _turnType = TRUE;
	_turnCount++;
}
