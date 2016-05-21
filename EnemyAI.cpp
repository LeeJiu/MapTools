#include "stdafx.h"
#include "EnemyAI.h"
#include "battleManager.h"
#include "gameObjectManager.h"

EnemyAI::EnemyAI()
{
}


EnemyAI::~EnemyAI()
{
}

HRESULT EnemyAI::init()
{
	_isDoOrderAction = false;
	_orderCount = 0;
	_enemySize = 0;

	return S_OK;
}

HRESULT EnemyAI::init(battleManager * bm, gameObjectManager * gom)
{
	_isDoOrderAction = false;
	_orderCount = 0;
	_enemySize = 0;

	_battleMgr = bm;
	_gameObjMgr = gom;

	return S_OK;
}

void EnemyAI::release()
{
}

void EnemyAI::update()
{
	if (_orderCount > _gameObjMgr->getEnmSize())
	{
		_isDoOrderAction = false;
		_battleMgr->setTurnChange(PLAYER_TURN);
		_battleMgr->turnChangingShow();
		return;
	}

	checkAllEnemyUnitOrder();
}

void EnemyAI::render()
{
}

void EnemyAI::checkAllEnemyUnitOrder()
{
	int _objectSize = _gameObjMgr->getCharSize() + _gameObjMgr->getEnmSize();

	//모든 오브젝트 사이즈만큼 돌면서
	for (int i = 0; i < _objectSize; i++)
	{
		//해당 오브젝트가 ENEMY 이면
		if (_gameObjMgr->getGameObject()[i]->getIsCharacter() == false)
		{
			//해당 오브젝트의 ACTION이 내려진게 없다면
			if (_gameObjMgr->getGameObject()[i]->getIsAction() == false)
			{
				int _enemyUnitMv = _gameObjMgr->getGameObject()[i]->getMv();
				for (int j = 0; j < TOTALTILE(TILENUM); j++)
				{
					if (abs(_gameObjMgr->getGameObject()[i]->getIndexX() - _gameObjMgr->getTile()[j]->x) + abs(_gameObjMgr->getGameObject()[i]->getIndexY() - _gameObjMgr->getTile()[j]->y) <= _enemyUnitMv)
					{
						if (_gameObjMgr->getTile()[j]->state == S_NONE)
						{
							IMAGEMANAGER->findImage("walkable")->render(getMemDC(), _gameObjMgr->getTile()[j]->rc.left, _gameObjMgr->getTile()[j]->rc.top);
							_vRndMoveTile.push_back(j);
						}
					}
				}
				int rndSelectNumber = RND->getInt(_vRndMoveTile.size());
				_gameObjMgr->setUnitMove(i, _gameObjMgr->getTile()[_vRndMoveTile[rndSelectNumber]]->x, _gameObjMgr->getTile()[_vRndMoveTile[rndSelectNumber]]->y);
				_vRndMoveTile.clear();
				_gameObjMgr->getGameObject()[i]->setIsAction(true);
				_orderCount++;
			}			
		}		
	}
}
