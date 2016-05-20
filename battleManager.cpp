#include "stdafx.h"
#include "battleManager.h"
#include "gameObjectManager.h"
#include "battleUI.h"

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
	_ishaveToChange = false;
	_isDoOrdering = false;

	_orderNumber = 0;
	_orderComplete = false;
	_isDidOrderTurnShow = false;

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

	//예약 된 오더가 있는지 체크하자
	if (_orderNumber < _vOrder.size())
	{
		//오더를 수행하라는 명령이 TRUE 이면
		if (_isDoOrdering)
		{
			//예약 된 명령을 수행하자
			doOrdering();
		}
	}

	//턴을 바꿀것이다라는 값이 TRUE인지 체크하자
	if (_ishaveToChange)
	{
		//예약 된 명령이 0 보다 작거나 없으면
		if (_vOrder.size() <= 0)
		{
			if (!_isDidOrderTurnShow)
			{
				_battleUI->setIsShowTurnChanging(true);
				_isDidOrderTurnShow = true;
			}

			if (_battleUI->getIsShowTurnChanging() == false)
			{
				_isTurnType = !_isTurnType; //현재 턴 타입을 바꾸자
				_ishaveToChange = false;	//HAVE TO CHANGE BOOL 값 초기화
				_battleUI->showTurnChange();
				_isDidOrderTurnShow = false;
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

void battleManager::setOrderNumber()
{
	//_gameObjMgr->setUnitPain(_vOrder[_orderNumber].targetX, _vOrder[_orderNumber].targetY, _vOrder[_orderNumber].character);
	_orderNumber++;
	if (_orderNumber >= _vOrder.size())
	{
		_isDoOrdering = false;
		_vOrder.clear();
		_orderNumber = 0;
	}
}

void battleManager::setTurnChange()
{
	_isDoOrdering = true;
	_ishaveToChange = true;
	_isTurnType = false; //에너미 턴으로 바꾼다
}

void battleManager::doAction()
{
	_isDoOrdering = true;
}

void battleManager::doOrdering()
{
	if (_vOrder[_orderNumber].isDone == false)
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