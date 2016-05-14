#include "stdafx.h"
#include "battleUI.h"
#include "gameObjectManager.h"

battleUI::battleUI()
{
}


battleUI::~battleUI()
{
}

HRESULT battleUI::init()
{
	_vOrderList.push_back("���ݰ���");
	_vOrderList.push_back("�� ����");
	_vOrderList.push_back("���ʽ� ǥ");
	_vOrderList.push_back("ĳ���� ���");
	_vOrderList.push_back("��������");
	_vOrderList.push_back("����");
	_vOrderList.push_back("����");

	_vUnitOrderList.push_back("�̵�");
	_vUnitOrderList.push_back("����");
	_vUnitOrderList.push_back("Ư�����");
	_vUnitOrderList.push_back("? ? ? ?");
	_vUnitOrderList.push_back("���");
	_vUnitOrderList.push_back("������");
	_vUnitOrderList.push_back("���");
	_vUnitOrderList.push_back("�������ͽ�");

	_unitOrderListSize = _vUnitOrderList.size();
	_orderListSize = _vOrderList.size();
	_characterSize = _vCharacter.size();

	_imageStatusBack = IMAGEMANAGER->addImage("character_status", "image/ui_characterstatus_back.bmp", 300, 500, true, 0xff00ff);
	_imageBottomStatusBack = IMAGEMANAGER->addImage("bottom_status", "image/ui_battle_bottom_status.bmp", 314, 110, true, 0xff00ff);
	_imageSkillTitleBack = IMAGEMANAGER->addImage("skill_title", "image/dialog_type_title.bmp", 162, 65, false, false);
	_imageCharacterListBack = IMAGEMANAGER->addImage("character_list", "image/ui_battle_summon.bmp", 250, 300, true, 0xff00ff);
	_imageIconCharacter = IMAGEMANAGER->addImage("icon_character", "image/icon_character_fuka.bmp", 96, 96, false, false);

	_imageOrderListTop = IMAGEMANAGER->addImage("orderlist_top", "image/ui_orderlist_top.bmp", 254, 29, false, false);				  //�Ϲ� ��� â ����Ʈ BACKGROUND IMAGE TOP
	for (int i = 0; i < _vOrderList.size(); i++)																					  //�Ϲ� ��� â ����Ʈ BACKGROUND IMAGE BODY
	{																																  //
		image* tempBody = new image;																								  //
		tempBody->init("image/ui_orderlist_body.bmp", 254, 30, false, false);														  //
		_imageOrderListBody.push_back(tempBody);																					  //
	}																																  //~ �Ϲ� ��� â ����Ʈ BACKGROUND IMAGE BODY
	_imageOrderListBottom = IMAGEMANAGER->addImage("orderlist_bottom", "image/ui_orderlist_bottom.bmp", 254, 30, false, false);		  //�Ϲ� ��� â ����Ʈ BACKGROUND IMAGE BOTTOM

	
	_imageUnitOrderListTop = IMAGEMANAGER->findImage("orderlist_top");
	for (int i = 0; i < _unitOrderListSize; i++)
	{
		image* tempBody = new image;
		tempBody->init("image/ui_orderlist_body.bmp", 254, 30, false, false);
		_imageUnitOrderListBody.push_back(tempBody);
	}
	_imageUnitOrderListBottom = IMAGEMANAGER->findImage("orderlist_bottom");


	_rcStatus = RectMake(50, 100, _imageStatusBack->getWidth(), _imageStatusBack->getHeight());
	_rcBottomStatus = RectMake(50, WINSIZEY - 150, _imageBottomStatusBack->getWidth(), _imageBottomStatusBack->getHeight());
	_rcSkillTitle = RectMakeCenter(CENTERX, 50, _imageSkillTitleBack->getWidth(), _imageSkillTitleBack->getHeight());
	_rcCharacterList = RectMake(WINSIZEX - 400, 100, _imageCharacterListBack->getWidth(), _imageCharacterListBack->getHeight());
	_rcIconCharacter = RectMake(_rcBottomStatus.left + 7, _rcBottomStatus.top + 7, 96, 96);

	_rcOrderListTop = RectMake(WINSIZEX - 300, 100, _imageOrderListTop->getWidth(), _imageOrderListTop->getHeight());
	for (int i = 0; i < _orderListSize; i++)
	{
		RECT tempBody = RectMake(_rcOrderListTop.left, _rcOrderListTop.bottom + (30 * i), 254, 30);
		_rcOrderListBody.push_back(tempBody);

		RECT tempRect = RectMake(_rcOrderListBody[i].left + 20, _rcOrderListBody[i].top + 5, _imageOrderListTop->getWidth(), _imageOrderListTop->getHeight());
		_rcOrderListStr.push_back(tempRect);
	}
	_rcOrderListBottom = RectMake(WINSIZEX - 300, _rcOrderListBody[_orderListSize - 1].bottom, _imageOrderListBottom->getWidth(), _imageOrderListBottom->getHeight());


	_rcUnitOrderListTop = RectMake(WINSIZEX - 300, 100, _imageUnitOrderListTop->getWidth(), _imageUnitOrderListTop->getHeight());
	for (int i = 0; i < _unitOrderListSize; i++)
	{
		RECT tempBody = RectMake(_rcUnitOrderListTop.left, _rcUnitOrderListTop.bottom + (30 * i), 254, 30);
		_rcUnitOrderListBody.push_back(tempBody);

		RECT tempRect = RectMake(_rcUnitOrderListBody[i].left + 20, _rcUnitOrderListBody[i].top + 5, _imageUnitOrderListTop->getWidth(), _imageUnitOrderListTop->getHeight());
		_rcUnitOrderListStr.push_back(tempRect);
	}
	_rcUnitOrderListBottom = RectMake(WINSIZEX - 300, _rcUnitOrderListBody[_unitOrderListSize - 1].bottom, _imageUnitOrderListBottom->getWidth(), _imageUnitOrderListBottom->getHeight());


	_isOnStatus = true;				//ĳ���� ���� â
	_isOnCharacterList = true;		//ĳ���� ����Ʈ â
	_isOnSkillTitle = false;		//��ų Ÿ��Ʋ
	_isOnBottomStatus = false;		//ĳ���� ���� â(�ٴ�)
	_isOnOrderList = false;			//�Ϲ� ���â
	_isOnUnitOrderList = false;		//���� ���â
	

	IMAGEMANAGER->addImage("turnStart", "image/ui_turnback_start.bmp", 461, 54, true, 0xff00ff);	   //TURN IMAGE STAGE START
	IMAGEMANAGER->addImage("turnPlayer", "image/ui_turnback_start.bmp", 489, 53, true, 0xff00ff);	   //TURN IMAGE PLAYER TURN
	IMAGEMANAGER->addImage("turnEnemy", "image/ui_turnback_start.bmp", 476, 53, true, 0xff00ff);	   //TURN IMAGE ENEMY TURN
	IMAGEMANAGER->addImage("turnBackground", "image/ui_turnback_black.bmp", 1280, 100, false, false);

	_isTurnShow = true;																				   //TURN SHOW�� �ؾ��ϴ°� ���ƾ��ϴ°��� ���� BOOL ��
	_isFirstShow = true;																			   //ó�� ������ ������ �� = TRUE	
	_turnBackPosX = 0 - WINSIZEX;																	   //TURN IMAGE�� POS X ��
	_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);								   //��� �� ������ ��� RECT
	_imageTurnStr = IMAGEMANAGER->findImage("turnStart");											   //��� �� ���� Image
	_imageTurnBack = IMAGEMANAGER->findImage("turnBackground");										   //��� �� ������ ��� Image
	_isTurnBackCenter = false;																		   //TURN IMAGE�� ���� ��� �ƴ°��� ���� BOOL ��
	_turnShowTime = 0;																				   //TURN IMAGE�� �߾ӱ��� ���� ���� �� 1�ʰ� ������Ű�� ���� TIME ��


	return S_OK;
}

void battleUI::release()
{
}

void battleUI::update()
{
	// ù ���̸� STAGE START�� �ѹ� �������
	if (_isFirstShow) turnChange(true);
	

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//��ȯ Ÿ���� �����ߴ��� üũ����
		if (PtInRect(&_gameObjMgr->getSummonRect(), _ptMouse))
		{
			
		}

		//ĳ���͸� �����ߴ��� üũ����
		//for (int i = 0; i < _characterSize; i++)
		//{
		//	if (PtInRect(&_vCharacter[i]->getCharacterRect(), _ptMouse))
		//	{
		//		_isOnCharacterList = true;
		//		break;
		//	}
		//}

		//�Ϲ� ���â�� �����ߴ��� üũ����
		for (int i = 0; i < _orderListSize; i++)
		{
			if (PtInRect(&_rcOrderListBody[i], _ptMouse))
			{
				orderListClick(i);
				break;
			}
		}

		//������ ���â�� �����ߴ��� üũ����
		for (int i = 0; i < _unitOrderListSize; i++)
		{
			if (PtInRect(&_rcUnitOrderListBody[i], _ptMouse))
			{
				unitOrderListClick(i);
				break;
			}
		}


	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_isOnStatus = false;
		_isOnSkillTitle = false;
		_isOnBottomStatus = false;
		_isOnCharacterList = false;
		_isOnOrderList = false;
		_isOnUnitOrderList = false;
	}

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		_isOnStatus = true;
		_isOnCharacterList = true;
	}
	

}

void battleUI::render()
{
	//Rectangle(getMemDC(), _rcStatus.left, _rcStatus.top, _rcStatus.right, _rcStatus.bottom);
	//Rectangle(getMemDC(), _rcBottomStatus.left, _rcBottomStatus.top, _rcBottomStatus.right, _rcBottomStatus.bottom);
	//Rectangle(getMemDC(), _rcIconCharacter.left, _rcIconCharacter.top, _rcIconCharacter.right, _rcIconCharacter.bottom);
	//Rectangle(getMemDC(), _rcSkillTitle.left, _rcSkillTitle.top, _rcSkillTitle.right, _rcSkillTitle.bottom);
	//Rectangle(getMemDC(), _rcOrderListTop.left, _rcOrderListTop.top, _rcOrderListTop.right, _rcOrderListTop.bottom);
	//for (int i = 0; i < _orderListSize; i++) Rectangle(getMemDC(), _rcOrderListBody[i].left, _rcOrderListBody[i].top, _rcOrderListBody[i].right, _rcOrderListBody[i].bottom);
	//Rectangle(getMemDC(), _rcOrderListBottom.left, _rcOrderListBottom.top, _rcOrderListBottom.right, _rcOrderListBottom.bottom);
	//Rectangle(getMemDC(), _rcUnitOrderListTop.left, _rcUnitOrderListTop.top, _rcUnitOrderListTop.right, _rcUnitOrderListTop.bottom);
	//for (int i = 0; i < _unitOrderListSize; i++) Rectangle(getMemDC(), _rcUnitOrderListBody[i].left, _rcUnitOrderListBody[i].top, _rcUnitOrderListBody[i].right, _rcUnitOrderListBody[i].bottom);
	//Rectangle(getMemDC(), _rcUnitOrderListBottom.left, _rcUnitOrderListBottom.top, _rcUnitOrderListBottom.right, _rcUnitOrderListBottom.bottom);

	HFONT font, oldFont;
	font = CreateFont(20, 0, 0, 0, 800, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("����"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	if(_isOnStatus) _imageStatusBack->render(getMemDC(), _rcStatus.left, _rcStatus.top);
	if(_isOnBottomStatus) _imageBottomStatusBack->render(getMemDC(), _rcBottomStatus.left, _rcBottomStatus.top);
	if(_isOnBottomStatus) _imageIconCharacter->render(getMemDC(), _rcIconCharacter.left, _rcIconCharacter.top);
	if(_isOnSkillTitle) _imageSkillTitleBack->render(getMemDC(), _rcSkillTitle.left, _rcSkillTitle.top);
	if(_isOnCharacterList) _imageCharacterListBack->render(getMemDC(), _rcCharacterList.left, _rcCharacterList.top);

	if (_isOnOrderList)
	{
		_imageOrderListTop->render(getMemDC(), _rcOrderListTop.left, _rcOrderListTop.top);
		for (int i = 0; i < _orderListSize; i++) _imageOrderListBody[i]->render(getMemDC(), _rcOrderListBody[i].left, _rcOrderListBody[i].top);
		_imageOrderListBottom->render(getMemDC(), _rcOrderListBottom.left, _rcOrderListBottom.top);
		for (int i = 0; i < _orderListSize; i++) DrawText(getMemDC(), TEXT(_vOrderList[i]), -1, &_rcOrderListStr[i], DT_LEFT | DT_VCENTER);
	}


	if (_isOnUnitOrderList)
	{
		_imageUnitOrderListTop->render(getMemDC(), _rcUnitOrderListTop.left, _rcUnitOrderListTop.top);
		for (int i = 0; i < _unitOrderListSize; i++) _imageUnitOrderListBody[i]->render(getMemDC(), _rcUnitOrderListBody[i].left, _rcUnitOrderListBody[i].top);
		_imageOrderListBottom->render(getMemDC(), _rcUnitOrderListBottom.left, _rcUnitOrderListBottom.top);
		for (int i = 0; i < _unitOrderListSize; i++) DrawText(getMemDC(), TEXT(_vUnitOrderList[i]), -1, &_rcUnitOrderListStr[i], DT_LEFT | DT_VCENTER);
	}

	
	
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	if (_isTurnShow)
	{
		//Rectangle(getMemDC(), _rcTurnBack.left, _rcTurnBack.top, _rcTurnBack.right, _rcTurnBack.bottom);
		_imageTurnBack->alphaRender(getMemDC(), _rcTurnBack.left, _rcTurnBack.top, 170);
		_imageTurnStr->render(getMemDC(), _rcTurnBack.left + 450, _rcTurnBack.top + 25);
	}

	
}

//_isOnStatus = false;
//_isOnSkillTitle = false;
//_isOnBottomStatus = false;
//_isOnCharacterList = false;
//_isOnOrderList = false;
//_isOnUnitOrderList = false;

void battleUI::orderListClick(int orderNumber)
{
	switch (orderNumber)
	{
	case 1:	//���ݰ���
		
		break;
	case 2:	//�� ����
		
		turnChange(false);
		break;
	case 3:	//���ʽ� ǥ

		break;
	case 4:	//ĳ���� ���

		break;
	case 5:	//���� ����

		break;
	case 6:	//����

		break;
	case 7:	//����

		break;
	default:
		break;
	}
}

void battleUI::unitOrderListClick(int unitOrderNumber)
{
	switch (unitOrderNumber)
	{
	case 1:	//�̵�

		break;
	case 2:	//����

		break;
	case 3:	//Ư�����

		break;
	case 4:	//? ? ? ?

		break;
	case 5:	//���

		break;
	case 6:	//������

		break;
	case 7:	//���

		break;
	case 8:	//�������ͽ�

		break;
	default:
		break;
	}
}

void battleUI::turnChange(bool turn)
{
	_isTurnShow = true;

	//ù ���� �ƴ� ��
	if (!_isFirstShow)
	{
		//TURN TRUE = PLAYER TURN
		if (turn == TRUE)
		{
			_imageTurnStr = IMAGEMANAGER->findImage("turnPlayer");
			if (!_isTurnBackCenter)
			{
				_turnBackPosX += 20;
				_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
				if (_turnBackPosX >= 0) _isTurnBackCenter = true;
			}

			if (_isTurnBackCenter)
			{
				_turnShowTime += TIMEMANAGER->getElapsedTime();
				if (_turnShowTime > 1)
				{
					_turnBackPosX += 20;
					_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
					if (_turnBackPosX > WINSIZEX) _isTurnShow = false;
				}
			}
		}

		//TURN FALSE = ENEMY TURN
		if (turn == FALSE)
		{
			_imageTurnStr = IMAGEMANAGER->findImage("turnEnemy");
			if (!_isTurnBackCenter)
			{
				_turnBackPosX += 20;
				_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
				if (_turnBackPosX >= 0) _isTurnBackCenter = true;
			}

			if (_isTurnBackCenter)
			{
				_turnShowTime += TIMEMANAGER->getElapsedTime();
				if (_turnShowTime > 1)
				{
					_turnBackPosX += 20;
					_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
					if (_turnBackPosX > WINSIZEX) _isTurnShow = false;
				}
			}
		}
	}

	//ó�� ���� �� STAGE START ���
	if (_isFirstShow)
	{
		if (!_isTurnBackCenter)
		{
			_turnBackPosX += 20;
			_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
			if (_turnBackPosX >= 0) _isTurnBackCenter = true;
		}

		if (_isTurnBackCenter)
		{
			_turnShowTime += TIMEMANAGER->getElapsedTime();
			if (_turnShowTime > 1)
			{
				_turnBackPosX += 20;
				_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);
				if (_turnBackPosX > WINSIZEX)
				{
					_isFirstShow = false;
					_isTurnShow = false;
				}
			}
		}
	}

}
