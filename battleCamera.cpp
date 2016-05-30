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

	_joomSize = 150;

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
	cameraKeyControl();
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

void battleCamera::cameraKeyControl()
{
	if (KEYMANAGER->isStayKeyDown('I'))
	{
		_sourWidth -= _joomSize / 10;
		_sourHeight -= _joomSize / 10;

		_cameraX += _joomSize / 20;
		_cameraY += _joomSize / 20;
	}

	if (KEYMANAGER->isStayKeyDown('O'))
	{
		if (_sourWidth >= WINSIZEX) return;

		_sourWidth += _joomSize / 10;
		_sourHeight += _joomSize / 10;

		_cameraX -= _joomSize / 20;
		_cameraY -= _joomSize / 20;

		if (_sourWidth >= WINSIZEX)
		{
			_sourWidth = WINSIZEX;
			_sourHeight = WINSIZEY;
		//	_cameraX += _joomSize / 20;
		//	_cameraY += _joomSize / 20;
		}
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

	if (_vibrateCount > 20)
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
		if (_cameraY <= 0)
		{
			_cameraY = 0;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_cameraY += 5;
		if ((TILENUM - 1) * WIDTH / 2 <= _cameraY)
		{
			_cameraY = (TILENUM - 1) * WIDTH / 2;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cameraX += 5;
		if ((TILENUM - 1) * WIDTH <= _cameraX)
		{
			_cameraX = (TILENUM - 1) * WIDTH;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cameraX -= 5;
		if (_cameraX <= 0)
		{
			_cameraX = 0;
		}
	}
}
