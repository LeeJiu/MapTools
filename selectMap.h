#pragma once
#include "gameNode.h"
class selectMap : public gameNode
{
private:
	image* _imageListTop;
	vector<image*> _imageListBody;
	image* _imageListBottom;

	image* _imageTitleBack;
	image* _imageBottomBack;
	image* _imageGoingBack;
	image* _imageArrow;

	RECT _rcListTop;
	vector<RECT> _rcListBody;
	RECT _rcListBottom;

	RECT _rcTitle;
	RECT _rcBottom;
	RECT _rcGoing;
	RECT _rcArrow;

	RECT _rcTitleStr;
	RECT _rcGoingStart;
	RECT _rcGoingSkip;
	RECT _rcGoingExit;

	vector<char*> _vMapList;
	
	
	int _mapListSize;

	int _selectMapNumber;

public:
	selectMap();
	~selectMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void setMapListSize(int mapListSize) { _mapListSize = mapListSize; }
};

