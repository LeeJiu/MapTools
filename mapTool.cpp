#include "stdafx.h"
#include "mapTool.h"


//����-> ������Ʈ, �̹���, �ѹ�, �ǹ�, �ʳ���

mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	//1152 x 576 / 9 x 9
	IMAGEMANAGER->addFrameImage("isoTile", "image/isoTile.bmp", 1152, 576, 9, 9, true, 0xff00ff);

	int count = 0;

	_drawX = _drawY = 0;

	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };

	// ����Ÿ��
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			TagTile tile;
			ZeroMemory(&tile, sizeof(TagTile));
			tile.image = new image;
			tile.image->init("image/isoTile.bmp", 1024, 1408, 4, 11, true, 0xff00ff);
			tile.width = WIDTH;
			tile.height = WIDTH / 2;
			tile.rc = RectMake(10, 10, tile.image->getFrameWidth(), tile.image->getFrameHeight());
			tile.pivot.x = (tile.rc.left + tile.rc.right) / 2;
			tile.pivot.y = (tile.rc.top + tile.rc.bottom) / 2;
			tile.number = count; // imageNum���� �ҷ��ü��ִ� ����Ÿ�� �ε���
			tile.state = S_NONE;
			tile.mapName = M_NONE;
			tile.draw = true;

			tile.image->setFrameX(tile.number % 4);
			tile.image->setFrameY(tile.number / 11);
			_vIsoTile.push_back(tile);

			count++;
		}
	}

	count = 0;
	for (int i = 0; i < 15; i++)		// ���� ( �� )
	{
		for (int j = 0; j < 15; j++)	// ���� ( �� )
		{	
			// �Ʒ� �ʱ�ȭ�κ� ���ؾȵǸ� �������
			// ���� �˷��ټ��������� �ǹ���
			TagTile tile;
			ZeroMemory(&tile, sizeof(TagTile));
			tile.image = new image;
			tile.image->init("image/isoTile.bmp", 1024, 1408, 4, 11, true, 0xff00ff);
			tile.width = WIDTH;
			tile.height = WIDTH / 2;
			tile.rc = RectMakeCenter(firstPivot.x + j * tile.width / 2 - i * tile.width / 2, firstPivot.y + j * tile.width / 4 + i * tile.width / 4, tile.width, tile.height);
			tile.pivot.x = (tile.rc.left + tile.rc.right) / 2;
			tile.pivot.y = (tile.rc.top + tile.rc.bottom) / 2;
			tile.x = j;
			tile.y = i;
			tile.imageNum = 100;	//�̹��� �ѹ�.
			tile.number = count;	
			tile.state = S_NONE;
			tile.mapName = M_NONE;
			tile.draw = false;

			_vTile.push_back(tile);

			count++;
		}
	}

	selectedNum = 0;
	//IMAGEMANAGER->addFrameImage("button", "image/button.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tile", "image/mapTile.bmp", 208, 156, 4, 3, false, false);

	//_button = new button;
	//_button->init("button", WINSIZEX - 100, 200, PointMake(1, 0), PointMake(1, 0), nextTile);

	selectedImage = IMAGEMANAGER->findImage("tile");

	///////////////////////////////////////////////////////////////////////////////////////////////////

	rcUI = RectMake(0, 0, 300, WINSIZEY);
	rcSelectTile = RectMake(5, 5, 290, 160);

	///////////////////////////////////////////////////////////////////////////////////////////////////


	tileNum = 0;	//����Ÿ�� Ÿ�ϳѹ�
	_pickNum = 0;	//����� Ÿ�ϳѹ�


	return S_OK;
}

void mapTool::release()
{
	 //���� �̹��� ������
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		if (!_viTile->image)
		SAFE_DELETE(_viTile->image);
	}
	 //���� Ŭ����
	_vTile.clear();
}

void mapTool::update()
{
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
			_vTile[i].image->frameRender(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, _vTile[i].rc.right - _vTile[i].rc.left, _vTile[i].rc.bottom - _vTile[i].rc.top, _vTile[i].image->getFrameX(), _vTile[i].image->getFrameY());
		}

		sprintf_s(str, "%d", _vTile[i].number);
		TextOut(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, str, strlen(str));
		sprintf_s(str, "%d", _vTile[i].imageNum);
		TextOut(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top + 15, str, strlen(str));

		sprintf_s(str, "vTile size = %d, vIsoT size = %d", _vTile.size(), _vIsoTile.size());
		TextOut(getMemDC(), CENTERX - 150, 10, str, strlen(str));
		sprintf_s(str, "pickNum = %d", _pickNum);
		TextOut(getMemDC(), CENTERX - 150, 25, str, strlen(str));
	}

	///////////////////////////////////////////////////////////////////////////////

	Rectangle(getMemDC(), rcUI.left, rcUI.top, rcUI.right, rcUI.bottom);
	Rectangle(getMemDC(), rcSelectTile.left, rcSelectTile.top, rcSelectTile.right, rcSelectTile.bottom);

	///////////////////////////////////////////////////////////////////////////////

	// ��ư ����
	//_button->render();

	// ���õ� Ÿ���̹��� ���
	//IMAGEMANAGER->findImage("tile")->frameRender(getMemDC(), WINSIZEX - 200, 100, IMAGEMANAGER->findImage("tile")->getFrameX(), IMAGEMANAGER->findImage("tile")->getFrameY());
	
	Rectangle(getMemDC(), _vIsoTile[tileNum].rc.left, _vIsoTile[tileNum].rc.top, _vIsoTile[tileNum].rc.right, _vIsoTile[tileNum].rc.bottom);
	_vIsoTile[tileNum].image->frameRender(getMemDC(), _vIsoTile[tileNum].rc.left, _vIsoTile[tileNum].rc.top);
	sprintf_s(str, "tileNum = %d", tileNum);
	TextOut(getMemDC(), _vIsoTile[tileNum].rc.left, _vIsoTile[tileNum].rc.top, str, strlen(str));

	sprintf_s(str, "x : %d, y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, str, strlen(str));
}


void mapTool::keyControl()
{
	//����Ÿ�� �Ⱦ�
	if (PtInRect(&_vIsoTile[tileNum].rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_pickNum = tileNum;
		}
	}

	// ���콺 Ŭ�� �� ��ġ �̹��� �׸���

	for (int i = 0; i < _vTile.size(); i++)
	{
		if (PtInRect(&_vTile[i].rc, _ptMouse))
		{
			if ((_ptMouse.y - _vTile[i].pivot.y) >= -0.5 * (_ptMouse.x - _vTile[i].pivot.x) - WIDTH / 4 &&
				(_ptMouse.y - _vTile[i].pivot.y) >= 0.5 * (_ptMouse.x - _vTile[i].pivot.x) - WIDTH / 4 &&
				(_ptMouse.y - _vTile[i].pivot.y) <= -0.5 * (_ptMouse.x - _vTile[i].pivot.x) + WIDTH / 4 &&
				(_ptMouse.y - _vTile[i].pivot.y) <= 0.5 * (_ptMouse.x - _vTile[i].pivot.x) + WIDTH / 4)
			{
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
				{
					_vTile[i].draw = true;
					//_vTile[i].image = _vIsoTile[_pickNum].image;
					_vTile[i].imageNum = _pickNum;
				}
			}
		}
	}

	// �ӽ� �ʽ�ũ�� Ű �Է� ������
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _vTile[0].rc.top < 0)
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i].rc = RectMake(_vTile[i].rc.left, _vTile[i].rc.top + 3, _vTile[i].width, _vTile[i].height);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _vTile[_vTile.size() - 1].rc.bottom > WINSIZEY - 15)
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i].rc = RectMake(_vTile[i].rc.left, _vTile[i].rc.top - 3, _vTile[i].width, _vTile[i].height);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i].rc = RectMake(_vTile[i].rc.left + 3, _vTile[i].rc.top, _vTile[i].width, _vTile[i].height);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i].rc = RectMake(_vTile[i].rc.left - 3, _vTile[i].rc.top, _vTile[i].width, _vTile[i].height);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if(tileNum > 0) tileNum--;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (tileNum < 44) tileNum++;
	}

	//������ ��Ʈ ���
	for (int i = 0; i < _vTile.size(); i++)
		//�� �����͸� ���̺�
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		saveMapData();
	}
	//�� �����͸� �ε�
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		loadMapData();
	}
	//�� �����͸� ����
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		resetMapData();
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
		vStr.push_back(itoa(_viTile->number, temp, 10));		//Ÿ�� �ѹ�
		vStr.push_back(itoa(_viTile->state, temp, 10));		//Ÿ�� ����
		vStr.push_back(itoa(_viTile->rc.left, temp, 10));	//�ҷ��ö� ��ġ������ �������� �ǹ�.
		vStr.push_back(itoa(_viTile->rc.top, temp, 10));
		vStr.push_back(itoa(_viTile->imageNum, temp, 10));	//Ÿ�� �̹��� (_pickNum)
	}
	TXTDATA->txtSave("battleMap1.txt", vStr);
}

void mapTool::loadMapData()
{
	DATABASE->loadDatabase("battleMap1.txt");
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		//_viTile->number �� �ڷḦ ã�� �ε���. ������ȣ
		_viTile->number = DATABASE->getElementData(itoa(_viTile->number, temp, 10))->number;
		_viTile->state = (TILESTATE)DATABASE->getElementData(itoa(_viTile->number, temp, 10))->state;
		_viTile->rc = RectMake(DATABASE->getElementData(itoa(_viTile->number, temp, 10))->drawX,
			DATABASE->getElementData(itoa(_viTile->number, temp, 10))->drawY,
			WIDTH,
			WIDTH / 2);
		_viTile->imageNum = DATABASE->getElementData(itoa(_viTile->number, temp, 10))->imageNum;
		if (_viTile->imageNum < 50)
		{
			_viTile->draw = true;
			//_viTile->image = _vIsoTile[_viTile->imageNum].image;
		}

	}
}

//����
void mapTool::resetMapData()
{
	release();
	init();
}

void mapTool::nextTile()
{
	selectedNum++;
	
	if (selectedNum >= selectedImage->getMaxFrameX() * selectedImage->getMaxFrameY()) selectedNum = 0;
	
	selectedImage->setFrameX(selectedNum % selectedImage->getMaxFrameX());
	selectedImage->setFrameY(selectedNum / selectedImage->getMaxFrameY());
}

