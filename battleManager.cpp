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
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
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
					clickCharacter();
					break;

				case S_ONENM:			//적
					clickEnemy();
					break;

				case S_ONOBJ: case S_ETC://이동 불가능한 타일/장애물
					clickObject(i);
					break;

				case S_NONE:			//이동 가능한 타일
					clickTile();
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

void battleManager::clickCharacter()
{
	//명령창을 띄운다. (현재 캐릭터의 인덱스 저장)
	//카메라 포커스 맞춘다.

}

void battleManager::clickEnemy()
{
	//적의 인덱스를 저장하고,
	//선택된 캐릭터의 공격 가능 타일을 끈다.
	//->공격 명령을 push


	//공격 가능 타일이 켜져있지 않은 경우,
	//카메라 포커스를 맞춘다.

}

void battleManager::clickObject(int i)
{
	//카메라 포커스를 맞춘다.
	_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);

}

void battleManager::clickTile()
{
	//이동 가능 타일이 켜진 경우,
	//캐릭터 이동한다.


	//이동 가능 타일이 켜지지 않은 경우,
	//카메라 포커스 맞춘다.

}
