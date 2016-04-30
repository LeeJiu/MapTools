#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	_tileImage = IMAGEMANAGER->addFrameImage("tile", "image/mapTile.bmp", 208, 156, 4, 3, false, false);

	int index;
	for (int y = 0; y < TILENUM; ++y)
	{
		for (int x = 0; x < TILENUM; ++x)
		{
			index = y * TILENUM + x;
			rc[index] = RectMake((index % TILENUM) * _tileImage->getFrameWidth(), y * _tileImage->getFrameHeight(),
				_tileImage->getFrameWidth(), _tileImage->getFrameHeight());
		}
	}

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
}

void mapTool::render()
{
	for (int i = 0; i < TILEMAX; ++i)
	{
		Rectangle(getMemDC(), rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
	}
}
