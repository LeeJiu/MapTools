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

	/*			character status setting			*/
	//character 정보를 load 해오기
	loadData();

	//_hell = 1000;

	_character = IMAGEMANAGER->findImage("prinny_idle");
	_characterState = IDLE;
	_characterDir = LB;
	_curFrameX = 0;
	_count = 0;
	_x = CENTERX;
	_y = CENTERY;
	_rc = RectMakeCenter(_x, _y, _character->getFrameWidth(), _character->getFrameHeight());

	_mercenary.reserve(4);	//벡터 크기 4로 예약

	return S_OK;
}

HRESULT prinny::init(vector<TagTile*> tile)
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

	_indexX = 4;
	_indexY = 9;
	_mv = 4;
	_isShow = false;
	_isbattle = true;

	for (int i = 0; i < TOTALTILE(TILENUM); i++)
	{
		_tile[i % TILENUM][i / TILENUM] = tile[i];
	}

	_vTile = tile;

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
	setImage();
	setDirectionImage();

	if (_isbattle)
	{
		if (!_isMove)
		{
			_rc = RectMakeIso(_tile[_indexX][_indexY]->pivotX, _tile[_indexX][_indexY]->pivotY, _character->getFrameWidth(), _character->getFrameHeight());
			_x = (_rc.right + _rc.left) / 2;
			_y = (_rc.top + _rc.bottom) / 2;
		}
		battleKeyControl();
		move();
	}
	else
	{
		_inventory->update();
		keyControl();
	}
}

void prinny::render()
{
	if (!_isbattle)
	{
		_character->frameRender(getMemDC(), _rc.left, _rc.top, _curFrameX, _curFrameY);
		_inventory->render();
	}
	else
	{
		if (_isShow)
		{
			//if (_isShowPossibleMoveTile) character::render();

			if (_isShowPossibleMoveTile) showPossibleMoveTile();
			if (_isShowPossibleAttackTile) gameObject::showPossibleAttackTile();
			_character->frameRender(getMemDC(), _rc.left, _rc.top, _curFrameX, _curFrameY);
			//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
			
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
		_inventory->showInventory();
		_inventory->setName(_name);
		_inventory->setHell(_hell);
		_inventory->setClassStates(_level, _counter, _mv, _jm);
		_inventory->setCharacterStates(_hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next);
		_invenExit = _inventory->getExit();
	}

	if (PtInRect(&_invenExit, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_inventory->closeInventory();
			_invenExit = RectMake(0, 0, 0, 0);
		}
	}
}

void prinny::battleKeyControl()
{
}

void prinny::move()
{
	gameObject::move();
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

	setFrame();
}

void prinny::setFrame()
{
	_count++;

	switch (_characterDir)
	{
	case LB:
		_curFrameY = 0;
		_character->setFrameY(_curFrameY);
		break;

	case RB:
		_curFrameY = 1;
		_character->setFrameY(_curFrameY);
		break;

	case RT:
		_curFrameY = 2;
		_character->setFrameY(_curFrameY);
		break;

	case LT:
		_curFrameY = 3;
		_character->setFrameY(_curFrameY);
		break;
	}

	if (_count % 10 == 0)
	{
		_curFrameX++;
		if (_curFrameX > _character->getMaxFrameX())
		{
			_curFrameX = 0;
		}
		_character->setFrameX(_curFrameX);
	}
}

void prinny::previousState()
{
}

void prinny::showPossibleMoveTile()
{
	gameObject::showPossibleMoveTile();
}

void prinny::setDirectionImage()
{
	gameObject::setDirectionImage();
}

void prinny::attack(int targetX, int targetY)
{
	gameObject::attack(targetX, targetY);
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
	_hell = atoi(vStr[idx++].c_str());

	int itemNum = atoi(vStr[idx++].c_str());
	for (int i = 0; i < itemNum; ++i)		//index = 16 ~ 16+itemNum
	{
		setItem(vStr[idx++].c_str());
	}

	_mercenaryNum = atoi(vStr[idx++].c_str());
	for (int i = 0; i < _mercenaryNum; ++i)
	{
		setMercenary(vStr[idx++].c_str());
	}
}

void prinny::setCharacterMove(int endX, int endY, vector<TagTile*> vRoute)
{
	gameObject::setCharacterMove(endX, endY, vRoute);
}

void prinny::setItem(const char* itemName)
{
	_inventory->setItem(itemName);
}

void prinny::setMercenary(const char * characterName)
{
	_mercenary.push_back(characterName);
}
