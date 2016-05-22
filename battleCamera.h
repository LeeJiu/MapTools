#pragma once
#include "gameNode.h"
class battleCamera : public gameNode
{

	////////   cameraTile   /////////
	float _cameraTileX, _cameraTileY;// cameraTile �ε��� x, y;
	float _scroolSpeed;				// cameraTile �ӵ�
	float _scroolAngle;				// cameraTile �̵�����

	//////   cameraCharacter   //////
	int _joomSize;

	bool _isMapScrool;				// �� ��ũ�� ����
	bool _isVibrate;				// ���� ����
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

	void setIsVibrate(bool isVibrate) { _isVibrate = isVibrate; }
	void setIsJoomIn(bool isJoomIn) { _isJoomIn = isJoomIn; }
	void setIsJoomOut(bool isJoomOut) { _isJoomOut = isJoomOut; }
	
	void cameraVibrate();
	void cameraTile();
	void cameraFree();
};

