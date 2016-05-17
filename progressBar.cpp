#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}


HRESULT progressBar::init(float x, float y, int width, int height, bool type)
{
	_x = x;
	_y = y;
	_type = type;
	_rcProgress = RectMake(_x, _y, width, height);
	
	if(_type) _progressBarFront = IMAGEMANAGER->addImage("barTop_hp", "image/ui_battle_bottom_hpbar.bmp", x, y, width, height, true, 0xff00ff);
	if (!_type) _progressBarFront = IMAGEMANAGER->addImage("barTop_sp", "image/ui_battle_bottom_spbar.bmp", x, y, width, height, true, 0xff00ff);
	_progressBarBack = IMAGEMANAGER->addImage("barBottom", "image/ui_battle_bottom_spbar_back.bmp", x, y, width + 2, height + 2, true, 0xff00ff);

	_width = width;

	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rcProgress = RectMake(_x, _y, _progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void progressBar::render()
{
	IMAGEMANAGER->render("barBottom", getMemDC(),
		_rcProgress.left,
		_y,
		0, 0, 
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	if (_type)
	{
		IMAGEMANAGER->render("barTop_hp", getMemDC(),
			_rcProgress.left + 1,
			_y + 1,
			0, 0,
			_width, _progressBarFront->getHeight());
	}

	if (!_type)
	{
		IMAGEMANAGER->render("barTop_sp", getMemDC(),
			_rcProgress.left + 1,
			_y + 1,
			0, 0,
			_width, _progressBarFront->getHeight());
	}
}

//게이지 바
void progressBar::gauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarFront->getWidth();
}