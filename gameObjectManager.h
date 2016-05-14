#pragma once
#include "gameNode.h"

class battleUI;
class gameObjectManager : public gameNode
{
private:
	int _turnCount;
	bool _turnType;


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
	

	int getTurnCount() { return _turnCount; }
	bool getTurnType() { return _turnType; }
	RECT getSummonRect() { return _rcSummon; }
};

