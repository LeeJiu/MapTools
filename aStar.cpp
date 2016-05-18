#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
{
}


aStar::~aStar()
{
}

HRESULT aStar::init()
{
	_finish = false;

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
	for (int i = 0; i < _vRoute.size(); i++)
	{
		IMAGEMANAGER->findImage("tile_green")->render(getMemDC(), _vRoute[i]->rc.left, _vRoute[i]->rc.top);
	}
}

void aStar::checkTile()
{
	// ó���� �־����
	if (_vCloseList.size() == 0)
	{
		if (_vRoute.size() != 0)
		{
			for (_viRoute = _vRoute.begin(); _viRoute != _vRoute.end(); )
			{
				(*_viRoute)->parent = NULL;
				_viRoute = _vRoute.erase(_viRoute);
			}
			_vRoute.clear();
		}

		_tile[_start.x][_start.y]->h = abs(_end.x - _start.x) * 10 + abs(_end.y - _start.y) * 10;
		_tile[_start.x][_start.y]->g = 0;
		_tile[_start.x][_start.y]->f = _tile[_start.x][_start.y]->g + _tile[_start.x][_start.y]->h;
		_vCloseList.push_back(_tile[_start.x][_start.y]);
	}

	// �������� ���� Ŭ�����Ʈ Ȯ������
	int lastCloseTile = _vCloseList.size() - 1;

	// ���� �� ã�� ���¶�� ������
	if (_vCloseList[lastCloseTile]->x == _end.x && _vCloseList[lastCloseTile]->y == _end.y)
	{
		_finish = true;
		return;
	}


	// 8���� �˻�
	for (int i = _vCloseList[lastCloseTile]->x - 1; i <= _vCloseList[lastCloseTile]->x + 1; i++)
	{
		for (int j = _vCloseList[lastCloseTile]->y - 1; j <= _vCloseList[lastCloseTile]->y + 1; j++)
		{
			// �迭 ���� �Ѿ�°� ��Ƽ��
			if (i < 0 || j < 0 || i >= TILENUM || j >= TILENUM) continue;

			// ��ֹ��� �����¿쿡 ������ �н�����
			if (_vCloseList[lastCloseTile]->x + 1 < TILENUM && _tile[_vCloseList[lastCloseTile]->x + 1][_vCloseList[lastCloseTile]->y]->state == S_ONOBJ && i == _vCloseList[lastCloseTile]->x + 1) continue;
			else if (_vCloseList[lastCloseTile]->x - 1 >= 0 && _tile[_vCloseList[lastCloseTile]->x - 1][_vCloseList[lastCloseTile]->y]->state == S_ONOBJ && i == _vCloseList[lastCloseTile]->x - 1) continue;
			if (_vCloseList[lastCloseTile]->y + 1 < TILENUM && _tile[_vCloseList[lastCloseTile]->x][_vCloseList[lastCloseTile]->y + 1]->state == S_ONOBJ && j == _vCloseList[lastCloseTile]->y + 1) continue;
			else if (_vCloseList[lastCloseTile]->y - 1 >= 0 && _tile[_vCloseList[lastCloseTile]->x][_vCloseList[lastCloseTile]->y - 1]->state == S_ONOBJ && j == _vCloseList[lastCloseTile]->y - 1) continue;
			// ���� �����¿쿡 ������ �н�����
			if (_vCloseList[lastCloseTile]->x + 1 < TILENUM && _tile[_vCloseList[lastCloseTile]->x + 1][_vCloseList[lastCloseTile]->y]->state == S_ONENM && i == _vCloseList[lastCloseTile]->x + 1) continue;
			else if (_vCloseList[lastCloseTile]->x - 1 >= 0 && _tile[_vCloseList[lastCloseTile]->x - 1][_vCloseList[lastCloseTile]->y]->state == S_ONENM && i == _vCloseList[lastCloseTile]->x - 1) continue;
			if (_vCloseList[lastCloseTile]->y + 1 < TILENUM && _tile[_vCloseList[lastCloseTile]->x][_vCloseList[lastCloseTile]->y + 1]->state == S_ONENM && j == _vCloseList[lastCloseTile]->y + 1) continue;
			else if (_vCloseList[lastCloseTile]->y - 1 >= 0 && _tile[_vCloseList[lastCloseTile]->x][_vCloseList[lastCloseTile]->y - 1]->state == S_ONENM && j == _vCloseList[lastCloseTile]->y - 1) continue;
			// �츮���� �����¿쿡 ������ �н�����
			if (_vCloseList[lastCloseTile]->x + 1 < TILENUM && _tile[_vCloseList[lastCloseTile]->x + 1][_vCloseList[lastCloseTile]->y]->state == S_ONCHAR && i == _vCloseList[lastCloseTile]->x + 1) continue;
			else if (_vCloseList[lastCloseTile]->x - 1 >= 0 && _tile[_vCloseList[lastCloseTile]->x - 1][_vCloseList[lastCloseTile]->y]->state == S_ONCHAR && i == _vCloseList[lastCloseTile]->x - 1) continue;
			if (_vCloseList[lastCloseTile]->y + 1 < TILENUM && _tile[_vCloseList[lastCloseTile]->x][_vCloseList[lastCloseTile]->y + 1]->state == S_ONCHAR && j == _vCloseList[lastCloseTile]->y + 1) continue;
			else if (_vCloseList[lastCloseTile]->y - 1 >= 0 && _tile[_vCloseList[lastCloseTile]->x][_vCloseList[lastCloseTile]->y - 1]->state == S_ONCHAR && j == _vCloseList[lastCloseTile]->y - 1) continue;
			// ��� Ÿ�� ��Ƽ��
			if (i == _vCloseList[lastCloseTile]->x && j == _vCloseList[lastCloseTile]->y) continue;

			// �˻��� Ÿ�� �ɸ��� �Ǵ� ������Ʈ�� ��Ƽ��
			else if (_tile[i][j]->state == S_ONOBJ) continue;
			else if (_tile[i][j]->state == S_ONENM) continue;
			else if (_tile[i][j]->state == S_ONCHAR) continue;


			////////////////////////////////////////////// openList �߰� ��ġ ///////////////////////////////////////////////////

			// �밢���� ��Ƽ��
			else if (abs(i - _vCloseList[lastCloseTile]->x) == 1 && abs(j - _vCloseList[lastCloseTile]->y) == 1)
			{
				continue;
				//// �ӽð��� ���س��� �ִ� f���� ������
			/*	int tempH = abs(_end.x - i) * 10 + abs(_end.y - j) * 10;
				int tempG = _vCloseList[lastCloseTile]->g + 17;
				int tempF = tempH + tempG;

				if (tempF < _tile[i][j]->f)
				{
					_tile[i][j]->h = tempH;
					_tile[i][j]->g = tempG;
					_tile[i][j]->f = tempF;
					_tile[i][j]->parent = _tile[_vCloseList[lastCloseTile]->x][_vCloseList[lastCloseTile]->y];
					eraseVector(i, j);
					_vOpenList.push_back(_tile[i][j]);
				}*/
			}
			// ���� �Ÿ� 10
			else
			{
				// �ӽð��� ���س��� �ִ� f���� ������
				int tempH = abs(_end.x - i) * 10 + abs(_end.y - j) * 10;
				int tempG = _vCloseList[lastCloseTile]->g + 10;
				int tempF = tempH + tempG;

				if (tempF < _tile[i][j]->f)
				{
					_tile[i][j]->h = tempH;
					_tile[i][j]->g = tempG;
					_tile[i][j]->f = tempF;
					_tile[i][j]->parent = _tile[_vCloseList[lastCloseTile]->x][_vCloseList[lastCloseTile]->y];
					eraseVector(i, j);
					_vOpenList.push_back(_tile[i][j]);
				}
			}
		}
	}

	// ���� ���̶�� ������
	if (_vCloseList.size() > 1 && _vOpenList.size() == 0)
	{
		_finish = true;
		return;
	}

	// f �������� ��������
	std::sort(_vOpenList.begin(), _vOpenList.end(), cmp);

	// ���� �� f�� ���� ���� ���� Ŭ�����Ʈ�� �߰��ϰ� ���¸���Ʈ���� ��������
	if (_vOpenList.size() <= 0)
	{
		_finish = true;
		return;
	}
	_vCloseList.push_back(_vOpenList[0]);
	_vOpenList.erase(_vOpenList.begin());
}

vector<TagTile*> aStar::moveCharacter(int startX, int startY, int endX, int endY)
{
	_start = { startX, startY };
	_end = { endX, endY };

	while (!_finish)
	{
		checkTile();
	}

	_finish = false;
	resultRoute(endX, endY);
	reset();

	return _vRoute;
}

void aStar::resultRoute(int x, int y)
{
	if (x == _start.x && y == _start.y)
	{
		return;
	}

	_viRoute = _vRoute.begin();
	_vRoute.insert(_viRoute, _tile[x][y]);

	if (_tile[x][y]->parent == NULL) return;
	else resultRoute(_tile[x][y]->parent->x, _tile[x][y]->parent->y);
}

void aStar::setTile(vector<TagTile*> tile)
{
	for (int i = 0; i < 100; i++)
	{
		_tile[i % TILENUM][i / TILENUM] = tile[i];
		_tile[i % TILENUM][i / TILENUM]->f = 9999;
	}
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

	for (int j = 0; j < TILENUM; j++)      // ���� ( �� )
	{
		for (int i = 0; i < TILENUM; i++)   // ���� ( �� )
		{
			_tile[i][j]->f = 9999;
			_tile[i][j]->g = 0;
			_tile[i][j]->h = 0;
		}
	}
}

void aStar::eraseVector(int x, int y)
{
	for (int i = 0; i < _vOpenList.size(); i++)
	{
		if (_vOpenList[i]->x == x && _vOpenList[i]->y == y)
		{
			_vOpenList.erase(_vOpenList.begin() + i);
			return;
		}
	}
}
