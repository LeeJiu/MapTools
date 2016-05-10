#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
{
}


aStar::~aStar()
{
}

HRESULT aStar::init(int battleMapNumber)
{
	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };

	int count = 0;
	// �ʿ� ���� ������ ������Ʈ �޾ƿ���
	for (int i = 0; i < TILENUM; i++)		// ���� ( �� )
	{
		for (int j = 0; j < TILENUM; j++)	// ���� ( �� )
		{
			_tile[j][i].width = WIDTH;
			_tile[j][i].height = WIDTH / 2;
			_tile[j][i].rc = RectMakeCenter(firstPivot.x + j * _tile[j][i].width / 2 - i * _tile[j][i].width / 2,
											firstPivot.y + j * _tile[j][i].width / 4 + i * _tile[j][i].width / 4, _tile[j][i].width, _tile[j][i].height);
			_tile[j][i].pivot.x = (_tile[j][i].rc.left + _tile[j][i].rc.right) / 2;
			_tile[j][i].pivot.y = (_tile[j][i].rc.top + _tile[j][i].rc.bottom) / 2;
			_tile[j][i].x = j;
			_tile[j][i].y = i;
			_tile[j][i].number = count;
			_tile[j][i].state = S_NONE;
			_tile[j][i].mapName = M_NONE;
			_tile[j][i].draw = false;

		//	_vTile.push_back(tile);

			count++;
		}
	}

	
	return S_OK;
}

void aStar::release()
{
}

void aStar::update()
{
}

void aStar::render()
{
}

void aStar::checkTile()
{
}

void aStar::celulateRoute(POINT start, POINT end)
{
}


// ��������
void aStar::reset()
{
	// Ŭ�����Ʈ ����
	for (_viCloseList = _vCloseList.begin(); _viCloseList != _vCloseList.end(); )
	{
		(*_viCloseList)->parent = NULL;
		_viCloseList = _vCloseList.erase(_viCloseList);
	}
	_vCloseList.clear();

	// ���¸���Ʈ ����
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); )
	{
		(*_viOpenList)->parent = NULL;
		_viOpenList = _vOpenList.erase(_viOpenList);
	}
	_vOpenList.clear();

	for (_viRoute = _vRoute.begin(); _viRoute != _vRoute.end(); )
	{
		(*_viRoute)->parent = NULL;
		_viRoute = _vOpenList.erase(_viRoute);
	}
	_vOpenList.clear();
}
