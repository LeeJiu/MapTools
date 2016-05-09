#pragma once
#include "gameNode.h"
#include <vector>
#include <map>

struct tagTile
{
	image* image;
	float x, y;//중심점
	RECT rc;
	RECT realRc;
	int number;
};

class mapTool : public gameNode
{
private:
	RECT rcArr[MAPSIZEX][MAPSIZEY];//배경
	
	vector<tagTile> _vTile;
	vector<tagTile>::iterator _viTile;
	
	vector<tagTile> _vMap;
	vector<tagTile>::iterator _viMap;

	int tileNum;
	int pickTile;
public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	void drawBg();
	void drawTile();

	void keyControl();
	void putTile(RECT* rc);

	//=====================추가할 함수=====================

};

