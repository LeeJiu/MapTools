#pragma once
#include "gameNode.h"
#include "aStar.h"
#include "battleMapLoad.h"

class gameObject : public gameNode
{
protected:
	TagTile _tile[TILENUM][TILENUM];
	vector<TagTile*> _vRoute;

	image* _character;
	RECT _rc;
	int _x, _y;					// �̹���(��Ʈ) ����x ����y
	int _idxX, _idxY;			// �������� x, y �ε���
	int _destX, _destY;
	vector<string> _mercenary;

	aStar* _aStar;
	battleMapLoad* _mapLoad;

	int _idx;					// �̵��� vRoute���� ���� �ε���
	int _moveSpeed;

	bool _isMove;

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
	virtual void attack();
	virtual void setImage();
	virtual void setFrame();

	virtual void saveData();
	virtual void loadData();

	virtual void setItem(const char* itemName) = 0;
	virtual void setMercenary(const char* characterName) = 0;
	virtual void setHell(int hell) = 0;

	virtual RECT getRect() { return _rc; }
	virtual int getHell() = 0;

	virtual vector<string>& getMercenary() { return _mercenary; }
};