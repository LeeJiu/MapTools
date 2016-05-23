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
	_isShowLabel = true;

	_cameraX = CENTERX;
	_cameraY = CENTERY;

	_ui = new battleUI;
	_ui->init();

	_isPlayerTurn = true;	//�÷��̾� ���� ����
	
	_turnbackImage = new image;
	_turnbackImage = IMAGEMANAGER->findImage("turnback");
	_turnUIImage = new image;
	_turnUIImage = IMAGEMANAGER->findImage("stageStart");
	_rcTurnback = RectMakeCenter(_cameraX, _cameraY + CENTERY, WINSIZEX, 100);
	_time = 0;

	_takeTurns = _onAction = false;
	_action = IMAGEMANAGER->addImage("action", "image/ui/ui_action.bmp", 250, 150, false, false);
	_rcAction = RectMakeCenter(_cameraX + CENTERX, _cameraY + CENTERY, 250, 150);

	_selectTile = IMAGEMANAGER->findImage("select_tile");
	_selectArrow = IMAGEMANAGER->findImage("ui_arrow_blue");

	_count = 0;
	return S_OK;
}

void battleManager::release()
{
	_ui->release();
	_turnbackImage->release();
	_turnUIImage->release();
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

	setRect();
	
	if (!_isShowLabel)
	{
		//�÷��̾��� ���� ��
		if (_isPlayerTurn)
		{
			//�÷��̾ ui�� ������ �� �ִ�.
			if (!_takeTurns)
			{
				if (_leftButtonDown && !_onUI)
				{
					_leftButtonDown = false;
					tileControl();
				}
				else if (_leftButtonDown && _onUI)
				{
					_leftButtonDown = false;
					UIControl();
				}

				//��� uiâ�� ����.
				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					_ui->onCharacterList(false);
					_ui->onOrder(false);
					_ui->onSummary(false);
					_ui->onStatus(false);
					_onAction = false;
					_onUI = false;
				}

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
			//�÷��̾ ui�� ������ �� ����. / �� ���� ��
			else
			{
				orderAction();
			}
		}
		//���ʹ��� ���� ��
		else
		{
			//AI
			setRect();
			enemyAI();
		}

	//����â(������, �ߵ�����)
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_takeTurns = true;
		_onAction = false;
		_onUI = false;
	}

	_count++;
	setFrame();

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

	turnbarRender();	//�Ϲ� ��ο�

	char str[100];
	sprintf_s(str, "_isShowLabel = %d , time = %f", _isShowLabel, _time);
	TextOut(getMemDC(), _cameraX + 10, _cameraY + 10, str, strlen(str));
}

void battleManager::setRect()
{
	_rcAction = RectMakeCenter(_cameraX + CENTERX, _cameraY + CENTERY, 250, 150);

	if (_isShowLabel)
	{
		if (_rcTurnback.left == _cameraX)
		{
			_time += TIMEMANAGER->getElapsedTime();
			if (_time > 1.5)
			{
				_time = 0;
				_rcTurnback.left += 1;
			}
		}
		else 
		{
			_rcTurnback.left += 20;
			_rcTurnback.right += 20;
		}
	}

	if (_rcTurnback.left > _cameraX + WINSIZEX || !_isShowLabel)
	{
		_rcTurnback = RectMakeCenter(_cameraX - WINSIZEX / 2, _cameraY + CENTERY, WINSIZEX, 100);
		_isShowLabel = false;
	}
}

void battleManager::turnbarRender()
{
	if (!_isShowLabel)
	{
		if (!_isPlayerTurn)
			_turnUIImage = IMAGEMANAGER->findImage("playerTurn");
		else if (_isPlayerTurn)
			_turnUIImage = IMAGEMANAGER->findImage("enemyTurn");
	}

	_turnbackImage->render(getMemDC(),_rcTurnback.left, _rcTurnback.top);
	_turnUIImage->render(getMemDC(), _rcTurnback.left + _turnUIImage->getWidth(), _rcTurnback.top + _turnUIImage->getHeight() / 2);
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
	//ĳ���Ͱ� ������Ʈ ���� �ִ��� ������ Ȯ��
	characterIsOnZenPoint();

	for (int i = 0; i < TOTALTILE(TILENUM); ++i)
	{
		if (PtInRect(&_objectMgr->getVTile()[i]->rc, _click))
		{
			//���̼� Ÿ�� Ŭ�� ����
			if ((_click.y - _objectMgr->getVTile()[i]->pivotY) >= -0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) - WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) >=  0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) - WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) <= -0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) + WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) <=  0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) + WIDTH / 4)
			{
				//�� ����Ʈ
				if (_objectMgr->getVTile()[i]->state == ZEN_POINT)
				{
					//ĳ���Ͱ� ������Ʈ ���� ��
					if (!_isOnZenPonit)
					{
						clickZenPoint();
						break;
					}
					//ĳ���Ͱ� ������Ʈ ���� �ƴ� ��
					else
					{
						clickCharacter(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
						break;
					}
				}
				//ĳ����
				else if (_objectMgr->getVTile()[i]->state == S_ONCHAR)
				{
					clickCharacter(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
					break;
				}
				//��
				else if (_objectMgr->getVTile()[i]->state == S_ONENM)
				{
					clickEnemy(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
					break;
				}
				//�̵� �Ұ����� Ÿ��/��ֹ�
				else if (_objectMgr->getVTile()[i]->state == S_ONOBJ
					|| _objectMgr->getVTile()[i]->state == S_ETC)
				{
					clickObject(i);
					break;
				}
				//�̵� ������ Ÿ��
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

			//ĳ���� ����Ʈ�� ����.
			_ui->onCharacterList(false);
			_onUI = false;
		}
	}

	// UI���� Ŭ���Ѱ��� ������
	if (_ui->getOrderNumber() == 1)
	{
		_objectMgr->getVCharacter()[_selectCharIdx]->setIsShowPossibleMoveTile(true);
		_ui->setOrderNumber(0);
		_ui->onOrder(false);
		_onUI = false;
	}
	// UI���� Ŭ���Ѱ��� �����̶��
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
		_takeTurns = true;
		_onAction = false;
		_onUI = false;
		_isShowLabel = true;

		return;
	}

	_camera->setIsJoomIn(true);

	// �ش� �ɸ��Ͱ� ����� �������̶�� ���Ͻ��Ѷ�
	if (_objectMgr->getOrderList() == OL_ORDERING) return;
	if (_objectMgr->getOrderList() == OL_END) return;

	// ����� ������ �����̶�� �ɸ��Ͱ���, ���ʹ� �ǰ� �Լ��� ȣ���Ѵ�
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
			//���̼� Ÿ�� Ŭ�� ����
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
	//������Ʈ�� �ƹ��͵� ���� �� - ĳ���� ������
	//ĳ���� ����Ʈ�� ���������
	//ĳ���� ����Ʈ���� �����ϸ� (���� Ŭ���� ĳ���� �ε���)
	//���õ� ĳ���� �̸��� �����, ĳ���� ����Ʈ�� �ݴ´�.

	if (!_ui->isOnCharList())
	{
		//ĳ���� ����Ʈ�� �����ش�.
		_ui->onCharacterList(true);
		_onUI = true;
	}
}

void battleManager::clickCharacter(int x, int y, int i)
{
	//���â�� ����. (���� ĳ������ �ε��� ����)

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
	//ī�޶� ��Ŀ�� �����.
	_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);

}

void battleManager::clickEnemy(int x, int y, int i)
{
	/* �ϴ��� ���ݸ� ¥���� ���߿� ��ų�� �߰��ϰ� �ȴٸ� �ѹ��� ����(�������� ��ų����)�� �ɸ� �ɵ� */

	//���࿡ ���õ� �ɸ����� ���ݰ����� Ÿ���� ���������ִٸ�
	if (_objectMgr->getVCharacter()[_selectCharIdx]->getIsShowPossibleAttackTile())
	{
		// ���� ����ִ� ����� �޾ƿͼ� 
		int enemySize = _objectMgr->getVEnemy().size();
	
		for (int i = 0; i < enemySize; i++)
		{	
			// �ش� ��ġ�� �ִ� ���� ã�� 
			if (_objectMgr->getVEnemy()[i]->getIndexX() == x && _objectMgr->getVEnemy()[i]->getIndexY() == y)
			{
				// ��� ������ ������ ���Ϳ� push_back �Ѵ�.
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
		// ���ݰ����� Ÿ���� ���ش�.
		_objectMgr->getVCharacter()[_selectCharIdx]->setIsShowPossibleAttackTile(false);
	}
	// ����Ÿ���� �������� �ʰ� �ִ� ���
	else
	{
		//ī�޶� ��Ŀ���� �����.
		_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);
	}
}

void battleManager::clickObject(int i)
{
	//ī�޶� ��Ŀ���� �����.
	_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);

}

void battleManager::clickTile(int x, int y, int i)
{
	//ĳ���� �̵��Ѵ�.
	
	//�̵� ���� Ÿ���� ���� ���,
	if (_objectMgr->getVCharacter()[_selectCharIdx]->getIsShowPossibleMoveTile())
	{
		_objectMgr->characterMove(_selectCharIdx, x, y);
		_objectMgr->getVCharacter()[_selectCharIdx]->setIsShowPossibleMoveTile(false);
	}
	//�̵� ���� Ÿ���� ������ ���� ���,
	else
	{
		//ī�޶� ��Ŀ�� �����.
		_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);
	}
}

void battleManager::enemyAI()
{
	if (_objectMgr->getOrderList() == OL_ORDERING) return;
	if (_objectMgr->getOrderList() == OL_END) return;

	// ��� ���� ���� ���ʹ��� 4���� �˻�
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

	// ��ġŸ�� �� �ε��� �޾Ƽ� �ӽ����� (���������� == ��Ÿ�� or �ɸ���)
	int tempTileIdx = searchTile(_enemyIdx);

	// ������������ ��Ÿ���̶�� �װ����� �̵��ض�
	if (_objectMgr->getVTile()[tempTileIdx]->state == S_NONE)
	{
		_objectMgr->enemyMove(_enemyIdx, _objectMgr->getVTile()[tempTileIdx]->x, _objectMgr->getVTile()[tempTileIdx]->y);
	}
	// ������������ �ɸ��Ͷ��
	else if (_objectMgr->getVTile()[tempTileIdx]->state == S_ONCHAR)
	{
		// Ÿ���� �ε����� ���� ����, S_NONE�̶�� 4���� �˻��ؼ� �������� �̵��� �� �����Ѵ�.
		if (tempTileIdx - TILENUM >= 0 && tempTileIdx - TILENUM < TOTALTILE(TILENUM) && _objectMgr->getVTile()[tempTileIdx - TILENUM]->state == S_NONE)
		{
			_objectMgr->enemyMoveToAttack(_enemyIdx, _objectMgr->getVTile()[tempTileIdx - TILENUM]->x, _objectMgr->getVTile()[tempTileIdx - TILENUM]->y,
				_objectMgr->getVTile()[tempTileIdx]->x, _objectMgr->getVTile()[tempTileIdx]->y);
		}
		else if (tempTileIdx - 1 >= 0 && tempTileIdx - 1 < TOTALTILE(TILENUM) && _objectMgr->getVTile()[tempTileIdx - 1]->state == S_NONE)
		{
			_objectMgr->enemyMoveToAttack(_enemyIdx, _objectMgr->getVTile()[tempTileIdx - 1]->x, _objectMgr->getVTile()[tempTileIdx - 1]->y,
				_objectMgr->getVTile()[tempTileIdx]->x, _objectMgr->getVTile()[tempTileIdx]->y);
		}
		else if (tempTileIdx + 1 >= 0 && tempTileIdx + 1 < TOTALTILE(TILENUM) && _objectMgr->getVTile()[tempTileIdx + 1]->state == S_NONE)
		{
			_objectMgr->enemyMoveToAttack(_enemyIdx, _objectMgr->getVTile()[tempTileIdx + 1]->x, _objectMgr->getVTile()[tempTileIdx + 1]->y,
				_objectMgr->getVTile()[tempTileIdx]->x, _objectMgr->getVTile()[tempTileIdx]->y);
		}
		else if (tempTileIdx + TILENUM >= 0 && tempTileIdx + TILENUM < TOTALTILE(TILENUM) && _objectMgr->getVTile()[tempTileIdx + TILENUM]->state == S_NONE)
		{
			_objectMgr->enemyMoveToAttack(_enemyIdx, _objectMgr->getVTile()[tempTileIdx + TILENUM]->x, _objectMgr->getVTile()[tempTileIdx + TILENUM]->y,
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

		// ī�޶� �� �ƿ� ȣ��
		_camera->setIsJoomOut(true);

		_isShowLabel = true;
	}
}

int battleManager::searchTile(int enemyIdx)
{
	// ���� ��� ���� ���� ���ʹ��� �ε����� Ÿ���� �˻��Ѵ�.
	// ���ʹ̰� �̵� ������ Ÿ�� �߿��� �ε����� ��ȯ�Ѵ�.
	// �̵� ���� Ÿ���� ���� ������ �ε����� ��� �����ϰ�,
	// Ÿ�� �߿� ĳ���Ͱ� ������ �� Ÿ���� �ε����� �����ϰ� �ٷ� ��ȯ�Ѵ�.
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

	if (_vOrder.size() <= _orderNum)
	{
		_orderNum = 0;
		_isPlayerTurn = false;
		_vOrder.clear();
		// ī�޶� �� �ƿ� ȣ��
		_camera->setIsJoomOut(true);

		//_isShowLabel = true;
	}
}
