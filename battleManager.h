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

class battleManager : public gameNode
{
private:
	gameObjectManager* _objectMgr;
	battleUI* _ui;

	vector<tagOrder> _vOrder;	//�÷��̾� ��� ����Ʈ

	int _selectCharIdx;
	int _orderNum;				//��� �����ؾ��� ���� �ε��� �ѹ�

	bool _setUI;

	//turn ���� ����
	bool _isPlayerTurn;

	//ui ���� ����
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
	void clickCharacter();
	void clickEnemy();
	void clickObject();
	void clickTile();

	void setObjectMgrMemoryLink(gameObjectManager* objectMgr) { _objectMgr = objectMgr; }
};

