#pragma once
#include "singletonBase.h"

enum ORDER_TYPE
{
	ORDER_NONE, ORDER_ATTACK, ORDER_SKILL, ORDER_DEFENCE
};
struct tagOrder
{
<<<<<<< HEAD
	int character;
	int targetX;
	int targetY;
	ORDER_TYPE order;
	bool isDone;
=======
	int _character;
	int _targetX;
	int _targetY;
	ORDER_TYPE _order;
	bool _isDone;
>>>>>>> refs/remotes/origin/development
};

class gameObjectManager;
class battleUI;
class battleManager : public singletonBase<battleManager>
{
private:
	int _turnCount;
	bool _isTurnType;

	vector<tagOrder> _vOrder;
	int _orderNumber;

	bool _orderComplete;
	

	battleUI* _battleUI;
	gameObjectManager* _gameObjMgr;

public:
	battleManager();
	~battleManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setCharacterNone(int character, int targetX, int targetY);
	void setCharacterAttack(int character, int targetX, int targetY);
	void setCharacterDefence(int character);
	void setCharacterSkill(int character, int targetX, int targetY);
	

	void setActionAttack();
	void setTurnChange();

	int getOrderNumber() { return _orderNumber; }
	void setOrderNumber(int number) { _orderNumber = number; }

	int getTurnCount() { return _turnCount; }

	void setGameObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
	void setBattleUIMemoryLink(battleUI* battleUI) { _battleUI = battleUI; }
};

