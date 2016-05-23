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

	vector<tagOrder> _vOrder;	// �÷��̾� ��� ����Ʈ

	image* _action;
	RECT _rcAction;
	bool _onAction;

	bool _setUI;
	bool _isOnZenPonit;			// ĳ���Ͱ� ������Ʈ ���� �ִ��� ����
	bool _takeTurns;			// ���� �ѱ�� true

	int _selectCharIdx;			// ������ �ɸ����� �ε���
	int _orderNum;				// ��� �����ؾ��� ���� �ε��� �ѹ�

	//turn ���� ����
	bool _isPlayerTurn;

	//ui ���� ����
	bool _onCharacterList, _onSummary, _onStatus, _onOrder, _onUI;

public:
	battleManager();
	~battleManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileControl();
	void UIControl();
	void characterIsOnZenPoint();

	void clickZenPoint();
	void clickCharacter(int x, int y, int i);
	void clickEnemy(int x, int y, int i);			// �Ű����� Ÿ���� �ε���
	void clickObject(int i);
	void clickTile(int x, int y, int i);

	void setObjectMgrMemoryLink(gameObjectManager* objectMgr) { _objectMgr = objectMgr; }
	void setCameraMemoryLink(battleCamera* camera) { _camera = camera; }
};

