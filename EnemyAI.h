#pragma once

class battleManager;
class gameObjectManager;
class EnemyAI 
{
private:
	bool _isDoOrderAction;
	int _orderCount;
	int _enemySize;

	battleManager* _battleMgr;
	gameObjectManager* _gameObjMgr;
public:
	EnemyAI();
	~EnemyAI();

	HRESULT init();
	void release();
	void update();
	void render();

	void checkAllUnitOrder();
	void checkSelectedUnitClosedEnemy();
	void setEnemyUnitMove();
	void setEnemyUnitAttack();
	void setEnemyUnitDefence();

	void setDoOrderAction() { _isDoOrderAction = true; }

	void setbattleManagerMemoryLink(battleManager* battleMgr) { _battleMgr = battleMgr; }
	void setgameObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
};

