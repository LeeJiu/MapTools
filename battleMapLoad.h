#pragma once
#include "gameNode.h"
#include <algorithm>



class battleMapLoad : public gameNode
{
private:
	TagTile _tile[TILENUM][TILENUM];

	vector<TagTile> _vTile;					   //타일 vector
	vector<TagTile>::iterator _viTile;		   //타일 vector::iterator
											   
	vector<TagObject> _vObj;				   //오브젝트 vector
	vector<TagObject>::iterator _viObj;		   //오브젝트 vector::iterator
											   
	vector<TagObject> _vEnemy;				   //에너미 vector
	vector<TagObject>::iterator _viEnemy;	   //에너미 vector::iterator
											   
	vector<TagObject> _vRender;				   //렌더용 vector
	vector<TagObject>::iterator _viRender; 	   //렌더용 vector::iterator

	vector<TagTile> _vIsoTile;

public:
	battleMapLoad();
	~battleMapLoad();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadMapData();
	vector<TagTile> getTileVector() { return _vTile; }	
};

