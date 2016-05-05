#include "stdafx.h"
#include "mapTool.h"

int mapTool::_tileIndex = 0;

mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
<<<<<<< HEAD
	_tileImage = IMAGEMANAGER->addFrameImage("tile", "image/mapTile.bmp", 208, 156, 4, 3, false, false);

	IMAGEMANAGER->addFrameImage("button", "image/button.bmp", 64, 32, 2, 1, true, 0xff00ff);

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

	for (int i = 0; i < TILEMAX; ++i)
	{
		tagTile tile;
		memset(&tile, 0, sizeof(tagTile));
		tile.tile = new image;
		tile.tile->init("image/mapTile.bmp", 208, 156, 4, 3, false, false);
		tile.index = i;
		_vTile.push_back(tile);
	}

	_btLeft = new button;
	_btLeft->init("button", WINSIZEX - 200, 100, PointMake(0, 0), PointMake(0, 0), onLeftButton);
	_btRight = new button;
	_btRight->init("button", WINSIZEX - 100, 100, PointMake(1, 0), PointMake(1, 0), onRightButton);
=======
	int count = 0;

	_drawX = _drawY = 0;

	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };

	for (int i = 0; i < TILENUM; i++)		// 세로 ( 열 )
	{
		for (int j = 0; j < TILENUM; j++)	// 가로 ( 행 )
		{	
			// 아래 초기화부분 이해안되면 물어보세용
			// 물론 알려줄수있을지는 의문임
			TagTile tile;
			ZeroMemory(&tile, sizeof(TagTile));
			//tile.image = new image;
			//tile.image->init("image/mapTile.bmp", 208, 156, 4, 3, false, false);
			tile.width = WIDTH;
			tile.height = WIDTH / 2;
			tile.rc = RectMakeCenter(firstPivot.x + j * tile.width / 2 - i * tile.width / 2, firstPivot.y + j * tile.width / 4 + i * tile.width / 4, tile.width, tile.height);
			tile.pivot.x = (tile.rc.left + tile.rc.right) / 2;
			tile.pivot.y = (tile.rc.top + tile.rc.bottom) / 2;
			tile.x = j;
			tile.y = i;
			tile.number = count;
			tile.state = S_NONE;
			tile.mapName = M_NONE;

			_vTile.push_back(tile);

			count++;
		}
	}

	selectedNum = 0;
	IMAGEMANAGER->addFrameImage("button", "image/button.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tile", "image/mapTile.bmp", 208, 156, 4, 3, false, false);

	//_button = new button;
	//_button->init("button", WINSIZEX - 100, 200, PointMake(1, 0), PointMake(1, 0), nextTile);

	selectedImage = IMAGEMANAGER->findImage("tile");

	///////////////////////////////////////////////////////////////////////////////////////////////////

	rcUI = RectMake(0, 0, 300, WINSIZEY);
	rcSelectTile = RectMake(5, 5, 290, 160);

	///////////////////////////////////////////////////////////////////////////////////////////////////


	// 가로 스크롤
	_hScrollHri = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 
		315, WINSIZEY - 15, WINSIZEX - 315, 15, _hWnd, (HMENU)100, _hInstance, NULL);
	SetScrollRange(_hScrollHri, SB_CTL, 0, 255, true);
	SetScrollPos(_hScrollHri, SB_CTL, 0, true);
	
	// 세로 스크롤
	_hScrollVer = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_VERT, 
		300, 0, 15, WINSIZEY - 15, _hWnd, (HMENU)101, _hInstance, NULL);
	SetScrollRange(_hScrollVer, SB_CTL, 0, 255, true);
	SetScrollPos(_hScrollVer, SB_CTL, 0, true);
>>>>>>> refs/remotes/origin/master

	return S_OK;
}

void mapTool::release()
{
<<<<<<< HEAD
	SAFE_DELETE(_btLeft);
	SAFE_DELETE(_btRight);
=======
	// 벡터 이미지 지우자
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		SAFE_DELETE(_viTile->image);
	}
	// 벡터 클리어
	_vTile.clear();
>>>>>>> refs/remotes/origin/master
}

void mapTool::update()
{
<<<<<<< HEAD
	_btLeft->update();
	_btRight->update();

	changeTile();
	keyControl();
=======
	// 마우스 클릭 된 위치 이미지 그리자
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			if (PtInRect(&_vTile[i].rc, _ptMouse))
			{
				//drawTile(i);
			}
		}
	}

	// 임시 맵스크롤 키 입력 만들자
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _vTile[0].rc.top < 0)
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i].rc = RectMake(_vTile[i].rc.left, _vTile[i].rc.top + 1, _vTile[i].width, _vTile[i].height);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _vTile[_vTile.size() - 1].rc.bottom > WINSIZEY - 15)
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i].rc = RectMake(_vTile[i].rc.left, _vTile[i].rc.top - 1, _vTile[i].width, _vTile[i].height);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i].rc = RectMake(_vTile[i].rc.left + 1, _vTile[i].rc.top, _vTile[i].width, _vTile[i].height);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i].rc = RectMake(_vTile[i].rc.left - 1, _vTile[i].rc.top, _vTile[i].width, _vTile[i].height);
		}
	}

	//_button->update();
>>>>>>> refs/remotes/origin/master
}

void mapTool::render()
{
<<<<<<< HEAD
	_btLeft->render();
	_btRight->render();

	_tileImage->frameRender(getMemDC(), WINSIZEX - 150 - _tileImage->getFrameWidth() / 2, 
		100 - _tileImage->getFrameHeight() / 2, _tileFrameX, _tileFrameY);

	for (int i = 0; i < TILEMAX; ++i)
	{
		Rectangle(getMemDC(), rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
	}

	for (int i = 0; i < _vTile.size(); ++i)
	{
		if (!_vTile[i].draw) continue;

		_vTile[i].tile->frameRender(getMemDC(), _vTile[i].screenPos.x, _vTile[i].screenPos.y, 
			_vTile[i].imagePos.x, _vTile[i].imagePos.y);
	}
}

void mapTool::keyControl()
{
	int index;
	for (int y = 0; y < TILENUM; ++y)
	{
		for (int x = 0; x < TILENUM; ++x)
		{
			index = y * TILENUM + x;
			if (PtInRect(&rc[index], _ptMouse))
			{
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
				{
					inputTile(index);
				}
			}
		}
	}
}

void mapTool::changeTile()
{
	_tileFrameX = mapTool::_tileIndex % 4;
	_tileFrameY = mapTool::_tileIndex / 4;
}

void mapTool::inputTile(int idx)
{
	_vTile[idx].draw = true;
	_vTile[idx].imagePos = PointMake(_tileFrameX, _tileFrameY);
	_vTile[idx].screenPos = PointMake(rc[idx].left, rc[idx].top);
}

void mapTool::saveMap()
{
}

void mapTool::loadMap()
{
}

void mapTool::onLeftButton()
{
	_tileIndex--;
	if (_tileIndex < 0)
	{
		_tileIndex = 11;
	}
}

void mapTool::onRightButton()
{
	_tileIndex++;
	if (_tileIndex > 11)
	{
		_tileIndex = 0;
	}
=======
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	char str[128];

	//각각의 렉트 출력
	for (int i = 0; i < _vTile.size(); i++)
	{
		//Rectangle(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, _vTile[i].rc.right, _vTile[i].rc.bottom);
		IsoRender(getMemDC(), _vTile[i].rc);

		if (_vTile[i].draw)
		{
			_vTile[i].image->frameRender(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, _vTile[i].image->getFrameX(), _vTile[i].image->getFrameY());
		}

		sprintf_s(str, "%d", _vTile[i].number);
		TextOut(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, str, strlen(str));
	}

	///////////////////////////////////////////////////////////////////////////////

	Rectangle(getMemDC(), rcUI.left, rcUI.top, rcUI.right, rcUI.bottom);
	Rectangle(getMemDC(), rcSelectTile.left, rcSelectTile.top, rcSelectTile.right, rcSelectTile.bottom);

	///////////////////////////////////////////////////////////////////////////////

	// 버튼 랜더
	//_button->render();

	// 선택될 타일이미지 출력
	//IMAGEMANAGER->findImage("tile")->frameRender(getMemDC(), WINSIZEX - 200, 100, IMAGEMANAGER->findImage("tile")->getFrameX(), IMAGEMANAGER->findImage("tile")->getFrameY());


	sprintf_s(str, "x : %d, y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, str, strlen(str));
}


void mapTool::selectMap()
{
	
}

void mapTool::drawTile(int index)
{
	_vTile[index].draw = true;
	_vTile[index].number = selectedNum;
	_vTile[index].image->setFrameX(_vTile[index].number % _vTile[index].image->getMaxFrameX());
	_vTile[index].image->setFrameY(_vTile[index].number / _vTile[index].image->getMaxFrameY());
}

void mapTool::nextTile()
{
	selectedNum++;
	
	if (selectedNum >= selectedImage->getMaxFrameX() * selectedImage->getMaxFrameY()) selectedNum = 0;
	
	selectedImage->setFrameX(selectedNum % selectedImage->getMaxFrameX());
	selectedImage->setFrameY(selectedNum / selectedImage->getMaxFrameY());
>>>>>>> refs/remotes/origin/master
}
