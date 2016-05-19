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
	//init����  ��Ʋ�ʶ�ﶧ�ҷ��� Ÿ�� �����͸� ī��Ʈ�ؼ� vEnmSize����
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


//����
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
	// �̸� Ÿ�� ���س���
	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };

	int count = 0;
	for (int j = 0; j < TILENUM; j++)      // ���� ( �� )
	{
		for (int i = 0; i < TILENUM; i++)   // ���� ( �� )
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
			_tile[i][j]->imageNum = 100;   //�̹��� �ѹ�.
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
	// ���������� �ε��ؿ´� (�뺴 ���� + �̸�)									-> ��������Ȱ� �Ŀ� Ȯ������
	gameObject* _prinny = new prinny;
	_prinny->init(_vTile);
	_vGameObject.push_back(_prinny);
	_vToTalRender.push_back(_prinny);

	gameObject* _prinny1 = new prinny;
	_prinny1->init(_vTile);
	_vGameObject.push_back(_prinny1);
	_vToTalRender.push_back(_prinny1);

	//_vCharacter[0]->�ٿ뺴��������;
	
	//for (int i = 0; i < �뺴����; i++)
	//{
	//	switch (�뺴�̸�[i])
	//	{
	//		//�̸����� ���̽� ������ ���� + ������Ʈ(������Ʈ)
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



	// ���ʹ����� �ε�
	DATABASE->loadDatabase("battleMap1_enm.txt");
	
		// ���� ���� ���ʹ������ �����ʹ� ������ �Ǿ����� ������ "|" �� �������� 3���� �ִµ�
		// 0��°�� DATABASE�� �� Ű���� �Ǵ°�?
		// �׸��� ���͸� �����ҷ��� ��� ���°�?
		// �׸��� ����� 3�̸� ������ �����鼭 ���Ϳ� �־��ٷ����ϴµ� ������� ������ ���ƾ��ϴ���
		
		// �Ʒ��� ���� �̷��� �� ������

	for (int i = 0; i < vEnmSize; i++)
	{
		//gameObject* enemy;
		//switch(DATABASE->getElementData(std::to_string(i))->imageNum)   // (������ ����)
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
		//_vStr[4] -> �� ���� �ѹ����̸� �̰ɷ� ����ġ ������
		//_vStr[3] _vStr[2]-> x, y Ÿ�� �ѹ� �Ѱ��ָ鼭 �����ϰ� ���� �־��ش�.

}

void gameObjectManager::setObject()
{
	DATABASE->loadDatabase("battleMap1_obj.txt");

	//������Ʈ ������ŭ
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
		//Ÿ�Ϸε�
		DATABASE->loadDatabase("battleMap1.txt");		
	}
	if (STAGEDATA->getSelectStageNumber() == 1)
	{
		DATABASE->loadDatabase("battleMap2.txt");
	}

	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		//(*_viTile)->number �� �ڷḦ ã�� �ε���. ������ȣ
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
