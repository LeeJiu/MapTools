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
	int _x, _y;					// 이미지(렉트) 센터x 센터y
	int _idxX, _idxY;			// 전투맵의 x, y 인덱스
	int _destX, _destY;
	vector<string> _mercenary;

	aStar* _aStar;
	battleMapLoad* _mapLoad;

	int _idx;					// 이동시 vRoute에서 사용될 인덱스
	int _moveSpeed;

	bool _isMove;

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