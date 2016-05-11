#pragma once

#pragma warning(disable : 4996)

#include "gameNode.h"
#include <vector>
#include <algorithm>
#include "button.h"



struct OBJ_Y_RENDER
{
	bool operator()(const TagObject& obj1, const TagObject& obj2)
	{
		return obj1.rc.bottom < obj2.rc.bottom;
	}
};

struct ENM_Y_RENDER
{
	bool operator()(const TagEnemy& enm1, const TagEnemy& enm2)
	{
		return enm1.rc.bottom < enm2.rc.bottom;
	}
};

struct OBJ_NUM
{
	bool operator()(const TagObject& obj1, const TagObject& obj2)
	{
		return obj1.number < obj2.number;
	}
};

struct ENM_NUM
{
	bool operator()(const TagEnemy& enm1, const TagEnemy& enm2)
	{
		return enm1.number < enm2.number;
	}
};

enum STATE
{
	SET_TILE, SET_OBJ, SET_ENM
};

static int selectedNum = 0;
static image* selectedImage = NULL;
static STATE _state = SET_TILE;

class mapTool : public gameNode
{
private:
	//맵
	vector<TagTile> _vTile;
	vector<TagTile>::iterator _viTile;

	vector<TagObject> _vObj;
	vector<TagObject>::iterator _viObj;

	vector<TagObject> _vEnemy;
	vector<TagObject>::iterator _viEnemy;


	//샘플
	vector<TagTile> _vIsoTile;
	vector<TagTile>::iterator _viIsoTile;

	vector<TagObject> _vIsoObj;
	vector<TagObject>::iterator _viIsoObj;

	vector<TagObject> _vIsoEnemy;
	vector<TagObject>::iterator _viIsoEnemy;

	//랜더
	vector<TagObject> _vRender;
	vector<TagObject>::iterator _viRender;

	button* _TileButton;
	button* _ObjectButton;
	button* _EnemyButton;
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

	RECT cam;

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
	void setObjectsRender();
	void saveMapData();
	void loadMapData();
	void resetMapData();

	
	static void onTile();
	static void onObject();
	static void onEnemy();
	static void goToMenu();
};

