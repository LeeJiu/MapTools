#include "stdafx.h"
#include "battleUI.h"
#include "gameObjectManager.h"
#include "battleManager.h"

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
	_vOrderList.push_back("ĳ���� ����");
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
	_characterSize = 0;

	_imageStatusBack = IMAGEMANAGER->addImage("character_status", "image/ui_characterstatus_back.bmp", 300, 500, true, 0xff00ff);
	_imageBottomStatusBack = IMAGEMANAGER->addImage("bottom_status", "image/ui_battle_bottom_status.bmp", 314, 110, true, 0xff00ff);
	_imageSkillTitleBack = IMAGEMANAGER->addImage("skill_title", "image/dialog_type_title.bmp", 162, 65, false, false);
	_imageIconCharacter = IMAGEMANAGER->addImage("icon_character", "image/icon_character_fuka.bmp", 96, 96, false, false);

	_imageCharacterListTop = IMAGEMANAGER->addImage("character_list_top", "image/ui_characterList_top.bmp", 250, 50, false, false);			  //ĳ���� ��ȯ ��� â BACKGROUND IMAGE TOP
	for (int i = 0; i < _characterSize; i++)																								  //ĳ���� ��ȯ ��� â BACKGROUND IMAGE BODY~
	{																																		  //
		image* tempBody = new image;																										  //
		tempBody->init("image/ui_characterList_body.bmp", 250, 30, false, false);															  //
		_imageCharacterListBody.push_back(tempBody);																						  //
	}																																		  //~ĳ���� ��ȯ ��� â BACKGROUND IMAGE BODY
	_imageCharacterListBottom = IMAGEMANAGER->addImage("character_list_bottom", "image/ui_characterList_bottom.bmp", 250, 30, false, false);  //ĳ���� ��ȯ ��� â BACKGROUND IMAGE BOTTOM


	_imageOrderListTop = IMAGEMANAGER->addImage("orderlist_top", "image/ui_orderlist_top.bmp", 254, 29, false, false);				  //�Ϲ� ���� â ����Ʈ BACKGROUND IMAGE TOP
	for (int i = 0; i < _vOrderList.size(); i++)																					  //�Ϲ� ���� â ����Ʈ BACKGROUND IMAGE BODY
	{																																  //
		image* tempBody = new image;																								  //
		tempBody->init("image/ui_orderlist_body.bmp", 254, 30, false, false);														  //
		_imageOrderListBody.push_back(tempBody);																					  //
	}																																  //~ �Ϲ� ���� â ����Ʈ BACKGROUND IMAGE BODY
	_imageOrderListBottom = IMAGEMANAGER->addImage("orderlist_bottom", "image/ui_orderlist_bottom.bmp", 254, 30, false, false);		  //�Ϲ� ���� â ����Ʈ BACKGROUND IMAGE BOTTOM

	
	_imageUnitOrderListTop = IMAGEMANAGER->findImage("orderlist_top");																  //���� ���� â ����Ʈ BACKGROUND IMAGE TOP
	for (int i = 0; i < _unitOrderListSize; i++)																					  //���� ���� â ����Ʈ BACKGROUND IMAGE BODY
	{																																  //
		image* tempBody = new image;																								  //
		tempBody->init("image/ui_orderlist_body.bmp", 254, 30, false, false);														  //
		_imageUnitOrderListBody.push_back(tempBody);																				  //
	}																																  //~ ���� ���� â ����Ʈ BACKGROUND IMAGE BODY
	_imageUnitOrderListBottom = IMAGEMANAGER->findImage("orderlist_bottom");														  //���� ���� â ����Ʈ BACKGROUND IMAGE BOTTOM


	_rcStatus = RectMake(50, 100, _imageStatusBack->getWidth(), _imageStatusBack->getHeight());										  //ĳ���� ���� â RECT
	_rcBottomStatus = RectMake(50, WINSIZEY - 150, _imageBottomStatusBack->getWidth(), _imageBottomStatusBack->getHeight());		  //ĳ���� ���� â(�ٴ�) RECT
	_rcSkillTitle = RectMakeCenter(CENTERX, 50, _imageSkillTitleBack->getWidth(), _imageSkillTitleBack->getHeight());				  //��ų Ÿ��Ʋ RECT
	_rcIconCharacter = RectMake(_rcBottomStatus.left + 7, _rcBottomStatus.top + 7, 96, 96);											  //ĳ���� ���� â(ĳ���� ����-�ٴ�)


	_rcCharacterListTop = RectMake(WINSIZEX - 400, 50, _imageCharacterListTop->getWidth(), _imageCharacterListTop->getHeight());
	for (int i = 0; i < _characterSize; i++)
	{
		RECT tempBody = RectMake(_rcCharacterListTop.left, _rcCharacterListTop.bottom + (30 * i), 250, 30);						
		_rcCharacterListBody.push_back(tempBody);																				
																																
		RECT tempRect = RectMake(_rcCharacterListBody[i].left + 20, _rcCharacterListBody[i].top + 5, 250, 30);
		_rcCharacterListStr.push_back(tempRect);
	}
	if (_characterSize > 0)
	{
		_rcCharacterListBottom = RectMake(WINSIZEX - 400, _rcCharacterListBody[_characterSize - 1].bottom, _imageCharacterListBottom->getWidth(), _imageCharacterListBottom->getHeight());
	}
	else
	{
		_rcCharacterListBottom = RectMake(WINSIZEX - 400, _rcCharacterListTop.bottom, _imageCharacterListBottom->getWidth(), _imageCharacterListBottom->getHeight());
	}


	_rcOrderListTop = RectMake(WINSIZEX - 300, 100, _imageOrderListTop->getWidth(), _imageOrderListTop->getHeight());													//�Ϲ� ���� â TOP RECT
	for (int i = 0; i < _orderListSize; i++)																															//�Ϲ� ���� â BODY RECT~
	{																																									//
		RECT tempBody = RectMake(_rcOrderListTop.left, _rcOrderListTop.bottom + (30 * i), 254, 30);																		//
		_rcOrderListBody.push_back(tempBody);																															//
																																										//
		RECT tempRect = RectMake(_rcOrderListBody[i].left + 20, _rcOrderListBody[i].top + 5, _imageOrderListTop->getWidth(), _imageOrderListTop->getHeight());			//
		_rcOrderListStr.push_back(tempRect);																															//
	}																																									//~�Ϲ� ���� â TOP RECT
	_rcOrderListBottom = RectMake(WINSIZEX - 300, _rcOrderListBody[_orderListSize - 1].bottom, _imageOrderListBottom->getWidth(), _imageOrderListBottom->getHeight());	//�Ϲ� ���� â BOTTOM RECT


	_rcUnitOrderListTop = RectMake(WINSIZEX - 300, 100, _imageUnitOrderListTop->getWidth(), _imageUnitOrderListTop->getHeight());														   //���� ���� â TOP RECT
	for (int i = 0; i < _unitOrderListSize; i++)																																		   //���� ���� â BODY RECT~
	{																																													   //
		RECT tempBody = RectMake(_rcUnitOrderListTop.left, _rcUnitOrderListTop.bottom + (30 * i), 254, 30);																				   //
		_rcUnitOrderListBody.push_back(tempBody);																																		   //
																																														   //
		RECT tempRect = RectMake(_rcUnitOrderListBody[i].left + 20, _rcUnitOrderListBody[i].top + 5, _imageUnitOrderListTop->getWidth(), _imageUnitOrderListTop->getHeight());			   //
		_rcUnitOrderListStr.push_back(tempRect);																																		   //
	}																																													   //~���� ���� â TOP RECT
	_rcUnitOrderListBottom = RectMake(WINSIZEX - 300, _rcUnitOrderListBody[_unitOrderListSize - 1].bottom, _imageUnitOrderListBottom->getWidth(), _imageUnitOrderListBottom->getHeight()); //���� ���� â BOTTOM RECT


	_isOnStatus = false;			//ĳ���� ���� â
	_isOnCharacterList = false;		//ĳ���� ����Ʈ â
	_isOnSkillTitle = false;		//��ų Ÿ��Ʋ
	_isOnBottomStatus = false;		//ĳ���� ���� â(�ٴ�)
	_isOnOrderList = false;			//�Ϲ� ����â
	_isOnUnitOrderList = false;		//���� ����â


	IMAGEMANAGER->addImage("turnStart", "image/ui_turnback_start.bmp", 461, 54, true, 0xff00ff);	   //TURN IMAGE STAGE START
	IMAGEMANAGER->addImage("turnPlayer", "image/ui_turnback_start.bmp", 489, 53, true, 0xff00ff);	   //TURN IMAGE PLAYER TURN
	IMAGEMANAGER->addImage("turnEnemy", "image/ui_turnback_start.bmp", 476, 53, true, 0xff00ff);	   //TURN IMAGE ENEMY TURN
	IMAGEMANAGER->addImage("turnBackground", "image/ui_turnback_black.bmp", 1280, 100, false, false);  //TURN BACKGROUND(ALPHA BLACK) IMAGE

	_isTurnType = true;
	_isTurnShow = true;																				   //TURN SHOW�� �ؾ��ϴ°� ���ƾ��ϴ°��� ���� BOOL ��
	_isFirstShow = true;																			   //ó�� ������ ������ �� = TRUE	
	_turnBackPosX = 0 - WINSIZEX;																	   //TURN IMAGE�� POS X ��
	_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);								   //��� �� ������ ��� RECT
	_imageTurnStr = IMAGEMANAGER->findImage("turnStart");											   //��� �� ���� Image
	_imageTurnBack = IMAGEMANAGER->findImage("turnBackground");										   //��� �� ������ ��� Image
	_isTurnBackCenter = false;																		   //TURN IMAGE�� ���� ��� �ƴ°��� ���� BOOL ��
	_turnShowTime = 0;																				   //TURN IMAGE�� �߾ӱ��� ���� ���� �� 1�ʰ� ������Ű�� ���� TIME ��


	_imageSelectTile = IMAGEMANAGER->addImage("selectTile", "image/ui_selectTile.bmp", 192, 96, true, 0xff00ff);
	_rcSelectTile = RectMake(0, 0, 0, 0);

	_imageTurnCountBackground = IMAGEMANAGER->addImage("turnBackground", "image/ui_dialog_total", 300, 67, false, false);
	_rcTurnCountBack = RectMake(_rcOrderListTop.left, _rcOrderListTop.top - _imageTurnCountBackground->getHeight(), _imageTurnCountBackground->getWidth(), _imageTurnCountBackground->getHeight());
	_strTurnCount = 0;

	return S_OK;
}

void battleUI::release()
{
}

void battleUI::update()
{
	// ù ���̸� STAGE START�� �ѹ� �������
	if (_isFirstShow)
	{
		turnChange();
		return;
	}

	if (_isTurnShow)
	{
		turnChange();
		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//��ȯ Ÿ���� Ŭ���ߴ��� üũ����
		for (int i = 0; i < _gameObjMgr->getTile().size(); i++)
		{
			if (PtInRect(&_gameObjMgr->getTile()[i]->rc, _ptMouse))
			{
				if ((_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) >= -0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) - WIDTH / 4 &&
					(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) >= 0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) - WIDTH / 4 &&
					(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) <= -0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) + WIDTH / 4 &&
					(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) <= 0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) + WIDTH / 4)
				{

					if (_gameObjMgr->getTile()[i]->state == ZEN_POINT)
					{
						_isOnStatus = true;
						_isOnCharacterList = true;
					}
				}
			}
		}

		//ĳ���� ����Ʈ �߿� � ���� �����ߴ��� üũ����
		for (int i = 0; i < _characterSize; i++)
		{
			if (PtInRect(&_rcCharacterListBody[i], _ptMouse))
			{
				
			}
		}

		
		//�Ϲ� ����â�� �����ߴ��� üũ����
		for (int i = 0; i < _orderListSize; i++)
		{
			if (PtInRect(&_rcOrderListBody[i], _ptMouse))
			{
				orderListClick(i);
				break;
			}
		}

		//������ ����â�� �����ߴ��� üũ����
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
		_isOnCharacterList = false;
		_isOnSkillTitle = false;
		_isOnBottomStatus = false;
		_isOnOrderList = false;
		_isOnUnitOrderList = false;
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
	if (_isOnCharacterList)
	{
		_imageCharacterListTop->render(getMemDC(), _rcCharacterListTop.left, _rcCharacterListTop.top);
		if(_characterSize > 0) for (int i = 0; i < _characterSize; i++) _imageCharacterListBody[i]->render(getMemDC(), _rcCharacterListBody[i].left, _rcCharacterListBody[i].top); 
		_imageCharacterListBottom->render(getMemDC(), _rcCharacterListBottom.left, _rcCharacterListBottom.top);
		for (int i = 0; i < _characterSize; i++) DrawText(getMemDC(), TEXT(_vCharacterList[i].c_str()), -1, &_rcCharacterListStr[i], DT_LEFT | DT_VCENTER);
	}

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

void battleUI::setCharacterList()
{
	_characterSize = _gameObjMgr->getCharacter().size();
	for (int i = 0; i < _characterSize; i++)
	{
		_vCharacterList.push_back(_gameObjMgr->getCharacter()[i]->getName());
	}

	for (int i = 0; i < _characterSize; i++)																								  //ĳ���� ��ȯ ��� â BACKGROUND IMAGE BODY~
	{																																		  //
		image* tempBody = new image;																										  //
		tempBody->init("image/ui_characterList_body.bmp", 250, 30, false, false);															  //
		_imageCharacterListBody.push_back(tempBody);																						  //
	}

	for (int i = 0; i < _characterSize; i++)
	{
		RECT tempBody = RectMake(_rcCharacterListTop.left, _rcCharacterListTop.bottom + (30 * i), 250, 30);
		_rcCharacterListBody.push_back(tempBody);

		RECT tempRect = RectMake(_rcCharacterListBody[i].left + 20, _rcCharacterListBody[i].top + 5, 250, 30);
		_rcCharacterListStr.push_back(tempRect);
	}
}

void battleUI::orderListClick(int orderNumber)
{
	_isOnOrderList = false;
	switch (orderNumber)
	{
	case 1:	//���ݰ���
		_battleMgr->setActionAttack();
		break;
	case 2:	//�� ����
		_battleMgr->setTurnChange();
		break;
	case 3:	//���ʽ� ǥ

		break;
	case 4:	//ĳ���� ����

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

void battleUI::turnChange()
{
	_isTurnShow = true;

	//ù ���� �ƴ� ��
	if (!_isFirstShow)
	{
		//TURN TRUE = PLAYER TURN
		if (_isTurnType)
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
		if (! _isTurnType)
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
	_isTurnType = !_isTurnType;
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
					_isOnStatus = true;
					_isOnCharacterList = true;
					
				}
			}
		}
	}

}