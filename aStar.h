#pragma once
#include "gameNode.h"
<<<<<<< HEAD
=======
#include <algorithm>
>>>>>>> refs/remotes/origin/development

class aStar : public gameNode
{
	TagTile _tile[TILENUM][TILENUM];

	vector<TagTile*> _vCloseList;
	vector<TagTile*>::iterator _viCloseList;

	vector<TagTile*> _vOpenList;
	vector<TagTile*>::iterator _viOpenList;

	vector<TagTile*> _vRoute;
	vector<TagTile*>::iterator _viRoute;

<<<<<<< HEAD
public:
	aStar();
	~aStar();
	
	HRESULT init(int battleMapNumber);
=======
	POINT _start, _end;

	bool _finish;

public:
	aStar();
	~aStar();

	HRESULT init(vector<TagTile*> tile);
>>>>>>> refs/remotes/origin/development
	void release();
	void update();
	void render();

<<<<<<< HEAD

	void checkTile();
	void celulateRoute(POINT start, POINT end);
	void reset();
};

=======
	/*           추가 함수          */
	void checkTile();
	void reset();
	void eraseVector(int x, int y);
	void resultRoute(int x, int y);

	vector<TagTile*> moveCharacter(int startX, int startY, int endX, int endY);

	static bool cmp(TagTile* start, TagTile* end) { return start->f < end->f; }
};
>>>>>>> refs/remotes/origin/development
