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

	_isPlayerTurn = true;	//�÷��̾� ���� ����
	
	_takeTurns = _onAction = false;
	_action = IMAGEMANAGER->addImage("action", "image/ui/ui_action.bmp", 250, 150, false, false);
	_rcAction = RectMakeCenter(_cameraX + CENTERX, _cameraY + CENTERY, 250, 150);

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
	}

	//����â(������, �ߵ�����)
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_takeTurns = true;
		_onAction = false;
		_onUI = false;
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
	//int enemySize = _objectMgr->getVEnemy().size();
	//
	//for (int i = 0; i < enemySize; ++i)
	//{
	//	//Ÿ���� �ε��� ��ȯ�� �޾ƿ´�.
	//	int temp; // <- �Լ� ��ȯ�� �ӽ÷� ���� ���ڸ��� �Լ� ��ȯ�� ������ ��
	//
	//	// ��ȯ�� ���� �ε����� ������Ʈ�� S_NONE�̶�� �� Ÿ�Ϸ� �̵��ض�
	//	if (_objectMgr->getVTile()[temp]->state == S_NONE)
	//	{
	//		// �̵��ض�
	//		_objectMgr->enemyMove(i, _objectMgr->getVTile()[temp]->x, _objectMgr->getVTile()[temp]->y);
	//	}
	//	// ��ȯ�� ���� �ε����� ������Ʈ�� S_ONCHAR�̶�� �� Ÿ���� �ֺ� Ÿ�Ϸ� �̵��ϰ� ������ �����Ѵ�.
	//	else if (_objectMgr->getVTile()[temp]->state == S_ONCHAR)
	//	{
	//
	//	}
	//}

	// searchTile() ���� �� ��ȯ�� Ÿ�� �ε����� ���ʹ��� ����� �����Ѵ�.
	// ��ȯ�� Ÿ���� ĳ���Ͱ� �ƴ϶�� (S_NONE)
	// �̵��� ����Ѵ�.
	// ��ȯ�� Ÿ���� ĳ���Ͷ�� (S_ONCHAR)
	// �̵� ��� �� ���� ����Ѵ�.





}

void battleManager::increaseEnemyIdx()
{
	_enemyIdx++;

	if (_enemyIdx <= _objectMgr->getVEnemy().size())
	{
		_enemyIdx = 0;
		_isPlayerTurn = true;

		// ī�޶� �� �ƿ� ȣ��
		_camera->setIsJoomOut(true);
	}
}

int battleManager::searchTile()
{
	// ���� ��� ���� ���� ���ʹ��� �ε����� Ÿ���� �˻��Ѵ�.
	// ���ʹ̰� �̵� ������ Ÿ�� �߿��� �ε����� ��ȯ�Ѵ�.
	// �̵� ���� Ÿ���� ���� ������ �ε����� ��� �����ϰ�,
	// Ÿ�� �߿� ĳ���Ͱ� ������ �� Ÿ���� �ε����� �����ϰ� �ٷ� ��ȯ�Ѵ�.

	return 0;
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
	}
}
