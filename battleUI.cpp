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
	_vOrderList.push_back("공격개시");
	_vOrderList.push_back("턴 종료");
	_vOrderList.push_back("보너스 표");
	_vOrderList.push_back("캐릭터 명단");
	_vOrderList.push_back("전투지식");
	_vOrderList.push_back("포기");
	_vOrderList.push_back("설정");

	_vUnitOrderList.push_back("이동");
	_vUnitOrderList.push_back("공격");
	_vUnitOrderList.push_back("특수기술");
	_vUnitOrderList.push_back("? ? ? ?");
	_vUnitOrderList.push_back("방어");
	_vUnitOrderList.push_back("아이템");
	_vUnitOrderList.push_back("장비");
	_vUnitOrderList.push_back("스테이터스");

	_unitOrderListSize = _vUnitOrderList.size();
	_orderListSize = _vOrderList.size();
	_characterSize = _vCharacter.size();

	_imageStatusBack = IMAGEMANAGER->addImage("character_status", "image/ui_characterstatus_back.bmp", 300, 500, true, 0xff00ff);
	_imageBottomStatusBack = IMAGEMANAGER->addImage("bottom_status", "image/ui_battle_bottom_status.bmp", 314, 110, true, 0xff00ff);
	_imageSkillTitleBack = IMAGEMANAGER->addImage("skill_title", "image/dialog_type_title.bmp", 162, 65, false, false);
	_imageCharacterListBack = IMAGEMANAGER->addImage("character_list", "image/ui_battle_summon.bmp", 250, 300, true, 0xff00ff);
	_imageIconCharacter = IMAGEMANAGER->addImage("icon_character", "image/icon_character_fuka.bmp", 96, 96, false, false);

	_imageOrderListTop = IMAGEMANAGER->addImage("orderlist_top", "image/ui_orderlist_top.bmp", 254, 29, false, false);				  //일반 명령 창 리스트 BACKGROUND IMAGE TOP
	for (int i = 0; i < _vOrderList.size(); i++)																					  //일반 명령 창 리스트 BACKGROUND IMAGE BODY
	{																																  //
		image* tempBody = new image;																								  //
		tempBody->init("image/ui_orderlist_body.bmp", 254, 30, false, false);														  //
		_imageOrderListBody.push_back(tempBody);																					  //
	}																																  //~ 일반 명령 창 리스트 BACKGROUND IMAGE BODY
	_imageOrderListBottom = IMAGEMANAGER->addImage("orderlist_bottom", "image/ui_orderlist_bottom.bmp", 254, 30, false, false);		  //일반 명령 창 리스트 BACKGROUND IMAGE BOTTOM

	
	_imageUnitOrderListTop = IMAGEMANAGER->findImage("orderlist_top");																  //유닛 명령 창 리스트 BACKGROUND IMAGE TOP
	for (int i = 0; i < _unitOrderListSize; i++)																					  //유닛 명령 창 리스트 BACKGROUND IMAGE BODY
	{																																  //
		image* tempBody = new image;																								  //
		tempBody->init("image/ui_orderlist_body.bmp", 254, 30, false, false);														  //
		_imageUnitOrderListBody.push_back(tempBody);																				  //
	}																																  //~ 유닛 명령 창 리스트 BACKGROUND IMAGE BODY
	_imageUnitOrderListBottom = IMAGEMANAGER->findImage("orderlist_bottom");														  //유닛 명령 창 리스트 BACKGROUND IMAGE BOTTOM


	_rcStatus = RectMake(50, 100, _imageStatusBack->getWidth(), _imageStatusBack->getHeight());										  //캐릭터 상태 창 RECT
	_rcBottomStatus = RectMake(50, WINSIZEY - 150, _imageBottomStatusBack->getWidth(), _imageBottomStatusBack->getHeight());		  //캐릭터 상태 창(바닥) RECT
	_rcSkillTitle = RectMakeCenter(CENTERX, 50, _imageSkillTitleBack->getWidth(), _imageSkillTitleBack->getHeight());				  //스킬 타이틀 RECT
	_rcCharacterList = RectMake(WINSIZEX - 400, 100, _imageCharacterListBack->getWidth(), _imageCharacterListBack->getHeight());	  //캐릭터 목록 RECT
	_rcIconCharacter = RectMake(_rcBottomStatus.left + 7, _rcBottomStatus.top + 7, 96, 96);											  //캐릭터 상태 창(캐릭터 사진-바닥)

	_rcOrderListTop = RectMake(WINSIZEX - 300, 100, _imageOrderListTop->getWidth(), _imageOrderListTop->getHeight());													//일반 명령 창 TOP RECT
	for (int i = 0; i < _orderListSize; i++)																															//일반 명령 창 BODY RECT~
	{																																									//
		RECT tempBody = RectMake(_rcOrderListTop.left, _rcOrderListTop.bottom + (30 * i), 254, 30);																		//
		_rcOrderListBody.push_back(tempBody);																															//
																																										//
		RECT tempRect = RectMake(_rcOrderListBody[i].left + 20, _rcOrderListBody[i].top + 5, _imageOrderListTop->getWidth(), _imageOrderListTop->getHeight());			//
		_rcOrderListStr.push_back(tempRect);																															//
	}																																									//~일반 명령 창 TOP RECT
	_rcOrderListBottom = RectMake(WINSIZEX - 300, _rcOrderListBody[_orderListSize - 1].bottom, _imageOrderListBottom->getWidth(), _imageOrderListBottom->getHeight());	//일반 명령 창 BOTTOM RECT


	_rcUnitOrderListTop = RectMake(WINSIZEX - 300, 100, _imageUnitOrderListTop->getWidth(), _imageUnitOrderListTop->getHeight());														   //유닛 명령 창 TOP RECT
	for (int i = 0; i < _unitOrderListSize; i++)																																		   //유닛 명령 창 BODY RECT~
	{																																													   //
		RECT tempBody = RectMake(_rcUnitOrderListTop.left, _rcUnitOrderListTop.bottom + (30 * i), 254, 30);																				   //
		_rcUnitOrderListBody.push_back(tempBody);																																		   //
																																														   //
		RECT tempRect = RectMake(_rcUnitOrderListBody[i].left + 20, _rcUnitOrderListBody[i].top + 5, _imageUnitOrderListTop->getWidth(), _imageUnitOrderListTop->getHeight());			   //
		_rcUnitOrderListStr.push_back(tempRect);																																		   //
	}																																													   //~유닛 명령 창 TOP RECT
	_rcUnitOrderListBottom = RectMake(WINSIZEX - 300, _rcUnitOrderListBody[_unitOrderListSize - 1].bottom, _imageUnitOrderListBottom->getWidth(), _imageUnitOrderListBottom->getHeight()); //유닛 명령 창 BOTTOM RECT


	_isOnStatus = false;			//캐릭터 상태 창
	_isOnCharacterList = false;		//캐릭터 리스트 창
	_isOnSkillTitle = false;		//스킬 타이틀
	_isOnBottomStatus = false;		//캐릭터 상태 창(바닥)
	_isOnOrderList = false;			//일반 명령창
	_isOnUnitOrderList = false;		//유닛 명령창
	

	IMAGEMANAGER->addImage("turnStart", "image/ui_turnback_start.bmp", 461, 54, true, 0xff00ff);	   //TURN IMAGE STAGE START
	IMAGEMANAGER->addImage("turnPlayer", "image/ui_turnback_start.bmp", 489, 53, true, 0xff00ff);	   //TURN IMAGE PLAYER TURN
	IMAGEMANAGER->addImage("turnEnemy", "image/ui_turnback_start.bmp", 476, 53, true, 0xff00ff);	   //TURN IMAGE ENEMY TURN
	IMAGEMANAGER->addImage("turnBackground", "image/ui_turnback_black.bmp", 1280, 100, false, false);

	_isTurnShow = true;																				   //TURN SHOW를 해야하는가 말아야하는가에 대한 BOOL 값
	_isFirstShow = true;																			   //처음 전투에 들어왔을 시 = TRUE	
	_turnBackPosX = 0 - WINSIZEX;																	   //TURN IMAGE용 POS X 값
	_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);								   //출력 할 글자의 배경 RECT
	_imageTurnStr = IMAGEMANAGER->findImage("turnStart");											   //출력 할 글자 Image
	_imageTurnBack = IMAGEMANAGER->findImage("turnBackground");										   //출력 할 글자의 배경 Image
	_isTurnBackCenter = false;																		   //TURN IMAGE가 전부 출력 됐는가에 대한 BOOL 값
	_turnShowTime = 0;																				   //TURN IMAGE가 중앙까지 도착 했을 시 1초간 지연시키기 위한 TIME 값


	_imageSelectTile = IMAGEMANAGER->addImage("selectTile", "image/ui_selectTile.bmp", 192, 96, true, 0xff00ff);
	_rcSelectTile = RectMake(0,0,0,0);

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
	// 첫 턴이면 STAGE START를 한번 출력하자
	if (_isFirstShow)
	{
		turnChange(true);
		return;
	}

	//마우스 커서가 캐릭터가 올려져 있는 타일에 충돌했는지 체크하자
	


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//그냥 타일을 선택했는지 검사하자
		//for (int i = 0; i < 100; i++)
		//{
		//	if(PtInRect(&_gameObjMgr->get))                          ------- SELECT TILE 작업해야됨..
		//}

		//캐릭터를 선택했는지 체크하자
		//for (int i = 0; i < _characterSize; i++)
		//{
		//	if (PtInRect(&_vCharacter[i]->getCharacterRect(), _ptMouse))
		//	{
		//		_isOnCharacterList = true;
		//		break;
		//	}
		//}

		//일반 명령창을 선택했는지 체크하자
		for (int i = 0; i < _orderListSize; i++)
		{
			if (PtInRect(&_rcOrderListBody[i], _ptMouse))
			{
				orderListClick(i);
				break;
			}
		}

		//유닛의 명령창을 선택했는지 체크하자
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
	font = CreateFont(20, 0, 0, 0, 800, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
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
	_isOnOrderList = false;
	switch (orderNumber)
	{
	case 1:	//공격개시
		
		break;
	case 2:	//턴 종료
		
		turnChange(false);
		break;
	case 3:	//보너스 표

		break;
	case 4:	//캐릭터 명단

		break;
	case 5:	//전투 지식

		break;
	case 6:	//포기

		break;
	case 7:	//설정

		break;
	default:
		break;
	}
}

void battleUI::unitOrderListClick(int unitOrderNumber)
{
	switch (unitOrderNumber)
	{
	case 1:	//이동

		break;
	case 2:	//공격

		break;
	case 3:	//특수기술

		break;
	case 4:	//? ? ? ?

		break;
	case 5:	//방어

		break;
	case 6:	//아이템

		break;
	case 7:	//장비

		break;
	case 8:	//스테이터스

		break;
	default:
		break;
	}
}

void battleUI::turnChange(bool turn)
{
	_isTurnShow = true;

	//첫 턴이 아닐 때
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

	//처음 턴일 때 STAGE START 출력
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
