#pragma once
#include "gameNode.h"

class selectStage : public gameNode
{
private:
	float _volume;

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
	vector<RECT> _vRcMapListStr;

	int _mapListSize;
	int _selectMapNumber;

public:
	selectStage();
	~selectStage();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	void mapListInit();
	void setMapListSize(int mapListSize) { _mapListSize = mapListSize; }
};
