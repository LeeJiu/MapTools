#include "stdafx.h"
#include "progressBar2.h"


progressBar2::progressBar2()
{
}


progressBar2::~progressBar2()
{
}


HRESULT progressBar2::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMakeCenter(_x, _y, width, height);
	
	_progressBarFront = new image;
	_progressBarFront->init("image/battleUI/ui_hpBarFront.bmp", x, y, width, height, 1, 1, true, 0xff00ff);
	_progressBarBack = new image;
	_progressBarBack->init("image/battleUI/ui_hpBarBack.bmp", x, y, width, height, 1, 1, true, 0xff00ff);

	_width = width;

	return S_OK;
}

void progressBar2::release()
{
	SAFE_DELETE(_progressBarBack);
	SAFE_DELETE(_progressBarFront);
}

void progressBar2::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void progressBar2::render()
{
	_progressBarBack->render(getMemDC(),
		_rcProgress.left,
		_rcProgress.top,
		0, 0, 
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	_progressBarFront->render(getMemDC(),
		_rcProgress.left,
		_rcProgress.top,
		0, 0, 
		_width, _progressBarFront->getHeight());
}

//게이지 바
void progressBar2::gauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarFront->getWidth();
}