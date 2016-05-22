#include "stdafx.h"
#include "battleCamera.h"


battleCamera::battleCamera()
{
}


battleCamera::~battleCamera()
{
}

HRESULT battleCamera::init()
{

	_isMapScrool = false;

	_joomSize = 20;
	_vibrateCount = 0;

	return S_OK;
}

void battleCamera::release()
{
}

void battleCamera::update()
{
	cameraFree();
	cameraTile();
	cameraVibrate();
	setCameraJoomIn();
	setCameraJoomOut();
}

void battleCamera::render()
{

}

void battleCamera::setCameraTile(float x, float y)
{
	if (!_isMapScrool)
	{
		// 목적지 저장
		if (_cameraTileX == x && _cameraTileY == y) return;
		_cameraTileX = x;
		_cameraTileY = y;

		// 0.5초만에 가기위한 스피드, 각도 계산
		_scroolSpeed = getDistance(_cameraX + CENTERX, _cameraY + CENTERY, _cameraTileX, _cameraTileY) / 0.5 * TIMEMANAGER->getElapsedTime();
		_scroolAngle = getAngle(_cameraX + CENTERX, _cameraY + CENTERY, _cameraTileX, _cameraTileY);

		_isMapScrool = true;
	}
}


void battleCamera::setCameraJoomIn()
{
	if (!_isJoomIn) return;

	_sourWidth -= _joomSize;
	_sourHeight -= _joomSize / 2;

	_cameraX += _joomSize / 2;
	_cameraY += _joomSize / 2;

	if (_sourHeight < CENTERY + 100)
	{
		_isJoomIn = false;
		_isJoomOut = true;
	}
}

void battleCamera::setCameraJoomOut()
{
	if (!_isJoomOut) return;

	_sourWidth += _joomSize;
	_sourHeight += _joomSize / 2;

	_cameraX -= _joomSize / 2;
	_cameraY -= _joomSize / 2;

	if (_sourHeight > WINSIZEY)
	{
		_sourWidth = WINSIZEX;
		_sourHeight = WINSIZEY;
		_cameraX += _joomSize / 2;
		_cameraY += _joomSize / 2;
		_isJoomOut = false;
	}
}

void battleCamera::cameraVibrate()
{
	if (!_isVibrate) return;

	if (_vibrateCount % 2 == 0)
	{
		_cameraX += 10;
	}
	else
	{
		_cameraX -= 10;
	}

	_vibrateCount++;

	if (_vibrateCount >= 20)
	{
		_vibrateCount = 0;
		_isVibrate = false;
	}
}

void battleCamera::cameraTile()
{
	if (!_isMapScrool) return;

	_cameraX += cosf(_scroolAngle) * _scroolSpeed;
	_cameraY += -sinf(_scroolAngle) * _scroolSpeed;

	if (getDistance(_cameraX + CENTERX, _cameraY + CENTERY, _cameraTileX, _cameraTileY) < _scroolSpeed)
	{
		_cameraX = _cameraTileX - CENTERX;
		_cameraY = _cameraTileY - CENTERY;

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
