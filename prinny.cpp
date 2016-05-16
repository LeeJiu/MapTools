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
	IMAGEMANAGER->addFrameImage("prinny_idle", "image/character/prinny_idle.bmp", 714, 484, 7, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_walk", "image/character/prinny_walk.bmp", 776, 492, 8, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_attack", "image/character/prinny_attack.bmp", 780, 484, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_lift", "image/character/prinny_lift.bmp", 720, 524, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_etc", "image/character/prinny_etc.bmp", 468, 528, 4, 4, true, 0xff00ff);

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

	return S_OK;
}

HRESULT prinny::init(vector<TagTile*> tile)
{
	_name = "prinny";

	//loadData();

	_character = IMAGEMANAGER->findImage("prinny_idle");
	_characterState = IDLE;
	_characterDir = RB;
	_curFrameX = 0;
	_count = 0;

	_indexX = 4;
	_indexY = 9;
	_mv = 4;

	_isShow = false;

	for (int i = 0; i < 100; i++)
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
}

void prinny::update()
{
	_inventory->update();
	keyControl();
	setImage();
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
		if (_isShowPossibleMoveTile) character::render();
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
		if (_isUp)
		{
			_characterDir = LT;
		}
		else
		{
			_characterDir = LB;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isRight = true;
		if (_characterState != WALK)
		{
			_characterState = WALK;
		}
		if (_isUp)
		{
			_characterDir = RT;
		}
		else
		{
			_characterDir = RB;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_isUp = true;
		if (_characterState != WALK)
		{
			_characterState = WALK;
		}
		if (_isRight)
		{
			_characterDir = RT;
		}
		else
		{
			_characterDir = LT;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_isUp = false;
		if (_characterState != WALK)
		{
			_characterState = WALK;
		}
		if (_isRight)
		{
			_characterDir = RB;
		}
		else
		{
			_characterDir = LB;
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

void prinny::move(int endX, int endY)
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
}

void prinny::saveData()
{
	vector<string> vStr;

	vStr.push_back(std::to_string(_level));
	vStr.push_back(std::to_string(_counter));
	vStr.push_back(std::to_string(_mv));
	vStr.push_back(std::to_string(_jm));
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
	for (int i = 0; i < itemNum; ++i)		//index = 14 ~ 14+itemNum
	{
		setItem(vStr[idx++].c_str());
	}
}

void prinny::setItem(const char* itemName)
{
	_inventory->setItem(itemName);
}
