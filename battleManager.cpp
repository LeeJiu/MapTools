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
	

	_orderNumber = 0;
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


	if (_vOrder[_orderNumber].isDone == false)
	{
		if (_gameObjMgr->getIsAction() == FALSE)
		{
			switch (_vOrder[_orderNumber].order)
			{
			case ORDER_NONE:
				_vOrder[_orderNumber].isDone = true;
				break;
			case ORDER_ATTACK:
				_gameObjMgr->setUnitAttack(_vOrder[_orderNumber].character, _vOrder[_orderNumber].targetX, _vOrder[_orderNumber].targetY);
				break;
			case ORDER_SKILL:
				break;
			case ORDER_DEFENCE:
				break;
			default:
				break;
			}
		}	
	}
}

void battleManager::render()
{
}

void battleManager::setCharacterNone(int character, int targetX, int targetY)
{
}

void battleManager::setCharacterAttack(int character, int targetX, int targetY)
{
	tagOrder tempOrder;
	tempOrder.character = character;
	tempOrder.isDone = false;
	tempOrder.order = ORDER_ATTACK;
	tempOrder.targetX = targetX;
	tempOrder.targetY = targetY;

	_vOrder.push_back(tempOrder);
}

void battleManager::setCharacterDefence(int character)
{
}

void battleManager::setCharacterSkill(int character, int targetX, int targetY)
{
}

void battleManager::setActionAttack()
{
}

void battleManager::setTurnChange()
{
	_isTurnType = !_isTurnType;
}
