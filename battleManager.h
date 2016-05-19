#pragma once
#include "singletonBase.h"

enum ORDER_TYPE
{
	ORDER_NONE, ORDER_ATTACK, ORDER_SKILL, ORDER_DEFENCE
};
struct tagOrder
{
	int character;
	int targetX;
	int targetY;
	ORDER_TYPE order;
	bool isDone;
};

class gameObjectManager;
class battleUI;
class battleManager : public singletonBase<battleManager>
{
private:
	int _turnCount;
	bool _isTurnType;
	bool _isDoOrdering;

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

	void doActionAttack();
	void doOrdering();

	void setCharacterNone(int character, int targetX, int targetY);
	void setCharacterAttack(int character, int targetX, int targetY);
	void setCharacterDefence(int character);
	void setCharacterSkill(int character, int targetX, int targetY);
	
	void setTurnChange();
	void setOrderNumber(int number) { _orderNumber = number; }

	int getOrderNumber() { return _orderNumber; }
	bool getTurnType() { return _isTurnType; }
	int getTurnCount() { return _turnCount; }
	

	void setGameObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
	void setBattleUIMemoryLink(battleUI* battleUI) { _battleUI = battleUI; }
};

