#pragma once
#include "singletonBase.h"

enum ORDER_TYPE
{
	ORDER_NONE, ORDER_ATTACK, ORDER_SKILL, ORDER_DEFENCE
};
struct tagOrder
{
	int _character;
	int _targetX;
	int _targetY;
	ORDER_TYPE _order;
	bool _isDone;
};

class gameObjectManager;
class battleUI;
class battleManager : public singletonBase<battleManager>
{
private:
	int _turnCount;
	bool _isTurnType;

	vector<tagOrder> _vOrder;
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

	void setCharacterNone(int character, int target);
	void setCharacterAttack(int character, int target);
	void setCharacterDefence(int character);
	void setCharacterSkill(int character, int target);
	

	void setActionAttack();
	void setTurnChange();


	int getTurnCount() { return _turnCount; }

	void setGameObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
	void setBattleUIMemoryLink(battleUI* battleUI) { _battleUI = battleUI; }
};

