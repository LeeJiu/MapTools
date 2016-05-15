#pragma once
#include "gameNode.h"
class battleCamera : public gameNode
{
public:
	battleCamera();
	~battleCamera();

	HRESULT init();
	void release();
	void update();
	void render();

	void cameraTile();
	void cameraCharacter();
	void cameraFree();
};

