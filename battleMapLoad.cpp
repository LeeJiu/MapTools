#include "stdafx.h"
#include "battleMapLoad.h"


battleMapLoad::battleMapLoad()
{
}


battleMapLoad::~battleMapLoad()
{
}

HRESULT battleMapLoad::init()
{
	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };

	int count = 0;
	for (int j = 0; j < TILENUM; j++)      // 세로 ( 열 )
	{
		for (int i = 0; i < TILENUM; i++)   // 가로 ( 행 )
		{
			// 아래 초기화부분 이해안되면 물어보세용
			// 물론 알려줄수있을지는 의문임
			//TagTile tile;
			//ZeroMemory(&tile, sizeof(TagTile));
			_tile[i][j].image = new image;
			_tile[i][j].image->init("image/isoTile.bmp", 1024, 1408, 4, 11, true, 0xff00ff);
			_tile[i][j].width = WIDTH;
			_tile[i][j].height = WIDTH / 2;
			_tile[i][j].rc = RectMakeCenter(firstPivot.x + i * _tile[i][j].width / 2 - j * _tile[i][j].width / 2, firstPivot.y + i * _tile[i][j].width / 4 + j * _tile[i][j].width / 4, _tile[i][j].width, _tile[i][j].height);
			_tile[i][j].pivotX = (_tile[i][j].rc.left + _tile[i][j].rc.right) / 2;
			_tile[i][j].pivotY = (_tile[i][j].rc.top + _tile[i][j].rc.bottom) / 2;
			_tile[i][j].x = i;
			_tile[i][j].y = j;
			_tile[i][j].imageNum = 100;   //이미지 넘버.
			_tile[i][j].number = count;
			_tile[i][j].state = S_NONE;
			_tile[i][j].draw = false;
				
			_vTile.push_back(_tile[i][j]);

			count++;
		}
	}

	count = 0;
	// 샘플타일
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
			tile.number = count; // imageNum으로 불러올수있는 샘플타일 인덱스
			tile.state = S_NONE;
			tile.draw = true;

			tile.image->setFrameX(tile.number % 4);
			tile.image->setFrameY(tile.number / 4);
			_vIsoTile.push_back(tile);

			count++;
		}
	}

	loadMapData();

	return S_OK;
}

void battleMapLoad::release()
{
}

void battleMapLoad::update()
{
}

void battleMapLoad::render()
{
	//int _vTileSize = _vTile.size();
	//for (int i = 0; i < _vTileSize; i++)
	//{
	//	_vTile[i].image->frameRender(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, _vTile[i].image->getFrameX(), _vTile[i].image->getFrameY());
	//}
	//
	//sort(_vRender.begin(), _vRender.end(), OBJ_Y_RENDER());
	//int _vRenderSize = _vRender.size();
	//for (int i = 0; i < _vRenderSize; i++)
	//{
	//	_vRender[i].image->frameRender(getMemDC(), _vRender[i].rc.left, _vRender[i].rc.top, _vRender[i].image->getFrameX(), _vRender[i].image->getFrameY());
	//}

}
void battleMapLoad::loadMapData()
{

	int vObjSize = 0;
	int vEnmSize = 0;

	//타일로드
	DATABASE->loadDatabase("battleMap1.txt");
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		//_viTile->number 는 자료를 찾는 인덱스. 고유번호
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

		if (_viTile->state == S_ONOBJ) vObjSize++;
		if (_viTile->state == S_ONENM) vEnmSize++;
	}

	//오브젝트 로드
	DATABASE->loadDatabase("battleMap1_obj.txt");
	for (int i = 0; i < vObjSize; i++)
	{
		char temp[128];

		TagObject obj;
		ZeroMemory(&obj, sizeof(TagObject));
		obj.image = new image;
		obj.x = DATABASE->getElementData(itoa(i, temp, 10))->x;
		obj.y = DATABASE->getElementData(itoa(i, temp, 10))->y;
		obj.imageNum = DATABASE->getElementData(itoa(i, temp, 10))->imageNum;;
		obj.state = (OBJSTATE)DATABASE->getElementData(itoa(i, temp, 10))->state;
		switch (obj.imageNum)
		{
		case 0:
			obj.image->init("image/object_block.bmp", 192, 197, true, 0xff00ff);
			obj.state = S_NOMAL;
			break;
		case 1:
			obj.image->init("image/object_block2.bmp", 192, 192, true, 0xff00ff);
			obj.state = S_NOMAL;
			break;
		case 2:
			obj.image->init("image/object_woods.bmp", 192, 125, true, 0xff00ff);
			obj.state = S_NOMAL;
			break;
		case 3:
			obj.image->init("image/object_tree.bmp", 192, 200, true, 0xff00ff);
			obj.state = S_NOMAL;
			break;
		case 4:
			obj.image->init("image/object_zen.bmp", 1536, 62, 8, 1, true, 0xff00ff);
			obj.image->setFrameX(0);
			obj.image->setFrameX(0);
			obj.state = S_ZEN;
			break;
		default:
			break;
		}
		obj.width = WIDTH;
		obj.height = obj.image->getHeight();
		for (unsigned int j = 0; j < /*_vTile.size()*/ 100; j++)
		{
			if (obj.x == _vTile[j].x && obj.y == _vTile[j].y)
			{
				obj.rc = RectMake(_vTile[j].rc.left, _vTile[j].rc.bottom - obj.height, obj.width, obj.height);
			}
		}
		obj.number = DATABASE->getElementData(itoa(i, temp, 10))->number;
		obj.draw = true;

		_vObj.push_back(obj);
		_vRender.push_back(obj);
	}

	//에너미로드
	DATABASE->loadDatabase("battleMap1_enm.txt");
	for (int i = 0; i < vEnmSize; i++)
	{
		char temp[128];

		TagObject enemy;
		ZeroMemory(&enemy, sizeof(TagObject));
		enemy.image = new image;
		enemy.state = (OBJSTATE)DATABASE->getElementData(itoa(i, temp, 10))->state;
		enemy.x = DATABASE->getElementData(itoa(i, temp, 10))->x;
		enemy.y = DATABASE->getElementData(itoa(i, temp, 10))->y;
		enemy.imageNum = DATABASE->getElementData(itoa(i, temp, 10))->imageNum;;
		switch (enemy.imageNum)
		{
		case 0:
			enemy.image->init("image/priny.bmp", 714, 484, 7, 4, true, 0xff00ff);
			enemy.image->setFrameX(0);
			enemy.image->setFrameY(0);
			break;
		default:
			break;
		}
		enemy.width = enemy.image->getFrameWidth();
		enemy.height = enemy.image->getFrameHeight();

		for (unsigned int j = 0; j < _vTile.size(); j++)
		{
			if (enemy.x == _vTile[j].x && enemy.y == _vTile[j].y)
			{
				enemy.rc = RectMake(_vTile[j].rc.left + enemy.width / 2 - 10, _vTile[j].rc.bottom - enemy.height - 20, enemy.width, enemy.height);
			}
		}
		enemy.number = DATABASE->getElementData(itoa(i, temp, 10))->number;
		enemy.draw = true;

		_vEnemy.push_back(enemy);
		_vRender.push_back(enemy);
	}

}
