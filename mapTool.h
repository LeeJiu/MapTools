#pragma once
#include "gameNode.h"
<<<<<<< HEAD
#include "button.h"

struct tagTile
{
	image* tile;
	POINT imagePos;		//가져올 이미지의 좌표
	POINT screenPos;	//화면 상의 좌표
	int index;
	bool draw;
};
=======
#include <vector>
#include "button.h"
>>>>>>> refs/remotes/origin/master

#define TILENUM 20
#define WIDTH 128

static int selectedNum = 0;
static image* selectedImage = NULL;

enum TILESTATE
{
	S_NONE, S_ICE, S_FIRE
};

enum MAPNAME
{
	M_NONE, M_CAMP, M_FLOOPY, M_ICE
};

struct TagTile
{
	int x, y;					   // 타일의인덱스 x, y
	int width;					   // 타일의 폭
	int height;					   // 타일의 높이
	int number;					   // 타일의 넘버값 (여러가지 이미지가 합쳐진 이미지를 init해서 쓸꺼기때문에 이 넘버값으로 해당 이미지를 찾기위한 용도)
	image* image;				   // 타일의 이미지
	RECT rc;					   // 타일의 렉트 (아이소타일이라해서 보여지는 부분만 렉트라 생각하면 ㄴㄴ)
	POINT pivot;				   // 타일 렉트의 중심점
	TILESTATE state;			   // 타일의 상태
	MAPNAME mapName;			   // 타일맵이름 (이건 변경해도 됨. 크아기준으로 만들었던거라 ice맵 캠프맵 이런식으로 있어서 나눠줬던것)
	bool draw;					   // 타일 그려진 유무 ( 이 타일위에 이미지가 그려져있는지 확인 유무)
};								   

class mapTool : public gameNode
{
private:
<<<<<<< HEAD
	image* _tileImage;

	vector<tagTile> _vTile;
	vector<tagTile>::iterator _viVector;

	RECT rc[TILEMAX];

	button* _btLeft;
	button* _btRight;

	int _tileFrameX, _tileFrameY;
=======
	vector<TagTile> _vTile;
	vector<TagTile>::iterator _viTile;

	button* _button;

	bool _rectOn;

	int _drawX;
	int _drawY;

	/* 
				UI Rect
		아래부분은 UI렉트 
		그냥 깔끔하게 보일려고 만든 렉트
	*/
	RECT rcDrawMap;
	RECT rcUI;
	RECT rcSelectTile;
	RECT rcButton;

	/*
				Scrool Bar
		위치 추가만 하고 아직 마우스랑 연동 안시킴 화팅!
	*/
	HWND _hScrollVer;
	HWND _hScrollHri;
>>>>>>> refs/remotes/origin/master

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	//=====================추가할 함수=====================
<<<<<<< HEAD
	void keyControl();
	void changeTile();
	void inputTile(int idx);

	void saveMap();
	void loadMap();

	//=====================버		튼=====================
	static int _tileIndex;
	
	static void onLeftButton();
	static void onRightButton();
=======

	void selectMap();
	void drawTile(int index);

	static void nextTile();
>>>>>>> refs/remotes/origin/master
};

