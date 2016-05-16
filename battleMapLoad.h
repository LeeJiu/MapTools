#pragma once
#include "gameNode.h"
#include <algorithm>



class battleMapLoad : public gameNode
{
private:
	TagTile _tile[TILENUM][TILENUM];

	vector<TagTile> _vTile;					   //Ÿ�� vector
	vector<TagTile>::iterator _viTile;		   //Ÿ�� vector::iterator
											   
	vector<TagObject> _vObj;				   //������Ʈ vector
	vector<TagObject>::iterator _viObj;		   //������Ʈ vector::iterator
											   
	vector<TagObject> _vEnemy;				   //���ʹ� vector
	vector<TagObject>::iterator _viEnemy;	   //���ʹ� vector::iterator
											   
	vector<TagObject> _vRender;				   //������ vector
	vector<TagObject>::iterator _viRender; 	   //������ vector::iterator

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

