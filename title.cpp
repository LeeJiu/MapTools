#include "stdafx.h"
#include "title.h"


title::title()
{
}


title::~title()
{
}

HRESULT title::init()
{
	IMAGEMANAGER->addImage("title_background", "image/title/title_background.bmp", WINSIZEX, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("title_logo", "image/title/title_logo.bmp", 1500, 553, true, 0xff00ff);
	IMAGEMANAGER->addImage("title_dialog_type_small", "image/title/title_dialog_type_small.bmp", 264, 63, false, false);
	IMAGEMANAGER->addImage("title_arrow", "image/title/title_arrow.bmp", 35, 35, true, 0xff00ff);
	IMAGEMANAGER->addImage("title_button_start", "image/title/title_button_start.bmp", 264, 63, false, false);
	IMAGEMANAGER->addImage("title_button_exit", "image/title/title_button_exit.bmp", 264, 63, false, false);
	IMAGEMANAGER->addImage("title_button_maptool", "image/title/title_button_maptool.bmp", 264, 63, false, false);

	_alpha = 0;
	_x = 200;
	_y = 100;

	_showAlpha = true;
	_show = _showMenu = _startButton = _maptoolButton = _exitButton = false;
	
	for (int i = 0; i < 3; i++)
	{
		_button[i] = RectMake(CENTERX - IMAGEMANAGER->findImage("title_dialog_type_small")->getWidth() / 2, 420 + i * 80,
			IMAGEMANAGER->findImage("title_dialog_type_small")->getWidth(), IMAGEMANAGER->findImage("title_dialog_type_small")->getHeight());
		_draw[i] = RectMakeCenter((_button[i].left + _button[i].right) / 2 , (_button[i].top + _button[i].bottom) / 2 + 10, 
			IMAGEMANAGER->findImage("title_dialog_type_small")->getWidth() - 100, IMAGEMANAGER->findImage("title_dialog_type_small")->getHeight() - 20);
	}

	return S_OK;
}

void title::release()
{
}

void title::update()
{
	showLogo();
	clickMenu();

<<<<<<< HEAD
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_y = 0;
		_show = true;
		_showMenu = true;
	}

	if (_showMenu) showArrow();
=======
	if (_showMenu) showArrow();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_alpha = 255;
		_showAlpha = false;
		_show = true;
		_y = 0;
		_showMenu = true;
	}
>>>>>>> refs/remotes/origin/development
}

void title::render()
{
	IMAGEMANAGER->findImage("title_background")->render(getMemDC(), 0, 0);

	if (_showAlpha)
	{
		IMAGEMANAGER->findImage("title_logo")->alphaRender(getMemDC(), _x, _y, WINSIZEX - 300, 400, _alpha);
	}
	else if (_show)
	{
		IMAGEMANAGER->findImage("title_logo")->render(getMemDC(), _x, _y, WINSIZEX - 300, 400, 0, 0, 
												IMAGEMANAGER->findImage("title_logo")->getWidth(), IMAGEMANAGER->findImage("title_logo")->getHeight());
	}

	if (_showMenu)
	{
		IMAGEMANAGER->findImage("title_button_start")->render(getMemDC(), _button[0].left, _button[0].top);
		IMAGEMANAGER->findImage("title_button_maptool")->render(getMemDC(), _button[1].left, _button[1].top);
		IMAGEMANAGER->findImage("title_button_exit")->render(getMemDC(), _button[2].left, _button[2].top);
		
		if (_startButton)
		{
			IMAGEMANAGER->findImage("title_arrow")->render(getMemDC(), _button[0].left - IMAGEMANAGER->findImage("title_arrow")->getWidth() / 2,
													(_button[0].top + _button[0].bottom) / 2 - IMAGEMANAGER->findImage("title_arrow")->getHeight() / 2);
		}
		else if (_maptoolButton)
		{
			IMAGEMANAGER->findImage("title_arrow")->render(getMemDC(), _button[1].left - IMAGEMANAGER->findImage("title_arrow")->getWidth() / 2,
													(_button[1].top + _button[1].bottom) / 2 - IMAGEMANAGER->findImage("title_arrow")->getHeight() / 2);
		}
		else if (_exitButton)
		{
			IMAGEMANAGER->findImage("title_arrow")->render(getMemDC(), _button[2].left - IMAGEMANAGER->findImage("title_arrow")->getWidth() / 2,
													(_button[2].top + _button[2].bottom) / 2 - IMAGEMANAGER->findImage("title_arrow")->getHeight() / 2);
		}
	}
}

void title::showLogo()
{
	if (_showAlpha)
	{
		_alpha += 2;
		if (_alpha >= 255)
		{
			_alpha = 255;
			_showAlpha = false;
			_show = true;
		}
	}
	else if (_show)
	{
		_y -= 1;
		if (_y <= 0)
		{
			_y = 0;
			_showMenu = true;
		}
	}
}

void title::showArrow()
{
	for (int i = 0; i < 3; i++)
	{
		if (PtInRect(&_button[i], _ptMouse))
		{
			switch (i)
			{
			case 0:
				_startButton = true;
				_maptoolButton = false;
				_exitButton = false;
				return;
			case 1:
				_startButton = false;
				_maptoolButton = true;
				_exitButton = false;
				return;
			case 2:
				_startButton = false;
				_maptoolButton = false;
				_exitButton = true;
				return;
			}
		}
		else
		{
			_startButton = false;
			_maptoolButton = false;
			_exitButton = false;
		}
	}
}

void title::clickMenu()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_startButton)
		{
			SCENEMANAGER->changeScene("town");
		}
		else if (_maptoolButton)
		{
			SCENEMANAGER->changeScene("mapTool");
		}
		else if (_exitButton)
		{
			PostQuitMessage(0);
		}
	}
}
