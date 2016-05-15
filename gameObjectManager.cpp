#include "stdafx.h"
#include "gameObjectManager.h"


gameObjectManager::gameObjectManager()
{
}


gameObjectManager::~gameObjectManager()
{
}

HRESULT gameObjectManager::init()
{
	_turnCount = 0;

	return S_OK;
}

void gameObjectManager::release()
{
}

void gameObjectManager::update()
{
}

void gameObjectManager::render()
{
}

void gameObjectManager::setActionAttack()
{

}

void gameObjectManager::setChangeTurn()
{
	if (_turnType == TURN_ENEMY) _turnType = TURN_PLAYER;
	if (_turnType == TURN_PLAYER) _turnType = TURN_ENEMY;
	_turnCount++;
	int _vTileSize = _vTile.size();
	for (int i = 0; i < _vTileSize; i++)
	{
		_vTile[i]->image->frameRender(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top, _vTile[i]->image->getFrameX(), _vTile[i]->image->getFrameY());
	}
}

void gameObjectManager::setTile()
{	
	// 미리 타일 셋해놓자
	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };

	int count = 0;
	for (int j = 0; j < TILENUM; j++)      // 세로 ( 열 )
	{
		for (int i = 0; i < TILENUM; i++)   // 가로 ( 행 )
		{
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

			_vTile.push_back(&_tile[i][j]);

			count++;
		}
	}
	// 그리고 그 타일 위에 정보를 로드해와서 덮어씌우자
	loadMapData();
}

void gameObjectManager::setCharacter()
{
	// 프리니정보 로드해온다 (용병 개수 + 이름)									-> 지우저장된거 후에 확인하자
	gameObject* _prinny = new prinny;
	_vCharacter.push_back(_prinny);
	_vGameObject.push_back(_prinny);
	_vCharacter[0]->init();
	//_vCharacter[0]->겟용병개수백터;
	
	//for (int i = 0; i < 용병개수; i++)
	//{
	//	switch (용병이름[i])
	//	{
	//		//이름마다 케이스 나눠서 인잇 + 셋포인트(젠포인트)
	//	default:
	//		break;
	//	}
	//}

}

void gameObjectManager::setEnemy()
{
	//|,0,2,2,5,0,|,1,2,3,5,0,|,2,2,4,5,0
	// 
	// 에너미파일 로드

	DATABASE->loadDatabase("battleMap1_enm.txt");


	for (int i = 0; i < vEnmSize; i++)
	{
		//DATABASE->getElementData(std::to_string(i))->;
		//_vStr[4] -> 몹 구별 넘버값이면 이걸로 스위치 돌리고
		//_vStr[3] _vStr[2]-> x, y 타일 넘버 넘겨주면서 인잇하고 벡터 넣어준다.

	}
}

void gameObjectManager::setObject()
{
}

void gameObjectManager::loadMapData()
{
	//타일로드
	DATABASE->loadDatabase("battleMap1.txt");
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		//(*_viTile)->number 는 자료를 찾는 인덱스. 고유번호
		(*_viTile)->number = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->number;
		(*_viTile)->state = (TILESTATE)DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->state;

		(*_viTile)->x = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->x;
		(*_viTile)->y = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->y;
		(*_viTile)->imageNum = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->imageNum;
		if ((*_viTile)->imageNum < 50)
		{
			(*_viTile)->draw = true;
			(*_viTile)->image->setFrameX((*_viTile)->imageNum % 4);
			(*_viTile)->image->setFrameY((*_viTile)->imageNum / 4);
		}

		if ((*_viTile)->state == S_ONOBJ) vObjSize++;
		if ((*_viTile)->state == S_ONENM) vEnmSize++;
	}
}
