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
	//background
	for (int i = 0; i < MAPSIZEX; i++)
	{
		for (int j = 0; j < MAPSIZEY; j++)
		{
			rcArr[i][j] = RectMake(TILESIZE + TILESIZE * j, TILESIZE + TILESIZE * i, TILESIZE, TILESIZE);
		}
	}

	int num = 0;
	for (int i = 0; i < TILEMAXY; i++)
	{
		for (int j = 0; j < TILEMAXX; j++)
		{
			tagTile tile;
			ZeroMemory(&tile, sizeof(tagTile));
			tile.number = num;
			tile.image = new image;
			tile.image->init("image/mapTile.bmp", 208, 156, false, false);
			tile.rc = RectMake(TILESIZE * j, TILESIZE * i, TILESIZE, TILESIZE);
			tile.realRc = tile.rc;
			tile.x = tile.realRc.left + TILESIZE / 2;
			tile.y = tile.realRc.top + TILESIZE / 2;
			
			_vTile.push_back(tile);
			num++;
		}
	}

	tileNum = 0;

	return S_OK;
}

void mapTool::release()
{
	for (_viTile = _vTile.begin(); _viTile != _vTile.end();)
	{
		SAFE_DELETE(_viTile->image);
		_viTile = _vTile.erase(_viTile);
	}

	_vTile.clear();

	for (_viMap = _vMap.begin(); _viMap != _vMap.end();)
	{
		SAFE_DELETE(_viMap->image);
		_viMap = _vMap.erase(_viMap);
	}

	_vMap.clear();
}

void mapTool::update()
{
	keyControl();
}

void mapTool::render()
{
	drawBg();
	drawTile();
}

void mapTool::drawBg()
{
	for (int i = 0; i < MAPSIZEX; i++)
	{
		for (int j = 0; j < MAPSIZEY; j++)
		{
			Rectangle(getMemDC(), rcArr[i][j].left, rcArr[i][j].top, rcArr[i][j].right, rcArr[i][j].bottom);
		}
	}

	char str[100];
	sprintf_s(str, "x : %d ", _ptMouse.x);
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y - 20, str, strlen(str));

	sprintf_s(str, "y : %d", _ptMouse.y);
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y , str, strlen(str));
	
	sprintf_s(str, "pickTile : %d  tileNum : %d", pickTile, tileNum);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
}

void mapTool::drawTile()
{
	//샘플타일.
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		if (_viTile->number == tileNum)
		{
			_viTile->image->render(getMemDC(), 700, CENTERY, _viTile->rc.left, _viTile->rc.top, TILESIZE, TILESIZE);
			
			char str[50];
			sprintf_s(str, "%d", _viTile->number);
			TextOut(getMemDC(), 700 + TILESIZE / 2, CENTERY + TILESIZE / 2, str, strlen(str));

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				RECT rc = RectMake(700, CENTERY, TILESIZE, TILESIZE);
				if (PtInRect(&rc, _ptMouse))
				{
					pickTile = _viTile->number;
				}
				
			}
		}
	}

	for (_viMap = _vMap.begin(); _viMap != _vMap.end(); ++_viMap)
	{
		_viMap->image->render(getMemDC(), _viMap->realRc.left, _viMap->realRc.top, _viMap->rc.left, _viMap->rc.top, TILESIZE, TILESIZE);
		//_viMap->image->render(getMemDC(), _viMap->realRc.left, _viMap->realRc.right);


		//char str[50];
		//sprintf_s(str, "%d", _viMap->number);
		//TextOut(getMemDC(), _viMap->realRc.left, _viMap->realRc.left, str, strlen(str));
		//
		//sprintf_s(str, "l %d t %d",_viMap->rc.left, _viMap->rc.top);
		//TextOut(getMemDC(), _viMap->realRc.left, _viMap->realRc.left + 15, str, strlen(str));
		//
		//sprintf_s(str, "r %d b %d", _viMap->rc.right, _viMap->rc.bottom);
		//TextOut(getMemDC(), _viMap->realRc.left, _viMap->realRc.left + 30, str, strlen(str));

		//char str[50];
		//sprintf_s(str, "%d", _viMap->number);
		//TextOut(getMemDC(), _viMap->rc.left, _viMap->rc.left, str, strlen(str));
		//
		//sprintf_s(str, "l %d t %d",_viMap->rc.left, _viMap->rc.top);
		//TextOut(getMemDC(), _viMap->rc.left, _viMap->rc.left + 15, str, strlen(str));
		//
		//sprintf_s(str, "r %d b %d", _viMap->rc.right, _viMap->rc.bottom);
		//TextOut(getMemDC(), _viMap->rc.left, _viMap->rc.left + 30, str, strlen(str));
	}
}

void mapTool::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) if (tileNum > 0) tileNum--;
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) if (tileNum < TILEMAXX * TILEMAXY - 1) tileNum++;

	
	//타일위에
	for (int i = 0; i < MAPSIZEX; i++)
	{
		for (int j = 0; j < MAPSIZEY; j++)
		{
			if (PtInRect(&rcArr[i][j], _ptMouse))//맵렉트
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					tagTile map;
					ZeroMemory(&map, sizeof(tagTile));
					map.image = new image;
					map.image->init("image/mapTile.bmp", 208, 156, false, false);
					map.number = pickTile;
					map.rc = _vTile[pickTile].rc;
					map.realRc = rcArr[i][j];
					map.x = map.realRc.left;

					_vMap.push_back(map);
				}
			}
		}
	}
}

void mapTool::putTile(RECT* rc)
{
	// 넘버랑 같은 타일.
		tagTile map;
		ZeroMemory(&map, sizeof(tagTile));
		map.image = new image;
		map.image->init("image/mapTile.bmp", 208, 156, false, false);
		map.number = pickTile;
		map.rc = RectMake(_vTile[pickTile].rc.left, _vTile[pickTile].rc.top, TILESIZE, TILESIZE);
		map.realRc = *rc;
		map.x = rc->left;
		map.y = rc->top;

		_vMap.push_back(map);
}

//배경타일도 ?