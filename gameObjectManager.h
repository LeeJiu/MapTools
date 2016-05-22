#pragma once

#include "aStar.h"
#include "gameNode.h"
#include "prinny.h"
#include "etna.h"
#include "flonne.h"
#include "raspberyl.h"
#include "orc.h"
#include "catsaver.h"
#include "boss.h"
#include "objects.h"
#include <algorithm>

struct GOBJ_Y_RENDER
{
	bool operator()(gameObject* obj1, gameObject* obj2)
	{
		//return obj1->getRect().bottom < obj2->getRect().bottom;
		return obj1->getPivotY() < obj2->getPivotY();
	}
};

class gameObjectManager : public gameNode
{
	RECT _rcTurnBack;
	RECT _rcTurnStr;
	image* _imageTurn;
	bool _isTurnCenter;


	TagTile* _tile[TILENUM][TILENUM];

	vector<TagTile*> _vTile;
	vector<TagTile*>::iterator _viTile;

	vector<gameObject*> _vGameObject;
	vector<gameObject*> _vToTalRender;		

	int vCharSize;
	int vObjSize;
	int vEnmSize;

	int _zenPosX, _zenPosY;

	bool _isAction;
	bool isCharacterTurn;

	aStar* _aStar;

public:
	gameObjectManager();
	~gameObjectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//get함수
	

	//set함수
	void setTile();
	void setCharacter();
	void setEnemy();
	void setObject();
	void setAstar();

	void loadMapData();

	vector<TagTile*>& getTile() { return _vTile; }
	vector<gameObject*>& getGameObject() { return _vGameObject; }
};

