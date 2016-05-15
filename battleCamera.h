#pragma once
#include "gameNode.h"
class battleCamera : public gameNode
{
	TagTile* _tile[TILENUM][TILENUM];
	RECT _rc;
	////////   cameraTile   /////////
	int _cameraTileX, _cameraTileY;// cameraTile 인덱스 x, y;
	float _scroolSpeed;				// cameraTile 속도
	float _scroolAngle;				// cameraTile 이동각도

									//////   cameraCharacter   //////
	int _moveSpeed;					// cameraCharacter 속도

	bool _isMapScrool;				// 맵 스크롤 유무
public:
	battleCamera();
	~battleCamera();

	HRESULT init(vector<TagTile*>& tile);
	void release();
	void update();
	void render();

	void setCameraTile(int x, int y);
	void setCameraCharacter(RECT rc);

	void cameraTile();
	void cameraCharacter(vector<TagTile*> cameraTile);
	void cameraFree();

};

