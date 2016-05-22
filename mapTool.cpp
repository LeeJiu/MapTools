#include "stdafx.h"
#include "mapTool.h"


//저장-> 스테이트, 이미지, 넘버, 피벗, 맵네임

mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	setSampleTile();
	setSampleObject();
	setSampleEnemy();

	setTile();
	setObject();
	setEnemy();
	setFirstRender();

	//버튼이미지들
	IMAGEMANAGER->addFrameImage("stageButton", "image/mapTool/button.bmp", 64, 32, 2, 1, true, 0xff00ff);
	IMAGEMANAGER->addImage("tileB", "image/mapTool/tileButton.bmp", 104, 44, false, false);
	IMAGEMANAGER->addImage("objectB", "image/mapTool/objectButton.bmp", 104, 44, false, false);
	IMAGEMANAGER->addImage("enemyB", "image/mapTool/enemyButton.bmp", 104, 44, false, false);
	IMAGEMANAGER->addImage("exitB", "image/mapTool/exitButton.bmp", 104, 44, false, false);

	//맵타일 이미지
	IMAGEMANAGER->addFrameImage("tile", "image/mapTile.bmp", 208, 156, 4, 3, false, false);


	_TileButton = new button;
	_TileButton->init("tileB", 90, 35, PointMake(0, 0), PointMake(0, 0), onTile);

	_ObjectButton = new button;
	_ObjectButton->init("objectB", 200, 35, PointMake(0, 0), PointMake(0, 0), onObject);

	_EnemyButton = new button;
	_EnemyButton->init("enemyB", 90, 85, PointMake(0, 0), PointMake(0, 0), onEnemy);

	_ExitButton = new button;
	_ExitButton->init("exitB", 200, 85, PointMake(0, 0), PointMake(0, 0), goToMenu);

	_StageBefore = new button;
	_StageBefore->init("stageButton", 110, 140, PointMake(0, 0), PointMake(0, 0), stageBack);

	_StageAfter = new button;
	_StageAfter->init("stageButton", 170, 140, PointMake(1, 0), PointMake(1, 0), stageNext);

	selectedImage = IMAGEMANAGER->findImage("tile");

	///////////////////////////////////////////////////////////////////////////////////////////////////

	rcUI = RectMake(0, 0, 300, WINSIZEY);
	rcSelectTile = RectMake(5, 5, 290, 160);

	///////////////////////////////////////////////////////////////////////////////////////////////////


	tileNum = 0;   //샘플타일 타일넘버
	_pickNum = 0;   //찍어줄 타일넘버


	return S_OK;
}
///////////////////////////////////////////////////////////인잇 끝////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////릴리즈////////////////////////////////////////////////////////////////////
void mapTool::release()
{
	//타일벡터 이미지 지우자
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		if (!(*_viTile)->image)
			SAFE_DELETE((*_viTile)->image);
	}
	//타일벡터 클리어
	_vTile.clear();

	//오브젝트 벡터 이미지 지우자
	for (_viObj = _vObj.begin(); _viObj != _vObj.end(); ++_viObj)
	{
		if (!(*_viObj)->image)
			SAFE_DELETE((*_viObj)->image);
	}
	//오브젝트 벡터 클리어
	_vObj.clear();

	//적벡터 이미지 지우자
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		if (!(*_viEnemy)->image)
			SAFE_DELETE((*_viEnemy)->image);
	}
	//적벡터 클리어
	_vEnemy.clear();

	//랜더벡터 이미지 지우자
	for (_viRender = _vRender.begin(); _viRender != _vRender.end(); ++_viRender)
	{
		if (!(*_viRender)->image)
			SAFE_DELETE((*_viRender)->image);
	}
	//랜더벡터 클리어
	_vRender.clear();

}
///////////////////////////////////////////////////////////릴리즈 끝////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////업데이트////////////////////////////////////////////////////////////////////
void mapTool::update()
{
	keyControl();
	setPickNum();
	setRender();

	_ObjectButton->update();
	_TileButton->update();
	_EnemyButton->update();
	_ExitButton->update();
	_StageAfter->update();
	_StageBefore->update();
}	
///////////////////////////////////////////////////////////업데이트 끝////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////랜더////////////////////////////////////////////////////////////////////
void mapTool::render()
{
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	char str[128];

	//각각의 렉트 출력
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		IsoRender(getMemDC(), _vTile[i]->rc);

		if (_vTile[i]->draw)
		{
			_vTile[i]->image->frameRender(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top/* - OFFSET*/);
		}

		sprintf_s(str, "%d, %d", _vTile[i]->x, _vTile[i]->y);
		TextOut(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top, str, strlen(str));
		sprintf_s(str, "%d", _vTile[i]->state);
		TextOut(getMemDC(), _vTile[i]->rc.left, _vTile[i]->rc.top + 15, str, strlen(str));

		int _vRenderSize = 0;
		int objrender = 0;
		int enmrender = 0;
		for (int i = 0; i < TOTALTILE(TILENUM); i++)
		{
			if (_vRender[i]->draw) _vRenderSize++;
			if (_vRender[i]->state == S_NOMAL || _vRender[i]->state == S_ZEN) objrender++;
			if (_vRender[i]->state == E_NORMAL || _vRender[i]->state == E_BOSS) enmrender++;
		}

		sprintf_s(str, "vTile size = %d, vObj size = %d vEnm size =%d _vRender = %d", _vTile.size(), objrender, enmrender, _vRenderSize);
		//sprintf_s(str, "vTile size = %d, vObj size = %d vEnm size =%d _vRender = %d", _vTile.size(), _vObj.size(), _vEnemy.size(), _vRenderSize);
		TextOut(getMemDC(), CENTERX - 200, 10, str, strlen(str));
		sprintf_s(str, "pickNum = %d", _pickNum);
		TextOut(getMemDC(), CENTERX - 150, 25, str, strlen(str));
	}

	//오브젝트 출려어어엉ㄱ
	sort(_vRender.begin(), _vRender.end(), OBJ_Y_RENDER());
	for (int i = 0; i < TILENUM * TILENUM; i++)
	{
		if (_vRender[i]->draw)
		{
			//Rectangle(getMemDC(), _vRender[i]->rc.left, _vRender[i]->rc.top, _vRender[i]->rc.right, _vRender[i]->rc.bottom);
			_vRender[i]->image->frameRender(getMemDC(), _vRender[i]->rc.left, _vRender[i]->rc.top);
	
			sprintf_s(str, "number = %d", _vRender[i]->number);
			TextOut(getMemDC(), _vRender[i]->rc.left, _vRender[i]->rc.top, str, strlen(str));
		}
	}


	///////////////////////////////////////////////////////////////////////////////

	Rectangle(getMemDC(), rcUI.left, rcUI.top, rcUI.right, rcUI.bottom);
	Rectangle(getMemDC(), rcSelectTile.left, rcSelectTile.top, rcSelectTile.right, rcSelectTile.bottom);

	///////////////////////////////////////////////////////////////////////////////

	// 버튼 랜더
	_ObjectButton->render();
	_TileButton->render();
	_EnemyButton->render();
	_ExitButton->render();
	_StageAfter->render();
	_StageBefore->render();

	sprintf_s(str, "%d", _stage);
	TextOut(getMemDC(), 136, 130, str, strlen(str));

	//타일샘플
	if (_state == SET_TILE)
	{
		for (int i = tileNum * 4; i < tileNum * 4 + 4; i++)
		{
			Rectangle(getMemDC(), _vIsoTile[i]->rc.left, _vIsoTile[i]->rc.top, _vIsoTile[i]->rc.right, _vIsoTile[i]->rc.bottom);
			_vIsoTile[i]->image->frameRender(getMemDC(), _vIsoTile[i]->rc.left, _vIsoTile[i]->rc.top);
			sprintf_s(str, "tileNum = %d", i);
			TextOut(getMemDC(), _vIsoTile[i]->rc.left, _vIsoTile[i]->rc.top, str, strlen(str));
		}
	}

	//오브젝트 샘플
	if (_state == SET_OBJ)
	{
		int vIsoOSize = _vIsoObj.size();
		for (int i = 0; i < vIsoOSize; i++)
		{
			_vIsoObj[i]->image->frameRender(getMemDC(), _vIsoObj[i]->rc.left, _vIsoObj[i]->rc.top);

			sprintf_s(str, "objNum = %d", _vIsoObj[i]->number);
			TextOut(getMemDC(), _vIsoObj[i]->rc.left, _vIsoObj[i]->rc.top, str, strlen(str));
		}
	}

	//적 샘플
	if (_state == SET_ENM)
	{
		int vIsoESize = _vIsoEnemy.size();
		for (int i = 0; i < vIsoESize; i++)
		{
			_vIsoEnemy[i]->image->frameRender(getMemDC(), _vIsoEnemy[i]->rc.left, _vIsoEnemy[i]->rc.top);

			sprintf_s(str, "objNum = %d", _vIsoEnemy[i]->number);
			TextOut(getMemDC(), _vIsoEnemy[i]->rc.left, _vIsoEnemy[i]->rc.top, str, strlen(str));
		}
	}

	//sprintf_s(str, "x : %d, y : %d", _ptMouse.x, _ptMouse.y);
	//TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, str, strlen(str));

}
///////////////////////////////////////////////////////////랜더 끝////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////키컨트롤 시작////////////////////////////////////////////////////////////////////

void mapTool::keyControl()
{
	//샘플타일 픽업
	if (_state == SET_TILE)
	{
		int vIsoSize = _vIsoTile.size();
		for (int i = 0; i < vIsoSize; i++)//i = 0 1 2 3 
		{
			if (PtInRect(&_vIsoTile[i]->rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_pickNum = _vIsoTile[tileNum * 4 + i]->number;
				}
			}
		}
	}

	//샘플오브젝트 픽업
	if (_state == SET_OBJ)
	{
		int vIsoOSize = _vIsoObj.size();
		for (int i = 0; i < vIsoOSize; i++)
		{
			if (PtInRect(&_vIsoObj[i]->rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_pickNum = _vIsoObj[i]->number;
				}
			}
		}
	}

	// 샘플에너미 픽업
	if (_state == SET_ENM)
	{
		int vIsoESize = _vIsoEnemy.size();
		for (int i = 0; i < vIsoESize; i++)
		{
			if (PtInRect(&_vIsoEnemy[i]->rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_pickNum = _vIsoEnemy[i]->number;
				}
			}
		}
	}

	if (_ptMouse.x > 300)
	{
		// 마우스 클릭 된 위치 이미지 그리자
		for (int i = 0; i < TOTALTILE(TILENUM); i++)
		{
			if (PtInRect(&_vTile[i]->rc, _ptMouse))
			{
				if ((_ptMouse.y - _vTile[i]->pivotY) >= -0.5 * (_ptMouse.x - _vTile[i]->pivotX) - WIDTH / 4 &&
					(_ptMouse.y - _vTile[i]->pivotY) >=  0.5 * (_ptMouse.x - _vTile[i]->pivotX) - WIDTH / 4 &&
					(_ptMouse.y - _vTile[i]->pivotY) <= -0.5 * (_ptMouse.x - _vTile[i]->pivotX) + WIDTH / 4 &&
					(_ptMouse.y - _vTile[i]->pivotY) <=  0.5 * (_ptMouse.x - _vTile[i]->pivotX) + WIDTH / 4)
				{
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
					{
						//타일깔기
						if (_state == SET_TILE)
						{
							if (!_vTile[i]->draw)
							{
								_vTile[i]->draw = true;
								_vTile[i]->imageNum = _pickNum;
								_vTile[i]->image->setFrameX(_vTile[i]->imageNum % 4);
								_vTile[i]->image->setFrameY(_vTile[i]->imageNum / 4);
								
								if (_vTile[i]->image->getFrameY() < 15)
									_vTile[i]->state = S_NONE;
								else
									_vTile[i]->state = S_ETC;
							}
						}


						//오브젝트깔기
						if (_state == SET_OBJ)
						{
							if (_vTile[i]->draw == true && _vTile[i]->state == S_NONE)
							{
								_vObj[i]->imageNum = _pickNum;
								switch (_vObj[i]->imageNum)
								{
								case 0:
									_vObj[i]->image->init("image/mapTool/object_tree.bmp", 222, 265, 1, 1, true, 0xff00ff);
									_vObj[i]->state = S_NOMAL;
									break;
								case 1:
									_vObj[i]->image->init("image/mapTool/object_tree2.bmp", 180, 185, 1, 1, true, 0xff00ff);
									_vObj[i]->state = S_NOMAL;
									break;
								case 2:
									_vObj[i]->image->init("image/mapTool/object_wood.bmp", 128, 118, 1, 1, true, 0xff00ff);
									_vObj[i]->state = S_NOMAL;
									break;
								case 3:
									_vObj[i]->image->init("image/mapTool/object_mushiroom.bmp", 63, 65, 1, 1, true, 0xff00ff);
									_vObj[i]->state = S_NOMAL;
									break;
								case 4:
									_vObj[i]->image->init("image/mapTool/object_zen.bmp", 2583, 76, 21, 1, true, 0xff00ff);
									_vObj[i]->state = S_ZEN;
									break;
								default:
									break;
								}
								_vObj[i]->width = _vObj[i]->image->getFrameWidth();
								_vObj[i]->height = _vObj[i]->image->getFrameHeight();
								if (_vObj[i]->height < WIDTH / 2)
									_vObj[i]->rc = RectMake(_vTile[i]->pivotX - _vObj[i]->width / 2, _vTile[i]->pivotY + WIDTH / 4 - _vObj[i]->height / 2, _vObj[i]->width, _vObj[i]->height);
								else if (_vObj[i]->height > WIDTH / 2)
									_vObj[i]->rc = RectMake(_vTile[i]->pivotX - _vObj[i]->width / 2, _vTile[i]->rc.bottom - _vObj[i]->height, _vObj[i]->width, _vObj[i]->height);
								_vObj[i]->draw = true;
						
								if (_vObj[i]->state == S_ZEN) _vTile[i]->state = ZEN_POINT;
								else _vTile[i]->state = S_ONOBJ;
							}
						}

						if (_state == SET_ENM)
						{
							if (_vTile[i]->draw == true && _vTile[i]->state == S_NONE)
							{
								_vEnemy[i]->imageNum = _pickNum;
								switch (_vEnemy[i]->imageNum)
								{
								case 0:
									_vEnemy[i]->image->init("image/character/prinny_idle.bmp", 714, 484, 7, 4, true, 0xff00ff);
									_vEnemy[i]->state = E_NORMAL;
									break;
								case 1:
									_vEnemy[i]->image->init("image/character/orc_idle.bmp", 1008, 668, 6, 4, true, 0xff00ff);
									_vEnemy[i]->state = E_NORMAL;
									break;
								case 2:
									_vEnemy[i]->image->init("image/character/catsaver_idle.bmp", 612, 500, 6, 4, true, 0xff00ff);
									_vEnemy[i]->state = E_NORMAL;
									break;
								default:
									break;
								}
								_vEnemy[i]->width = _vEnemy[i]->image->getFrameWidth();
								_vEnemy[i]->height = _vEnemy[i]->image->getFrameHeight();
								_vEnemy[i]->rc = RectMake(_vTile[i]->pivotX - _vEnemy[i]->width / 2, _vTile[i]->pivotY - _vEnemy[i]->height, _vEnemy[i]->width, _vEnemy[i]->height);
								_vEnemy[i]->draw = true;

								_vTile[i]->state = S_ONENM;
							}
						}
					}


					//삭제
					if ((_ptMouse.y - _vTile[i]->pivotY) >= -0.5 * (_ptMouse.x - _vTile[i]->pivotX) - WIDTH / 4 &&
						(_ptMouse.y - _vTile[i]->pivotY) >=  0.5 * (_ptMouse.x - _vTile[i]->pivotX) - WIDTH / 4 &&
						(_ptMouse.y - _vTile[i]->pivotY) <= -0.5 * (_ptMouse.x - _vTile[i]->pivotX) + WIDTH / 4 &&
						(_ptMouse.y - _vTile[i]->pivotY) <=  0.5 * (_ptMouse.x - _vTile[i]->pivotX) + WIDTH / 4)
					{
						if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
						{
							//타일
							if (_state == SET_TILE)
							{
								_vTile[i]->draw = false;
								_vTile[i]->imageNum = 100;
								_vTile[i]->state = S_NONE;
							}

							//오브젝트
							if (_state == SET_OBJ)
							{
								if ((_vTile[i]->state == S_ONOBJ) ||
									(_vTile[i]->state == ZEN_POINT))
								{
									_vObj[i]->draw = false;
									_vObj[i]->rc = RectMake(0, 0, 0, 0);
									_vObj[i]->imageNum = 100;
									_vObj[i]->state = S_NOMAL;

									_vRender[i]->draw = false;
									_vRender[i]->rc = RectMake(0, 0, 0, 0);
									_vRender[i]->imageNum = 100;
									_vRender[i]->state = S_NOMAL;

									_vTile[i]->state = S_NONE;
								}
							}

							//적
							if (_state == SET_ENM)
							{
								if (_vTile[i]->state == S_ONENM)
								{
									_vEnemy[i]->draw = false;
									_vEnemy[i]->rc = RectMake(0, 0, 0, 0);
									_vEnemy[i]->imageNum = 100;
									_vEnemy[i]->state = S_NOMAL;

									_vRender[i]->draw = false;
									_vRender[i]->rc = RectMake(0, 0, 0, 0);
									_vRender[i]->imageNum = 100;
									_vRender[i]->state = E_NORMAL;

									_vTile[i]->state = S_NONE;
								}
							}
						}
					}
				}
			}
		}
	}
	moveTile();

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (tileNum > 0) tileNum--;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (tileNum < 16) tileNum++;
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		saveMapData();
	}
	//맵 데이터를 로드
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		loadMapData();
	}
	//맵 데이터를 리셋
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		resetMapData();
	}
}
///////////////////////////////////////////////////////////키컨트롤 끝///////////////////////////////////////////////

void mapTool::saveMapData()
{
	char temp1[128], temp2[128], temp3[128];

	//타일저장
	vector<string> vStr;
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		vStr.push_back("|");							//구분자
		vStr.push_back(itoa((*_viTile)->number, temp1, 10));		//타일 넘버
		vStr.push_back(itoa((*_viTile)->state, temp1, 10));		//타일 상태
		vStr.push_back(itoa((*_viTile)->x, temp1, 10));	//불러올때 위치정보를 갖고있을 피벗.
		vStr.push_back(itoa((*_viTile)->y, temp1, 10));
		vStr.push_back(itoa((*_viTile)->imageNum, temp1, 10));	//타일 이미지 (_pickNum)
	}
	
	//오브젝트저장
	vector<string> vStr2;
	for (_viObj = _vObj.begin(); _viObj != _vObj.end(); _viObj++)
	{
		vStr2.push_back("|");
		vStr2.push_back(itoa((*_viObj)->number, temp2, 10));
		vStr2.push_back(itoa((*_viObj)->state, temp2, 10));
		vStr2.push_back(itoa((*_viObj)->x, temp2, 10));
		vStr2.push_back(itoa((*_viObj)->y, temp2, 10));
		vStr2.push_back(itoa((*_viObj)->imageNum, temp2, 10));
	}
	
	//적저장
	vector<string> vStr3;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		vStr3.push_back("|");
		vStr3.push_back(itoa((*_viEnemy)->number, temp3, 10));
		vStr3.push_back(itoa((*_viEnemy)->state, temp3, 10));
		vStr3.push_back(itoa((*_viEnemy)->x, temp3, 10));
		vStr3.push_back(itoa((*_viEnemy)->y, temp3, 10));
		vStr3.push_back(itoa((*_viEnemy)->imageNum, temp3, 10));
	}
	
	switch (_stage)
	{
	case 1:
		TXTDATA->txtSave("battleMap1.txt", vStr);
		TXTDATA->txtSave("battleMap1_obj.txt", vStr2);
		TXTDATA->txtSave("battleMap1_enm.txt", vStr3);
		break;
	case 2:
		TXTDATA->txtSave("battleMap2.txt", vStr);
		TXTDATA->txtSave("battleMap2_obj.txt", vStr2);
		TXTDATA->txtSave("battleMap2_enm.txt", vStr3);
		break;
	case 3:
		TXTDATA->txtSave("battleMap3.txt", vStr);
		TXTDATA->txtSave("battleMap3_obj.txt", vStr2);
		TXTDATA->txtSave("battleMap3_enm.txt", vStr3);
		break;
	}

}

void mapTool::loadMapData()
{
	resetMapData();

	
	//타일로드
	switch (_stage)
	{
	case 1:
		DATABASE->loadDatabase("battleMap1.txt");
		break;
	case 2:
		DATABASE->loadDatabase("battleMap2.txt");
		break;
	case 3:
		DATABASE->loadDatabase("battleMap3.txt");
		break;
	}
	for (_viTile = _vTile.begin(); _viTile != _vTile.end(); ++_viTile)
	{
		char temp[128];
		//_viTile->number 는 자료를 찾는 인덱스. 고유번호
		(*_viTile)->number = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->number;
		(*_viTile)->state = (TILESTATE)DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->state;

		(*_viTile)->x = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->x;
		(*_viTile)->y = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->y;
		(*_viTile)->imageNum = DATABASE->getElementData(itoa((*_viTile)->number, temp, 10))->imageNum;
		if ((*_viTile)->imageNum < 100)
		{
			(*_viTile)->draw = true;
			(*_viTile)->image->setFrameX((*_viTile)->imageNum % 4);
			(*_viTile)->image->setFrameY((*_viTile)->imageNum / 4);
		}
	}

	//오브젝트 로드
	switch (_stage)
	{
	case 1:
		DATABASE->loadDatabase("battleMap1_obj.txt");
		break;
	case 2:
		DATABASE->loadDatabase("battleMap2_obj.txt");
		break;
	case 3:
		DATABASE->loadDatabase("battleMap3_obj.txt");
		break;
	}

	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		char temp[128];
		_vObj[i]->number = DATABASE->getElementData(itoa(i, temp, 10))->number;
		_vObj[i]->state = (OBJSTATE)DATABASE->getElementData(itoa(_vObj[i]->number, temp, 10))->state;
		_vObj[i]->x = DATABASE->getElementData(itoa(_vObj[i]->number, temp, 10))->x;
		_vObj[i]->y = DATABASE->getElementData(itoa(_vObj[i]->number, temp, 10))->y;
		_vObj[i]->imageNum = DATABASE->getElementData(itoa(_vObj[i]->number, temp, 10))->imageNum;
		if (_vObj[i]->imageNum < 50)
		{
			_vObj[i]->draw = true;
			switch (_vObj[i]->imageNum)
			{
			case 0:
				_vObj[i]->image->init("image/mapTool/object_tree.bmp", 222, 265, 1, 1, true, 0xff00ff);
				break;
			case 1:
				_vObj[i]->image ->init("image/mapTool/object_tree2.bmp", 180, 185, 1, 1, true, 0xff00ff);
				break;
			case 2:
				_vObj[i]->image->init("image/mapTool/object_wood.bmp", 128, 118, 1, 1, true, 0xff00ff);
				break;
			case 3:
				_vObj[i]->image->init("image/mapTool/object_mushiroom.bmp", 63, 65, 1, 1, true, 0xff00ff);
				break;
			case 4:
				_vObj[i]->image->init("image/mapTool/object_zen.bmp", 2583, 76, 21, 1, true, 0xff00ff);
				break;
			default:
				break;
			}
			_vObj[i]->width = _vObj[i]->image->getFrameWidth();
			_vObj[i]->height = _vObj[i]->image->getFrameHeight();
			if (_vObj[i]->height < WIDTH / 2)
				_vObj[i]->rc = RectMake(_vTile[i]->pivotX - _vObj[i]->width / 2, _vTile[i]->pivotY + WIDTH / 4 - _vObj[i]->height / 2, _vObj[i]->width, _vObj[i]->height);
			else if (_vObj[i]->height > WIDTH / 2)
				_vObj[i]->rc = RectMake(_vTile[i]->pivotX - _vObj[i]->width / 2, _vTile[i]->rc.bottom - _vObj[i]->height , _vObj[i]->width, _vObj[i]->height);
		}
	}

	
	//에너미 로듣

	switch (_stage)
	{
	case 1:
		DATABASE->loadDatabase("battleMap1_enm.txt");
		break;
	case 2:
		DATABASE->loadDatabase("battleMap2_enm.txt");
		break;
	case 3:
		DATABASE->loadDatabase("battleMap3_enm.txt");
		break;
	}
	//에너미로드
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		char temp[128];
	
		_vEnemy[i]->number = DATABASE->getElementData(itoa(i, temp, 10))->number;
		_vEnemy[i]->state = (OBJSTATE)DATABASE->getElementData(itoa(_vEnemy[i]->number, temp, 10))->state;
		_vEnemy[i]->x = DATABASE->getElementData(itoa(_vEnemy[i]->number, temp, 10))->x;
		_vEnemy[i]->y = DATABASE->getElementData(itoa(_vEnemy[i]->number, temp, 10))->y;
		_vEnemy[i]->imageNum = DATABASE->getElementData(itoa(_vEnemy[i]->number, temp, 10))->imageNum;
		
		if (_vEnemy[i]->imageNum < 50)
		{
			_vEnemy[i]->draw = true;
			switch (_vEnemy[i]->imageNum)
			{
			case 0:
				_vEnemy[i]->image->init("image/character/prinny_idle.bmp", 714, 484, 7, 4, true, 0xff00ff);
				break;
			case 1:
				_vEnemy[i]->image->init("image/character/orc_idle.bmp", 1008, 668, 6, 4, true, 0xff00ff);
				break;
			case 2:
				_vEnemy[i]->image->init("image/character/catsaver_idle.bmp", 612, 500, 6, 4, true, 0xff00ff);
				break;
			default:
				break;
			}
			_vEnemy[i]->width = _vEnemy[i]->image->getFrameWidth();
			_vEnemy[i]->height = _vEnemy[i]->image->getFrameHeight();
			_vEnemy[i]->rc = RectMake(_vTile[i]->pivotX - _vEnemy[i]->width / 2, _vTile[i]->pivotY - _vEnemy[i]->height, _vEnemy[i]->width, _vEnemy[i]->height);
		}
	}

	setRender();
}

//리셋
void mapTool::resetMapData()
{
	release();

	setTile();
	setObject();
	setEnemy();
	setFirstRender();
}

void mapTool::onTile()
{
	_state = SET_TILE;
}

void mapTool::onObject()
{
	_state = SET_OBJ;
}

void mapTool::onEnemy()
{
	_state = SET_ENM;
}

void mapTool::setPickNum()
{
	if (_state == SET_TILE)
	{
		if (_pickNum > _vIsoTile.size() - 1)
			_pickNum = _vIsoTile.size() - 1;
	}

	if (_state == SET_OBJ)
	{
		if (_pickNum > _vIsoObj.size() - 1)
			_pickNum = _vIsoObj.size() - 1;
	}

	if (_state == SET_ENM)
	{
		if (_pickNum > _vIsoEnemy.size() - 1)
			_pickNum = _vIsoEnemy.size() - 1;
	}
}

void mapTool::goToMenu()
{
	SCENEMANAGER->changeScene("title");
}

void mapTool::stageBack()
{
	if(_stage > 1) _stage--;
}
void mapTool::stageNext()
{
	if (_stage < 3) _stage++;
}

void mapTool::setTile()
{
	//전체 깔아둔타일
	int count = 0;
	POINT firstPivot = { (316 + WINSIZEX) / 2, WIDTH / 4 };
	for (int i = 0; i < TILENUM; i++)      // 세로 ( 열 )
	{
		for (int j = 0; j < TILENUM; j++)   // 가로 ( 행 )
		{
			//TagTile* tile;
			//tile = new TagTile;
			_tile[j][i].image = new image;
			_tile[j][i].image->init("image/mapTool/mapTile_iso.bmp", 512, 1938, 4, 17, true, 0xff00ff);
			_tile[j][i].width = WIDTH;
			_tile[j][i].height = WIDTH / 2;
			_tile[j][i].rc = RectMakeCenter(firstPivot.x + j * _tile[j][i].width / 2 - i * _tile[j][i].width / 2, 
											firstPivot.y + j * _tile[j][i].width / 4 + i * _tile[j][i].width / 4, _tile[j][i].width, _tile[j][i].height);
			_tile[j][i].pivotX = (_tile[j][i].rc.left + _tile[j][i].rc.right) / 2;
			_tile[j][i].pivotY = (_tile[j][i].rc.top + _tile[j][i].rc.bottom) / 2;
			_tile[j][i].x = j;
			_tile[j][i].y = i;
			_tile[j][i].imageNum = 100;	//이미지 넘버.
			_tile[j][i].number = count;
			_tile[j][i].state = S_NONE;
			_tile[j][i].draw = false;

			_vTile.push_back(&_tile[j][i]);

			count++;
		}
	}
}

void mapTool::setObject()
{
	int count = 0;
	for (int i = 0; i < TILENUM; i++)     
	{
		for (int j = 0; j < TILENUM; j++) 
		{
			TagObject* obj;
			obj = new TagObject;
			obj->image = new image;
			obj->x = j;
			obj->y = i;
			obj->imageNum = 100;
			obj->number = count;
			obj->state = S_NOMAL;
			obj->pivot.x = _vTile[i]->pivotX;
			obj->pivot.y = _vTile[i]->pivotY;
			obj->draw = false;

			_vObj.push_back(obj);
			count++;
		}
	}
}

void mapTool::setEnemy()
{
	int count = 0;
	for (int i = 0; i < TILENUM; i++)     
	{
		for (int j = 0; j < TILENUM; j++) 
		{
			TagObject* enm;
			enm = new TagObject;
			enm->image = new image;
			enm->x = j;
			enm->y = i;
			enm->imageNum = 100;
			enm->number = count;
			enm->state = E_NORMAL;
			enm->pivot.x = _vTile[i]->pivotX;
			enm->pivot.y = _vTile[i]->pivotY;
			enm->draw = false;

			_vEnemy.push_back(enm);
			count++;
		}
	}
}

void mapTool::setFirstRender()
{
	int count = 0;
	for (int i = 0; i < TILENUM; i++)
	{
		for (int j = 0; j < TILENUM; j++)
		{
			TagObject* rnd;
			rnd = new TagObject;
			rnd->image = new image;
			rnd->x = j;
			rnd->y = i;
			rnd->imageNum = 100;
			rnd->number = count;
			rnd->state = E_NORMAL;
			rnd->pivot.x = _vTile[i]->pivotX;
			rnd->pivot.y = _vTile[i]->pivotY;
			rnd->draw = false;

			_vRender.push_back(rnd);
			count++;
		}
	}
}

void mapTool::moveTile()
{
	// 임시 맵스크롤 키 입력 만들자
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _vTile[0]->rc.top < 0)
	{
		_vTile[0]->pivotY += 3;
		setTile(_vTile[0]->pivotX, _vTile[0]->pivotY);
		for (int i = 0; i < TOTALTILE(TILENUM); i++)
		{
			_vRender[i]->rc = RectMake(_vRender[i]->rc.left, _vRender[i]->rc.top + 3, _vRender[i]->rc.right, _vRender[i]->rc.bottom);
		}
	}

	//다운키
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _vTile[TOTALTILE(TILENUM) - 1]->rc.bottom > WINSIZEY - 15)
	{
		_vTile[0]->pivotY -= 3;
		setTile(_vTile[0]->pivotX, _vTile[0]->pivotY);
		for (int i = 0; i < TOTALTILE(TILENUM); i++)
		{
			_vRender[i]->rc = RectMake(_vRender[i]->rc.left, _vRender[i]->rc.top - 3, _vRender[i]->rc.right, _vRender[i]->rc.bottom);
		}
	}

	//왼쪽키
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _vTile[TOTALTILE(TILENUM) - TILENUM - 1]->rc.left > 300)
	{
		_vTile[0]->pivotX += 3;
		setTile(_vTile[0]->pivotX, _vTile[0]->pivotY);
		for (int i = 0; i < TOTALTILE(TILENUM); i++)
		{
			_vRender[i]->rc = RectMake(_vRender[i]->rc.left + 3, _vRender[i]->rc.top, _vRender[i]->rc.right, _vRender[i]->rc.bottom);
		}
	}

	//오른쪽키
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_vTile[0]->pivotX -= 3;
		setTile(_vTile[0]->pivotX, _vTile[0]->pivotY);
		for (int i = 0; i < TOTALTILE(TILENUM); i++)
		{
			_vRender[i]->rc = RectMake(_vRender[i]->rc.left - 3, _vRender[i]->rc.top, _vRender[i]->rc.right, _vRender[i]->rc.bottom);
		}
	}
}

void mapTool::setTile(float firstPivotX, float firstPivotY)
{
	int count = 0;
	POINT firstPivot = { firstPivotX, firstPivotY };
	for (int i = 0; i < TILENUM; i++)      // 세로 ( 열 )
	{
		for (int j = 0; j < TILENUM; j++)   // 가로 ( 행 )
		{
			_vTile[count]->rc = RectMakeCenter(firstPivot.x + j * _vTile[count]->width / 2 - i * _vTile[count]->width / 2, firstPivot.y + j * _vTile[count]->width / 4 + i * _vTile[count]->width / 4, _vTile[count]->width, _vTile[count]->height);
			_vTile[count]->pivotX = (_vTile[count]->rc.left + _vTile[count]->rc.right) / 2;
			_vTile[count]->pivotY = (_vTile[count]->rc.top + _vTile[count]->rc.bottom) / 2;

			count++;
		}
	}
}

void mapTool::setRender()
{
	int vRenderSize = _vRender.size();
	for (int i = 0; i < vRenderSize; i++)
	{
		if (_vRender[i]->draw) continue;

		if (_vObj[i]->draw)
		{
			_vRender[i]->imageNum = _vObj[i]->imageNum;
			_vRender[i]->image = _vObj[i]->image;
			_vRender[i]->width = _vObj[i]->width;
			_vRender[i]->height = _vObj[i]->height;
			_vRender[i]->rc = _vObj[i]->rc;
			_vRender[i]->draw = true;
		}

		if (_vEnemy[i]->draw)
		{
			_vRender[i]->imageNum = _vEnemy[i]->imageNum;
			_vRender[i]->image = _vEnemy[i]->image;
			_vRender[i]->width = _vEnemy[i]->width;
			_vRender[i]->height = _vEnemy[i]->height;
			_vRender[i]->rc = _vEnemy[i]->rc;
			_vRender[i]->draw = true;
		}
	}
}

void mapTool::setSampleTile()
{
	int count = 0;
	// 샘플타일
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//TagTile* tile;
			//_sampleTile[j][i]
			//tile = new TagTile;
			_sampleTile[j][i].image = new image;
			_sampleTile[j][i].image->init("image/mapTool/mapTile_iso.bmp", 512, 1938, 4, 17, true, 0xff00ff);
			_sampleTile[j][i].width = WIDTH;
			_sampleTile[j][i].height = WIDTH / 2;
			_sampleTile[j][i].rc = RectMake(10, 190 + _sampleTile[j][i].image->getFrameHeight() * j, _sampleTile[j][i].image->getFrameWidth(), _sampleTile[j][i].image->getFrameHeight());
			_sampleTile[j][i].pivotX = (_sampleTile[j][i].rc.left + _sampleTile[j][i].rc.right) / 2;
			_sampleTile[j][i].pivotY = (_sampleTile[j][i].rc.top + _sampleTile[j][i].rc.bottom) / 2;
			_sampleTile[j][i].number = count; // imageNum으로 불러올수있는 샘플타일 인덱스
			_sampleTile[j][i].draw = true;

			_sampleTile[j][i].image->setFrameX(_sampleTile[j][i].number % 4);
			_sampleTile[j][i].image->setFrameY(_sampleTile[j][i].number / 4);

			if (_sampleTile[j][i].image->getFrameX() < 15)
				_sampleTile[j][i].state = S_NONE;
			else
				_sampleTile[j][i].state = S_ETC;
			_vIsoTile.push_back(&_sampleTile[j][i]);

			count++;
		}
	}
}

void mapTool::setSampleObject()
{
	//나무
	TagObject* obj;
	obj = new TagObject;
	obj->image = new image;
	obj->image->init("image/mapTool/object_tree.bmp", 222, 265, 1, 1, true, 0xff00ff);
	obj->state = S_NOMAL;
	obj->width = WIDTH;
	obj->height = obj->image->getHeight();
	obj->rc = RectMake(10, 180, obj->width, obj->height);
	obj->number = 0;
	obj->draw = true;
	_vIsoObj.push_back(obj);

	//나무2
	obj = new TagObject;
	obj->image = new image;
	obj->image->init("image/mapTool/object_tree2.bmp", 180, 185, 1, 1, true, 0xff00ff);
	obj->state = S_NOMAL;
	obj->width = WIDTH;
	obj->height = obj->image->getHeight();
	obj->rc = RectMake(10, 430, obj->width, obj->height);
	obj->number = 1;
	obj->draw = true;
	_vIsoObj.push_back(obj);

	//나무밑동
	obj = new TagObject;
	obj->image = new image;
	obj->image->init("image/mapTool/object_wood.bmp", 128, 118, 1, 1, true, 0xff00ff);
	obj->state = S_NOMAL;
	obj->width = WIDTH;
	obj->height = obj->image->getHeight();
	obj->rc = RectMake(10, 615, obj->width, obj->height);
	obj->number = 2;
	obj->draw = true;
	_vIsoObj.push_back(obj);
	
	//버섯
	obj = new TagObject;
	obj->image = new image;
	obj->image->init("image/mapTool/object_mushiroom.bmp", 63, 65, 1, 1, true, 0xff00ff);
	obj->state = S_NOMAL;
	obj->width = WIDTH;
	obj->height = obj->image->getHeight();
	obj->rc = RectMake(200, 580, obj->width, obj->height);
	obj->number = 3;
	obj->draw = true;
	_vIsoObj.push_back(obj);
	
	//젠포인트
	obj = new TagObject;
	obj->image = new image;
	obj->image->init("image/mapTool/object_zen.bmp", 2583, 76, 21, 1, true, 0xff00ff);
	obj->state = S_ZEN;
	obj->width = WIDTH;
	obj->height = obj->image->getHeight();
	obj->rc = RectMake(138, 650, obj->width, obj->height);
	obj->number = 4;
	obj->draw = true;
	
	_vIsoObj.push_back(obj);
}

void mapTool::setSampleEnemy()
{
	//프리니
	TagObject* enemy;
	enemy = new TagObject;
	enemy->image = new image;
	enemy->image->init("image/character/prinny_idle.bmp", 714, 484, 7, 4, true, 0xff00ff);
	enemy->state = E_NORMAL;
	enemy->width = WIDTH;
	enemy->height = enemy->image->getFrameHeight();
	enemy->rc = RectMake(10, 190, enemy->width, enemy->height);
	enemy->number = 0;
	enemy->draw = true;

	_vIsoEnemy.push_back(enemy);

	//오크
	enemy = new TagObject;
	enemy->image = new image;
	enemy->image->init("image/character/orc_idle.bmp", 1008, 668, 6, 4, true, 0xff00ff);
	enemy->state = E_NORMAL;
	enemy->width = WIDTH;
	enemy->height = enemy->image->getFrameHeight();
	enemy->rc = RectMake(100, 190, enemy->width, enemy->height);
	enemy->number = 1;
	enemy->draw = true;

	_vIsoEnemy.push_back(enemy);

	//캣세이버
	enemy = new TagObject;
	enemy->image = new image;
	enemy->image->init("image/character/catsaver_idle.bmp", 612, 500, 6, 4, true, 0xff00ff);
	enemy->state = E_NORMAL;
	enemy->width = WIDTH;
	enemy->height = enemy->image->getFrameHeight();
	enemy->rc = RectMake(10, 330, enemy->width, enemy->height);
	enemy->number = 2;
	enemy->draw = true;
	_vIsoEnemy.push_back(enemy);
}