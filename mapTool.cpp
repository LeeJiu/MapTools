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

	return S_OK;
}

void mapTool::release()
{
	// ���� �̹��� ������
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		SAFE_DELETE(_viTile->image);
	}
	// ���� Ŭ����
	_vTile.clear();
}

void mapTool::update()
{
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
}
