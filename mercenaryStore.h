#pragma once
#include "gameNode.h"
#include "prinny.h"

class mercenaryStore : public gameNode
{
private:
	//�÷��̾�
	gameObject* _prinny;
	string _hell;		//�÷��̾� ������

	//�뺴 ������ ����� ���� �߰� (lv, cntr, mv, jm, atk, def, int, spd ...)
	image* _mercenaryImage;
	CHARACTER_STATE _characterState;
	const char* _name;
	char* _info;
	string _level, _counter, _mv, _jm, _hp, _sp, _atk, _int, _def, _spd, _hit, _res;	//�ɷ�ġ
	string _price;		//�뺴 ��밡
	int _buyIdx;
	int _stateNum;		//�뺴 ��� ������ ���� ����

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

	/*			�Լ� �߰�			*/
	void buyMercenary(const char* characterName);
	void keyControl();
	void showMercenaryInfoAll();		//�뺴 ����â ����

	void setImage();
	void setFrame();

	void saveMercenaryData();
	void loadMercenaryData();
};

