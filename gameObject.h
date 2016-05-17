#pragma once
#include "gameNode.h"

class gameObject : public gameNode
{
protected:
	TagTile* _tile[TILENUM][TILENUM];
	vector<TagTile*> _vTile;
	vector<TagTile*> _vRoute;

	const char* _name;												//ĳ���� �̸�
	int _level, _counter, _mv, _jm;									//ĳ���� �ɷ�ġ 1
	int _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp;

	image* _character;
	RECT _rc;
	int _x, _y;														// �̹���(��Ʈ) ����x ����y
	int _oldX, _oldY;												// �������� ���� x, y �ε���
	int _indexX, _indexY;											// �������� x, y �ε���
	int _destX, _destY;

	vector<string> _mercenary;

	int _idx;														// �̵��� vRoute���� ���� �ε���
	int _moveSpeed;

	bool _isMove;
	bool _isShowPossibleMoveTile;									// �̵������� Ÿ�� �������
	bool _isOrdering;												// ���ɼ������̴�.

public:
	gameObject();
	~gameObject();

	virtual HRESULT init();
	virtual HRESULT init(vector<TagTile*> tile);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			�Լ� �߰�			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void move(int endX, int endY);
	virtual void attack(int targetX, int targetY);
	virtual void setImage();
	virtual void setFrame();
	virtual void previousState() = 0;								// �������� ���ư��� �Լ�
	virtual void showPossibleMoveTile() = 0;						// �̵������� Ÿ�� �����ִ� �Լ�

	virtual void saveData();
	virtual void loadData();

	// set�Լ�
	virtual void setItem(const char* itemName) = 0;
	virtual void setHell(int hell) = 0;
	virtual void setIsShowPossibleMoveTile(bool isShowPossibleMoveTile) { _isShowPossibleMoveTile = isShowPossibleMoveTile; }

	// get�Լ�
	virtual const char* getName() { return _name; }
	virtual RECT getRect() { return _rc; }
	virtual int getHell() = 0;
	virtual int getLevel() { return _level; }
	virtual int getCounter() { return _counter; }
	virtual int getMv() { return _mv; }
	virtual int getJm() { return _jm; }
	virtual int getHp() { return _hp; }
	virtual int getSp() { return _sp; }
	virtual int getAtk() { return _atk; }
	virtual int getInt() { return _int; }
	virtual int getDef() { return _def; }
	virtual int getSpd() { return _spd; }
	virtual int getHit() { return _hit; }
	virtual int getRes() { return _res; }
	virtual int getExp() { return _exp; }
	virtual vector<string>& getMercenary() { return _mercenary; }
};