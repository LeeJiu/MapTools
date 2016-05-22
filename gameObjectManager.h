#pragma once
#include "gameNode.h"
#include "aStar.h"
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
		return obj1->getPivotY() < obj2->getPivotY();
	}
};

class battleCamera;

class gameObjectManager : public gameNode
{
	TagTile _tile[TILENUM][TILENUM];

	vector<TagTile*> _vTile;
	vector<TagTile*>::iterator _viTile;

	vector<gameObject*> _vCharacter;
	vector<gameObject*> _vEnemy;
	vector<gameObject*> _vToTalRender;

	int _zenPosX, _zenPosY;

	aStar* _aStar;
	battleCamera* _camera;


public:
	gameObjectManager();
	~gameObjectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadMapData();


	//set함수
	void setTile();
	void setCharacter();
	void setEnemy();
	void setObject();


	//get함수
	vector<TagTile*>& getVTile() { return _vTile; }
	vector<gameObject*>& getVCharacter() { return _vCharacter; }
	vector<gameObject*>& getVEnemy() { return _vEnemy; }

	//메모리 링크
	void setCameraMemoryLink(battleCamera* camera) { _camera = camera; }
};

