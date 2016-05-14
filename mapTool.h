#pragma once

#pragma warning(disable : 4996)

#include "gameNode.h"
#include <vector>
#include <algorithm>
#include "button.h"

static int selectedNum = 0;
static image* selectedImage = NULL;
static bool _isTile = true;

class mapTool : public gameNode
{
private:
	vector<TagTile> _vTile;
	vector<TagTile>::iterator _viTile;

	vector<TagObject> _vObj;
	vector<TagObject>::iterator _viObj;


	vector<TagTile> _vIsoTile;
	vector<TagTile>::iterator _viIsoTile;

	vector<TagObject> _vIsoObj;
	vector<TagObject>::iterator _viIsoObj;


	button* _TileButton;
	button* _ObjectButton;
	button* _ExitButton;
	
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


	
	static void onTile();
	static void onObject();
	static void goToMenu();
};

