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
	//IMAGEMANAGER->addFrameImage("isoTile", "image/isoTile.bmp", 1152, 576, 9, 9, true, 0xff00ff);
	//IMAGEMANAGER->addFrameImage("object_block", "image/isoTile.bmp", 1152, 576, 9, 9, true, 0xff00ff);

	int count = 0;

	_drawX = _drawY = 0;

	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };

	// ����Ÿ��
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			TagTile tile;
			ZeroMemory(&tile, sizeof(TagTile));
			tile.image = new image;
			tile.image->init("image/isoTile.bmp", 1024, 1408, 4, 11, true, 0xff00ff);
			tile.width = WIDTH;
			tile.height = WIDTH / 2;
			tile.rc = RectMake(10, 190 + tile.image->getFrameHeight() * j, tile.image->getFrameWidth(), tile.image->getFrameHeight());
			tile.pivotX = (tile.rc.left + tile.rc.right) / 2;
			tile.pivotY = (tile.rc.top + tile.rc.bottom) / 2;
			tile.number = count; // imageNum���� �ҷ��ü��ִ� ����Ÿ�� �ε���
			tile.state = S_NONE;
			tile.draw = true;

			tile.image->setFrameX(tile.number % 4);
			tile.image->setFrameY(tile.number / 4);
			_vIsoTile.push_back(tile);

			count++;
		}
	}

	//���� ������Ʈ
	TagObject obj;
	ZeroMemory(&obj, sizeof(TagObject));
	obj.image = new image;
	obj.image->init("image/object_block.bmp", 192, 197, true, 0xff00ff);
	obj.width = WIDTH;
	obj.height = obj.image->getHeight();
	obj.rc = RectMake(10, 190, obj.width, obj.height);
	obj.number = 0;
	obj.draw = true;
	_vIsoObj.push_back(obj);

	ZeroMemory(&obj, sizeof(TagObject));
	obj.image = new image;
	obj.image->init("image/object_block2.bmp", 192, 194, true, 0xff00ff);
	obj.width = WIDTH;
	obj.height = obj.image->getHeight();
	obj.rc = RectMake(10, 190 + obj.height, obj.width, obj.height);
	obj.number = 1;
	obj.draw = true;

	_vIsoObj.push_back(obj);

	//��ü ��Ƶ�Ÿ��
	count = 0;
	for (int i = 0; i < TILENUM; i++)		// ���� ( �� )
	{
		for (int j = 0; j < TILENUM; j++)	// ���� ( �� )
		{	
			TagTile tile;
			ZeroMemory(&tile, sizeof(TagTile));
			tile.image = new image;
			tile.image->init("image/isoTile.bmp", 1024, 1408, 4, 11, true, 0xff00ff);
			tile.width = WIDTH;
			tile.height = WIDTH / 2;
			tile.rc = RectMakeCenter(firstPivot.x + j * tile.width / 2 - i * tile.width / 2, firstPivot.y + j * tile.width / 4 + i * tile.width / 4, tile.width, tile.height);
			tile.pivotX = (tile.rc.left + tile.rc.right) / 2;
			tile.pivotY = (tile.rc.top + tile.rc.bottom) / 2;
			tile.x = j;
			tile.y = i;
			tile.imageNum = 100;	//�̹��� �ѹ�.
			tile.number = count;	
			tile.state = S_NONE;
			tile.draw = false;

			_vTile.push_back(tile);

			count++;
		}
	}

	selectedNum = 0;
	//IMAGEMANAGER->addFrameImage("button", "image/button.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));

	//addImage("tileButton", "image/tileButton.bmp", 104, 44, 0, 0, false, false);
	IMAGEMANAGER->addImage("tileB", "image/tileButton.bmp", 104, 44, false, false);
	IMAGEMANAGER->addImage("objectB", "image/objectButton.bmp", 104, 44, false, false);
	IMAGEMANAGER->addImage("exitB", "image/exitButton.bmp", 104, 44, false, false);

	IMAGEMANAGER->addFrameImage("tile", "image/mapTile.bmp", 208, 156, 4, 3, false, false);


	_TileButton = new button;
	_TileButton->init("tileB", 150, 35, PointMake(0, 0), PointMake(0, 0), onTile);
	_ObjectButton = new button;
	_ObjectButton->init("objectB", 150, 85, PointMake(0, 0), PointMake(0, 0), onObject);
	_ExitButton = new button;
	_ExitButton->init("exitB", 150, 135, PointMake(0, 0), PointMake(0, 0), goToMenu);

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

	_ObjectButton->update();
	_TileButton->update();
	_ExitButton->update();

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
		sprintf_s(str, "%d", _vTile[i].state);
		TextOut(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top + 15, str, strlen(str));

		sprintf_s(str, "vTile size = %d, vIsoT size = %d", _vTile.size(), _vIsoTile.size());
		TextOut(getMemDC(), CENTERX - 150, 10, str, strlen(str));
		sprintf_s(str, "pickNum = %d", _pickNum);
		TextOut(getMemDC(), CENTERX - 150, 25, str, strlen(str));
	}

	//������ ������Ʈ ���
	for (int i = 0; i < _vObj.size(); i++)
	{
		//Rectangle(getMemDC(), _vObj[i].rc.left, _vObj[i].rc.top, _vObj[i].rc.right, _vObj[i].rc.bottom);
		sort(_vObj.begin(), _vObj.end(), OBJ_Y_RENDER());

		if (_vObj[i].draw)
		{
			_vObj[i].image->render(getMemDC(), _vObj[i].rc.left, _vObj[i].rc.top);
		}
	}

	///////////////////////////////////////////////////////////////////////////////

	Rectangle(getMemDC(), rcUI.left, rcUI.top, rcUI.right, rcUI.bottom);
	Rectangle(getMemDC(), rcSelectTile.left, rcSelectTile.top, rcSelectTile.right, rcSelectTile.bottom);

	///////////////////////////////////////////////////////////////////////////////

	// ��ư ����
	_ObjectButton->render();
	_TileButton->render();
	_ExitButton->render();

	// ���õ� Ÿ���̹��� ���
	//IMAGEMANAGER->findImage("tile")->frameRender(getMemDC(), WINSIZEX - 200, 100, IMAGEMANAGER->findImage("tile")->getFrameX(), IMAGEMANAGER->findImage("tile")->getFrameY());

	//Ÿ�ϻ���
	if (_isTile)
	{
		for (int i = tileNum * 4; i < tileNum * 4 + 4; i++)
		{
			Rectangle(getMemDC(), _vIsoTile[i].rc.left, _vIsoTile[i].rc.top, _vIsoTile[i].rc.right, _vIsoTile[i].rc.bottom);
			_vIsoTile[i].image->frameRender(getMemDC(), _vIsoTile[i].rc.left, _vIsoTile[i].rc.top);
	
			sprintf_s(str, "tileNum = %d", i);
			TextOut(getMemDC(), _vIsoTile[i].rc.left, _vIsoTile[i].rc.top, str, strlen(str));
		}
	}

	//������Ʈ ����
	if (!_isTile)
	{
		for (int i = 0; i < _vIsoObj.size(); i++)
		{
			//Rectangle(getMemDC(), _vIsoObj[i].rc.left, _vIsoObj[i].rc.top, _vIsoObj[i].rc.right, _vIsoObj[i].rc.bottom);
			_vIsoObj[i].image->frameRender(getMemDC(), _vIsoObj[i].rc.left, _vIsoObj[i].rc.top);

			sprintf_s(str, "objNum = %d", _vIsoObj[i].number);
			TextOut(getMemDC(), _vIsoObj[i].rc.left, _vIsoObj[i].rc.top, str, strlen(str));
		}
	}


	sprintf_s(str, "x : %d, y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, str, strlen(str));
}


void mapTool::keyControl()
{
	//����Ÿ�� �Ⱦ�
	if (_isTile)
	{
		for (int i = 0; i < _vIsoTile.size(); i++)//i = 0 1 2 3 
		{
			if (PtInRect(&_vIsoTile[i].rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_pickNum = _vIsoTile[tileNum * 4 + i].number;
				}
			}
		}
	}

	//���ÿ�����Ʈ �Ⱦ�
	if (!_isTile)
	{
		for (int i = 0; i < _vIsoObj.size(); i++)
		{
			if (PtInRect(&_vIsoObj[i].rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_pickNum = _vIsoObj[i].number;
				}
			}
		}
	}

	// ���콺 Ŭ�� �� ��ġ �̹��� �׸���

	for (int i = 0; i < _vTile.size(); i++)
	{
		if (PtInRect(&_vTile[i].rc, _ptMouse))
		{
			if ((_ptMouse.y - _vTile[i].pivotY) >= -0.5 * (_ptMouse.x - _vTile[i].pivotX) - WIDTH / 4 &&
				(_ptMouse.y - _vTile[i].pivotY) >=  0.5 * (_ptMouse.x - _vTile[i].pivotX) - WIDTH / 4 &&
				(_ptMouse.y - _vTile[i].pivotY) <= -0.5 * (_ptMouse.x - _vTile[i].pivotX) + WIDTH / 4 &&
				(_ptMouse.y - _vTile[i].pivotY) <=  0.5 * (_ptMouse.x - _vTile[i].pivotX) + WIDTH / 4)
			{
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
				{
					if (_isTile)
					{
						_vTile[i].draw = true;
						_vTile[i].imageNum = _pickNum;
						_vTile[i].image->setFrameX(_vIsoTile[_vTile[i].imageNum].image->getFrameX());
						_vTile[i].image->setFrameY(_vIsoTile[_vTile[i].imageNum].image->getFrameY());
					}
					if (!_isTile)
					{
						if (_vTile[i].draw == true)
						{
							TagObject obj;
							ZeroMemory(&obj, sizeof(TagObject));
							obj.image = new image;
							obj.x = _vTile[i].x;
							obj.y = _vTile[i].y;
							obj.imageNum = _pickNum;
							switch (obj.imageNum)
							{
							case 0:
								obj.image->init("image/object_block.bmp", 192, 197, true, 0xff00ff);
								break;
							case 1:
								obj.image->init("image/object_block2.bmp", 192, 192, true, 0xff00ff);
								break;
							default:
								break;
							}
							obj.width = WIDTH;
							obj.height = obj.image->getHeight();
							obj.rc = RectMake(_vTile[i].rc.left, _vTile[i].rc.bottom - obj.height, obj.width, obj.height);
							obj.number = _vObj.size() + 1;
							obj.draw = true;

							_vObj.push_back(obj);
							_vTile[i].state = S_ONOBJ;
						}
					}

					if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
					{
						_vTile[i].draw = false;
						_vTile[i].imageNum = 100;
					}
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
		if (tileNum < 10) tileNum++;
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
		vStr.push_back("|");								//������
		vStr.push_back(itoa(_viTile->number, temp, 10));	//Ÿ�� �ѹ�
		vStr.push_back(itoa(_viTile->state, temp, 10));		//Ÿ�� ����
		vStr.push_back(itoa(_viTile->x, temp, 10));			//�ҷ��ö� ��ġ������ �������� �ǹ�.
		vStr.push_back(itoa(_viTile->y, temp, 10));
		vStr.push_back(itoa(_viTile->imageNum, temp, 10));	//Ÿ�� �̹��� (_pickNum)
	}
	TXTDATA->txtSave("battleMap1.txt", vStr);
}

void mapTool::loadMapData()
{
	resetMapData();

	DATABASE->loadDatabase("battleMap1.txt");
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		//_viTile->number �� �ڷḦ ã�� �ε���. ������ȣ
		_viTile->number = DATABASE->getElementData(itoa(_viTile->number, temp, 10))->number;
		_viTile->state = (TILESTATE)DATABASE->getElementData(itoa(_viTile->number, temp, 10))->state;

		_viTile->x = DATABASE->getElementData(itoa(_viTile->number, temp, 10))->x;
		_viTile->y = DATABASE->getElementData(itoa(_viTile->number, temp, 10))->y;
		_viTile->imageNum = DATABASE->getElementData(itoa(_viTile->number, temp, 10))->imageNum;
		if (_viTile->imageNum < 50)
		{
			_viTile->draw = true;
			_viTile->image->setFrameX(_vIsoTile[_viTile->imageNum].image->getFrameX());
			_viTile->image->setFrameY(_vIsoTile[_viTile->imageNum].image->getFrameY());
		}

	}
}

//����
void mapTool::resetMapData()
{
	release();
	
	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };

	int count = 0;
	for (int i = 0; i < TILENUM; i++)		// ���� ( �� )
	{
		for (int j = 0; j < TILENUM; j++)	// ���� ( �� )
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
			tile.pivotX = (tile.rc.left + tile.rc.right) / 2;
			tile.pivotY = (tile.rc.top + tile.rc.bottom) / 2;
			tile.x = j;
			tile.y = i;
			tile.imageNum = 100;	//�̹��� �ѹ�.
			tile.number = count;
			tile.state = S_NONE;
			tile.draw = false;

			_vTile.push_back(tile);

			count++;
		}
	}
}

//void mapTool::nextTile()
//{
//	selectedNum++;
//	
//	if (selectedNum >= selectedImage->getMaxFrameX() * selectedImage->getMaxFrameY()) selectedNum = 0;
//	
//	selectedImage->setFrameX(selectedNum % selectedImage->getMaxFrameX());
//	selectedImage->setFrameY(selectedNum / selectedImage->getMaxFrameY());
//}

void mapTool::onTile()
{
	if (!_isTile) _isTile = !_isTile;
}

void mapTool::onObject()
{
	if (_isTile) _isTile = !_isTile;
}

void mapTool::goToMenu()
{
	SCENEMANAGER->changeScene("title");
}