#pragma once
#include "gameNode.h"
#include <algorithm>

class aStar : public gameNode
{
	TagTile _tile[TILENUM][TILENUM];

	vector<TagTile*> _vCloseList;
	vector<TagTile*>::iterator _viCloseList;

	vector<TagTile*> _vOpenList;
	vector<TagTile*>::iterator _viOpenList;

	vector<TagTile*> _vRoute;
	vector<TagTile*>::iterator _viRoute;

	POINT _start, _end;

	bool _finish;

public:
	aStar();
	~aStar();
	
	HRESULT init();
	void release();
	void update();
	void render();

	void checkTile();
	void reset();

	void eraseVector(int x, int y);

	vector<TagTile*> moveCharacter(int startX, int startY, int endX, int endY);

	void resultRoute(int x, int y);

	static bool cmp(TagTile* start, TagTile* end) { return start->f < end->f; }
};

