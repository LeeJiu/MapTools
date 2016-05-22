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
<<<<<<< HEAD
	void clickCharacter();
	void clickEnemy();
	void clickObject(int i);
	void clickTile();
=======
	void clickCharacter(int x, int y);
	void clickEnemy(int x, int y);			// �Ű����� Ÿ���� �ε���
	void clickObject();
	void clickTile(int x, int y);
>>>>>>> refs/remotes/origin/development

	void setObjectMgrMemoryLink(gameObjectManager* objectMgr) { _objectMgr = objectMgr; }
	void setCameraMemoryLink(battleCamera* camera) { _camera = camera; }
};

