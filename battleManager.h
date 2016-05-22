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

	vector<tagOrder> _vOrder;	// �÷��̾� ��� ����Ʈ

	int _selectCharIdx;			// ������ �ɸ����� �ε���
	int _orderNum;				// ��� �����ؾ��� ���� �ε��� �ѹ�

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
	void clickCharacter(int x, int y);
	void clickEnemy(int x, int y);			// �Ű����� Ÿ���� �ε���
	void clickObject();
	void clickTile(int x, int y);

	void setObjectMgrMemoryLink(gameObjectManager* objectMgr) { _objectMgr = objectMgr; }
};

