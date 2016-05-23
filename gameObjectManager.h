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

	bool _isOrdering;							// ���ӿ�����Ʈ �ɸ��͵��� ����� ���������� �Ǵ� ����

public:
	gameObjectManager();
	~gameObjectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadMapData();

	void characterMove(int index, int destX, int destY);				// �÷��̾� ���� �Լ� 
	void characterAttack(int index, int destX, int destY);				// �÷��̾� ���� �Լ�
	void characterPain(int index, int destX, int destY, int damage);	// �÷��̾� �ǰ� �Լ�
	void enemyMove(int index, int destX, int destY);					// ���ʹ� ���� �Լ�
	void enemyAttack(int index, int destX, int destY);					// ���ʹ� ���� �Լ�
	void enemyPain(int index, int destX, int destY, int damage);		// ���ʹ� �ǰ� �Լ�

	//set�Լ�
	void setTile();
	void setCharacter();
	void setEnemy();
	void setObject();
	void setIsOrderting(bool isOrdering) { _isOrdering = isOrdering; }

	//get�Լ�
	vector<TagTile*>& getVTile() { return _vTile; }
	vector<gameObject*>& getVCharacter() { return _vCharacter; }
	vector<gameObject*>& getVEnemy() { return _vEnemy; }
	bool getIsOrdering() { return _isOrdering; }

	//�޸� ��ũ
	void setCameraMemoryLink(battleCamera* camera) { _camera = camera; }
};

