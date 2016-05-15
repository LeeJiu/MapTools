#pragma once
#include "gameNode.h"
#include "aStar.h"

class gameObject : public gameNode
{
protected:
	TagTile _tile[TILENUM][TILENUM];
	vector<TagTile*> _vRoute;

	char* _name;				//캐릭터 이름
	int _level, _counter, _mv, _jm;									//캐릭터 능력치 1
	int _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp;

	image* _character;
	RECT _rc;
	int _x, _y;					// 이미지(렉트) 센터x 센터y
	int _oldX, _oldY;			// 전투맵의 이전 x, y 인덱스
	int _indexX, _indexY;		// 전투맵의 x, y 인덱스
	int _destX, _destY;
	vector<string> _mercenary;
	

	aStar* _aStar;

	int _idx;					// 이동시 vRoute에서 사용될 인덱스
	int _moveSpeed;

	bool _isMove;
	bool _isShowMoveTile;
	bool _isOrdering;			// 명령수행중이다.

public:
	gameObject();
	~gameObject();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
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