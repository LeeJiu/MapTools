#include "stdafx.h"
#include "battleManager.h"


battleManager::battleManager()
{
}


battleManager::~battleManager()
{
}

HRESULT battleManager::init()
{
	_turnCount = 0;					// TURN COUNT
	_isTurnType = true;				// TURN TYPE = true(PLAYER) || false(ENEMY)
	
	return S_OK;
}

void battleManager::release()
{
}

void battleManager::update()
{
	//(PLAYER TURN)
	if (_isTurnType)
	{

	}

	//(ENEMY TURN)
	if (!_isTurnType)
	{

	}
}

void battleManager::render()
{

}

void battleManager::setActionAttack()
{
}

void battleManager::setTurnChange()
{
	_isTurnType = !_isTurnType;
}
