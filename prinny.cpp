#include "stdafx.h"
#include "prinny.h"


prinny::prinny()
{
}


prinny::~prinny()
{
}

HRESULT prinny::init()
{
	_inventory = new inventory;
	_inventory->init();

	_name = "prinny";
	_mercenary.reserve(4);	//벡터 크기 4로 예약

	/*			character status setting			*/
	//character 정보를 load 해오기
	loadData();

	_character = IMAGEMANAGER->findImage("prinny_idle");
	_characterState = IDLE;
	_characterDir = LB;
	_characterNum = 0;
	_curFrameX = 0;
	_count = 0;
	_x = CENTERX;
	_y = CENTERY;
	_rc = RectMakeCenter(_x, _y, _character->getFrameWidth(), _character->getFrameHeight());


	return S_OK;
}

HRESULT prinny::init(int x, int y, vector<TagTile*> tile)
{
	_inventory = new inventory;
	_inventory->init();

	_name = "prinny";

	loadData();
	_isCharacter = true;
	_character = IMAGEMANAGER->findImage("prinny_idle");
	_characterState = IDLE;
	_characterDir = RT;
	_curFrameX = 0;
	_count = 0;

	_isRight = true;
	_isUp = true;

	_indexX = x;
	_indexY = y;
	_mv = 4;
	_isShow = false;
	_isbattle = true;
	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		_tile[i % TILENUM][i / TILENUM] = tile[i];
	}

	_vTile = tile;
	_pivotY = _tile[_indexX][_indexY]->pivotY;
	
	_moveSpeed = 3;

	return S_OK;
}

void prinny::release()
{
	SAFE_DELETE(_inventory);
	_mercenary.clear();
}

void prinny::update()
{
	gameObject::setDirectionImage();
	setImage();

	if (_isbattle)
	{
		if (!_isMove)
		{
			_rc = RectMakeIso(_tile[_indexX][_indexY]->pivotX, _tile[_indexX][_indexY]->pivotY, _character->getFrameWidth(), _character->getFrameHeight());
			_x = (_rc.right + _rc.left) / 2;
			_y = (_rc.top + _rc.bottom) / 2;
			//_pivotY = _tile[_x][_y]->pivotY;
		}
		battleKeyControl();
		gameObject::move();
	}
	else
	{
		_inventory->update();
		keyControl();
	}

	setImage();
	gameObject::setDirectionImage();
}

void prinny::render()
{
	if (!_isbattle)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		_character->frameRender(getMemDC(), _rc.left, _rc.top, _curFrameX, _curFrameY);
		_inventory->render();
	}
	else
	{
		if (_isShow)
		{
			if (_isShowPossibleMoveTile) gameObject::showPossibleMoveTile();
			if (_isShowPossibleAttackTile) gameObject::showPossibleAttackTile();
			{
				//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
				_character->frameRender(getMemDC(), _rc.left, _rc.top, _curFrameX, _curFrameY);
			}
		}
	}
}

void prinny::keyControl()
{
	//마을에서 움직일 때 사용
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isRight = false;
		if (_characterState != WALK)
		{
			_characterState = WALK;
		}
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isRight = true;
		if (_characterState != WALK)
		{
			_characterState = WALK;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_isUp = true;
		if (_characterState != WALK)
		{
			_characterState = WALK;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_isUp = false;
		if (_characterState != WALK)
		{
			_characterState = WALK;
		}
	}

	if(KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) 
		|| KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_characterState = IDLE;
		_curFrameX = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (!_isOpenInven)
		{
			_isOpenInven = true;
			changeLoadData(_characterNum);
			setInventory();
			_inventory->showInventory();
			_invenExit = _inventory->getExit();
			_invenNext = _inventory->getNext();
		}
		else
		{
			_isOpenInven = false;
			setChangeData();	//인벤에서 변경된 정보를 프리니에 세팅
			changeSaveData();	//넘기기 전에 정보를 저장
			_inventory->closeInventory();
			_invenExit = RectMake(0, 0, 0, 0);
			_invenNext = RectMake(0, 0, 0, 0);
		}
	}

	if (PtInRect(&_invenExit, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_isOpenInven = false;
			setChangeData();	//인벤에서 변경된 정보를 프리니에 세팅
			changeSaveData();	//넘기기 전에 정보를 저장
			_characterNum = 0;
			_inventory->closeInventory();
			_invenExit = RectMake(0, 0, 0, 0);
		}
	}

	if (PtInRect(&_invenNext, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			setChangeData();	//인벤에서 변경된 정보를 프리니에 세팅
			changeSaveData();	//넘기기 전에 정보를 저장

			_characterNum++;
			if (_characterNum > _mercenaryNum) _characterNum = 0;

			changeLoadData(_characterNum);
			setInventory();
		}
	}
}

void prinny::battleKeyControl()
{
}


void prinny::setImage()
{
	switch (_characterState)
	{
	case IDLE:
		_character = IMAGEMANAGER->findImage("prinny_idle");
		break;

	case WALK:
		_character = IMAGEMANAGER->findImage("prinny_walk");
		break;

	case ATTACK:
		_character = IMAGEMANAGER->findImage("prinny_attack");
		break;

	case LIFT:
		_character = IMAGEMANAGER->findImage("prinny_lift");
		break;

	case ETC:
		_character = IMAGEMANAGER->findImage("prinny_etc");
		break;
	}

	gameObject::setFrame();
}

void prinny::saveData()
{
	vector<string> vStr;

	vStr.push_back(std::to_string(_level));
	vStr.push_back(std::to_string(_counter));
	vStr.push_back(std::to_string(_mv));
	vStr.push_back(std::to_string(_jm));
	vStr.push_back(std::to_string(_hp));
	vStr.push_back(std::to_string(_sp));
	vStr.push_back(std::to_string(_atk));
	vStr.push_back(std::to_string(_int));
	vStr.push_back(std::to_string(_def));
	vStr.push_back(std::to_string(_spd));
	vStr.push_back(std::to_string(_hit));
	vStr.push_back(std::to_string(_res));
	vStr.push_back(std::to_string(_exp));
	vStr.push_back(std::to_string(_next));
	vStr.push_back(std::to_string(_equipWeapon));
	vStr.push_back(std::to_string(_hell));

	int itemNum = _inventory->getItem()->getVItem().size();
	
	vStr.push_back(std::to_string(itemNum));	//아이템 개수

	//아이템 이름
	for (int i = 0; i < itemNum; ++i)
	{
		vStr.push_back(_inventory->getItem()->getVItem()[i].name);
	}

	_mercenaryNum = _mercenary.size();
	vStr.push_back(std::to_string(_mercenaryNum));	//용병 수
	
	//용병 이름
	for (int i = 0; i < _mercenaryNum; ++i)
	{
		vStr.push_back(_mercenary[i]);
	}

	TXTDATA->txtSave("prinny.txt", vStr);

	saveItemData();
}

void prinny::loadData()
{
	vector<string> vStr;
	
	vStr = TXTDATA->txtLoad("prinny.txt");
	
	int idx = 0;

	_level = atoi(vStr[idx++].c_str());
	_counter = atoi(vStr[idx++].c_str());
	_mv = atoi(vStr[idx++].c_str());
	_jm = atoi(vStr[idx++].c_str());
	_hp = atoi(vStr[idx++].c_str());
	_sp = atoi(vStr[idx++].c_str());
	_atk = atoi(vStr[idx++].c_str());
	_int = atoi(vStr[idx++].c_str());
	_def = atoi(vStr[idx++].c_str());
	_spd = atoi(vStr[idx++].c_str());
	_hit = atoi(vStr[idx++].c_str());
	_res = atoi(vStr[idx++].c_str());
	_exp = atoi(vStr[idx++].c_str());
	_next = atoi(vStr[idx++].c_str());
	_equipWeapon = (WEAPON_TYPE)atoi(vStr[idx++].c_str());
	_hell = atoi(vStr[idx++].c_str());

	_itemNum = atoi(vStr[idx++].c_str());
	for (int i = 0; i < _itemNum; ++i)		//index = 18 ~ 18 + itemNum
	{
		setItem(vStr[idx++].c_str(), false);
	}
	loadItemData();							//소지 중인 아이템의 착용 정보 불러오기

	_mercenaryNum = atoi(vStr[idx++].c_str());
	for (int i = 0; i < _mercenaryNum; ++i)
	{
		setMercenary(vStr[idx++].c_str());
	}
}

void prinny::loadItemData()
{
	vector<string> vStr;

	vStr = TXTDATA->txtLoad("itemState.txt");

	for (int i = 0; i < _itemNum; ++i)
	{
		_inventory->getItem()->getVItem()[i].isWear = atoi(vStr[i].c_str());
	}
}

void prinny::saveItemData()
{
	vector<string> vStr;

	_itemNum = _inventory->getItem()->getVItem().size();

	for (int i = 0; i < _itemNum; ++i)
	{
		vStr.push_back(std::to_string(_inventory->getItem()->getVItem()[i].isWear));
	}

	if (_itemNum == 0)
	{
		vStr.push_back(std::to_string(0));
	}

	TXTDATA->txtSave("itemState.txt", vStr);
}

void prinny::changeSaveData()
{
	vector<string> vStr;

	vStr.push_back(std::to_string(_level));
	vStr.push_back(std::to_string(_counter));
	vStr.push_back(std::to_string(_mv));
	vStr.push_back(std::to_string(_jm));
	vStr.push_back(std::to_string(_hp));
	vStr.push_back(std::to_string(_sp));
	vStr.push_back(std::to_string(_atk));
	vStr.push_back(std::to_string(_int));
	vStr.push_back(std::to_string(_def));
	vStr.push_back(std::to_string(_spd));
	vStr.push_back(std::to_string(_hit));
	vStr.push_back(std::to_string(_res));
	vStr.push_back(std::to_string(_exp));
	vStr.push_back(std::to_string(_next));
	vStr.push_back(std::to_string(_equipWeapon));

	if (strcmp(_name, "prinny") == 0)
	{
		vStr.push_back(std::to_string(_hell));

		int itemNum = _inventory->getItem()->getVItem().size();

		vStr.push_back(std::to_string(itemNum));	//아이템 개수

		//아이템 이름
		for (int i = 0; i < itemNum; ++i)
		{
			vStr.push_back(_inventory->getItem()->getVItem()[i].name);
		}

		_mercenaryNum = _mercenary.size();
		vStr.push_back(std::to_string(_mercenaryNum));	//용병 수

		//용병 이름
		for (int i = 0; i < _mercenaryNum; ++i)
		{
			vStr.push_back(_mercenary[i]);
		}

		TXTDATA->txtSave("prinny.txt", vStr);
	}
	else if (strcmp(_name, "etna") == 0)
	{
		TXTDATA->txtSave("etna.txt", vStr);
	}
	else if (strcmp(_name, "flonne") == 0)
	{
		TXTDATA->txtSave("flonne.txt", vStr);
	}
	else if (strcmp(_name, "raspberyl") == 0)
	{
		TXTDATA->txtSave("raspberyl.txt", vStr);
	}

	saveItemData();
}

void prinny::changeLoadData(int arrNum)
{
	if (arrNum == 0)	//플레이어(prinny)
	{
		_name = "prinny";
	}
	else
	{
		_name = _mercenary[arrNum - 1].c_str();
	}

	vector<string> vStr;

	if (strcmp(_name, "prinny") == 0)
	{
		vStr = TXTDATA->txtLoad("prinny.txt");
	}
	else if (strcmp(_name, "etna") == 0)
	{
		vStr = TXTDATA->txtLoad("etna.txt");
	}
	else if (strcmp(_name, "flonne") == 0)
	{
		vStr = TXTDATA->txtLoad("flonne.txt");
	}
	else if (strcmp(_name, "raspberyl") == 0)
	{
		vStr = TXTDATA->txtLoad("raspberyl.txt");
	}

	int idx = 0;

	_level = atoi(vStr[idx++].c_str());
	_counter = atoi(vStr[idx++].c_str());
	_mv = atoi(vStr[idx++].c_str());
	_jm = atoi(vStr[idx++].c_str());
	_hp = atoi(vStr[idx++].c_str());
	_sp = atoi(vStr[idx++].c_str());
	_atk = atoi(vStr[idx++].c_str());
	_int = atoi(vStr[idx++].c_str());
	_def = atoi(vStr[idx++].c_str());
	_spd = atoi(vStr[idx++].c_str());
	_hit = atoi(vStr[idx++].c_str());
	_res = atoi(vStr[idx++].c_str());
	_exp = atoi(vStr[idx++].c_str());
	_next = atoi(vStr[idx++].c_str());
	_equipWeapon = (WEAPON_TYPE)atoi(vStr[idx++].c_str());
}

void prinny::setItem(const char* itemName, bool isWear)
{
	_inventory->setItem(itemName, isWear);
}

void prinny::setMercenary(const char * characterName)
{
	_mercenary.push_back(characterName);
}

void prinny::setInventory()
{
	_inventory->setName(_name);
	_inventory->setHell(_hell);
	_inventory->setClassStates(_level, _counter, _mv, _jm);
	_inventory->setCharacterStates(_hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next, _equipWeapon);
}

void prinny::setChangeData()
{
	_atk = atoi(_inventory->getAtk().c_str());
	_int = atoi(_inventory->getInt().c_str());
	_def = atoi(_inventory->getDef().c_str());
	_spd = atoi(_inventory->getSpd().c_str());
	_hit = atoi(_inventory->getHit().c_str());
	_res = atoi(_inventory->getRes().c_str());

	if (strcmp(_inventory->getWeapon().c_str(), "sword") == 0)
	{
		_equipWeapon = SWORD;
	}
	else if (strcmp(_inventory->getWeapon().c_str(), "staff") == 0)
	{
		_equipWeapon = STAFF;
	}
	else if (strcmp(_inventory->getWeapon().c_str(), "wand") == 0)
	{
		_equipWeapon = WAND;
	}
	else if (strcmp(_inventory->getWeapon().c_str(), "bow") == 0)
	{
		_equipWeapon = BOW;
	}
	else if (strcmp(_inventory->getWeapon().c_str(), "nothing") == 0)
	{
		_equipWeapon = NONE;
	}
}
