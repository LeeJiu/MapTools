#pragma once
#include "aStar.h"
#include "gameNode.h"
#include "prinny.h"
#include "etna.h"
#include "flonne.h"
#include "raspberyl.h"
#include "orc.h"
#include "boss.h"
#include "objects.h"

class battleUI;
class battleManager;

class gameObjectManager : public gameNode
{
	RECT _rcTurnBack;
	RECT _rcTurnStr;
	image* _imageTurn;
	bool _isTurnCenter;

	RECT _rcSummon;

	TagTile* _tile[TILENUM][TILENUM];

	vector<TagTile*> _vTile;
	vector<TagTile*>::iterator _viTile;

	vector<gameObject*> _vCharacter;

	vector<gameObject*> _vEnemy;
	
	vector<gameObject*> _vGameObject;

	int vObjSize;
	int vEnmSize;

	bool isCharacterTurn;

	aStar* _aStar;
	battleUI* _battleUI;
	battleManager* _battleMgr;
public:
	gameObjectManager();
	~gameObjectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setBattleUIMemoryLink(battleUI* battleUI) { _battleUI = battleUI; }
	void setBattleManagerMemoryLink(battleManager* battleMgr) { _battleMgr = battleMgr; }
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
	void setAstar();

	void loadMapData();


	vector<TagTile*> getTile() { return _vTile; }
	vector<gameObject*> getCharacter() { return _vCharacter; }
	vector<gameObject*> getEnemy() { return _vEnemy; }
	vector<gameObject*> getGameObject() { return _vGameObject; }
};
