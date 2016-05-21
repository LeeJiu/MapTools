#pragma once
#include "singletonBase.h"
#include "EnemyAI.h"
#include "gameNode.h"

enum ORDER_TYPE
{
	ORDER_NONE, ORDER_ATTACK, ORDER_SKILL, ORDER_DEFENCE
};
struct tagOrder
{
	int character;
	int targetX;
	int targetY;
	ORDER_TYPE order;
	bool isDone;
};

class gameObjectManager;
class battleUI;
class battleManager : public gameNode
{
private:
	// ------------ 예약 된 명령 수행을 위한 변수 ------------
	vector<tagOrder> _vOrder;
	int _orderNumber;
	bool _isDoOrdering;
	bool _orderComplete;

	bool _isDoBattleManaging;

	// ------------ 턴 표기용 변수 ------------
	int _turnCount;					//현재 턴 수
	TURN_TYPE _isTurnType;			//현재 TURN이 누구의 턴인가? TRUE = PLAYER, FALSE = ENEMY
	bool _isTurnShow;				//TURN IMAGE를 SHOW 해줘야 하는가 말아야하는가?
	bool _isFirstShow;				//BATTLE SCENE에 처음 들어왔는가?
	bool _isTurnBackCenter;			//TURN IMAGE가 중앙까지 왔는가?
	RECT _rcTurnBack;				//TURN IMAGE의 뒷 배경 RECT
	image* _imageTurnStr;           //TURN IMAGE STR
	image* _imageTurnBack;          //TURN IMAGE BACKGROUND
	int _turnBackPosX;              //TURN RECT의 LEFT 위치
	float _turnShowTime;			//TURN IMAGE가 중앙까지 왔을 때 1초간 지연 시킬 용도의 TIME
	

	// ------------ 전방 선언 클래스 ------------
	EnemyAI* _enemyAI;
	battleUI* _battleUI;
	gameObjectManager* _gameObjMgr;

public:
	battleManager();
	~battleManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void doOrdering();

	void setCharacterNone(int character, int targetX, int targetY);
	void setCharacterAttack(int character, int targetX, int targetY);
	void setCharacterDefence(int character);
	void setCharacterSkill(int character, int targetX, int targetY);
	
	void setTurnChange(TURN_TYPE turnType);
	void setOrderNumber();
	void setEnemyAi();
	
	void setTurnShow() { _isTurnShow = true; }	//외부에서 Turn Show를 시켜야 할 때 이 함수를 이용하여 Turn을 Show 시킨다
	void turnChangingShow();
	void renderTurnShow();

	TURN_TYPE getTurnType() { return _isTurnType; }
	int getTurnCount() { return _turnCount; }
	

	void setGameObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
	void setBattleUIMemoryLink(battleUI* battleUI) { _battleUI = battleUI; }
};

