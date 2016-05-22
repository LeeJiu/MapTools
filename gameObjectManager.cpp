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
	//init에서  배틀맵띄울때불러온 타일 데이터를 카운트해서 vEnmSize구함


	_aStar = new aStar;
	_aStar->init();
	vEnmSize = vObjSize = 0;

	_isAction = false;

	return S_OK;
}

void gameObjectManager::release()
{
	SAFE_DELETE(_aStar);
}

void gameObjectManager::update()
{
	int _size = _vToTalRender.size();
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
		if (_vTile[i]->pivotX > _cameraX && _vTile[i]->pivotX < _cameraX + WINSIZEX && _vTile[i]->pivotY > _cameraY && _vTile[i]->pivotY < _cameraY + WINSIZEY)
		_vTile[i]->image->frameRender(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top);
	}

	char str[512];
	sprintf_s(str, "x = %d, y = %d", _vToTalRender[0]->getIndexX(), _vToTalRender[0]->getIndexY());
	TextOut(getMemDC(), 10, 10, str, strlen(str));

	//Y축 정렬
	sort(_vToTalRender.begin(), _vToTalRender.end(), GOBJ_Y_RENDER());

	int _size = _vToTalRender.size();
	for (int i = 0; i < _size; i++)
	{
		_vToTalRender[i]->render();
	}
}

void gameObjectManager::setTile()
{	
	// 미리 타일 셋해놓자
	POINT firstPivot = { WINSIZEX , WINSIZEY - TILENUM * WIDTH / 4 };

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
	// 프리니정보 로드해온다 (용병 개수 + 이름)
	gameObject* _prinny = new prinny;
	_prinny->init(_zenPosX, _zenPosY, this);
	_vGameObject.push_back(_prinny);
	_vToTalRender.push_back(_prinny);
	vCharSize++;

	int size = _vGameObject[0]->getMercenary().size();
	
	for (int i = 0; i < size; ++i)
	{
		if (strcmp(_vGameObject[0]->getMercenary()[i].c_str(), "etna") == 0)
		{
			gameObject* _etna = new etna;
			_etna->init(_zenPosX, _zenPosY, this);
			_vGameObject.push_back(_etna);
			_vToTalRender.push_back(_etna);
		}
		else if (strcmp(_vGameObject[0]->getMercenary()[i].c_str(), "flonne") == 0)
		{
			gameObject* _flonne = new flonne;
			_flonne->init(_zenPosX, _zenPosY, this);
			_vGameObject.push_back(_flonne);
			_vToTalRender.push_back(_flonne);
		}
		else if (strcmp(_vGameObject[0]->getMercenary()[i].c_str(), "raspberyl") == 0)
		{
			gameObject* _raspberyl = new raspberyl;
			_raspberyl->init(_zenPosX, _zenPosY, this);
			_vGameObject.push_back(_raspberyl);
			_vToTalRender.push_back(_raspberyl);
		}
		vCharSize++;
	}
}

void gameObjectManager::setEnemy()
{
	// 에너미파일 로드
	DATABASE->loadDatabase("battleMap1_enm.txt");
	
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		int imageNum = DATABASE->getElementData(std::to_string(i))->imageNum;
		if (imageNum < 100)
		{
			gameObject* enemy;
			int imageNum = DATABASE->getElementData(std::to_string(i))->imageNum;
			switch (imageNum)   // (몬스터의 종류)
			{
			case 1:
				enemy = new orc;
				enemy->init(
					DATABASE->getElementData(std::to_string(i))->x,
					DATABASE->getElementData(std::to_string(i))->y,
					this);
				break;
			case 2:
				enemy = new catsaver;
				enemy->init(
					DATABASE->getElementData(std::to_string(i))->x,
					DATABASE->getElementData(std::to_string(i))->y,
					this);
				break;
			default:
				break;
			}
	
			_vGameObject.push_back(enemy);
			_vToTalRender.push_back(enemy);
			vEnmSize++;
		}
		else continue;
	}
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
				_zenPosX = DATABASE->getElementData(std::to_string(i))->x;
				_zenPosY = DATABASE->getElementData(std::to_string(i))->y;
				break;
			default:
				break;
			}
			rnd->init(imageName,
				DATABASE->getElementData(std::to_string(i))->x,
				DATABASE->getElementData(std::to_string(i))->y,
				DATABASE->getElementData(std::to_string(i))->imageNum,
				this);

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
		//if ((*_viTile)->state == S_ONENM || (*_viTile)->state == BOSS) vEnmSize++;
	}
}
