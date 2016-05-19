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

	_imageStatusBack = IMAGEMANAGER->addImage("character_status", "image/battleUI/ui_characterstatus_back.bmp", 300, 500, true, 0xff00ff);
	_imageBottomStatusBack = IMAGEMANAGER->addImage("bottom_status", "image/battleUI/ui_battle_bottom_status.bmp", 420, 150, false, false);
	_imageSkillTitleBack = IMAGEMANAGER->addImage("skill_title", "image/battleUI/dialog_type_title.bmp", 162, 65, false, false);
	_imageIconCharacter = IMAGEMANAGER->addImage("icon_character", "image/battleUI/icon_character_fuka.bmp", 110, 110, false, false);

	_imageCharacterListTop = IMAGEMANAGER->addImage("character_list_top", "image/battleUI/ui_characterList_top.bmp", 250, 50, false, false);				//캐릭터 소환 목록 창 BACKGROUND IMAGE TOP
																																							//~캐릭터 소환 목록 창 BACKGROUND IMAGE BODY
	_imageCharacterListBottom = IMAGEMANAGER->addImage("character_list_bottom", "image/battleUI/ui_characterList_bottom.bmp", 250, 30, false, false);		//캐릭터 소환 목록 창 BACKGROUND IMAGE BOTTOM
	
	_rcStatus = RectMake(50, 100, _imageStatusBack->getWidth(), _imageStatusBack->getHeight());										  //캐릭터 상태 창 RECT
	_rcBottomStatus = RectMake(50, WINSIZEY - 180, _imageBottomStatusBack->getWidth(), _imageBottomStatusBack->getHeight());		  //캐릭터 상태 창(바닥) RECT
	_rcSkillTitle = RectMakeCenter(CENTERX, 50, _imageSkillTitleBack->getWidth(), _imageSkillTitleBack->getHeight());				  //스킬 타이틀 RECT
	_rcIconCharacter = RectMake(_rcBottomStatus.left + 20, _rcBottomStatus.top + 20, 110, 110);										  //캐릭터 상태 창(캐릭터 사진-바닥)
	_rcCharacterListTop = RectMake(WINSIZEX - 400, 50, _imageCharacterListTop->getWidth(), _imageCharacterListTop->getHeight());
	_imageListArrow = IMAGEMANAGER->addImage("ui_arrow", "image/battleUI/ui_arrow.bmp", 35, 35, true, 0xff00ff);					  //Order List Arrow Image
	_rcListArrow = RectMake(0, 0, 0, 0);

	initOrderList();
	initUnitOrderList();

	_isOnStatus = false;			//출력 여부 캐릭터 상태 창
	_isOnCharacterList = false;		//출력 여부 캐릭터 리스트 창
	_isOnSkillTitle = false;		//출력 여부 스킬 타이틀
	_isOnBottomStatus = false;		//출력 여부 캐릭터 상태 창(바닥)
	_isOnOrderList = false;			//출력 여부 일반 명령창
	_isOnUnitOrderList = false;		//출력 여부 유닛 명령창
	

	IMAGEMANAGER->addImage("turnStart", "image/battleUI/ui_turnback_start.bmp", 461, 54, true, 0xff00ff);	   //TURN IMAGE STAGE START
	IMAGEMANAGER->addImage("turnPlayer", "image/battleUI/ui_turnback_player.bmp", 489, 53, true, 0xff00ff);	   //TURN IMAGE PLAYER TURN
	IMAGEMANAGER->addImage("turnEnemy", "image/battleUI/ui_turnback_enemy.bmp", 476, 53, true, 0xff00ff);	   //TURN IMAGE ENEMY TURN
	IMAGEMANAGER->addImage("turnBackground", "image/battleUI/ui_turnback_black.bmp", 1280, 100, false, false);  //TURN BACKGROUND(ALPHA BLACK) IMAGE

	_isTurnType = true;
	_isTurnShow = true;																				   //TURN SHOW를 해야하는가 말아야하는가에 대한 BOOL 값
	_isFirstShow = true;																			   //처음 전투에 들어왔을 시 = TRUE	
	_turnBackPosX = 0 - WINSIZEX;																	   //TURN IMAGE용 POS X 값
	_rcTurnBack = RectMake(_turnBackPosX, CENTERY - 50, WINSIZEX, 100);								   //출력 할 글자의 배경 RECT
	_imageTurnStr = IMAGEMANAGER->findImage("turnStart");											   //출력 할 글자 Image
	_imageTurnBack = IMAGEMANAGER->findImage("turnBackground");										   //출력 할 글자의 배경 Image
	_isTurnBackCenter = false;																		   //TURN IMAGE가 전부 출력 됐는가에 대한 BOOL 값
	_turnShowTime = 0;																				   //TURN IMAGE가 중앙까지 도착 했을 시 1초간 지연시키기 위한 TIME 값


	_imageTurnCountBackground = IMAGEMANAGER->addImage("turnCountBack", "image/battleUI/ui_turnCountBack.bmp", 254, 56, false, false);	//TURN COUNT 출력 용 IMAGE
	_rcTurnCountBack = RectMake(_rcOrderListTop.left, _rcOrderListTop.top - _imageTurnCountBackground->getHeight(),						//TURN COUNT 출력 용 RECT
								_imageTurnCountBackground->getWidth(), _imageTurnCountBackground->getHeight());							//TURN COUNT 출력 용 RECT
	_strTurnCount = 0;																													//TURN COUNT 출력 용 STR(INT)
	_rcTurnCountStr = RectMake(_rcTurnCountBack.left + 10, _rcTurnCountBack.top + 15, 100, 40);

	IMAGEMANAGER->addFrameImage("ui_arrow_blue", "image/battleUI/ui_arrow_blue.bmp", 711, 100, 9, 1, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("ui_arrow_red", "image/battleUI/ui_arrow_red.bmp", 711, 100, 9, 1, true, 0xff00ff); 
	_imageSelectTile = IMAGEMANAGER->addImage("selectTile", "image/battleUI/ui_selectTile.bmp", 128, 64, true, 0xff00ff);

	_isOnSelectTarget = false;
	_selectTargetNumber = 0;
	_isSelectCharacter = false;
	_selectCharacterNumber = 0;



	_rcStatusBottomName = RectMake(_rcBottomStatus.left + 140, _rcBottomStatus.top + 20, 200, 40);
	_progressBarHp = new progressBar;
	_progressBarHp->init(_rcBottomStatus.left + 180, _rcBottomStatus.top + 50, 210, 15, true);
	_progressBarSp = new progressBar;
	_progressBarSp->init(_rcBottomStatus.left + 180, _rcBottomStatus.top + 80, 210, 15, false);


	//_imageAttackListTop = IMAGEMANAGER->addImage();
	_imageAttackListBody;
	_imageAttackListTop;
	_rcAttackListTop;
	_rcAttackListBody;
	_rcAttackListTop;
	_rcAttackListStr;
	_vAttackList;

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
		turnChange();
		return;
	}
	
	if (_isTurnShow)
	{
		turnChange();
		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) LButtonClick();
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) RButtonClick();

	checkMouseOverCharacter();
	checkMouseOverList();

	_battleCamera->update();
	setArrowFrame();
	_count++;

	_progressBarHp->update();
	_progressBarSp->update();
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
	//for (int i = 0; i < _characterSize; i++) Rectangle(getMemDC(), _rcCharacterListBody[i].left, _rcCharacterListBody[i].top, _rcCharacterListBody[i].right, _rcCharacterListBody[i].bottom);
	//Rectangle(getMemDC(), _rcTurnCountBack.left, _rcTurnCountBack.top, _rcTurnCountBack.right, _rcTurnCountBack.bottom);

	HFONT font, oldFont;
	font = CreateFont(20, 0, 0, 0, 800, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	if(_isOnStatus) _imageStatusBack->render(getMemDC(), _rcStatus.left, _rcStatus.top);
	if (_isOnBottomStatus)
	{
		_imageBottomStatusBack->render(getMemDC(), _rcBottomStatus.left, _rcBottomStatus.top);
		_imageIconCharacter->render(getMemDC(), _rcIconCharacter.left, _rcIconCharacter.top);
		DrawText(getMemDC(), TEXT(_statusBottomName), -1, &_rcStatusBottomName, DT_LEFT | DT_VCENTER);
		_progressBarHp->render();
		_progressBarSp->render();
	}
	if(_isOnSkillTitle) _imageSkillTitleBack->render(getMemDC(), _rcSkillTitle.left, _rcSkillTitle.top);

	// 케릭터 리스트 출력
	if (_isOnCharacterList)
	{
		_imageCharacterListTop->render(getMemDC(), _rcCharacterListTop.left, _rcCharacterListTop.top);

		if (_characterSize > 0) for (int i = 0; i < _characterSize; i++)
		{
			_imageCharacterListBody[i]->render(getMemDC(), _rcCharacterListBody[i].left, _rcCharacterListBody[i].top);
		}

		for (int i = 0; i < _characterSize; i++)
		{
			_imageCharacterListBody[i]->render(getMemDC(), _rcCharacterListBody[i].left, _rcCharacterListBody[i].top);
		}

		_imageCharacterListBottom->render(getMemDC(), _rcCharacterListBottom.left, _rcCharacterListBottom.top);

		for (int i = 0; i < _characterSize; i++)
		{
			DrawText(getMemDC(), TEXT(_vCharacterList[i].c_str()), -1, &_rcCharacterListStr[i], DT_LEFT | DT_VCENTER);
		}

		if(_IsOnListArrow) _imageListArrow->render(getMemDC(), _rcListArrow.left, _rcListArrow.top);
	}

	if (_isOnOrderList)
	{
		_imageOrderListTop->render(getMemDC(), _rcOrderListTop.left, _rcOrderListTop.top);
		for (int i = 0; i < _orderListSize; i++) _imageOrderListBody[i]->render(getMemDC(), _rcOrderListBody[i].left, _rcOrderListBody[i].top);
		_imageOrderListBottom->render(getMemDC(), _rcOrderListBottom.left, _rcOrderListBottom.top);
		for (int i = 0; i < _orderListSize; i++) DrawText(getMemDC(), TEXT(_vOrderList[i]), -1, &_rcOrderListStr[i], DT_LEFT | DT_VCENTER);
		_imageTurnCountBackground->render(getMemDC(), _rcTurnCountBack.left, _rcTurnCountBack.top);

		_strTurnCount = " 턴 : ";
		//strcat(_strTurnCount, itoa(_battleMgr->getTurnCount(), _strTurnCount, 10));
		DrawText(getMemDC(), TEXT(_strTurnCount), -1, &_rcTurnCountStr, DT_LEFT|DT_VCENTER);
		if (_IsOnListArrow) _imageListArrow->render(getMemDC(), _rcListArrow.left, _rcListArrow.top);
	}


	if (_isOnUnitOrderList)
	{
		_imageUnitOrderListTop->render(getMemDC(), _rcUnitOrderListTop.left, _rcUnitOrderListTop.top);
		for (int i = 0; i < _unitOrderListSize; i++) _imageUnitOrderListBody[i]->render(getMemDC(), _rcUnitOrderListBody[i].left, _rcUnitOrderListBody[i].top);
		_imageOrderListBottom->render(getMemDC(), _rcUnitOrderListBottom.left, _rcUnitOrderListBottom.top);
		for (int i = 0; i < _unitOrderListSize; i++) DrawText(getMemDC(), TEXT(_vUnitOrderList[i]), -1, &_rcUnitOrderListStr[i], DT_LEFT | DT_VCENTER);
		if (_IsOnListArrow) _imageListArrow->render(getMemDC(), _rcListArrow.left, _rcListArrow.top);
	}

	
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	
	// 스테이지시작, 에너미턴, 플레이어턴 출력
	if (_isTurnShow)
	{
		//Rectangle(getMemDC(), _rcTurnBack.left, _rcTurnBack.top, _rcTurnBack.right, _rcTurnBack.bottom);
		_imageTurnBack->alphaRender(getMemDC(), _rcTurnBack.left, _rcTurnBack.top, 170);
		_imageTurnStr->render(getMemDC(), _rcTurnBack.left + 450, _rcTurnBack.top + 25);
	}

	_IsOnListArrow = false;
}

void battleUI::setCharacterList()
{
	_characterSize = _gameObjMgr->getCharSize();
	for (int i = 0; i < _characterSize; i++)
	{
		_vCharacterList.push_back(_gameObjMgr->getGameObject()[i]->getName());
	}

	for (int i = 0; i < _characterSize; i++)										 
	{
		image* tempBody = new image;
		tempBody->init("image/battleUI/ui_characterList_body.bmp", 250, 30, false, false);
		_imageCharacterListBody.push_back(tempBody);
	}

	for (int i = 0; i < _characterSize; i++)
	{
		RECT tempBody = RectMake(_rcCharacterListTop.left, _rcCharacterListTop.bottom + (30 * i), 250, 30);
		_rcCharacterListBody.push_back(tempBody);

		RECT tempRect = RectMake(_rcCharacterListBody[i].left + 20, _rcCharacterListBody[i].top + 5, 250, 30);
		_rcCharacterListStr.push_back(tempRect);
	}
}

void battleUI::initOrderList()
{
	_imageOrderListTop = IMAGEMANAGER->addImage("orderlist_top", "image/battleUI/ui_orderlist_top.bmp", 254, 29, false, false);					//일반 명령 창 리스트 BACKGROUND IMAGE TOP
	for (int i = 0; i < _vOrderList.size(); i++)																								//일반 명령 창 리스트 BACKGROUND IMAGE BODY
	{																																			//
		image* tempBody = new image;																											//
		tempBody->init("image/battleUI/ui_orderlist_body.bmp", 254, 30, false, false);															//
		_imageOrderListBody.push_back(tempBody);																								//
	}																																			//~ 일반 명령 창 리스트 BACKGROUND IMAGE BODY
	_imageOrderListBottom = IMAGEMANAGER->addImage("orderlist_bottom", "image/battleUI/ui_orderlist_bottom.bmp", 254, 30, false, false);		//일반 명령 창 리스트 BACKGROUND IMAGE BOTTOM

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

}

void battleUI::initUnitOrderList()
{	
	_imageUnitOrderListTop = IMAGEMANAGER->findImage("orderlist_top");																  //유닛 명령 창 리스트 BACKGROUND IMAGE TOP
	for (int i = 0; i < _unitOrderListSize; i++)																					  //유닛 명령 창 리스트 BACKGROUND IMAGE BODY
	{																																  //
		image* tempBody = new image;																								  //
		tempBody->init("image/battleUI/ui_orderlist_body.bmp", 254, 30, false, false);												  //
		_imageUnitOrderListBody.push_back(tempBody);																				  //
	}																																  //~ 유닛 명령 창 리스트 BACKGROUND IMAGE BODY
	_imageUnitOrderListBottom = IMAGEMANAGER->findImage("orderlist_bottom");														  //유닛 명령 창 리스트 BACKGROUND IMAGE BOTTOM

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
}

//타일에 마우스 오버 랩 시 Blue Arrow 출력
void battleUI::renderOverlapSelectTile()
{
	if (!_isOnCharacterList)
	{
		//공격 타일을 출력 중이 아닌 상태일 때
		if (!_isOnSelectTarget)
		{
			// 셀렉트 타일 + 케릭터 위 에로우출력
			for (int i = 0; i < TOTALTILE(TILENUM); i++)
			{
				if (PtInRect(&_gameObjMgr->getTile()[i]->rc, _ptMouse))
				{
					if ((_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) >= -0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) - WIDTH / 4 &&
						(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) >= 0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) - WIDTH / 4 &&
						(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) <= -0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) + WIDTH / 4 &&
						(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) <= 0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) + WIDTH / 4)
					{
						_imageSelectTile->render(getMemDC(), _gameObjMgr->getTile()[i]->rc.left, _gameObjMgr->getTile()[i]->rc.top);
						IMAGEMANAGER->findImage("ui_arrow_blue")->frameRender(getMemDC(), (_gameObjMgr->getTile()[i]->rc.left + _gameObjMgr->getTile()[i]->rc.right) / 2 - IMAGEMANAGER->findImage("ui_arrow_blue")->getFrameWidth() / 2
							, _gameObjMgr->getTile()[i]->rc.top - IMAGEMANAGER->findImage("ui_arrow_blue")->getFrameHeight() - 80, IMAGEMANAGER->findImage("ui_arrow_blue")->getFrameX(), IMAGEMANAGER->findImage("ui_arrow_blue")->getFrameY());
					}
				}
			}
		}

		//공격 타일을 출력 중이라면 SelectTile을 선택한 캐릭터 위치로 고정시키자
		if (_isOnSelectTarget)
		{
			int tempX = _gameObjMgr->getGameObject()[_selectCharacterNumber]->getIndexX();
			int tempY = _gameObjMgr->getGameObject()[_selectCharacterNumber]->getIndexY();
			int index = tempY * TILENUM + tempX;

			_imageSelectTile->render(getMemDC(), _gameObjMgr->getTile()[index]->rc.left, _gameObjMgr->getTile()[index]->rc.top);
			IMAGEMANAGER->findImage("ui_arrow_blue")->frameRender(getMemDC(),
				(_gameObjMgr->getTile()[index]->rc.left + _gameObjMgr->getTile()[index]->rc.right) / 2 - IMAGEMANAGER->findImage("ui_arrow_blue")->getFrameWidth() / 2
				, _gameObjMgr->getTile()[index]->rc.top - IMAGEMANAGER->findImage("ui_arrow_blue")->getFrameHeight() - 80,
				IMAGEMANAGER->findImage("ui_arrow_blue")->getFrameX(),
				IMAGEMANAGER->findImage("ui_arrow_blue")->getFrameY());
		}
	}
}

//공격 타일 출력 시 적 위에 마우스가 오버 랩 되면 Red Arrow 출력
void battleUI::renderOverlapAttackSelectTile()
{
	if (_isOnSelectTarget)
	{
		for (int i = 0; i < TOTALTILE(TILENUM); i++)
		{
			if (PtInRect(&_gameObjMgr->getTile()[i]->rc, _ptMouse))
			{
				if ((_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) >= -0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) - WIDTH / 4 &&
					(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) >= 0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) - WIDTH / 4 &&
					(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) <= -0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) + WIDTH / 4 &&
					(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) <= 0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) + WIDTH / 4)
				{
					if (_gameObjMgr->getTile()[i]->state == S_ONENM)
					{
						_imageSelectTile->render(getMemDC(), _gameObjMgr->getTile()[i]->rc.left, _gameObjMgr->getTile()[i]->rc.top);
						IMAGEMANAGER->findImage("ui_arrow_red")->frameRender(getMemDC(),
							(_gameObjMgr->getTile()[i]->rc.left + _gameObjMgr->getTile()[i]->rc.right) / 2 - IMAGEMANAGER->findImage("ui_arrow_red")->getFrameWidth() / 2
							, _gameObjMgr->getTile()[i]->rc.top - IMAGEMANAGER->findImage("ui_arrow_red")->getFrameHeight() - 80,
							IMAGEMANAGER->findImage("ui_arrow_red")->getFrameX(),
							IMAGEMANAGER->findImage("ui_arrow_red")->getFrameY());
					}
				}
			}
		}		
	}
}

void battleUI::orderListClick(int orderNumber)
{
	_isOnOrderList = false;
	switch (orderNumber)
	{
	case 0:	//공격개시
		_battleMgr->doActionAttack();
		break;
	case 1:	//턴 종료
		_isTurnType = _battleMgr->getTurnType();
		turnChange();
		_battleMgr->setTurnChange();
		break;
	case 2:	//보너스 표

		break;
	case 3:	//캐릭터 명단

		break;
	case 4:	//전투 지식

		break;
	case 5:	//포기
		SCENEMANAGER->changeScene("town");
		break;
	case 6:	//설정

		break;
	default:
		break;
	}
}

void battleUI::unitOrderListClick(int unitOrderNumber)
{
	_isOnUnitOrderList = false;
	switch (unitOrderNumber)
	{
	case 0:	//이동
		_gameObjMgr->getGameObject()[_selectCharacterNumber]->setIsShowPossibleMoveTile(true);
		break;
	case 1:	//공격
		_isOnSelectTarget = true;
		_gameObjMgr->getGameObject()[_selectCharacterNumber]->setIsShowPossibleAttackTile(true);
		break;
	case 2:	//특수기술

		break;
	case 3:	//? ? ? ?

		break;
	case 4:	//방어

		break;
	case 5:	//아이템

		break;
	case 6:	//장비

		break;
	case 7:	//스테이터스

		break;
	default:
		break;
	}
}

void battleUI::turnChange()
{
	_isTurnShow = true;

	//첫 턴이 아닐 때
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
					if (_turnBackPosX > WINSIZEX)
					{
						_isTurnShow = false;
						_turnBackPosX = 0 - WINSIZEX;
						_turnShowTime = 0;
						_isTurnBackCenter = false;
					}
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
					if (_turnBackPosX > WINSIZEX)
					{
						_isTurnShow = false;
						_turnBackPosX = 0 - WINSIZEX;
						_turnShowTime = 0;
						_isTurnBackCenter = false;
					}

				}
			}
		}
	}
	//_isTurnType = !_isTurnType;
	

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
					_isOnStatus = false;
					_isOnCharacterList = false;
					_turnBackPosX = 0 - WINSIZEX;
					_turnShowTime = 0;
					_isTurnBackCenter = false;
					
				}
			}
		}
	}

}

//마우스 왼쪽 버튼 클릭 이벤트
void battleUI::LButtonClick()
{
	//캐릭터 소환 리스트가 켜져 있는 상태
	if (_isOnCharacterList)
	{
		//캐릭터 리스트 중에 어떤 것을 선택했는지 체크하자
		for (int i = 0; i < _characterSize; i++)
		{
			if (PtInRect(&_rcCharacterListBody[i], _ptMouse))
			{
				_gameObjMgr->getGameObject()[i]->setIsShow(true);
				_isOnStatus = false;
				_isOnCharacterList = false;
				return;
			}
		}
	}

	//일반 명령창이 켜져 있는 상태
	if (_isOnOrderList)
	{
		//일반 명령창을 선택했는지 체크하자
		for (int i = 0; i < _orderListSize; i++)
		{
			if (PtInRect(&_rcOrderListBody[i], _ptMouse))
			{
				orderListClick(i);
				_isOnOrderList = false;
				return;
			}
		}
	}

	//유닛 명령창이 켜져 있는 상태
	if (_isOnUnitOrderList)
	{
		//유닛의 명령창을 선택했는지 체크하자
		for (int i = 0; i < _unitOrderListSize; i++)
		{
			if (PtInRect(&_rcUnitOrderListBody[i], _ptMouse))
			{
				unitOrderListClick(i);
				return;
			}
		}
	}
	
	//if (_gameObjMgr->getGameObject()[i]->getIsShow())
	//{
	//	_selectCharacterNumber = i;
	//	_isSelectCharacter = true;
	//	_isOnUnitOrderList = true;
	//	_battleCamera->setCameraTile(_gameObjMgr->getGameObject()[_selectCharacterNumber]->getIndexX(), _gameObjMgr->getGameObject()[_selectCharacterNumber]->getIndexY());
	//	return;
	//}
	//else
	//{
	//	_isSelectCharacter = false;
	//	_selectCharacterNumber = 0;
	//	_isSelectCharacter = false;
	//	_isOnUnitOrderList = false;
	//}

	//타일을 클릭했는지 체크하자
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		if (PtInRect(&_gameObjMgr->getTile()[i]->rc, _ptMouse))
		{
			if ((_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) > -0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) - WIDTH / 4 &&
				(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) >  0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) - WIDTH / 4 &&
				(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) < -0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) + WIDTH / 4 &&
				(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) <  0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) + WIDTH / 4)
			{
				//소환 타일을 선택했는지 체크하자
				if (_gameObjMgr->getTile()[i]->state == ZEN_POINT)
				{
					_isOnStatus = true;
					_isOnCharacterList = true;
				}
				else
				{
					_isOnStatus = false;
					_isOnCharacterList = false;
				}

				if (!_isSelectCharacter)
				{
					for (int j = 0; j < _characterSize; j++)
					{
						if (_gameObjMgr->getGameObject()[j]->getIndexX() == _gameObjMgr->getTile()[i]->x
							&& _gameObjMgr->getGameObject()[j]->getIndexY() == _gameObjMgr->getTile()[i]->y)
						{
							_selectCharacterNumber = j;
							_isSelectCharacter = true;
							_isOnUnitOrderList = true;
							_battleCamera->setCameraTile(_gameObjMgr->getGameObject()[_selectCharacterNumber]->getIndexX(), _gameObjMgr->getGameObject()[_selectCharacterNumber]->getIndexY());
							break;
						}
					}				
				}

				else
				{
					//선택한 캐릭터의 MOVE SHOW가 FALSE인지 체크하자
					if (!_gameObjMgr->getGameObject()[_selectCharacterNumber]->getIsShowPossibleMoveTile()
						&& !_gameObjMgr->getGameObject()[_selectCharacterNumber]->getIsShowPossibleAttackTile())
					{
						//캐릭터의 MOVE SHOW 가 FALSE라면 카메라를 해당 캐릭터의 위치로 포커스를 잡는다
						_isOnOrderList = false;
						_battleCamera->setCameraTile(_gameObjMgr->getTile()[i]->x, _gameObjMgr->getTile()[i]->y);
						_isOnUnitOrderList = true;
					}


					// 케릭터의 이동 가능한 타일이 보여진다면
					else if (_gameObjMgr->getGameObject()[_selectCharacterNumber]->getIsShowPossibleMoveTile())
					{
						// 케릭터 이동 함수를 호출한다
						_gameObjMgr->setUnitMove(_selectCharacterNumber, _gameObjMgr->getTile()[i]->x, _gameObjMgr->getTile()[i]->y);
						// 이동가능한 타일을 꺼준다
						_gameObjMgr->getGameObject()[_selectCharacterNumber]->setIsShowPossibleMoveTile(false);
						_isSelectCharacter = false;
					}


					// 캐릭터의 공격 가능한 타일이 보여진다면
					else if (_gameObjMgr->getGameObject()[_selectCharacterNumber]->getIsShowPossibleAttackTile())
					{
						_battleMgr->setCharacterAttack(_selectCharacterNumber, _gameObjMgr->getTile()[i]->x, _gameObjMgr->getTile()[i]->y);
						_gameObjMgr->getGameObject()[_selectCharacterNumber]->setIsShowPossibleAttackTile(false);
						_isOnUnitOrderList = false;
						_isSelectCharacter = false;
					}
				}
				
			}
		}
	}
}

//마우스 오른쪽 버튼 클릭 이벤트
void battleUI::RButtonClick()
{
	if (!_isOnStatus && !_isOnCharacterList && !_isOnSkillTitle &&
		!_isOnBottomStatus&& !_isOnOrderList && !_isOnUnitOrderList)
	{
		_isOnOrderList = true;
	}
	else
	{
		_isOnStatus			= false;
		_isOnSkillTitle		= false;
		_isOnBottomStatus	= false;
		_isOnCharacterList	= false;
		_isOnOrderList		= false;
		_isOnUnitOrderList	= false;
		_isOnSelectTile		= false;
		_isOnSelectTarget	= false;
		_isSelectCharacter	= false;
		_gameObjMgr->getGameObject()[_selectCharacterNumber]->setIsShowPossibleAttackTile(false);
		_gameObjMgr->getGameObject()[_selectCharacterNumber]->setIsShowPossibleMoveTile(false);
	}
}

//리스트에 마우스가 올려져있는지 확인하고 ARROW 출력
void battleUI::checkMouseOverList()
{
	if (_isOnCharacterList)
	{
		for (int i = 0; i < _characterSize; i++)
		{
			if (PtInRect(&_rcCharacterListBody[i], _ptMouse))
			{
				_rcListArrow = RectMake(_rcCharacterListBody[i].left - _imageListArrow->getWidth() / 2, _rcCharacterListBody[i].top, _imageListArrow->getWidth(), _imageListArrow->getHeight());
				_IsOnListArrow = true;
			}
		}
	}
	else if (_isOnOrderList)
	{
		for (int i = 0; i < _orderListSize; i++)
		{
			if (PtInRect(&_rcOrderListBody[i], _ptMouse))
			{
				_rcListArrow = RectMake(_rcOrderListBody[i].left - _imageListArrow->getWidth() / 2, _rcOrderListBody[i].top, _imageListArrow->getWidth(), _imageListArrow->getHeight());
				_IsOnListArrow = true;
			}
		}
	}
	else if (_isOnUnitOrderList)
	{
		for (int i = 0; i < _unitOrderListSize; i++)
		{
			if (PtInRect(&_rcUnitOrderListBody[i], _ptMouse))
			{
				_rcListArrow = RectMake(_rcUnitOrderListBody[i].left - _imageListArrow->getWidth() / 2, _rcUnitOrderListBody[i].top, _imageListArrow->getWidth(), _imageListArrow->getHeight());
				_IsOnListArrow = true;
			}
		}
	}
	else _IsOnListArrow = false;
}

//마우스 커서가 캐릭터에 오버 랩 되어있으면 캐릭터 상태 창(바닥)을 출력
void battleUI::checkMouseOverCharacter()
{	
	for (int i = 0; i < TILENUM * TILENUM; i++)
	{
		if (_gameObjMgr->getTile()[i]->state == S_ONCHAR || _gameObjMgr->getTile()[i]->state == S_ZEN)
		{
			if (PtInRect(&_gameObjMgr->getTile()[i]->rc, _ptMouse))
			{
				if ((_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) > -0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) - WIDTH / 4 &&
					(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) > 0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) - WIDTH / 4 &&
					(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) < -0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) + WIDTH / 4 &&
					(_ptMouse.y - _gameObjMgr->getTile()[i]->pivotY) < 0.5 * (_ptMouse.x - _gameObjMgr->getTile()[i]->pivotX) + WIDTH / 4)
				{
					for (int j = 0; j < _characterSize; j++)
					{
						if (_gameObjMgr->getGameObject()[j]->getIsShow())
						{
							if (PtInRect(&_gameObjMgr->getGameObject()[j]->getCharacterRect(), _ptMouse))
							{
								_isOnBottomStatus = true;
								_statusBottomName = _gameObjMgr->getGameObject()[j]->getName();
								_progressBarHp->gauge(_gameObjMgr->getGameObject()[j]->getHp(), 100);
								_progressBarSp->gauge(_gameObjMgr->getGameObject()[j]->getSp(), 100);
							}							
						}

					}
				}
			}
			else
			{
				_isOnBottomStatus = false;
			}
		}
	}	

	
}

void battleUI::setArrowFrame()
{
	if (_count % 5 == 0)
	{
		IMAGEMANAGER->findImage("ui_arrow_blue")->setFrameX(IMAGEMANAGER->findImage("ui_arrow_blue")->getFrameX() + 1);

		if (IMAGEMANAGER->findImage("ui_arrow_blue")->getFrameX() >= IMAGEMANAGER->findImage("ui_arrow_blue")->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("ui_arrow_blue")->setFrameX(0);
		}

		IMAGEMANAGER->findImage("ui_arrow_red")->setFrameX(IMAGEMANAGER->findImage("ui_arrow_red")->getFrameX() + 1);
		if (IMAGEMANAGER->findImage("ui_arrow_red")->getFrameX() >= IMAGEMANAGER->findImage("ui_arrow_red")->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("ui_arrow_red")->setFrameX(0);
		}

	}
}

void battleUI::setCamera()
{
	_battleCamera = new battleCamera;
	_battleCamera->init(_gameObjMgr->getTile());
}

void battleUI::setGameObjectSize()
{
	_characterSize = _gameObjMgr->getCharSize();
	for (int i = 0; i < _characterSize; i++)											//캐릭터 소환 목록 창 BACKGROUND IMAGE BODY~													  
	{																					//													  
		image* tempBody = new image;													//													  
		tempBody->init("image/battleUI/ui_characterList_body.bmp", 250, 30, false, false);		//													  
		_imageCharacterListBody.push_back(tempBody);									//													  
	}

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
}
