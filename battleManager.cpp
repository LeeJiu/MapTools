#include "stdafx.h"
#include "battleManager.h"
#include "gameObjectManager.h"

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

	return S_OK;
}

void battleManager::release()
{
	_ui->release();
	SAFE_DELETE(_ui);
}

void battleManager::update()
{
	if (!_setUI)
	{
		_ui->setCharList(_objectMgr->getVCharacter()[0]->getMercenary());
		_setUI = true;
	}

	_ui->update();

	//�÷��̾��� ���� ��
	if (_isPlayerTurn)
	{
		if(_leftButtonDown)
			keyControl();
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
	if (_ui->isOnCharList())
	{
		if (_ui->getCharIdx() != 100)
		{
			_selectCharIdx = _ui->getCharIdx();
			_ui->setCharIdx(100);
			//ĳ���� ����Ʈ�� ����.
			_ui->onCharacterList(false);
		}
	}

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
					clickCharacter();
					break;

				case S_ONENM:			//��
					clickEnemy();
					break;

				case S_ONOBJ: case S_ETC://�̵� �Ұ����� Ÿ��/��ֹ�
					clickObject();
					break;

				case S_NONE:			//�̵� ������ Ÿ��
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
	//������Ʈ�� �ƹ��͵� ���� �� - ĳ���� ������
	//ĳ���� ����Ʈ�� ���������
	//ĳ���� ����Ʈ���� �����ϸ� (���� Ŭ���� ĳ���� �ε���)
	//ĳ���� ����Ʈ�� �ݰ�, ���â�� ����.

	if (!_ui->isOnCharList())
	{
		//ĳ���� ����Ʈ�� �����ش�.
		_ui->onCharacterList(true);
	}
}

void battleManager::clickCharacter()
{
	//���â�� ����. (���� ĳ������ �ε��� ����)
	//ī�޶� ��Ŀ�� �����.

}

void battleManager::clickEnemy()
{
	//���� �ε����� �����ϰ�,
	//���õ� ĳ������ ���� ���� Ÿ���� ����.
	//->���� ����� push


	//���� ���� Ÿ���� �������� ���� ���,
	//ī�޶� ��Ŀ���� �����.

}

void battleManager::clickObject()
{
	//ī�޶� ��Ŀ���� �����.

}

void battleManager::clickTile()
{
	//�̵� ���� Ÿ���� ���� ���,
	//ĳ���� �̵��Ѵ�.


	//�̵� ���� Ÿ���� ������ ���� ���,
	//ī�޶� ��Ŀ�� �����.

}
