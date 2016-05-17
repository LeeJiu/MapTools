#pragma once
#include "singletonBase.h"

class gameObjectManager;
class battleUI;
class battleManager : public singletonBase<battleManager>
{
private:
	int _turnCount;
	bool _isTurnType;

	battleUI* _battleUI;
	gameObjectManager* _gameObjMgr;

public:
	battleManager();
	~battleManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setUnitMove();
	void setUnitAttack();
	void setUnitDefence();
	void setUnitPain();


	void setCharacter();
	void setActionAttack();
	void setTurnChange();


	int getTurnCount() { return _turnCount; }

	void setGameObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
	void setBattleUIMemoryLink(battleUI* battleUI) { _battleUI = battleUI; }
};

