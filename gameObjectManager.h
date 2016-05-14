#pragma once
#include "gameNode.h"

enum TURN_TYPE
{
	TURN_ENEMY, TURN_PLAYER
};

class battleUI;
class gameObjectManager : public gameNode
{
private:
	int _turnCount;
	TURN_TYPE _turnType;

	RECT _rcTurnBack;
	RECT _rcTurnStr;
	image* _imageTurn;
	bool _isTurnCenter;

	RECT _rcSummon;

	battleUI* _battleUI;

public:
	gameObjectManager();
	~gameObjectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setbattleUIMemoryLink(battleUI* battleUI) { _battleUI = battleUI; }


	void setUnitMove();
	void setUnitAttack();
	void setUnitDefence();

	void setActionAttack();
	void setChangeTurn();


	RECT getSummonRect() { return _rcSummon; }
};

