#pragma once

#pragma warning(disable : 4996)

#include "gameNode.h"
#include <vector>
#include <algorithm>
#include "button.h"

<<<<<<< HEAD
=======

>>>>>>> refs/remotes/origin/moobin
struct OBJ_Y_RENDER
{
	bool operator()(const TagObject* obj1, const TagObject* obj2)
	{
		return obj1->rc.bottom < obj2->rc.bottom;
	}
};

struct OBJ_NUM
{
	bool operator()(const TagObject* obj1, const TagObject* obj2)
	{
		return obj1->number < obj2->number;
	}
};

<<<<<<< HEAD
=======

>>>>>>> refs/remotes/origin/moobin
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
	vector<TagTile*> _vTile;
	vector<TagTile*>::iterator _viTile;
<<<<<<< HEAD

	vector<TagObject*> _vObj;
	vector<TagObject*>::iterator _viObj;

	vector<TagObject*> _vEnemy;
	vector<TagObject*>::iterator _viEnemy;


	//샘플
	vector<TagTile*> _vIsoTile;
	vector<TagTile*>::iterator _viIsoTile;

	vector<TagObject*> _vIsoObj;
	vector<TagObject*>::iterator _viIsoObj;

	vector<TagObject*> _vIsoEnemy;
	vector<TagObject*>::iterator _viIsoEnemy;

=======

	vector<TagObject*> _vObj;
	vector<TagObject*>::iterator _viObj;

	vector<TagObject*> _vEnemy;
	vector<TagObject*>::iterator _viEnemy;


	//샘플
	vector<TagTile*> _vIsoTile;
	vector<TagTile*>::iterator _viIsoTile;

	vector<TagObject*> _vIsoObj;
	vector<TagObject*>::iterator _viIsoObj;

	vector<TagObject*> _vIsoEnemy;
	vector<TagObject*>::iterator _viIsoEnemy;

>>>>>>> refs/remotes/origin/moobin
	//랜더
	vector<TagObject*> _vRender;
	vector<TagObject*>::iterator _viRender;

	button* _TileButton;
	button* _ObjectButton;
	button* _EnemyButton;
	button* _ExitButton;


	bool _rectOn;

	int tileNum;
	int _pickNum;


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

	void setSampleTile();
	void setSampleObject();
	void setSampleEnemy();

	void setTile();

	void keyControl();
	void selectMap();
<<<<<<< HEAD
	//void drawTile(int index);
	//void setObjectsRender();
=======
	void drawTile(int index);
	void setObjectsRender();
>>>>>>> refs/remotes/origin/moobin
	void saveMapData();
	void loadMapData();
	void resetMapData();


	static void onTile();
	static void onObject();
	static void onEnemy();
	static void goToMenu();
};