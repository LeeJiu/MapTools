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
<<<<<<< HEAD
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
=======
	int count = 0;

	_drawX = _drawY = 0;

	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };

	for (int i = 0; i < TILENUM; i++)		// ���� ( �� )
	{
		for (int j = 0; j < TILENUM; j++)	// ���� ( �� )
		{	
			// �Ʒ� �ʱ�ȭ�κ� ���ؾȵǸ� �������
			// ���� �˷��ټ��������� �ǹ���
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


	// ���� ��ũ��
	_hScrollHri = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 
		315, WINSIZEY - 15, WINSIZEX - 315, 15, _hWnd, (HMENU)100, _hInstance, NULL);
	SetScrollRange(_hScrollHri, SB_CTL, 0, 255, true);
	SetScrollPos(_hScrollHri, SB_CTL, 0, true);
	
	// ���� ��ũ��
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
=======
	// ���� �̹��� ������
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		SAFE_DELETE(_viTile->image);
	}
	// ���� Ŭ����
	_vTile.clear();
>>>>>>> refs/remotes/origin/master
}

void mapTool::update()
{
<<<<<<< HEAD
<<<<<<< HEAD
	keyControl();
=======
=======
	keyControl();

	//_button->update();
}

void mapTool::render()
{
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	char str[128];

	//������ ��Ʈ ���
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

	// ��ư ����
	//_button->render();

	// ���õ� Ÿ���̹��� ���
	//IMAGEMANAGER->findImage("tile")->frameRender(getMemDC(), WINSIZEX - 200, 100, IMAGEMANAGER->findImage("tile")->getFrameX(), IMAGEMANAGER->findImage("tile")->getFrameY());


	sprintf_s(str, "x : %d, y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, str, strlen(str));
}


void mapTool::keyControl()
{
>>>>>>> refs/remotes/origin/master
	// ���콺 Ŭ�� �� ��ġ �̹��� �׸���
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

	// �ӽ� �ʽ�ũ�� Ű �Է� ������
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

<<<<<<< HEAD
	//_button->update();
>>>>>>> refs/remotes/origin/master
}

void mapTool::render()
{
<<<<<<< HEAD
	drawBg();
	drawTile();
=======
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	char str[128];

	//������ ��Ʈ ���
	for (int i = 0; i < _vTile.size(); i++)
=======
	//�� �����͸� ���̺�
	if (KEYMANAGER->isOnceKeyDown('S'))
>>>>>>> refs/remotes/origin/master
	{
		saveMapData();
	}
	//�� �����͸� �ε�
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		loadMapData();
	}
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

void mapTool::saveMapData()
{
	char temp[128];

	vector<string> vStr;
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		vStr.push_back("|");							//������
		vStr.push_back(itoa(_viTile->number, temp, 10));
		vStr.push_back(itoa(_viTile->state, temp, 10));
	}
	TXTDATA->txtSave("database.txt", vStr);
}

void mapTool::loadMapData()
{
	DATABASE->loadDatabase("database.txt");
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		_viTile->number = DATABASE->getElementData(itoa(_viTile->number, temp, 10))->number;
		_viTile->state = (TILESTATE)DATABASE->getElementData(itoa(_viTile->number, temp, 10))->state;
	}
}

void mapTool::nextTile()
{
	selectedNum++;
	
	if (selectedNum >= selectedImage->getMaxFrameX() * selectedImage->getMaxFrameY()) selectedNum = 0;
	
	selectedImage->setFrameX(selectedNum % selectedImage->getMaxFrameX());
	selectedImage->setFrameY(selectedNum / selectedImage->getMaxFrameY());
<<<<<<< HEAD
>>>>>>> refs/remotes/origin/master
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
	//����Ÿ��.
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

	
	//Ÿ������
	for (int i = 0; i < MAPSIZEX; i++)
	{
		for (int j = 0; j < MAPSIZEY; j++)
		{
			if (PtInRect(&rcArr[i][j], _ptMouse))//�ʷ�Ʈ
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
	// �ѹ��� ���� Ÿ��.
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

//���Ÿ�ϵ� ?
=======
}
>>>>>>> refs/remotes/origin/master
