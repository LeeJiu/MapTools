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
<<<<<<< HEAD
	setSampleTile();
	setSampleObject();
	setSampleEnemy();

	setTile();

	//��ư�̹�����
	IMAGEMANAGER->addImage("tileB", "image/tileButton.bmp", 104, 44, false, false);
	IMAGEMANAGER->addImage("objectB", "image/objectButton.bmp", 104, 44, false, false);
	IMAGEMANAGER->addImage("enemyB", "image/enemyButton.bmp", 104, 44, false, false);
	IMAGEMANAGER->addImage("exitB", "image/exitButton.bmp", 104, 44, false, false);

	//��Ÿ�� �̹���
=======
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

>>>>>>> refs/remotes/origin/development
	IMAGEMANAGER->addFrameImage("tile", "image/mapTile.bmp", 208, 156, 4, 3, false, false);


	_TileButton = new button;
<<<<<<< HEAD
	_TileButton->init("tileB", 90, 35, PointMake(0, 0), PointMake(0, 0), onTile);
	
	_ObjectButton = new button;
	_ObjectButton->init("objectB", 200, 35, PointMake(0, 0), PointMake(0, 0), onObject);
	
	_EnemyButton = new button;
	_EnemyButton->init("enemyB", 90, 85, PointMake(0, 0), PointMake(0, 0), onEnemy);
	
	_ExitButton = new button;
	_ExitButton->init("exitB", 200, 85, PointMake(0, 0), PointMake(0, 0), goToMenu);
=======
	_TileButton->init("tileB", 150, 35, PointMake(0, 0), PointMake(0, 0), onTile);
	_ObjectButton = new button;
	_ObjectButton->init("objectB", 150, 85, PointMake(0, 0), PointMake(0, 0), onObject);
	_ExitButton = new button;
	_ExitButton->init("exitB", 150, 135, PointMake(0, 0), PointMake(0, 0), goToMenu);
>>>>>>> refs/remotes/origin/development

	selectedImage = IMAGEMANAGER->findImage("tile");

	///////////////////////////////////////////////////////////////////////////////////////////////////

	rcUI = RectMake(0, 0, 300, WINSIZEY);
	rcSelectTile = RectMake(5, 5, 290, 160);

	///////////////////////////////////////////////////////////////////////////////////////////////////


	tileNum = 0;	//����Ÿ�� Ÿ�ϳѹ�
	_pickNum = 0;	//����� Ÿ�ϳѹ�

	return S_OK;
}
///////////////////////////////////////////////////////////���� ��////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////������////////////////////////////////////////////////////////////////////
void mapTool::release()
{
	 //Ÿ�Ϻ��� �̹��� ������
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		if (!(*_viTile)->image);
		SAFE_DELETE((*_viTile)->image);
	}
	 //Ÿ�Ϻ��� Ŭ����
	_vTile.clear();

	//������Ʈ ���� �̹��� ������
	for (_viObj = _vObj.begin(); _viObj != _vObj.end(); ++_viObj)
	{
		if (!(*_viObj)->image)
			SAFE_DELETE((*_viObj)->image);
	}
	//������Ʈ ���� Ŭ����
	_vObj.clear();

	//������ �̹��� ������
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		if (!(*_viEnemy)->image)
			SAFE_DELETE((*_viEnemy)->image);
	}
	//������ Ŭ����
	_vEnemy.clear();

	//�������� �̹��� ������
	for (_viRender = _vRender.begin(); _viRender != _vRender.end(); ++_viRender)
	{
		if (!(*_viRender)->image)
			SAFE_DELETE((*_viRender)->image);
	}
	//�������� Ŭ����
	_vRender.clear();

}
///////////////////////////////////////////////////////////������ ��////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////������Ʈ////////////////////////////////////////////////////////////////////
void mapTool::update()
{
	keyControl();

	_ObjectButton->update();
	_TileButton->update();
<<<<<<< HEAD
	_EnemyButton->update();
	_ExitButton->update();
}	
///////////////////////////////////////////////////////////������Ʈ ��////////////////////////////////////////////////////////////////////

=======
	_ExitButton->update();

}	
>>>>>>> refs/remotes/origin/development

///////////////////////////////////////////////////////////����////////////////////////////////////////////////////////////////////
void mapTool::render()
{
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	char str[128];

	//������ ��Ʈ ���
	for (int i = 0; i < _vTile.size(); i++)
	{
		//Rectangle(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, _vTile[i].rc.right, _vTile[i].rc.bottom);
		
		IsoRender(getMemDC(), _vTile[i]->rc);

		if (_vTile[i]->draw)
		{
<<<<<<< HEAD
			_vTile[i]->image->frameRender(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top, _vTile[i]->rc.right - _vTile[i]->rc.left, _vTile[i]->rc.bottom - _vTile[i]->rc.top, _vTile[i]->image->getFrameX(), _vTile[i]->image->getFrameY());
		}

		sprintf_s(str, "%d, %d", _vTile[i]->x, _vTile[i]->y);
		TextOut(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top, str, strlen(str));
		sprintf_s(str, "%d", _vTile[i]->state);
		TextOut(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top + 15, str, strlen(str));
=======
			_vTile[i].image->frameRender(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, _vTile[i].rc.right - _vTile[i].rc.left, _vTile[i].rc.bottom - _vTile[i].rc.top, _vTile[i].image->getFrameX(), _vTile[i].image->getFrameY());
		}

		sprintf_s(str, "%d", _vTile[i].number);
		TextOut(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, str, strlen(str));
		sprintf_s(str, "%d", _vTile[i].state);
		TextOut(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top + 15, str, strlen(str));
>>>>>>> refs/remotes/origin/development

		sprintf_s(str, "vTile size = %d, vObj size = %d vEnm size =%d _vRender = %d", _vTile.size(), _vObj.size(), _vEnemy.size(), _vRender.size());
		TextOut(getMemDC(), CENTERX - 200, 10, str, strlen(str));
		sprintf_s(str, "pickNum = %d", _pickNum);
		TextOut(getMemDC(), CENTERX - 150, 25, str, strlen(str));
	}

<<<<<<< HEAD
	//������Ʈ ���������
	sort(_vRender.begin(), _vRender.end(), OBJ_Y_RENDER());
	for (int i = 0; i < _vRender.size(); i++)
	{
		if (_vRender[i]->draw)
		{
			_vRender[i]->image->frameRender(getMemDC(), _vRender[i]->rc.left, _vRender[i]->rc.top);
	
			sprintf_s(str, "number = %d", _vRender[i]->number);
			TextOut(getMemDC(), _vRender[i]->rc.left, _vRender[i]->rc.top, str, strlen(str));
		}
	}

	//������ ������Ʈ ���
	//for (int i = 0; i < _vObj.size(); i++)
	//{
	//	//Rectangle(getMemDC(), _vObj[i].rc.left, _vObj[i].rc.top, _vObj[i].rc.right, _vObj[i].rc.bottom);
	//	sort(_vObj.begin(), _vObj.end(), OBJ_Y_RENDER());

	//	if (_vObj[i].draw)
	//	{
	//		_vObj[i].image->render(getMemDC(), _vObj[i].rc.left, _vObj[i].rc.top);
	//		
	//		sprintf_s(str, "number = %d", _vObj[i].number);
	//		TextOut(getMemDC(), _vObj[i].rc.left, _vObj[i].rc.top, str, strlen(str));
	//	}
	//}

	////������ �� ���
	//for (int i = 0; i < _vEnemy.size(); i++)
	//{
	//	//Rectangle(getMemDC(), _vEnemy[i].rc.left, _vEnemy[i].rc.top, _vEnemy[i].rc.right, _vEnemy[i].rc.bottom);
	//	sort(_vEnemy.begin(), _vEnemy.end(), OBJ_Y_RENDER());

	//	if (_vEnemy[i].draw)
	//	{
	//		_vEnemy[i].image->frameRender(getMemDC(), _vEnemy[i].rc.left, _vEnemy[i].rc.top);
	//	}
	//}

=======
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

>>>>>>> refs/remotes/origin/development
	///////////////////////////////////////////////////////////////////////////////

	Rectangle(getMemDC(), rcUI.left, rcUI.top, rcUI.right, rcUI.bottom);
	Rectangle(getMemDC(), rcSelectTile.left, rcSelectTile.top, rcSelectTile.right, rcSelectTile.bottom);

	///////////////////////////////////////////////////////////////////////////////

	// ��ư ����
	_ObjectButton->render();
	_TileButton->render();
<<<<<<< HEAD
	_EnemyButton->render();
	_ExitButton->render();
	
	//Ÿ�ϻ���
	if (_state == SET_TILE)
	{
		for (int i = tileNum * 4; i < tileNum * 4 + 4; i++)
		{
			Rectangle(getMemDC(), _vIsoTile[i]->rc.left, _vIsoTile[i]->rc.top, _vIsoTile[i]->rc.right, _vIsoTile[i]->rc.bottom);
			_vIsoTile[i]->image->frameRender(getMemDC(), _vIsoTile[i]->rc.left, _vIsoTile[i]->rc.top);
	
			sprintf_s(str, "tileNum = %d", i);
			TextOut(getMemDC(), _vIsoTile[i]->rc.left, _vIsoTile[i]->rc.top, str, strlen(str));
		}
	}
=======
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

>>>>>>> refs/remotes/origin/development

	//������Ʈ ����
	if (_state == SET_OBJ)
	{
		for (int i = 0; i < _vIsoObj.size(); i++)
		{
			//Rectangle(getMemDC(), _vIsoObj[i].rc.left, _vIsoObj[i].rc.top, _vIsoObj[i].rc.right, _vIsoObj[i].rc.bottom);
			_vIsoObj[i]->image->frameRender(getMemDC(), _vIsoObj[i]->rc.left, _vIsoObj[i]->rc.top);

			sprintf_s(str, "objNum = %d", _vIsoObj[i]->number);
			TextOut(getMemDC(), _vIsoObj[i]->rc.left, _vIsoObj[i]->rc.top, str, strlen(str));
		}
	}

	//�� ����
	if (_state == SET_ENM)
	{
		for (int i = 0; i < _vIsoEnemy.size(); i++)
		{
			//Rectangle(getMemDC(), _vIsoObj[i].rc.left, _vIsoObj[i].rc.top, _vIsoObj[i].rc.right, _vIsoObj[i].rc.bottom);
			_vIsoEnemy[i]->image->frameRender(getMemDC(), _vIsoEnemy[i]->rc.left, _vIsoEnemy[i]->rc.top);

			sprintf_s(str, "objNum = %d", _vIsoEnemy[i]->number);
			TextOut(getMemDC(), _vIsoEnemy[i]->rc.left, _vIsoEnemy[i]->rc.top, str, strlen(str));
		}
	}
	sprintf_s(str, "x : %d, y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, str, strlen(str));
}
///////////////////////////////////////////////////////////���� ��////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////Ű��Ʈ�� ����////////////////////////////////////////////////////////////////////

void mapTool::keyControl()
{
	//����Ÿ�� �Ⱦ�
<<<<<<< HEAD
	if (_state == SET_TILE)
	{
		for (int i = 0; i < _vIsoTile.size(); i++)//i = 0 1 2 3 
		{
			if (PtInRect(&_vIsoTile[i]->rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_pickNum = _vIsoTile[tileNum * 4 + i]->number;
=======
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
>>>>>>> refs/remotes/origin/development
				}
			}
		}
	}

	//���ÿ�����Ʈ �Ⱦ�
	if (_state == SET_OBJ)
	{
		for (int i = 0; i < _vIsoObj.size(); i++)
		{
			if (PtInRect(&_vIsoObj[i]->rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_pickNum = _vIsoObj[i]->number;
				}
			}
		}
	}
	
	// ���ÿ��ʹ� �Ⱦ�
	if (_state == SET_ENM)
	{
<<<<<<< HEAD
		for (int i = 0; i < _vIsoEnemy.size(); i++)
		{
			if (PtInRect(&_vIsoEnemy[i]->rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_pickNum = _vIsoEnemy[i]->number;
=======
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
>>>>>>> refs/remotes/origin/development
				}
			}
		}
	}

	if (_ptMouse.x > 300)
	{
		// ���콺 Ŭ�� �� ��ġ �̹��� �׸���
		for (int i = 0; i < _vTile.size(); i++)
		{
			if (PtInRect(&_vTile[i]->rc, _ptMouse))
			{
				if ((_ptMouse.y - _vTile[i]->pivot.y) >= -0.5 * (_ptMouse.x - _vTile[i]->pivot.x) - WIDTH / 4 &&
					(_ptMouse.y - _vTile[i]->pivot.y) >= 0.5 * (_ptMouse.x - _vTile[i]->pivot.x) - WIDTH / 4 &&
					(_ptMouse.y - _vTile[i]->pivot.y) <= -0.5 * (_ptMouse.x - _vTile[i]->pivot.x) + WIDTH / 4 &&
					(_ptMouse.y - _vTile[i]->pivot.y) <= 0.5 * (_ptMouse.x - _vTile[i]->pivot.x) + WIDTH / 4)
				{
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
					{
						//Ÿ�ϱ��
						if (_state == SET_TILE)
						{
							_vTile[i]->draw = true;
							_vTile[i]->imageNum = _pickNum;
							_vTile[i]->image->setFrameX(_vIsoTile[_vTile[i]->imageNum]->image->getFrameX());
							_vTile[i]->image->setFrameY(_vIsoTile[_vTile[i]->imageNum]->image->getFrameY());
						}
						
						//������Ʈ���
						if (_state == SET_OBJ)
						{
							if (_vTile[i]->draw == true && _vTile[i]->state == S_NONE)
							{
								TagObject* obj;
								obj = new TagObject;
								obj->image = new image;
								obj->x = _vTile[i]->x;
								obj->y = _vTile[i]->y;
								obj->imageNum = _pickNum;
								switch (obj->imageNum)
								{
								case 0:
									obj->image->init("image/object_block.bmp", 192, 197, true, 0xff00ff);
									obj->state = S_NOMAL;
									break;
								case 1:
									obj->image->init("image/object_block2.bmp", 192, 192, true, 0xff00ff);
									obj->state = S_NOMAL;
									break;
								case 2:
									obj->image->init("image/object_woods.bmp", 192, 125, true, 0xff00ff);
									obj->state = S_NOMAL;
									break;
								case 3:
									obj->image->init("image/object_tree.bmp", 192, 200, true, 0xff00ff);
									obj->state = S_NOMAL;
									break;
								case 4:
									obj->image->init("image/object_zen.bmp", 1536, 62, 8, 1, true, 0xff00ff);
									obj->image->setFrameX(0);
									obj->image->setFrameX(0);
									obj->state = S_ZEN;
									break;
								default:
									break;
								}
								obj->width = WIDTH;
								obj->height = obj->image->getHeight();
								obj->rc = RectMake(_vTile[i]->rc.left, _vTile[i]->rc.bottom - obj->height, obj->width, obj->height);
								obj->number = _vObj.size();
								obj->draw = true;

								_vObj.push_back(obj);
								_vRender.push_back(obj);
								if (obj->state == S_ZEN) _vTile[i]->state = ZEN_POINT;
								else _vTile[i]->state = S_ONOBJ;
							}
						}

						if (_state == SET_ENM)
						{
							if (_vTile[i]->draw == true && _vTile[i]->state == S_NONE)
							{
								TagObject* enemy;
								enemy = new TagObject;
								enemy->image = new image;
								enemy->x = _vTile[i]->x;
								enemy->y = _vTile[i]->y;
								enemy->imageNum = _pickNum;
								switch (enemy->imageNum)
								{
								case 0:
									enemy->image->init("image/priny.bmp", 714, 484, 7, 4, true, 0xff00ff);
									enemy->state = E_NORMAL;
									enemy->image->setFrameX(0);
									enemy->image->setFrameY(0);
									break;
								default:
									break;
								}
								enemy->width = enemy->image->getFrameWidth();
								enemy->height = enemy->image->getFrameHeight();
								enemy->rc = RectMake(_vTile[i]->rc.left + enemy->width / 2 - 10, _vTile[i]->rc.bottom - enemy->height - 20, enemy->width, enemy->height);
								enemy->number = _vEnemy.size();
								enemy->draw = true;
						
								_vEnemy.push_back(enemy);
								_vRender.push_back(enemy);
								_vTile[i]->state = S_ONENM;
							}
						}
					}


					//����
					if ((_ptMouse.y - _vTile[i]->pivot.y) >= -0.5 * (_ptMouse.x - _vTile[i]->pivot.x) - WIDTH / 4 &&
						(_ptMouse.y - _vTile[i]->pivot.y) >= 0.5 * (_ptMouse.x - _vTile[i]->pivot.x) - WIDTH / 4 &&
						(_ptMouse.y - _vTile[i]->pivot.y) <= -0.5 * (_ptMouse.x - _vTile[i]->pivot.x) + WIDTH / 4 &&
						(_ptMouse.y - _vTile[i]->pivot.y) <= 0.5 * (_ptMouse.x - _vTile[i]->pivot.x) + WIDTH / 4)
					{
						if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
						{
							if (_state == SET_TILE)
							{

							}
							if (_state == SET_OBJ)
							{

							}
							if (_state == SET_ENM)
							{

							}
						}
					}
				}
			}
		}
	}
	// �ӽ� �ʽ�ũ�� Ű �Է� ������
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _vTile[0]->rc.top < 0)
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i]->pivot.y += 3;
			_vTile[i]->rc = RectMake(_vTile[i]->rc.left, _vTile[i]->rc.top + 3, _vTile[i]->width, _vTile[i]->height);
		}
		
		for (_viRender = _vRender.begin(); _viRender != _vRender.end(); ++_viRender)
		{
			(*_viRender)->rc = RectMake((*_viRender)->rc.left, (*_viRender)->rc.top +3 , (*_viRender)->width, (*_viRender)->height);
		}
	}

	//�ٿ�Ű
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _vTile[_vTile.size() - 1]->rc.bottom > WINSIZEY - 15)
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i]->pivot.y -= 3;
			_vTile[i]->rc = RectMake(_vTile[i]->rc.left, _vTile[i]->rc.top - 3, _vTile[i]->width, _vTile[i]->height);
		}

	
		for (_viRender = _vRender.begin(); _viRender != _vRender.end(); ++_viRender)
		{
			(*_viRender)->rc = RectMake((*_viRender)->rc.left, (*_viRender)->rc.top - 3, (*_viRender)->width, (*_viRender)->height);
		}
	}

	//����Ű
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i]->pivot.x += 3;
			_vTile[i]->rc = RectMake(_vTile[i]->rc.left + 3, _vTile[i]->rc.top, _vTile[i]->width, _vTile[i]->height);
		}
		
		for (_viRender = _vRender.begin(); _viRender != _vRender.end(); ++_viRender)
		{
			(*_viRender)->rc = RectMake((*_viRender)->rc.left + 3, (*_viRender)->rc.top, (*_viRender)->width, (*_viRender)->height);
		}
	}

	//������Ű
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			_vTile[i]->pivot.x -= 3;
			_vTile[i]->rc = RectMake(_vTile[i]->rc.left - 3, _vTile[i]->rc.top, _vTile[i]->width, _vTile[i]->height);
		}
		
		for (_viRender = _vRender.begin(); _viRender != _vRender.end(); ++_viRender)
		{
			(*_viRender)->rc = RectMake((*_viRender)->rc.left - 3, (*_viRender)->rc.top, (*_viRender)->width, (*_viRender)->height);
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
///////////////////////////////////////////////////////////Ű��Ʈ�� ��///////////////////////////////////////////////



void mapTool::selectMap()
{
	
}


void mapTool::saveMapData()
{
	char temp[128];

	//Ÿ������
	vector<string> vStr;
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
<<<<<<< HEAD
		vStr.push_back("|");							//������
		vStr.push_back(itoa((*_viTile)->number, temp, 10));		//Ÿ�� �ѹ�
		vStr.push_back(itoa((*_viTile)->state, temp, 10));		//Ÿ�� ����
		vStr.push_back(itoa((*_viTile)->x, temp, 10));	//�ҷ��ö� ��ġ������ �������� �ǹ�.
		vStr.push_back(itoa((*_viTile)->y, temp, 10));
		vStr.push_back(itoa((*_viTile)->imageNum, temp, 10));	//Ÿ�� �̹��� (_pickNum)
=======
		vStr.push_back("|");								//������
		vStr.push_back(itoa(_viTile->number, temp, 10));	//Ÿ�� �ѹ�
		vStr.push_back(itoa(_viTile->state, temp, 10));		//Ÿ�� ����
		vStr.push_back(itoa(_viTile->x, temp, 10));			//�ҷ��ö� ��ġ������ �������� �ǹ�.
		vStr.push_back(itoa(_viTile->y, temp, 10));
		vStr.push_back(itoa(_viTile->imageNum, temp, 10));	//Ÿ�� �̹��� (_pickNum)
>>>>>>> refs/remotes/origin/development
	}
	TXTDATA->txtSave("battleMap1.txt", vStr);

	//������Ʈ����
	vector<string> vStr2;
	sort(_vObj.begin(), _vObj.end(), OBJ_NUM());

	for (_viObj = _vObj.begin(); _viObj != _vObj.end(); _viObj++)
	{
		vStr2.push_back("|");
		vStr2.push_back(itoa((*_viObj)->number, temp, 10));
		vStr2.push_back(itoa((*_viObj)->state, temp, 10));
		vStr2.push_back(itoa((*_viObj)->x, temp, 10));
		vStr2.push_back(itoa((*_viObj)->y, temp, 10));
		vStr2.push_back(itoa((*_viObj)->imageNum, temp, 10));
	}
	TXTDATA->txtSave("battleMap1_obj.txt", vStr2);

	//������
	vector<string> vStr3;
	sort(_vEnemy.begin(), _vEnemy.end(), OBJ_NUM());

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		vStr3.push_back("|");
		vStr3.push_back(itoa((*_viEnemy)->number, temp, 10));
		vStr3.push_back(itoa((*_viEnemy)->state, temp, 10));
		vStr3.push_back(itoa((*_viEnemy)->x, temp, 10));
		vStr3.push_back(itoa((*_viEnemy)->y, temp, 10));
		vStr3.push_back(itoa((*_viEnemy)->imageNum, temp, 10));
	}
	TXTDATA->txtSave("battleMap1_enm.txt", vStr3);

}

void mapTool::loadMapData()
{
	resetMapData();
<<<<<<< HEAD
	
	int vObjSize = 0;
	int vEnmSize = 0;

	//Ÿ�Ϸε�
=======

>>>>>>> refs/remotes/origin/development
	DATABASE->loadDatabase("battleMap1.txt");
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		//_viTile->number �� �ڷḦ ã�� �ε���. ������ȣ
<<<<<<< HEAD
		(*_viTile)->number = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->number;
		(*_viTile)->state = (TILESTATE)DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->state;

		(*_viTile)->x = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->x;
		(*_viTile)->y = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->y;
		(*_viTile)->imageNum = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->imageNum;
		if ((*_viTile)->imageNum < 50)
		{
			(*_viTile)->draw = true;
			(*_viTile)->image->setFrameX(_vIsoTile[(*_viTile)->imageNum]->image->getFrameX());
			(*_viTile)->image->setFrameY(_vIsoTile[(*_viTile)->imageNum]->image->getFrameY());
		}

		if ((*_viTile)->state == S_ONOBJ || (*_viTile)->state == ZEN_POINT) vObjSize++;
		if ((*_viTile)->state == S_ONENM || (*_viTile)->state == BOSS) vEnmSize++;
	}

	//������Ʈ �ε�
	DATABASE->loadDatabase("battleMap1_obj.txt");
	for (int i = 0; i < vObjSize; i++)
	{
		char temp[128];

		TagObject* obj;
		obj = new TagObject;
		obj->image = new image;
		obj->x = DATABASE->getElementData(itoa(i, temp, 10))->x;
		obj->y = DATABASE->getElementData(itoa(i, temp, 10))->y;
		obj->imageNum = DATABASE->getElementData(itoa(i, temp, 10))->imageNum;;
		obj->state = (OBJSTATE)DATABASE->getElementData(itoa(i, temp, 10))->state;
		switch (obj->imageNum)
		{
		case 0:
			obj->image->init("image/object_block.bmp", 192, 197, true, 0xff00ff);
			break;
		case 1:
			obj->image->init("image/object_block2.bmp", 192, 192, true, 0xff00ff);
			break;
		case 2:
			obj->image->init("image/object_woods.bmp", 192, 125, true, 0xff00ff);
			break;
		case 3:
			obj->image->init("image/object_tree.bmp", 192, 200, true, 0xff00ff);
			break;
		case 4:
			obj->image->init("image/object_zen.bmp", 1536, 62, 8, 1, true, 0xff00ff);
			obj->image->setFrameX(0);
			obj->image->setFrameX(0);
			break;
		default:
			break;
		}
		obj->width = WIDTH;
		obj->height = obj->image->getHeight();
		for (int j = 0; j < _vTile.size(); j++)
		{
			if (obj->x == _vTile[j]->x && obj->y == _vTile[j]->y)
			{
				obj->rc = RectMake(_vTile[j]->rc.left, _vTile[j]->rc.bottom - obj->height, obj->width, obj->height);
			}
		}
		obj->number = DATABASE->getElementData(itoa(i, temp, 10))->number;
		obj->draw = true;

		_vObj.push_back(obj);
		_vRender.push_back(obj);
	
	}
	
	//���ʹ̷ε�
	DATABASE->loadDatabase("battleMap1_enm.txt");
	for (int i = 0; i < vEnmSize; i++)
	{
		char temp[128];
	
		TagObject* enemy;
		enemy = new TagObject;
		enemy->image = new image;
		enemy->state = (OBJSTATE)DATABASE->getElementData(itoa(i, temp, 10))->state;
		enemy->x = DATABASE->getElementData(itoa(i, temp, 10))->x;
		enemy->y = DATABASE->getElementData(itoa(i, temp, 10))->y;
		enemy->imageNum = DATABASE->getElementData(itoa(i, temp, 10))->imageNum;;
		switch (enemy->imageNum)
		{
		case 0:
			enemy->image->init("image/priny.bmp", 714, 484, 7, 4, true, 0xff00ff);
			enemy->image->setFrameX(0);
			enemy->image->setFrameY(0);
			break;
		default:
			break;
		}
		enemy->width = enemy->image->getFrameWidth();
		enemy->height = enemy->image->getFrameHeight();
		
		for (int j = 0; j < _vTile.size(); j++)
		{
			if (enemy->x == _vTile[j]->x && enemy->y == _vTile[j]->y)
			{
				enemy->rc = RectMake(_vTile[j]->rc.left + enemy->width / 2 - 10, _vTile[j]->rc.bottom - enemy->height - 20, enemy->width, enemy->height);
			}
		}
		enemy->number = DATABASE->getElementData(itoa(i, temp, 10))->number;
		enemy->draw = true;
	
		_vEnemy.push_back(enemy);
		_vRender.push_back(enemy);
=======
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

>>>>>>> refs/remotes/origin/development
	}
}

//����
void mapTool::resetMapData()
{
	release();
	
<<<<<<< HEAD
	setTile();
}

void mapTool::onTile()
{
	_state = SET_TILE;
}

void mapTool::onObject()
{
	_state = SET_OBJ;
}

void mapTool::onEnemy()
{
	_state = SET_ENM;
}

void mapTool::goToMenu()
{
	SCENEMANAGER->changeScene("title");
}

void mapTool::setTile()
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	//��ü ��Ƶ�Ÿ��
	int count = 0;
	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };
	for (int i = 0; i < TILENUM; i++)		// ���� ( �� )
	{
		for (int j = 0; j < TILENUM; j++)	// ���� ( �� )
		{
			// �Ʒ� �ʱ�ȭ�κ� ���ؾȵǸ� �������
			// ���� �˷��ټ��������� �ǹ���
			TagTile* tile;
			tile = new TagTile;
			tile->image = new image;
			tile->image->init("image/isoTile.bmp", 1024, 1408, 4, 11, true, 0xff00ff);
			tile->width = WIDTH;
			tile->height = WIDTH / 2;
			tile->rc = RectMakeCenter(firstPivot.x + j * tile->width / 2 - i * tile->width / 2, firstPivot.y + j * tile->width / 4 + i * tile->width / 4, tile->width, tile->height);
			tile->pivot.x = (tile->rc.left + tile->rc.right) / 2;
			tile->pivot.y = (tile->rc.top + tile->rc.bottom) / 2;
			tile->x = j;
			tile->y = i;
			tile->imageNum = 100;	//�̹��� �ѹ�.
			tile->number = count;
			tile->state = S_NONE;
			tile->draw = false;

			_vTile.push_back(tile);

			count++;
		}
	}

}


void mapTool::setSampleTile()
{
	int count = 0;


	// ����Ÿ��
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			TagTile* tile;
			tile = new TagTile;
			tile->image = new image;
			tile->image->init("image/isoTile.bmp", 1024, 1408, 4, 11, true, 0xff00ff);
			tile->width = WIDTH;
			tile->height = WIDTH / 2;
			tile->rc = RectMake(10, 190 + tile->image->getFrameHeight() * j, tile->image->getFrameWidth(), tile->image->getFrameHeight());
			tile->pivot.x = (tile->rc.left + tile->rc.right) / 2;
			tile->pivot.y = (tile->rc.top + tile->rc.bottom) / 2;
			tile->number = count; // imageNum���� �ҷ��ü��ִ� ����Ÿ�� �ε���
			tile->state = S_NONE;
			tile->draw = true;

			tile->image->setFrameX(tile->number % 4);
			tile->image->setFrameY(tile->number / 4);
			_vIsoTile.push_back(tile);

			count++;
		}
	}
}

void mapTool::setSampleObject()
{
	int count = 0;

	//�縷��
	TagObject* obj;
	obj = new TagObject;
	obj->image = new image;
	obj->image->init("image/object_block.bmp", 192, 197, true, 0xff00ff);
	obj->state = S_NOMAL;
	obj->width = WIDTH;
	obj->height = obj->image->getHeight();
	obj->rc = RectMake(10, 180, obj->width, obj->height);
	obj->number = 0;
	obj->draw = true;
	_vIsoObj.push_back(obj);

	////������
	obj = new TagObject;
	obj->image = new image;
	obj->image->init("image/object_block2.bmp", 192, 194, true, 0xff00ff);
	obj->state = S_NOMAL;
	obj->width = WIDTH;
	obj->height = obj->image->getHeight();
	obj->rc = RectMake(10, 180 + obj->height, obj->width, obj->height);
	obj->number = 1;
	obj->draw = true;
	
	_vIsoObj.push_back(obj);
	
	//��Ǯ
	obj = new TagObject;
	obj->image = new image;
	obj->image->init("image/object_woods.bmp", 192, 125, true, 0xff00ff);
	obj->state = S_NOMAL;
	obj->width = WIDTH;
	obj->height = obj->image->getHeight();
	obj->rc = RectMake(5, WINSIZEY - 160, obj->width, obj->height);
	obj->number = 2;
	obj->draw = true;
	
	_vIsoObj.push_back(obj);
	
	//����
	obj = new TagObject;
	obj->image = new image;
	obj->image->init("image/object_tree.bmp", 192, 200, true, 0xff00ff);
	obj->state = S_NOMAL;
	obj->width = WIDTH;
	obj->height = obj->image->getHeight();
	obj->rc = RectMake(150, WINSIZEY - 240, obj->width, obj->height);
	obj->number = 3;
	obj->draw = true;
	
	_vIsoObj.push_back(obj);
	
	//������Ʈ
	obj = new TagObject;
	obj->image = new image;
	obj->image->init("image/object_zen.bmp", 1536, 62, 8, 1, true, 0xff00ff);
	obj->state = S_ZEN;
	obj->width = WIDTH;
	obj->height = obj->image->getHeight();
	obj->rc = RectMake(150, WINSIZEY - 50, obj->width, obj->height);
	obj->number = 4;
	obj->draw = true;
	
	_vIsoObj.push_back(obj);
}

void mapTool::setSampleEnemy()
{
	int count = 0;

	//������
	TagObject* enemy;
	enemy = new TagObject;
	enemy->image = new image;
	enemy->image->init("image/priny.bmp", 714, 484, 7, 4, true, 0xff00ff);
	enemy->state = E_NORMAL;
	enemy->width = WIDTH;
	enemy->height = enemy->image->getFrameHeight();
	enemy->rc = RectMake(10, 190, enemy->width, enemy->height);
	enemy->number = 0;
	enemy->draw = true;

	enemy->image->setFrameX(0);
	enemy->image->setFrameY(0);
	_vIsoEnemy.push_back(enemy);
=======
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
>>>>>>> refs/remotes/origin/development
}