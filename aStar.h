#pragma once
#include "gameNode.h"

class aStar : public gameNode
{
	TagTile _tile[TILENUM][TILENUM];

	vector<TagTile*> _vCloseList;
	vector<TagTile*>::iterator _viCloseList;

	vector<TagTile*> _vOpenList;
	vector<TagTile*>::iterator _viOpenList;

	vector<TagTile*> _vRoute;
	vector<TagTile*>::iterator _viRoute;

public:
	aStar();
	~aStar();
	
	HRESULT init(int battleMapNumber);
	void release();
	void update();
	void render();


	void checkTile();
	void celulateRoute(POINT start, POINT end);
	void reset();
};

