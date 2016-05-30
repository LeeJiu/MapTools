#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}


HRESULT progressBar::init(int x, int y, int width, int height, bool character)
{
	_x = x;
	_y = y;

	_rcProgress = RectMakeCenter(_x, _y, width, height);
	
	_progressBarFront = new image;
	if (character == true)
	{
		_progressBarFront->init("image/ui/ui_hpBarFront1.bmp", x, y, width, height, 1, 1, true, 0xff00ff);
	}
	else
	{
		_progressBarFront->init("image/ui/ui_hpBarFront.bmp", x, y, width, height, 1, 1, true, 0xff00ff);
	}
	_progressBarBack = new image;
	_progressBarBack->init("image/ui/ui_hpBarBack.bmp", x, y, width, height, 1, 1, true, 0xff00ff);

	_width = width;

	return S_OK;
}

void progressBar::release()
{
	SAFE_DELETE(_progressBarBack);
	SAFE_DELETE(_progressBarFront);
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void progressBar::render()
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
void progressBar::gauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarFront->getWidth();
}