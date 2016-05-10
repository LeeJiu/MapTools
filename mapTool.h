#pragma once

#pragma warning(disable : 4996)

#include "gameNode.h"
#include <vector>
#include "button.h"

static int selectedNum = 0;
static image* selectedImage = NULL;
  

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

