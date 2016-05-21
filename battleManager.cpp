#include "stdafx.h"
#include "battleUI.h"
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
	_isTurnType = PLAYER_TURN;
	
	_orderNumber = 0;
	_orderComplete = false;
	_isDoOrdering = false;
	_isDoBattleManaging = false;

	// -------------- TURN SHOW 변수들 초기화 --------------
	IMAGEMANAGER->addImage("turnStart", "image/battleUI/ui_turnback_start.bmp", 461, 54, true, 0xff00ff);		//TURN IMAGE STAGE START
	IMAGEMANAGER->addImage("turnPlayer", "image/battleUI/ui_turnback_player.bmp", 489, 53, true, 0xff00ff);		//TURN IMAGE PLAYER TURN
	IMAGEMANAGER->addImage("turnEnemy", "image/battleUI/ui_turnback_enemy.bmp", 476, 53, true, 0xff00ff);		//TURN IMAGE ENEMY TURN
	IMAGEMANAGER->addImage("turnBackground", "image/battleUI/ui_turnback_black.bmp", 1280, 100, false, false);  //TURN BACKGROUND(ALPHA BLACK) IMAGE
	_isTurnType = PLAYER_TURN;
	_isTurnShow = true;																				   //TURN SHOW를 해야하는가 말아야하는가에 대한 BOOL 값
	_isFirstShow = true;																			   //처음 전투에 들어왔을 시 = TRUE	
	_turnBackPosX = 0 - WINSIZEX;																	   //TURN IMAGE용 POS X 값
	_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);								   //출력 할 글자의 배경 RECT
	_imageTurnStr = IMAGEMANAGER->findImage("turnStart");											   //출력 할 글자 Image
	_imageTurnBack = IMAGEMANAGER->findImage("turnBackground");										   //출력 할 글자의 배경 Image
	_isTurnBackCenter = false;																		   //TURN IMAGE가 전부 출력 됐는가에 대한 BOOL 값
	_turnShowTime = 0;																				   //TURN IMAGE가 중앙까지 도착 했을 시 1초간 지연시키기 위한 TIME 값

	return S_OK;
}

void battleManager::release()
{
}

void battleManager::update()
{
	// 첫 턴이면 STAGE START를 한번 출력하자
	if (_isFirstShow)
	{
		turnChangingShow();
		return;
	}

	if (_isTurnShow)
	{
		turnChangingShow();
		return;
	}


	if (_isDoBattleManaging)
	{
		//(PLAYER TURN)
		if (_isTurnType == PLAYER_TURN)
		{
			if (_orderNumber < _vOrder.size())
			{
				if (_isDoOrdering)
				{
					doOrdering();
				}
			}
			if (_orderNumber == 0)
			{
				_isTurnType = ENEMY_TURN;
				turnChangingShow();
			}
		}
		//(ENEMY TURN)
		if (_isTurnType == ENEMY_TURN)
		{
			_enemyAI->update();
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

void battleManager::setTurnChange(TURN_TYPE turnType)
{		
	_isDoOrdering = true;
	_isDoBattleManaging = true;
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
		_isTurnType = ENEMY_TURN;
		_isDoBattleManaging = false;
		turnChangingShow();
	}
}

void battleManager::setEnemyAi()
{
	_enemyAI = new EnemyAI;
	_enemyAI->init(this, _gameObjMgr);
}

void battleManager::turnChangingShow()
{
	_isTurnShow = true;

	//첫 턴이 아닐 때
	if (!_isFirstShow)
	{
		//TURN TRUE = PLAYER TURN
		if (_isTurnType == PLAYER_TURN)
		{
			_imageTurnStr = IMAGEMANAGER->findImage("turnPlayer");
			if (!_isTurnBackCenter)
			{
				_turnBackPosX += 20;
				_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
				if (_turnBackPosX >= 0) _isTurnBackCenter = true;
			}

			if (_isTurnBackCenter)
			{
				_turnShowTime += TIMEMANAGER->getElapsedTime();
				if (_turnShowTime > 1)
				{
					_turnBackPosX += 20;
					_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
					if (_turnBackPosX > WINSIZEX)
					{
						_isTurnShow = false;
						_turnBackPosX = 0 - WINSIZEX;
						_turnShowTime = 0;
						_isTurnBackCenter = false;
					}
				}
			}
		}

		//TURN FALSE = ENEMY TURN
		if (_isTurnType == ENEMY_TURN)
		{
			_imageTurnStr = IMAGEMANAGER->findImage("turnEnemy");
			if (!_isTurnBackCenter)
			{
				_turnBackPosX += 20;
				_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
				if (_turnBackPosX >= 0) _isTurnBackCenter = true;
			}

			if (_isTurnBackCenter)
			{
				_turnShowTime += TIMEMANAGER->getElapsedTime();
				if (_turnShowTime > 1)
				{
					_turnBackPosX += 20;
					_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
					if (_turnBackPosX > WINSIZEX)
					{
						_isTurnShow = false;
						_turnBackPosX = 0 - WINSIZEX;
						_turnShowTime = 0;
						_isTurnBackCenter = false;
					}

				}
			}
		}
	}

	//처음 턴일 때 STAGE START 출력
	if (_isFirstShow)
	{
		if (!_isTurnBackCenter)
		{
			_turnBackPosX += 20;
			_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
			if (_turnBackPosX >= 0) _isTurnBackCenter = true;
		}

		if (_isTurnBackCenter)
		{
			_turnShowTime += TIMEMANAGER->getElapsedTime();
			if (_turnShowTime > 1)
			{
				_turnBackPosX += 20;
				_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
				if (_turnBackPosX > WINSIZEX)
				{
					_isFirstShow = false;
					_isTurnShow = false;
					_battleUI->setIsOnStatus();
					_battleUI->setIsOnCharacterList();
					_turnBackPosX = 0 - WINSIZEX;
					_turnShowTime = 0;
					_isTurnBackCenter = false;

				}
			}
		}
	}
}

void battleManager::renderTurnShow()
{
	// 스테이지시작, 에너미턴, 플레이어턴 출력
	if (_isTurnShow)
	{
		//Rectangle(getMemDC(), _rcTurnBack.left, _rcTurnBack.top, _rcTurnBack.right, _rcTurnBack.bottom);
		_imageTurnBack->alphaRender(getMemDC(), _rcTurnBack.left, _rcTurnBack.top, 170);
		_imageTurnStr->render(getMemDC(), _rcTurnBack.left + 450, _rcTurnBack.top + 25);
	}
}

void battleManager::doOrdering()
{
	if (_vOrder.size() > 0)
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
}