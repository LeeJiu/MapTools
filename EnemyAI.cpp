#include "stdafx.h"
#include "EnemyAI.h"
#include "battleManager.h"
#include "gameObjectManager.h"

EnemyAI::EnemyAI()
{
}


EnemyAI::~EnemyAI()
{
}

HRESULT EnemyAI::init()
{
	_isDoOrderAction = false;


	return S_OK;
}

void EnemyAI::release()
{
}

void EnemyAI::update()
{
	if (_orderCount < _gameObjMgr->getEnmSize())
	{
		_isDoOrderAction = false;
		return;
	}

	
}

void EnemyAI::render()
{
}
