#pragma once
#include "gameNode.h"
class battleCamera : public gameNode
{

	////////   cameraTile   /////////
	float _cameraTileX, _cameraTileY;	// cameraTile 인덱스 x, y;
	float _scroolSpeed;					// cameraTile 속도
	float _scroolAngle;					// cameraTile 이동각도

	//////   cameraCharacter   //////
	int _joomSize;

	bool _isMapScrool;					// 맵 스크롤 유무
	bool _isVibrate;					// 진동 유무
	bool _isJoomIn;
	bool _isJoomOut;

	int _vibrateCount;

public:
	battleCamera();
	~battleCamera();

	HRESULT init();
	void release();
	void update();
	void render();

	void setCameraTile(float x, float y);
	void setCameraJoomIn();
	void setCameraJoomOut();

	// set함수
	void setIsVibrate(bool isVibrate) { _isVibrate = isVibrate; }
	void setIsJoomIn(bool isJoomIn) { _isJoomIn = isJoomIn; }
	void setIsJoomOut(bool isJoomOut) { _isJoomOut = isJoomOut; }
	
	// get함수
	bool getIsVibrate() { return _isVibrate; }
	bool getIsJoomIn() { return _isJoomIn; }
	bool getIsJoomOut() { return _isJoomOut; }

	void cameraVibrate();
	void cameraTile();
	void cameraFree();
};

