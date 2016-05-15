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
	_aStar = new aStar;
	_aStar->init();

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
	int _vTileSize = _vTile.size();
	for (int i = 0; i < _vTileSize; i++)
	{
		_vTile[i]->image->frameRender(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top, _vTile[i]->image->getFrameX(), _vTile[i]->image->getFrameY());
	}
}

void gameObjectManager::setUnitMove()
{
}

void gameObjectManager::setUnitAttack()
{
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
			_tile[i][j].image = new image;
			_tile[i][j].image->init("image/isoTile.bmp", 1024, 1408, 4, 11, true, 0xff00ff);
			_tile[i][j].width = WIDTH;
			_tile[i][j].height = WIDTH / 2;
			_tile[i][j].rc = RectMakeCenter(firstPivot.x + i * _tile[i][j].width / 2 - j * _tile[i][j].width / 2, firstPivot.y + i * _tile[i][j].width / 4 + j * _tile[i][j].width / 4, _tile[i][j].width, _tile[i][j].height);
			_tile[i][j].pivotX = (_tile[i][j].rc.left + _tile[i][j].rc.right) / 2;
			_tile[i][j].pivotY = (_tile[i][j].rc.top + _tile[i][j].rc.bottom) / 2;
			_tile[i][j].x = i;
			_tile[i][j].y = j;
			_tile[i][j].imageNum = 100;   //�̹��� �ѹ�.
			_tile[i][j].number = count;
			_tile[i][j].state = S_NONE;
			_tile[i][j].draw = false;

			_vTile.push_back(&_tile[i][j]);

			count++;
		}
	}
	// �׸��� �� Ÿ�� ���� ������ �ε��ؿͼ� �������
	loadMapData();
}

void gameObjectManager::setCharacter()
{
	// ���������� �ε��ؿ´� (�뺴 ���� + �̸�)									-> ��������Ȱ� �Ŀ� Ȯ������
	gameObject* _prinny = new prinny;
	_vCharacter.push_back(_prinny);
	_vGameObject.push_back(_prinny);
	_vCharacter[0]->init(_vTile);

	gameObject* _prinny1 = new prinny;
	_vCharacter.push_back(_prinny1);
	_vGameObject.push_back(_prinny1);
	_vCharacter[1]->init(_vTile);

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

}

void gameObjectManager::setEnemy()
{
	//DATABASE->getElementData(std::to_string(i))->;

	//---------------------------------------------------------------------------------

	//|,0,2,2,5,0,|,1,2,3,5,0,|,2,2,4,5,0
	// 
	// ���ʹ����� �ε�

	DATABASE->loadDatabase("battleMap1_enm.txt");


	//for (int i = 0; i < vEnmSize; i++)
	//{
		// ������ ���� ����͵�

		// ���� ���� ���ʹ������ �����ʹ� ������ �Ǿ����� ������ "|" �� �������� 3���� �ִµ�
		// 0��°�� DATABASE�� �� Ű���� �Ǵ°�?
		// �׸��� ���͸� �����ҷ��� ��� ���°�?
		// �׸��� ����� 3�̸� ������ �����鼭 ���Ϳ� �־��ٷ����ϴµ� ������� ������ ���ƾ��ϴ���
		
		// �Ʒ��� ���� �̷��� �� ������

	//for (int i = 0; i < vEnmSize; i++)
	//{
	//	switch(DATABASE->getElementData(std::to_string(i))->imageNum)   // (������ ����)
	//	{
	//	case 0:
	//		gameObject* _orc = new orc;
	//		_orc->init();
	//		_vEnemy.push_back(_orc);
	//		_vGameObject.push_back(_orc);
	//		break;
	//	case 1:
	//		gameObject* _boss = new boss;
	//		_boss->init();
	//		_vEnemy.push_back(_boss);
	//		_vGameObject.push_back(_boss);
	//		break;
	//	}
	//}

	//---------------------------------------------------------------------------------
		//DATABASE->getElementData(std::to_string(i))->;
		//_vStr[4] -> �� ���� �ѹ����̸� �̰ɷ� ����ġ ������
		//_vStr[3] _vStr[2]-> x, y Ÿ�� �ѹ� �Ѱ��ָ鼭 �����ϰ� ���� �־��ش�.

	//}
}

void gameObjectManager::setObject()
{
	//DATABASE->loadDatabase("battleMap1_obj.txt");

	//for (int i = 0; i < vObjSize; i++)
	//{
	//	switch(DATABASE->getElementData(std::to_string(i))->imageNum)   // (������ ����)
	//	{
	//	case 0:
	//		gameObject* _orc = new orc;
	//		_orc->init();
	//		_vEnemy.push_back(_orc);
	//		_vGameObject.push_back(_orc);
	//		break;
	//	case 1:
	//		gameObject* _boss = new boss;
	//		_boss->init();
	//		_vEnemy.push_back(_boss);
	//		_vGameObject.push_back(_boss);
	//		break;
	//	}
	//}
}

void gameObjectManager::setAstar()
{
	_aStar->setTile(_vTile);
}

void gameObjectManager::loadMapData()
{
	//Ÿ�Ϸε�
	DATABASE->loadDatabase("battleMap1.txt");
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		//(*_viTile)->number �� �ڷḦ ã�� �ε���. ������ȣ
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
