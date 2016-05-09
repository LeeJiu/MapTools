#include "stdafx.h"
#include "mapTool.h"


//저장-> 스테이트, 이미지, 넘버, 피벗, 맵네임

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

	// 샘플타일
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
			tile.number = count; // imageNum으로 불러올수있는 샘플타일 인덱스
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
	for (int i = 0; i < 15; i++)		// 세로 ( 열 )
	{
		for (int j = 0; j < 15; j++)	// 가로 ( 행 )
		{	
			// 아래 초기화부분 이해안되면 물어보세용
			// 물론 알려줄수있을지는 의문임
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
			tile.imageNum = 100;	//이미지 넘버.
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


	tileNum = 0;	//샘플타일 타일넘버
	_pickNum = 0;	//찍어줄 타일넘버


	return S_OK;
}

void mapTool::release()
{
	 //벡터 이미지 지우자
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		if (!_viTile->image)
		SAFE_DELETE(_viTile->image);
	}
	 //벡터 클리어
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

	//각각의 렉트 출력
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

	// 버튼 랜더
	//_button->render();

	// 선택될 타일이미지 출력
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
	//샘플타일 픽업
	if (PtInRect(&_vIsoTile[tileNum].rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_pickNum = tileNum;
		}
	}

	// 마우스 클릭 된 위치 이미지 그리자

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

	// 임시 맵스크롤 키 입력 만들자
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

	//각각의 렉트 출력
	for (int i = 0; i < _vTile.size(); i++)
		//맵 데이터를 세이브
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		saveMapData();
	}
	//맵 데이터를 로드
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		loadMapData();
	}
	//맵 데이터를 리셋
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
		vStr.push_back("|");							//구분자
		vStr.push_back(itoa(_viTile->number, temp, 10));		//타일 넘버
		vStr.push_back(itoa(_viTile->state, temp, 10));		//타일 상태
		vStr.push_back(itoa(_viTile->rc.left, temp, 10));	//불러올때 위치정보를 갖고있을 피벗.
		vStr.push_back(itoa(_viTile->rc.top, temp, 10));
		vStr.push_back(itoa(_viTile->imageNum, temp, 10));	//타일 이미지 (_pickNum)
	}
	TXTDATA->txtSave("battleMap1.txt", vStr);
}

void mapTool::loadMapData()
{
	DATABASE->loadDatabase("battleMap1.txt");
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		//_viTile->number 는 자료를 찾는 인덱스. 고유번호
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

//리셋
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

