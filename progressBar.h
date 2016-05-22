#pragma once

#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarFront;
	image* _progressBarBack;

public:
	progressBar();
	~progressBar();

	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render();

	//게이지 바
	void gauge(float currentGauge, float maxGauge);

	//좌표 셋업
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

};

