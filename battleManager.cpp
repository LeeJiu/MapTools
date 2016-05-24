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
	_cameraX = CENTERX;
	_cameraY = CENTERY;

	_ui = new battleUI;
	_ui->init();

	_isPlayerTurn = true;	//플레이어 먼저 시작

	_isShowLabel = true;
	
	_turnbackImage = IMAGEMANAGER->findImage("turnback");
	_turnUIImage = IMAGEMANAGER->findImage("stageStart");
	_rcTurnback = RectMakeCenter(_cameraX, _cameraY + CENTERY, WINSIZEX, 100);
	_time = _time2 = 0;

	_takeTurns = _onAction = false;
	_action = IMAGEMANAGER->addImage("action", "image/ui/ui_action.bmp", 250, 150, false, false);
	_rcAction = RectMakeCenter(_cameraX + CENTERX, _cameraY + CENTERY, 250, 150);

	_selectTile = IMAGEMANAGER->findImage("select_tile");
	_selectArrow = IMAGEMANAGER->findImage("ui_arrow_blue");

	IMAGEMANAGER->addImage("clear", "image/background/stage_clear.bmp", WINSIZEX, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("fail", "image/background/stage_fail.bmp", WINSIZEX, WINSIZEY, false, false);

	_count = 0;
	return S_OK;
}

void battleManager::release()
{
	_ui->release();
	SAFE_DELETE(_ui);
}

void battleManager::update()
{
	_ui->update();

	if (!_setUI)
	{
		_ui->setCharList(_objectMgr->getVCharacter()[0]->getMercenary());
		_setUI = true;
	}

	_rcAction = RectMakeCenter(_cameraX + CENTERX, _cameraY + CENTERY, 250, 150);

	//플레이어의 턴일 때
	if (_isPlayerTurn)
	{
		//플레이어가 ui를 조작할 수 있다.
		if (!_takeTurns)
		{
			if (!_camera->getIsJoomOut() && _isShowLabel)
			{
				_turnUIImage = IMAGEMANAGER->findImage("playerTurn");
				_time += TIMEMANAGER->getElapsedTime();
				if (_time > 1.5f)
				{
					_time = 0;
					_isShowLabel = false;
				}
			}

			if (_leftButtonDown && !_onUI && !_isShowLabel)
			{
				_leftButtonDown = false;
				tileControl();
			}
			else if (_leftButtonDown && _onUI && !_isShowLabel)
			{
				_leftButtonDown = false;
				UIControl();
			}

			//모든 ui창을 끈다.
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				_ui->onCharacterList(false);
				_ui->onOrder(false);
				_ui->onSummary(false);
				_ui->onStatus(false);
				_onAction = false;
				_onUI = false;
			}

			//실행창(턴종료, 중도포기)
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				if (_onAction)
				{
					_onAction = false;
					_onUI = false;
				}
				else
				{
					_onAction = true;
					_onUI = true;
				}
			}
		}
		//플레이어가 ui를 조작할 수 없다. / 턴 실행 중
		else
		{
			orderAction();
		}
	}
	//에너미의 턴일 때
	else
	{
		if (!_takeTurns)
		{
			if (!_camera->getIsJoomOut())
			{
				_isShowLabel = true;
				_turnUIImage = IMAGEMANAGER->findImage("enemyTurn");
				_time += TIMEMANAGER->getElapsedTime();
				if (_time > 1.5f)
				{
					_time = 0;
					_isShowLabel = false;
					_takeTurns = true;
				}
			}
			else
			{
				return;
			}
		}
		else
		{
			//AI
			enemyAI();
		}
	}

	_count++;
	setFrame();

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_takeTurns = true;
		_onAction = false;
		_onUI = false;
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_playerWin = true;
		_enemyWin = false;
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_playerWin = false;
		_enemyWin = true;
	}

	//플레이어 승리 / 패배
	if ((_playerWin && !_enemyWin)
		|| (!_playerWin && _enemyWin))
	{
		_time2 += TIMEMANAGER->getElapsedTime();
		if (_time2 > 2.f)
		{
			_time2 = 0;
			SCENEMANAGER->changeScene("town");
		}
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SCENEMANAGER->changeScene("selectStage");
	}
}

void battleManager::render()
{
	_ui->render();

	if (_onAction)
		_action->render(getMemDC(), _rcAction.left, _rcAction.top);

	if (_isShowLabel)
	{
		_turnUIImage->render(getMemDC()
			, _cameraX + CENTERX - _turnUIImage->getWidth() / 2
			, _cameraY + CENTERY - _turnUIImage->getHeight() / 2);
	}

	//플레이어 승리
	if (_playerWin && !_enemyWin)
	{
		IMAGEMANAGER->findImage("clear")->render(getMemDC(), _cameraX, _cameraY);
	}
	//플레이어 패배
	else if (!_playerWin && _enemyWin)
	{
		IMAGEMANAGER->findImage("fail")->render(getMemDC(), _cameraX, _cameraY);
	}
}

void battleManager::setFrame()
{
	if (_count % 5 == 0)
	{
		_selectArrow->setFrameX(_selectArrow->getFrameX() + 1);

		if (_selectArrow->getFrameX() >= _selectArrow->getMaxFrameX())
		{
			_selectArrow->setFrameX(0);
		}
	}
}

void battleManager::tileControl()
{
	//캐릭터가 젠포인트 위에 있는지 없는지 확인
	characterIsOnZenPoint();

	for (int i = 0; i < TOTALTILE(TILENUM); ++i)
	{
		if (PtInRect(&_objectMgr->getVTile()[i]->rc, _click))
		{
			//아이소 타일 클릭 조건
			if ((_click.y - _objectMgr->getVTile()[i]->pivotY) >= -0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) - WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) >=  0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) - WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) <= -0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) + WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) <=  0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) + WIDTH / 4)
			{
				//젠 포인트
				if (_objectMgr->getVTile()[i]->state == ZEN_POINT)
				{
					//캐릭터가 젠포인트 위일 때
					if (!_isOnZenPonit)
					{
						clickZenPoint();
						break;
					}
					//캐릭터가 젠포인트 위가 아닐 때
					else
					{
						clickCharacter(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
						break;
					}
				}
				//캐릭터
				else if (_objectMgr->getVTile()[i]->state == S_ONCHAR)
				{
					clickCharacter(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
					break;
				}
				//적
				else if (_objectMgr->getVTile()[i]->state == S_ONENM)
				{
					clickEnemy(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
					break;
				}
				//이동 불가능한 타일/장애물
				else if (_objectMgr->getVTile()[i]->state == S_ONOBJ
					|| _objectMgr->getVTile()[i]->state == S_ETC)
				{
					clickObject(i);
					break;
				}
				//이동 가능한 타일
				else if (_objectMgr->getVTile()[i]->state == S_NONE)
				{
					clickTile(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
					break;
				}
			}
		}
	}
}

void battleManager::UIControl()
{
	if (_ui->isOnCharList())
	{
		if (_ui->getCharIdx() != 100)
		{
			_selectCharIdx = _ui->getCharIdx();

			_objectMgr->getVCharacter()[_selectCharIdx]->setIsShow(true);

			_ui->setCharIdx(100);

			//캐릭터 리스트를 끈다.
			_ui->onCharacterList(false);
			_onUI = false;
		}
	}

	// UI에서 클릭한것이 무브라면
	if (_ui->getOrderNumber() == 1)
	{
		_objectMgr->getVCharacter()[_selectCharIdx]->setIsShowPossibleMoveTile(true);
		_ui->setOrderNumber(0);
		_ui->onOrder(false);
		_onUI = false;
	}
	// UI에서 클릭한것이 어택이라면
	else if (_ui->getOrderNumber() == 2)
	{
		_objectMgr->getVCharacter()[_selectCharIdx]->setIsShowPossibleAttackTile(true);
		_ui->setOrderNumber(0);
		_ui->onOrder(false);
		_onUI = false;
	}
}

void battleManager::characterIsOnZenPoint()
{
	int size = _objectMgr->getVCharacter().size();

	for (int i = 0; i < size; ++i)
	{
		if (!_objectMgr->getVCharacter()[i]->getIsShow()) continue;

		if (_objectMgr->getVCharacter()[i]->getIndexX() == 5
			&& _objectMgr->getVCharacter()[i]->getIndexY() == 11)
		{
			_isOnZenPonit = true;
			_selectCharIdx = i;
			return;
		}
	}

	_isOnZenPonit = false;
}

void battleManager::orderAction()
{
	if (_vOrder.size() == 0)
	{
		_isPlayerTurn = false;
		_takeTurns = false;
		_onAction = false;
		_onUI = false;
		return;
	}

	_camera->setIsJoomIn(true);

	//명령의 끝이거나, 명령 중이라면 명령을 실행하지 않는다
	if (_objectMgr->getOrderList() != OL_NONE) return;

	// 명령의 종류가 공격이라면 케릭터공격, 에너미 피격 함수를 호출한다
	if (_vOrder[_orderNum].order == O_ATTACK)
	{
		_objectMgr->characterAttack(_vOrder[_orderNum].playerVIdx, _vOrder[_orderNum].enemyIdx.x, _vOrder[_orderNum].enemyIdx.y);
		_objectMgr->enemyPain(_vOrder[_orderNum].enemyVIdx, _vOrder[_orderNum].playerIdx.x, _vOrder[_orderNum].playerIdx.y, _vOrder[_orderNum].damage);
		_camera->setIsVibrate(true);
	}
}

void battleManager::selectTileRender()
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
				_selectTile->render(getMemDC(), _objectMgr->getVTile()[i]->rc.left, _objectMgr->getVTile()[i]->rc.top);
				
				_selectArrow->frameRender(getMemDC(), (_objectMgr->getVTile()[i]->rc.left + _objectMgr->getVTile()[i]->rc.right) / 2 - _selectArrow->getFrameWidth() / 2,
														_objectMgr->getVTile()[i]->rc.top - 200, _selectArrow->getFrameX(), _selectArrow->getFrameY());
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
	//선택된 캐릭터 이름을 지우고, 캐릭터 리스트를 닫는다.

	if (!_ui->isOnCharList())
	{
		//캐릭터 리스트를 보여준다.
		_ui->onCharacterList(true);
		_onUI = true;
	}
}

void battleManager::clickCharacter(int x, int y, int i)
{
	//명령창을 띄운다. (현재 캐릭터의 인덱스 저장)

	_ui->onOrder(true);
	_onUI = true;

	int charSize = _objectMgr->getVCharacter().size();
	for (int i = 0; i < charSize; i++)
	{
		if (_objectMgr->getVCharacter()[i]->getIndexX() == x 
			&& _objectMgr->getVCharacter()[i]->getIndexY() == y)
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
		_objectMgr->getVCharacter()[_selectCharIdx]->setIsShowPossibleMoveTile(false);
	}
	//이동 가능 타일이 켜지지 않은 경우,
	else
	{
		//카메라 포커스 맞춘다.
		_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);
	}
}

void battleManager::enemyAI()
{
	if (_objectMgr->getOrderList() == OL_ORDERING) return;
	if (_objectMgr->getOrderList() == OL_END) return;

	// 명령 수행 중인 에너미의 4방향 검사
	int enemyX = _objectMgr->getVEnemy()[_enemyIdx]->getIndexX();
	int enemyY = _objectMgr->getVEnemy()[_enemyIdx]->getIndexY();
	if (enemyX + (enemyY - 1) * TILENUM >= 0
		&& _objectMgr->getVTile()[enemyX + (enemyY - 1) * TILENUM]->state == S_ONCHAR)
	{
		_objectMgr->enemyAttack(_enemyIdx, enemyX, enemyY - 1);
		return;
	}
	else if (enemyX + enemyY * TILENUM - 1 >= 0
		&& _objectMgr->getVTile()[enemyX + enemyY * TILENUM - 1]->state == S_ONCHAR)
	{
		_objectMgr->enemyAttack(_enemyIdx, enemyX - 1, enemyY);
		return;
	}
	else if (enemyX + enemyY * TILENUM + 1 < TOTALTILE(TILENUM)
		&& _objectMgr->getVTile()[enemyX + enemyY * TILENUM + 1]->state == S_ONCHAR)
	{
		_objectMgr->enemyAttack(_enemyIdx, enemyX + 1, enemyY);
		return;
	}
	else if (enemyX + (enemyY + 1) * TILENUM < TOTALTILE(TILENUM)
		&& _objectMgr->getVTile()[enemyX + (enemyY + 1) * TILENUM]->state == S_ONCHAR)
	{
		_objectMgr->enemyAttack(_enemyIdx, enemyX, enemyY + 1);
		return;
	}

	// 서치타일 한 인덱스 받아서 임시저장 (최종목적지 == 빈타일 or 케릭터)
	int tempTileIdx = searchTile(_enemyIdx);

	// 최종목적지가 빈타일이라면 그곳으로 이동해라
	if (_objectMgr->getVTile()[tempTileIdx]->state == S_NONE)
	{
		_objectMgr->enemyMove(_enemyIdx, _objectMgr->getVTile()[tempTileIdx]->x, _objectMgr->getVTile()[tempTileIdx]->y);
	}
	// 최종목적지가 케릭터라면
	else if (_objectMgr->getVTile()[tempTileIdx]->state == S_ONCHAR)
	{
		// 타일의 인덱스가 범위 내고, S_NONE이라면 4방향 검사해서 그쪽으로 이동한 후 공격한다.
		if (tempTileIdx - TILENUM >= 0 && tempTileIdx - TILENUM < TOTALTILE(TILENUM) && _objectMgr->getVTile()[tempTileIdx - TILENUM]->state == S_NONE)
		{
			_objectMgr->enemyMoveToAttack(_enemyIdx, _objectMgr->getVTile()[tempTileIdx - TILENUM]->x, _objectMgr->getVTile()[tempTileIdx - TILENUM]->y, tempTileIdx,
				_objectMgr->getVTile()[tempTileIdx]->x, _objectMgr->getVTile()[tempTileIdx]->y);
		}
		else if (tempTileIdx - 1 >= 0 && tempTileIdx - 1 < TOTALTILE(TILENUM) && _objectMgr->getVTile()[tempTileIdx - 1]->state == S_NONE)
		{
			_objectMgr->enemyMoveToAttack(_enemyIdx, _objectMgr->getVTile()[tempTileIdx - 1]->x, _objectMgr->getVTile()[tempTileIdx - 1]->y, tempTileIdx,
				_objectMgr->getVTile()[tempTileIdx]->x, _objectMgr->getVTile()[tempTileIdx]->y);
		}
		else if (tempTileIdx + 1 >= 0 && tempTileIdx + 1 < TOTALTILE(TILENUM) && _objectMgr->getVTile()[tempTileIdx + 1]->state == S_NONE)
		{
			_objectMgr->enemyMoveToAttack(_enemyIdx, _objectMgr->getVTile()[tempTileIdx + 1]->x, _objectMgr->getVTile()[tempTileIdx + 1]->y, tempTileIdx,
				_objectMgr->getVTile()[tempTileIdx]->x, _objectMgr->getVTile()[tempTileIdx]->y);
		}
		else if (tempTileIdx + TILENUM >= 0 && tempTileIdx + TILENUM < TOTALTILE(TILENUM) && _objectMgr->getVTile()[tempTileIdx + TILENUM]->state == S_NONE)
		{
			_objectMgr->enemyMoveToAttack(_enemyIdx, _objectMgr->getVTile()[tempTileIdx + TILENUM]->x, _objectMgr->getVTile()[tempTileIdx + TILENUM]->y, tempTileIdx,
				_objectMgr->getVTile()[tempTileIdx]->x, _objectMgr->getVTile()[tempTileIdx]->y);
		}
	}
}

void battleManager::increaseEnemyIdx()
{
	_enemyIdx++;

	if (_enemyIdx >= _objectMgr->getVEnemy().size())
	{
		_enemyIdx = 0;
		_isPlayerTurn = true;
		_takeTurns = false;
		_isShowLabel = true;

		// 카메라 줌 아웃 호출
		_camera->setIsJoomOut(true);
	}
}

int battleManager::searchTile(int enemyIdx)
{
	// 현재 명령 수행 중인 에너미의 인덱스로 타일을 검사한다.
	// 에너미가 이동 가능한 타일 중에서 인덱스을 반환한다.
	// 이동 가능 타일의 가장 마지막 인덱스를 계속 저장하고,
	// 타일 중에 캐릭터가 있으면 그 타일의 인덱스를 저장하고 바로 반환한다.
	int tempIdx;

	for (int i = 0; i < TOTALTILE(TILENUM); ++i)
	{
		if (abs(_objectMgr->getVEnemy()[enemyIdx]->getIndexX() - _objectMgr->getVTile()[i]->x) 
			+ abs(_objectMgr->getVEnemy()[enemyIdx]->getIndexX() - _objectMgr->getVTile()[i]->y) 
			< _objectMgr->getVEnemy()[enemyIdx]->getMv())
		{
			if (_objectMgr->getVTile()[i]->state == S_NONE)
			{
				tempIdx = i;
			}
			else if (_objectMgr->getVTile()[i]->state == S_ONCHAR)
			{
				tempIdx = i;
				return tempIdx;
			}
		}
	}
	return tempIdx;
}

void battleManager::increaseOrderNum()
{
	_orderNum++;

	if (_vOrder.size() == _orderNum)
	{
		_orderNum = 0;
		_isPlayerTurn = false;
		_takeTurns = false;
		_vOrder.clear();

		// 카메라 줌 아웃 호출
		_camera->setIsJoomOut(true);
	}
}
