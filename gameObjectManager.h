#pragma once
#include "gameNode.h"
#include "prinny.h"
#include "Etna.h"
#include "Flonne.h"
#include "Raspberyl.h"
#include "orc.h"
#include "objects.h"

class gameObjectManager : public gameNode
{
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
	
	void setTile();
	void setCharacter();
	void setEnemy();
	void setObject();

	void loadMapData();


};

