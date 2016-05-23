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

	image* _action;
	RECT _rcAction;
	bool _onAction;

	int _count;
	image* _selectTile;
	image* _selectArrow;
	
	image* _turnbackImage;
	image* _turnUIImage;
	RECT _rcTurnback;
	float _time;
	bool _isShowLabel; //스테이지 시작했을때. 변경은 스타트가 아닐경우에만.

	bool _setUI;
	bool _isOnZenPonit;			// 캐릭터가 젠포인트 위에 있는지 여부
	bool _takeTurns;			// 턴을 넘기면 true

	int _selectCharIdx;			// 선택한 케릭터의 인덱스
	int _orderNum;				// 명령 수행해야할 벡터 인덱스 넘버

	//turn 상태 변수
	bool _isPlayerTurn;

	//ui 상태 변수
	bool _onCharacterList, _onSummary, _onStatus, _onOrder, _onUI;


	/*			enemy AI			*/
	int _enemyIdx;				// 현재 명령 수행할 에너미 인덱스 넘버

public:
	battleManager();
	~battleManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setFrame();
	void setRect();
	void turnbarRender();
	void tileControl();
	void UIControl();
	void characterIsOnZenPoint();
	void orderAction();								// vOrder에 담은 명령들을 수행할 함수
	bool isPlayerTurn() { return _isPlayerTurn; }

	void selectTileRender();

	void clickZenPoint();
	void clickCharacter(int x, int y, int i);
	void clickEnemy(int x, int y, int i);			// 매개변수 타일의 인덱스
	void clickObject(int i);
	void clickTile(int x, int y, int i);

	void increaseOrderNum();						// 게임오브젝트에서 호출할 함수. orderNum를 증가시켜줄 함수

	void setObjectMgrMemoryLink(gameObjectManager* objectMgr) { _objectMgr = objectMgr; }
	void setCameraMemoryLink(battleCamera* camera) { _camera = camera; }


	/*			enemy AI func			*/
	void enemyAI();							// 에너미 ai함수
	void increaseEnemyIdx();				// 게임오브젝트에서 호출할 함수. enemyIdx를 증가시켜줄 함수

	int searchTile(int enemyIdx);			// 타일 검사 -> index set, enemy order set
};

