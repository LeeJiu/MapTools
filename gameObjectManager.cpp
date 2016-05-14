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
	if (_turnType == TURN_ENEMY) _turnType = TURN_PLAYER;
	if (_turnType == TURN_PLAYER) _turnType = TURN_ENEMY;
	_turnCount++;
}
