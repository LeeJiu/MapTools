#pragma once
#include "gameNode.h"
#include "battleUI.h"


enum ORDERKIND
{
	O_ATTACK, O_DEFENCE, O_SKILL
};

struct tagOrder
{
	POINT playerIdx;
	POINT enemyIdx;
	int playerVIdx;
	int enemyVIdx;
	int damage;
	ORDERKIND order;
};

class gameObjectManager;
class battleCamera;

class battleManager : public gameNode
{
private:
	gameObjectManager* _objectMgr;
	battleUI* _ui;
	battleCamera* _camera;

	vector<tagOrder> _vOrder;	// 플레이어 명령 리스트

	int _selectCharIdx;			// 선택한 케릭터의 인덱스
	int _orderNum;				// 명령 수행해야할 벡터 인덱스 넘버

	//turn 상태 변수
	bool _isPlayerTurn;

	//ui 상태 변수
	bool _onCharacterList, _onSummary, _onStatus, _onOrder, _onAction;


public:
	battleManager();
	~battleManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();

	void clickZenPoint();
<<<<<<< HEAD
	void clickCharacter();
	void clickEnemy();
	void clickObject(int i);
	void clickTile();
=======
	void clickCharacter(int x, int y);
	void clickEnemy(int x, int y);			// 매개변수 타일의 인덱스
	void clickObject();
	void clickTile(int x, int y);
>>>>>>> refs/remotes/origin/development

	void setObjectMgrMemoryLink(gameObjectManager* objectMgr) { _objectMgr = objectMgr; }
	void setCameraMemoryLink(battleCamera* camera) { _camera = camera; }
};

