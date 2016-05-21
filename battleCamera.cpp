#include "stdafx.h"
#include "battleCamera.h"


battleCamera::battleCamera()
{
}


battleCamera::~battleCamera()
{
}

HRESULT battleCamera::init(vector<TagTile*>& tile)
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
		_scroolSpeed = getDistance(_cameraX + CENTERX, _cameraY + CENTERY, _tile[x][y]->pivotX, _tile[x][y]->pivotY) / 0.5 * TIMEMANAGER->getElapsedTime();
		_scroolAngle = getAngle(_cameraX + CENTERX, _cameraY + CENTERY, _tile[x][y]->pivotX, _tile[x][y]->pivotY);

		_isMapScrool = true;
	}
}

void battleCamera::setCameraCharacter(RECT rc)
{
}

void battleCamera::cameraTile()
{
	if (!_isMapScrool) return;

	_cameraX += cosf(_scroolAngle) * _scroolSpeed;
	_cameraY += -sinf(_scroolAngle) * _scroolSpeed;

	if (getDistance(_cameraX + CENTERX, _cameraY + CENTERY, _tile[_cameraTileX][_cameraTileY]->pivotX, _tile[_cameraTileX][_cameraTileY]->pivotY) < _scroolSpeed)
	{
		_cameraX = _tile[_cameraTileX][_cameraTileY]->pivotX - CENTERX;
		_cameraY = _tile[_cameraTileX][_cameraTileY]->pivotY - CENTERY;
		_isMapScrool = false;
		return;
	}
}

void battleCamera::cameraFree()
{
	if (_isMapScrool) return;

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_cameraY -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_cameraY += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cameraX += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cameraX -= 5;
	}
}