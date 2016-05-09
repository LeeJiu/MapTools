#pragma once
#include "gameNode.h"
class selectMap : public gameNode
{
private:
	image* _imageListBack;
	image* _imageTitleBack;
	image* _imageBottomBack;
	image* _imageGoingBack;
	image* _imageArrow;

	RECT _rcList;
	RECT _rcTitle;
	RECT _rcBottom;
	RECT _rcGoing;
	RECT _rcArrow;

	
	vector<char*> _vMapList;
	

public:
	selectMap();
	~selectMap();

	HRESULT init();
	void release();
	void update();
	void render();

};

