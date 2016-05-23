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

enum ORDERLIST
{
	OL_NONE, OL_ORDERING, OL_END
};

class battleCamera;
class battleManager;

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
	battleManager* _battleMgr;

	ORDERLIST _orderList;

	int _charDeathCount;
	int _enemyDeathCount;

public:
	gameObjectManager();
	~gameObjectManager();

	HRESULT init();
	void release();
	void update();
	void render();			// total랜더 (케릭터, 에너미, 오브젝트)

	void loadMapData();
	void tileRender();		// 타일랜더

	void characterMove(int index, int destX, int destY);				// 플레이어 무브 함수 
	void characterAttack(int index, int destX, int destY);				// 플레이어 어택 함수
	void characterPain(int index, int destX, int destY, int damage);	// 플레이어 피격 함수
	void enemyAttack(int index, int destX, int destY);
	void enemyMove(int index, int destX, int destY);					// 에너미 무브 함수
	void enemyMoveToAttack(int index, int destX, int destY, int targetX, int targetY);
	void enemyPain(int index, int destX, int destY, int damage);		// 에너미 피격 함수

	//set함수
	void setTile();
	void setCharacter();
	void setEnemy();
	void setObject();
	void setOrderList(ORDERLIST orderList) { _orderList = orderList; }
	void setCharDeath();
	void setEnemyDeath();

	//get함수
	vector<TagTile*>& getVTile() { return _vTile; }
	vector<gameObject*>& getVCharacter() { return _vCharacter; }
	vector<gameObject*>& getVEnemy() { return _vEnemy; }
	ORDERLIST getOrderList() { return _orderList; }

	//메모리 링크
	void setCameraMemoryLink(battleCamera* camera) { _camera = camera; }
	void setbattleMgrMemoryLink(battleManager* battleMgr) { _battleMgr = battleMgr; }
};

