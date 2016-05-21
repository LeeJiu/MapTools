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
	// ------------ ���� �� ��� ������ ���� ���� ------------
	vector<tagOrder> _vOrder;
	int _orderNumber;
	bool _isDoOrdering;
	bool _orderComplete;

	bool _isDoBattleManaging;

	// ------------ �� ǥ��� ���� ------------
	int _turnCount;					//���� �� ��
	TURN_TYPE _isTurnType;			//���� TURN�� ������ ���ΰ�? TRUE = PLAYER, FALSE = ENEMY
	bool _isTurnShow;				//TURN IMAGE�� SHOW ����� �ϴ°� ���ƾ��ϴ°�?
	bool _isFirstShow;				//BATTLE SCENE�� ó�� ���Դ°�?
	bool _isTurnBackCenter;			//TURN IMAGE�� �߾ӱ��� �Դ°�?
	RECT _rcTurnBack;				//TURN IMAGE�� �� ��� RECT
	image* _imageTurnStr;           //TURN IMAGE STR
	image* _imageTurnBack;          //TURN IMAGE BACKGROUND
	int _turnBackPosX;              //TURN RECT�� LEFT ��ġ
	float _turnShowTime;			//TURN IMAGE�� �߾ӱ��� ���� �� 1�ʰ� ���� ��ų �뵵�� TIME
	

	// ------------ ���� ���� Ŭ���� ------------
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
	
	void setTurnShow() { _isTurnShow = true; }	//�ܺο��� Turn Show�� ���Ѿ� �� �� �� �Լ��� �̿��Ͽ� Turn�� Show ��Ų��
	void turnChangingShow();
	void renderTurnShow();

	TURN_TYPE getTurnType() { return _isTurnType; }
	int getTurnCount() { return _turnCount; }
	

	void setGameObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
	void setBattleUIMemoryLink(battleUI* battleUI) { _battleUI = battleUI; }
};

