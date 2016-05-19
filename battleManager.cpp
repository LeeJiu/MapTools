#include "stdafx.h"
#include "battleManager.h"
#include "gameObjectManager.h"

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
	
	_orderComplete = false;

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


	int tempCharacterSize = _gameObjMgr->getGameObject().size();
	int tempOrderSize = _vOrder.size();
	for (int i = 0; i < tempOrderSize; i++)
	{
		if (_vOrder[i]._isDone == false)
		{
			for (int k = 0; k < tempCharacterSize; k++)
			{
				//if (_gameObjMgr->getGameObject()[k]->getIsOrdering() == false)
				//{
				//	_gameObjMgr->getGameObject()[k]->setAttack();
				//}
				break;
			}
			break;
		}
		
	}
}

void battleManager::render()
{
}

void battleManager::setCharacterNone(int character, int target)
{
}

void battleManager::setCharacterAttack(int character, int target)
{
}

void battleManager::setCharacterDefence(int character)
{
}

void battleManager::setCharacterSkill(int character, int target)
{
}

void battleManager::setActionAttack()
{
}

void battleManager::setTurnChange()
{
	_isTurnType = !_isTurnType;
}
