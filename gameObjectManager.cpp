#include "stdafx.h"
#include "gameObjectManager.h"
#include "battleUI.h"

gameObjectManager::gameObjectManager()
{
}


gameObjectManager::~gameObjectManager()
{
}

HRESULT gameObjectManager::init()
{
	//init에서  배틀맵띄울때불러온 타일 데이터를 카운트해서 vEnmSize구함
	_aStar = new aStar;
	_aStar->init();
	vEnmSize = vObjSize = 0;

	return S_OK;
}

void gameObjectManager::release()
{
}

void gameObjectManager::update()
{
	int _size = vCharSize + vObjSize + 2;
	for (int i = 0; i < _size; i++)
	{
		_vToTalRender[i]->update();
	}
}


//랜더
void gameObjectManager::render()
{
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		_vTile[i]->image->frameRender(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top);
	}

	_battleUI->renderOverlapSelectTile();

<<<<<<< HEAD
	int _size = vCharSize + vObjSize + 2;

=======
	sort(_vToTalRender.begin(), _vToTalRender.end(), GOBJ_Y_RENDER());

	int _size = _vToTalRender.size();
>>>>>>> refs/remotes/origin/jihyun
	for (int i = 0; i < _size; i++)
	{
		_vToTalRender[i]->render();
	}

	//char str[128];
	//sprintf_s(str, "pivotX: %.f, pivotY: %.f", _vTile[0]->pivotX, _vTile[0]->pivotY);
	//TextOut(getMemDC(), 10, 10, str, strlen(str));
}

void gameObjectManager::setUnitMove(int i, int destX, int destY)
{
	_vGameObject[i]->setCharacterMove(destX, destY, _aStar->moveCharacter(_vGameObject[i]->getIndexX(), _vGameObject[i]->getIndexY(), destX, destY));
}

void gameObjectManager::setUnitAttack(int i, int destX, int destY)
{
	_vGameObject[i]->attack(destX, destY);
}

void gameObjectManager::setUnitDefence()
{
}

void gameObjectManager::setActionAttack()
{

}

void gameObjectManager::setChangeTurn()
{
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
			_tile[i][j] = new TagTile;
			_tile[i][j]->image = new image;
			_tile[i][j]->image->init("image/mapTool/mapTile_iso.bmp", 512, 1938, 4, 17, true, 0xff00ff);
			_tile[i][j]->width = WIDTH;
			_tile[i][j]->height = WIDTH / 2;
			_tile[i][j]->rc = RectMakeCenter(firstPivot.x + i * _tile[i][j]->width / 2 - j * _tile[i][j]->width / 2, firstPivot.y + i * _tile[i][j]->width / 4 + j * _tile[i][j]->width / 4, _tile[i][j]->width, _tile[i][j]->height);
			_tile[i][j]->pivotX = (_tile[i][j]->rc.left + _tile[i][j]->rc.right) / 2;
			_tile[i][j]->pivotY = (_tile[i][j]->rc.top + _tile[i][j]->rc.bottom) / 2;
			_tile[i][j]->x = i;
			_tile[i][j]->y = j;
			_tile[i][j]->imageNum = 100;   //이미지 넘버.
			_tile[i][j]->number = count;
			_tile[i][j]->state = S_NONE;
			_tile[i][j]->draw = false;

			_vTile.push_back(_tile[i][j]);

			count++;
		}
	}
	
	loadMapData();
}

void gameObjectManager::setCharacter()
{
	// 프리니정보 로드해온다 (용병 개수 + 이름)									-> 지우저장된거 후에 확인하자
	gameObject* _prinny = new prinny;
	_prinny->init(_vTile);
	_vGameObject.push_back(_prinny);
	_vToTalRender.push_back(_prinny);

	gameObject* _prinny1 = new prinny;
	_prinny1->init(_vTile);
	_vGameObject.push_back(_prinny1);
	_vToTalRender.push_back(_prinny1);

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
	vCharSize = 2;
}

void gameObjectManager::setEnemy()
{
	//DATABASE->getElementData(std::to_string(i))->;

	//---------------------------------------------------------------------------------

	//|,0,2,2,5,0,|,1,2,3,5,0,|,2,2,4,5,0
	// 



	// 에너미파일 로드
	DATABASE->loadDatabase("battleMap1_enm.txt");
	
		// 위에 보면 에너미저장된 데이터는 저렇게 되어있음 구분자 "|" 를 기준으로 3개가 있는데
		// 0번째가 DATABASE의 맵 키값이 되는거?
		// 그리고 몬스터를 구분할려면 어떤걸 쓰는거?
		// 그리고 사이즈가 3이면 포문을 돌리면서 벡터에 넣어줄려고하는데 어떤식으로 포문을 돌아야하는지
		
		// 아래는 예시 이렇게 할 생각임

	for (int i = 0; i < vEnmSize; i++)
	{
		//gameObject* enemy;
		//switch(DATABASE->getElementData(std::to_string(i))->imageNum)   // (몬스터의 종류)
		//{
		//case 0:
		//	enemy = new orc;
		//	enemy->init();
		//	break;
		//case 1:
		//	enemy = new boss;
		//	enemy->init();
		//	break;
		//default:
		//	break;
		//}
		//
		//_vGameObject.push_back(enemy);
	}

	gameObject* _orc = new orc;
	_orc->init(4, 7, _vTile);
	_vGameObject.push_back(_orc);
	_vToTalRender.push_back(_orc);

	gameObject* _orc1 = new orc;
	_orc1->init(6, 7, _vTile);
	_vGameObject.push_back(_orc1);
	_vToTalRender.push_back(_orc1);

	//---------------------------------------------------------------------------------
		//DATABASE->getElementData(std::to_string(i))->;
		//_vStr[4] -> 몹 구별 넘버값이면 이걸로 스위치 돌리고
		//_vStr[3] _vStr[2]-> x, y 타일 넘버 넘겨주면서 인잇하고 벡터 넣어준다.

}

void gameObjectManager::setObject()
{
	DATABASE->loadDatabase("battleMap1_obj.txt");

	//오브젝트 갯수만큼
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		int imageNum = DATABASE->getElementData(std::to_string(i))->imageNum;
		if (imageNum < 100)
		{
			const char* imageName = NULL;
			gameObject* rnd = new objects;
			switch (imageNum)
			{
			case 0:
				imageName = "tree1";
				break;
			case 1:
				imageName = "tree2";
				break;
			case 2:
				imageName = "woods";
				break;
			case 3:
				imageName = "mushiroom";
				break;
			case 4:
				imageName = "zenPoint";
				break;
			default:
				break;
			}


			rnd->init(imageName,
				DATABASE->getElementData(std::to_string(i))->x,
				DATABASE->getElementData(std::to_string(i))->y,
				DATABASE->getElementData(std::to_string(i))->imageNum,
				_vTile);

			_vToTalRender.push_back(rnd);
			vObjSize++;
		}
		else continue;
	}
}

void gameObjectManager::setAstar()
{
	_aStar->setTile(_vTile);
}

void gameObjectManager::loadMapData()
{
	if (STAGEDATA->getSelectStageNumber() == 0)
	{
		//타일로드
		DATABASE->loadDatabase("battleMap1.txt");		
	}
	if (STAGEDATA->getSelectStageNumber() == 1)
	{
		DATABASE->loadDatabase("battleMap2.txt");
	}

	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		//(*_viTile)->number 는 자료를 찾는 인덱스. 고유번호
		(*_viTile)->number = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->number;
		(*_viTile)->state = (TILESTATE)DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->state;

		(*_viTile)->x = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->x;
		(*_viTile)->y = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->y;
		(*_viTile)->imageNum = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->imageNum;
		if ((*_viTile)->imageNum < 100)
		{
			(*_viTile)->draw = true;
			(*_viTile)->image->setFrameX((*_viTile)->imageNum % 4);
			(*_viTile)->image->setFrameY((*_viTile)->imageNum / 4);
		}

		//if ((*_viTile)->state == S_ONOBJ || (*_viTile)->state == S_ZEN) vObjSize++;
		//if ((*_viTile)->state == S_ONENM) vEnmSize++;
	}
}
