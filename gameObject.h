#pragma once
#include "gameNode.h"
#include "aStar.h"

class gameObject : public gameNode
{
protected:
	TagTile _tile[TILENUM][TILENUM];
	vector<TagTile*> _vRoute;

	char* _name;				//ĳ���� �̸�
	int _level, _counter, _mv, _jm;									//ĳ���� �ɷ�ġ 1
	int _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp;

	image* _character;
	RECT _rc;
	int _x, _y;					// �̹���(��Ʈ) ����x ����y
	int _oldX, _oldY;			// �������� ���� x, y �ε���
	int _indexX, _indexY;		// �������� x, y �ε���
	int _destX, _destY;
	vector<string> _mercenary;
	

	aStar* _aStar;

	int _idx;					// �̵��� vRoute���� ���� �ε���
	int _moveSpeed;

	bool _isMove;
	bool _isShowMoveTile;
	bool _isOrdering;			// ��ɼ������̴�.

public:
	gameObject();
	~gameObject();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void move(int endX, int endY);
	virtual void attack(int targetX, int targetY);
	virtual void setImage();
	virtual void setFrame();
	virtual void previousState();
	virtual void showPossibleMoveTile();

	virtual void saveData();
	virtual void loadData();

	virtual void setItem(const char* itemName) = 0;
	virtual void setHell(int hell) = 0;

	virtual RECT getRect() { return _rc; }
	virtual int getHell() = 0;

	virtual vector<string>& getMercenary() { return _mercenary; }
};