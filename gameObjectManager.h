#pragma once
#include "gameNode.h"
#include "prinny.h"
#include "Etna.h"
#include "Flonne.h"
#include "Raspberyl.h"
#include "orc.h"
#include "objects.h"

enum TURN_TYPE
{
	TURN_ENEMY, TURN_PLAYER
};

class battleUI;

class gameObjectManager : public gameNode
{
	int _turnCount;
	TURN_TYPE _turnType;

	RECT _rcTurnBack;
	RECT _rcTurnStr;
	image* _imageTurn;
	bool _isTurnCenter;

	RECT _rcSummon;

	battleUI* _battleUI;
	TagTile _tile[TILENUM][TILENUM];

	vector<TagTile*> _vTile;
	vector<TagTile*>::iterator _viTile;

	vector<gameObject*> _vCharacter;

	vector<gameObject*> _vEnemy;
	
	vector<gameObject*> _vGameObject;

	int vObjSize;
	int vEnmSize;

	bool isCharacterTurn;

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
	
	void setTile();
	void setCharacter();
	void setEnemy();
	void setObject();

	void loadMapData();


};

