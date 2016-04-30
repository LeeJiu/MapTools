#pragma once
#include "gameNode.h"

struct tagTile
{
	image* tile;
	POINT imagePos;		//가져올 이미지의 좌표
	POINT screenPos;	//화면 상의 좌표
};


class mapTool : public gameNode
{
private:
	image* _tileImage;		//타일 조각 이미지 모음

	vector<tagTile*> _vTile;
	vector<tagTile*>::iterator _viVector;

private:
	RECT rc[TILEMAX];

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	//=====================추가할 함수=====================

};

