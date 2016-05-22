#include "stdafx.h"
#include "battleManager.h"
#include "gameObjectManager.h"
#include "battleCamera.h"

battleManager::battleManager()
{
}

battleManager::~battleManager()
{
}

HRESULT battleManager::init()
{
	_ui = new battleUI;
	_ui->init();
	_camera = new battleCamera;
	_camera->init();

	_isPlayerTurn = true;	//플레이어 먼저 시작

	return S_OK;
}

void battleManager::release()
{
	_ui->release();
	_camera->release();
	SAFE_DELETE(_ui);
	SAFE_DELETE(_camera);


}

void battleManager::update()
{
	_ui->update();
	//플레이어의 턴일 때
	if (_isPlayerTurn)
	{
		if (_leftButtonDown)
		{
			keyControl();
		}
	}
	//에너미의 턴일 때
	else
	{
		//AI
	}
}

void battleManager::render()
{
	_ui->render();
}

void battleManager::keyControl()
{
	for (int i = 0; i < TOTALTILE(TILENUM); ++i)
	{
		if (PtInRect(&_objectMgr->getVTile()[i]->rc, _click))
		{
			//아이소 타일 클릭 조건
			if ((_click.y - _objectMgr->getVTile()[i]->pivotY) >= -0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) - WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) >= 0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) - WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) <= -0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) + WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) <= 0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) + WIDTH / 4)
			{
				switch (_objectMgr->getVTile()[i]->state)
				{
				case ZEN_POINT:			//젠 포인트
					clickZenPoint();
					break;

				case S_ONCHAR:			//캐릭터
					clickCharacter(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
					break;

				case S_ONENM:			//적
					clickEnemy(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
					break;

				case S_ONOBJ: case S_ETC://이동 불가능한 타일/장애물
					clickObject(i);
					break;

				case S_NONE:			//이동 가능한 타일
					clickTile(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
					break;
				}
				break;
			}
		}
	}
}

void battleManager::clickZenPoint()
{
	//젠포인트에 아무것도 없을 때 - 캐릭이 미출전
	//캐릭터 리스트를 보여줘야함
	//캐릭터 리스트에서 선택하면 (현재 클릭된 캐릭터 인덱스)
	//캐릭터 리스트를 닫고, 명령창을 띄운다.

}

void battleManager::clickCharacter(int x, int y, int i)
{
	//명령창을 띄운다. (현재 캐릭터의 인덱스 저장)
	int charSize = _objectMgr->getVCharacter().size();

	for (int i = 0; i < charSize; i++)
	{
		if (_objectMgr->getVCharacter()[i]->getIndexX() == x && _objectMgr->getVCharacter()[i]->getIndexY() == y)
		{
			_selectCharIdx = i;
			break;
		}
	}
	//카메라 포커스 맞춘다.
	_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);

}

void battleManager::clickEnemy(int x, int y, int i)
{
	/* 일단은 공격만 짜놓고 나중에 스킬을 추가하게 된다면 한번더 조건(공격인지 스킬인지)를 걸면 될듯 */

	//만약에 선택된 케릭터의 공격가능한 타일이 보여지고있다면
	if (_objectMgr->getVCharacter()[_selectCharIdx]->getIsShowPossibleAttackTile())
	{
		// 적이 담겨있는 사이즈를 받아와서 
		int enemySize = _objectMgr->getVEnemy().size();
	
		for (int i = 0; i < enemySize; i++)
		{	
			// 해당 위치의 있는 적을 찾고 
			if (_objectMgr->getVEnemy()[i]->getIndexX() == x && _objectMgr->getVEnemy()[i]->getIndexY() == y)
			{
				// 명령 수행할 내용을 벡터에 push_back 한다.
				tagOrder _order;
				_order.playerVIdx = _selectCharIdx;
				_order.playerIdx.x = _objectMgr->getVCharacter()[_selectCharIdx]->getIndexX();
				_order.playerIdx.y = _objectMgr->getVCharacter()[_selectCharIdx]->getIndexY();
				_order.enemyVIdx = i;
				_order.enemyIdx.x = x;
				_order.enemyIdx.y = y;
				_order.order = O_ATTACK;
				_order.damage = _objectMgr->getVCharacter()[_selectCharIdx]->getAtk();

				_vOrder.push_back(_order);
				break;
			}
		}
		// 공격가능한 타일을 꺼준다.
		_objectMgr->getVCharacter()[_selectCharIdx]->setIsShowPossibleAttackTile(false);
	}
	// 공격타일이 보여지지 않고 있는 경우
	else
	{
		//카메라 포커스를 맞춘다.
		_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);
	}


}

void battleManager::clickObject(int i)
{
	//카메라 포커스를 맞춘다.
	_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);

}

void battleManager::clickTile(int x, int y, int i)
{
	//캐릭터 이동한다.
	
	//이동 가능 타일이 켜진 경우,
	if (_objectMgr->getVCharacter()[_selectCharIdx]->getIsShowPossibleMoveTile())
	{
		_objectMgr->characterMove(_selectCharIdx, x, y);
	}
	//이동 가능 타일이 켜지지 않은 경우,
	else
	{
		//카메라 포커스 맞춘다.
		_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);
	}
}
