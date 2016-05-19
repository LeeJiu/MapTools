#include "stdafx.h"
#include "battleCamera.h"


battleCamera::battleCamera()
{
}


battleCamera::~battleCamera()
{
}

HRESULT battleCamera::init(vector<TagTile*> tile)
{
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		_tile[i % TILENUM][i / TILENUM] = tile[i];
	}

	_isMapScrool = false;

	return S_OK;
}

void battleCamera::release()
{
}

void battleCamera::update()
{
	cameraFree();
	cameraTile();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isMapScrool = false;
	}
}

void battleCamera::render()
{
}

void battleCamera::setCameraTile(int x, int y)
{
	if (_cameraTileX == x && _cameraTileY == y) return;

	if (!_isMapScrool)
	{
		// 목적지 저장
		_cameraTileX = x;
		_cameraTileY = y;

		// 0.5초만에 가기위한 스피드, 각도 계산
		_scroolSpeed = getDistance(CENTERX, CENTERY, _tile[x][y]->pivotX, _tile[x][y]->pivotY) / 0.5 * TIMEMANAGER->getElapsedTime();
		_scroolAngle = getAngle(CENTERX, CENTERY, _tile[x][y]->pivotX, _tile[x][y]->pivotY);

		_isMapScrool = true;
	}
}

void battleCamera::setCameraCharacter(RECT rc)
{
}

void battleCamera::cameraTile()
{
	if (!_isMapScrool) return;

	for (int i = 0; i < TILENUM; i++)		// 세로 ( 열 )
	{
		for (int j = 0; j < TILENUM; j++)	// 가로 ( 행 )
		{
			_tile[j][i]->pivotX -= cosf(_scroolAngle) * _scroolSpeed;
			_tile[j][i]->pivotY -= -sinf(_scroolAngle) * _scroolSpeed;
			_tile[j][i]->rc = RectMakeCenter(_tile[j][i]->pivotX, _tile[j][i]->pivotY, _tile[j][i]->width, _tile[j][i]->height);
		}
	}

	if(getDistance(CENTERX, CENTERY, _tile[_cameraTileX][_cameraTileY]->pivotX, _tile[_cameraTileX][_cameraTileY]->pivotY) < _scroolSpeed)
	{
		POINT firstPivot = { CENTERX + (_cameraTileY - _cameraTileX) * WIDTH / 2 , CENTERY - (_cameraTileX + _cameraTileY) * WIDTH / 4};

		for (int i = 0; i < TILENUM; i++)		// 세로 ( 열 )
		{
			for (int j = 0; j < TILENUM; j++)	// 가로 ( 행 )
			{
				_tile[j][i]->rc = RectMakeCenter(firstPivot.x + j * _tile[j][i]->width / 2 - i * _tile[j][i]->width / 2,
					firstPivot.y + j * _tile[j][i]->width / 4 + i * _tile[j][i]->width / 4, _tile[j][i]->width, _tile[j][i]->height);
				_tile[j][i]->pivotX = (_tile[j][i]->rc.left + _tile[j][i]->rc.right) / 2;
				_tile[j][i]->pivotY = (_tile[j][i]->rc.top + _tile[j][i]->rc.bottom) / 2;
			}
		}
		_isMapScrool = false;
		return;
	}
}

void battleCamera::cameraFree()
{
	if (_isMapScrool) return;

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_tile[0][0]->pivotY += 3;
		setTile(_tile[0][0]->pivotX, _tile[0][0]->pivotY);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_tile[0][0]->pivotY -= 3;
		setTile(_tile[0][0]->pivotX, _tile[0][0]->pivotY);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_tile[0][0]->pivotX += 3;
		setTile(_tile[0][0]->pivotX, _tile[0][0]->pivotY);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_tile[0][0]->pivotX -= 3;
		setTile(_tile[0][0]->pivotX, _tile[0][0]->pivotY);
	}
}

void battleCamera::setTile(float firstPivotX, float firstPivotY)
{
	POINT firstPivot = { firstPivotX, firstPivotY };
	for (int i = 0; i < TILENUM; i++)      // 세로 ( 열 )
	{
		for (int j = 0; j < TILENUM; j++)   // 가로 ( 행 )
		{
			_tile[j][i]->rc = RectMakeCenter(firstPivot.x + j * _tile[j][i]->width / 2 - i * _tile[j][i]->width / 2, firstPivot.y + j * _tile[j][i]->width / 4 + i * _tile[j][i]->width / 4, _tile[j][i]->width, _tile[j][i]->height);
			_tile[j][i]->pivotX = (_tile[j][i]->rc.left + _tile[j][i]->rc.right) / 2;
			_tile[j][i]->pivotY = (_tile[j][i]->rc.top + _tile[j][i]->rc.bottom) / 2;

		}
	}
}
