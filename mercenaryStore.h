#pragma once
#include "gameNode.h"
#include "prinny.h"

class mercenaryStore : public gameNode
{
private:
	//플레이어
	gameObject* _prinny;
	string _hell;		//플레이어 소지금

	//용병 정보를 띄워줄 변수 추가 (lv, cntr, mv, jm, atk, def, int, spd ...)
	image* _mercenaryImage;
	CHARACTER_STATE _characterState;
	const char* _name;
	char* _info;
	string _level, _counter, _mv, _jm, _hp, _sp, _atk, _int, _def, _spd, _hit, _res;	//능력치
	string _price;		//용병 고용가
	int _buyIdx;
	int _stateNum;		//용병 모션 변경을 위한 변수

	int _x, _y, _curFrameX, _count;

	//ui rect
	RECT _rcStoreTitle, _rcListTitle;
	RECT _rcMercenaryList;
	RECT _rcMercenaryStatus;
	RECT _rcMercenaryInfo;
	RECT _rcMyList;
	RECT _rcHell;
	RECT _rcExit, _rcBuy;		//interactive rect

public:
	mercenaryStore();
	~mercenaryStore();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	void buyMercenary(const char* characterName);
	void keyControl();
	void showMercenaryInfoAll();		//용병 정보창 갱신

	void setImage();
	void setFrame();

	void saveMercenaryData();
	void loadMercenaryData();
};

