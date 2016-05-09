#pragma once

#pragma warning(disable : 4996)

#include "gameNode.h"
#include <vector>
#include "button.h"

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
	image* image;			// 타일의 이미지
	RECT rc;				// 타일의 렉트 (아이소타일이라해서 보여지는 부분만 렉트라 생각하면 ㄴㄴ)
	POINT pivot;			// 타일 렉트의 중심점
	TILESTATE state;		// 타일의 상태
	MAPNAME mapName;		// 타일맵이름 (이건 변경해도 됨. 크아기준으로 만들었던거라 ice맵 캠프맵 이런식으로 있어서 나눠줬던것)
	int x, y;				// 타일의인덱스 x, y
	int width;				// 타일의 폭
	int height;				// 타일의 높이
	int imageNum;			//이미지 가져오기
	int number;				// 타일의 고유 넘버값 
	bool draw;				// 타일 그려진 유무 ( 이 타일위에 이미지가 그려져있는지 확인 유무)
};								   

class mapTool : public gameNode
{
private:
	vector<TagTile> _vTile;
	vector<TagTile>::iterator _viTile;

	vector<TagTile> _vIsoTile;
	vector<TagTile>::iterator _viIsoTile;

	button* _button;

	bool _rectOn;

	int tileNum;
	int _pickNum;

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

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	//=====================추가할 함수=====================

	void keyControl();
	void selectMap();
	void drawTile(int index);
	void saveMapData();
	void loadMapData();
	void resetMapData();


	
	static void nextTile();

};

