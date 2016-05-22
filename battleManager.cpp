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

	_isPlayerTurn = true;	//�÷��̾� ���� ����

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
	//�÷��̾��� ���� ��
	if (_isPlayerTurn)
	{
		if (_leftButtonDown)
		{
			keyControl();
		}
	}
	//���ʹ��� ���� ��
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
			//���̼� Ÿ�� Ŭ�� ����
			if ((_click.y - _objectMgr->getVTile()[i]->pivotY) >= -0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) - WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) >= 0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) - WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) <= -0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) + WIDTH / 4 &&
				(_click.y - _objectMgr->getVTile()[i]->pivotY) <= 0.5 * (_click.x - _objectMgr->getVTile()[i]->pivotX) + WIDTH / 4)
			{
				switch (_objectMgr->getVTile()[i]->state)
				{
				case ZEN_POINT:			//�� ����Ʈ
					clickZenPoint();
					break;

				case S_ONCHAR:			//ĳ����
					clickCharacter(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
					break;

				case S_ONENM:			//��
					clickEnemy(_objectMgr->getVTile()[i]->x, _objectMgr->getVTile()[i]->y, i);
					break;

				case S_ONOBJ: case S_ETC://�̵� �Ұ����� Ÿ��/��ֹ�
					clickObject(i);
					break;

				case S_NONE:			//�̵� ������ Ÿ��
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
	//������Ʈ�� �ƹ��͵� ���� �� - ĳ���� ������
	//ĳ���� ����Ʈ�� ���������
	//ĳ���� ����Ʈ���� �����ϸ� (���� Ŭ���� ĳ���� �ε���)
	//ĳ���� ����Ʈ�� �ݰ�, ���â�� ����.

}

void battleManager::clickCharacter(int x, int y, int i)
{
	//���â�� ����. (���� ĳ������ �ε��� ����)
	int charSize = _objectMgr->getVCharacter().size();

	for (int i = 0; i < charSize; i++)
	{
		if (_objectMgr->getVCharacter()[i]->getIndexX() == x && _objectMgr->getVCharacter()[i]->getIndexY() == y)
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
	}
	//�̵� ���� Ÿ���� ������ ���� ���,
	else
	{
		//ī�޶� ��Ŀ�� �����.
		_camera->setCameraTile(_objectMgr->getVTile()[i]->pivotX, _objectMgr->getVTile()[i]->pivotY);
	}
}
