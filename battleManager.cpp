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

	//���� �� ������ �ִ��� üũ����
	if (_orderNumber < _vOrder.size())
	{
		//������ �����϶�� ����� TRUE �̸�
		if (_isDoOrdering)
		{
			//���� �� ����� ��������
			doOrdering();
		}
	}

	//���� �ٲܰ��̴ٶ�� ���� TRUE���� üũ����
	if (_ishaveToChange)
	{
		//���� �� ����� 0 ���� �۰ų� ������
		if (_vOrder.size() <= 0)
		{
			if (!_isDidOrderTurnShow)
			{
				_battleUI->setIsShowTurnChanging(true);
				_isDidOrderTurnShow = true;
			}

			if (_battleUI->getIsShowTurnChanging() == false)
			{
				_isTurnType = !_isTurnType; //���� �� Ÿ���� �ٲ���
				_ishaveToChange = false;	//HAVE TO CHANGE BOOL �� �ʱ�ȭ
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
	_isTurnType = false; //���ʹ� ������ �ٲ۴�
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