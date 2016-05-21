#pragma once
#include "gameNode.h"

class battleManager;
class gameObjectManager;
class EnemyAI : public gameNode
{
private:
	bool _isDoOrderAction;
	int _orderCount;
	int _enemySize;

	vector<int> _vRndMoveTile;

	battleManager* _battleMgr;
	gameObjectManager* _gameObjMgr;
public:
	EnemyAI();
	~EnemyAI();

	HRESULT init();
	HRESULT init(battleManager* bm, gameObjectManager* gom);
	void release();
	void update();
	void render();

	void checkAllEnemyUnitOrder();
	void checkSelectedUnitClosedEnemy();
	void setEnemyUnitMove();
	void setEnemyUnitAttack();
	void setEnemyUnitDefence();

	void setDoOrderAction() { _isDoOrderAction = true; }

	//void setbattleManagerMemoryLink(battleManager* battleMgr) { _battleMgr = battleMgr; }
	//void setgameObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
};

