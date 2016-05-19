#include "stdafx.h"
#include "mercenaryStore.h"


mercenaryStore::mercenaryStore()
{
}


mercenaryStore::~mercenaryStore()
{
}

HRESULT mercenaryStore::init()
{
	/*			store ui			*/
	_rcStoreTitle = RectMake(30, 30, 162, 65);
	_rcListTitle = RectMake(80, 120, 200, 50);
	_rcMercenaryList = RectMake(79, 150, 300, 389);
	_rcMercenaryStatus = RectMake(449, 150, 400, 389);
	_rcMercenaryInfo = RectMake(49, WINSIZEY - 115, 1182, 65);
	_rcMyList = RectMake(899, 150, 300, 389);
	_rcExit = RectMake(WINSIZEX - 202, 30, 162, 65);
	_rcBuy = RectMake(1000, 545, 200, 50);
	_rcHell = RectMake(650, 545, 300, 50);

	//플레이어를 정보를 받아온다.
	_prinny = new prinny;
	_prinny->init();
	_hell = std::to_string(_prinny->getHell());
	
	_curFrameX = 0;
	_count = 0;
	_x = (_rcMercenaryList.left + _rcMercenaryList.right) / 2;
	_y = (_rcMercenaryList.top + _rcMercenaryList.bottom) / 2;

	//초기 용병 정보
	//용병 기초 정보 데이터를 읽어와서 저장
	_name = "flonne";
	_buyIdx = 2;
	_mercenaryImage = IMAGEMANAGER->findImage("flonne_idle");
	_characterState = IDLE;
	
	loadMercenaryData();

	return S_OK;
}

void mercenaryStore::release()
{
}

void mercenaryStore::update()
{
	setImage();

	keyControl();
}

void mercenaryStore::render()
{
	IMAGEMANAGER->findImage("store_background")->render(getMemDC(), 0, 0);

	IMAGEMANAGER->findImage("store_title")->render(getMemDC(), _rcStoreTitle.left, _rcStoreTitle.top);
	IMAGEMANAGER->findImage("store_exit")->render(getMemDC(), _rcExit.left, _rcExit.top);
	IMAGEMANAGER->findImage("store_list_mercenary")->render(getMemDC(), _rcMercenaryList.left, _rcMercenaryList.top);
	IMAGEMANAGER->findImage("store_character_title")->render(getMemDC(), _rcListTitle.left, _rcListTitle.top);
	IMAGEMANAGER->findImage("store_status_mercenary")->render(getMemDC(), _rcMercenaryStatus.left, _rcMercenaryStatus.top);
	IMAGEMANAGER->findImage("store_mylist")->render(getMemDC(), _rcMyList.left, _rcMyList.top);
	IMAGEMANAGER->findImage("store_hell")->render(getMemDC(), _rcHell.left, _rcHell.top);
	IMAGEMANAGER->findImage("store_hire")->render(getMemDC(), _rcBuy.left, _rcBuy.top);
	IMAGEMANAGER->findImage("store_info")->render(getMemDC(), _rcMercenaryInfo.left, _rcMercenaryInfo.top);

	_mercenaryImage->frameRender(getMemDC(), _x - _mercenaryImage->getFrameWidth() / 2, _y - _mercenaryImage->getFrameHeight() / 2, _curFrameX, 0);

	HFONT font, oldFont;
	font = CreateFont(30, 0, 0, 0, 800, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	DrawText(getMemDC(), _name, -1, 
		&RectMake(_rcMercenaryStatus.left + 30, _rcMercenaryStatus.top + 30, 200, 30), DT_LEFT | DT_VCENTER);
	DrawText(getMemDC(), _level.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 45, _rcMercenaryStatus.top + 100, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _counter.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 45, _rcMercenaryStatus.top + 140, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _mv.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 45, _rcMercenaryStatus.top + 178, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _jm.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 45, _rcMercenaryStatus.top + 218, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _hp.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 45, _rcMercenaryStatus.top + 258, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _sp.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 45, _rcMercenaryStatus.top + 296, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _price.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 45, _rcMercenaryStatus.top + 335, 150, 30), DT_RIGHT | DT_VCENTER);

	DrawText(getMemDC(), _atk.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 215, _rcMercenaryStatus.top + 100, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _int.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 215, _rcMercenaryStatus.top + 140, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _def.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 215, _rcMercenaryStatus.top + 178, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _spd.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 215, _rcMercenaryStatus.top + 218, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _hit.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 215, _rcMercenaryStatus.top + 258, 150, 30), DT_RIGHT | DT_VCENTER);
	DrawText(getMemDC(), _res.c_str(), -1,
		&RectMake(_rcMercenaryStatus.left + 215, _rcMercenaryStatus.top + 296, 150, 30), DT_RIGHT | DT_VCENTER);
	
	DrawText(getMemDC(), _hell.c_str(), -1,
		&RectMake(_rcHell.left + 20, _rcHell.top + 10, 220, 50), DT_RIGHT | DT_VCENTER);

	int listNum = _prinny->getMercenary().size();
	for (int i = 0; i < listNum; ++i)
	{
		DrawText(getMemDC(), _prinny->getMercenary()[i].c_str(), -1,
			&RectMake(_rcMyList.left + 30, _rcMyList.top + (50 * (i + 1)), 200, 50), DT_LEFT | DT_VCENTER);
	}

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}

void mercenaryStore::buyMercenary(const char * characterName)
{
	//플레이어의 용병 리스트에 선택된 용병의 이름을 추가
	//선택된 용병이 이미 있으면 지워주는 조건을 만들어야함
	int remainHell = atoi(_hell.c_str()) - atoi(_price.c_str());
	if (remainHell >= 0)
	{
		_prinny->setHell(remainHell);
		_prinny->setMercenary(characterName);
		_hell = std::to_string(remainHell);
	}
}

void mercenaryStore::keyControl()
{
	if (PtInRect(&_rcMercenaryList, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//용병 캐릭터 넘기기
			if (_ptMouse.x < (_rcMercenaryList.left + _rcMercenaryList.right) / 3)
			{
				_buyIdx--;
				if (_buyIdx < 1) _buyIdx = 3;
				showMercenaryInfoAll();
			}
			else if (_ptMouse.x > (_rcMercenaryList.left + _rcMercenaryList.right) / 3 * 2)
			{
				_buyIdx++;
				if (_buyIdx > 3) _buyIdx = 1;
				showMercenaryInfoAll();
			}
			//용병 모션 변경
			else if ((_ptMouse.x > (_rcMercenaryList.left + _rcMercenaryList.right) / 3)
				&& (_ptMouse.x < (_rcMercenaryList.left + _rcMercenaryList.right) / 3 * 2))
			{
				_stateNum++;
				if (_stateNum > 2) _stateNum = 0;
				_characterState = (CHARACTER_STATE)_stateNum;
			}
		}
	}

	//buy를 누르면 현재 보이는 용병을 고용
	if (PtInRect(&_rcBuy, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			buyMercenary(_name);
		}
	}

	//exit를 누르면 현재 플레이어의 용병 리스트를 저장
	if (PtInRect(&_rcExit, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			saveMercenaryData();
			_prinny->saveData();
			SCENEMANAGER->changeScene("town");
		}
	}
}

void mercenaryStore::showMercenaryInfoAll()
{
	//현재 화면의 용병 정보로 갱신
	switch (_buyIdx)
	{
	case 1:		//etna
		_name = "etna";
		break;
	case 2:		//flonne
		_name = "flonne";
		break;
	case 3:		//raspberyl
		_name = "raspberyl";
		break;
	}
	loadMercenaryData();
}

void mercenaryStore::setImage()
{
	switch (_characterState)
	{
	case IDLE:
		if (strcmp(_name, "etna") == 0)
		{
			_mercenaryImage = IMAGEMANAGER->findImage("etna_idle");
		}
		else if (strcmp(_name, "flonne") == 0)
		{
			_mercenaryImage = IMAGEMANAGER->findImage("flonne_idle");
		}
		else if (strcmp(_name, "raspberyl") == 0)
		{
			_mercenaryImage = IMAGEMANAGER->findImage("raspberyl_idle");
		}
		break;

	case WALK:
		if (strcmp(_name, "etna") == 0)
		{
			_mercenaryImage = IMAGEMANAGER->findImage("etna_walk");
		}
		else if (strcmp(_name, "flonne") == 0)
		{
			_mercenaryImage = IMAGEMANAGER->findImage("flonne_walk");
		}
		else if (strcmp(_name, "raspberyl") == 0)
		{
			_mercenaryImage = IMAGEMANAGER->findImage("raspberyl_walk");
		}
		break;

	case ATTACK:
		if (strcmp(_name, "etna") == 0)
		{
			_mercenaryImage = IMAGEMANAGER->findImage("etna_attack");
		}
		else if (strcmp(_name, "flonne") == 0)
		{
			_mercenaryImage = IMAGEMANAGER->findImage("flonne_attack");
		}
		else if (strcmp(_name, "raspberyl") == 0)
		{
			_mercenaryImage = IMAGEMANAGER->findImage("raspberyl_attack");
		}
		break;
	}

	setFrame();
}

void mercenaryStore::setFrame()
{
	_count++;
	_mercenaryImage->setFrameY(0);
	if (_count % 10 == 0)
	{
		_curFrameX++;
		if (_curFrameX > _mercenaryImage->getMaxFrameX())
		{
			_curFrameX = 0;
		}
		_mercenaryImage->setFrameX(_curFrameX);
	}
}

void mercenaryStore::saveMercenaryData()
{
	//플레이어가 가지고 있는 용병 수
	int mercenaryNum = _prinny->getMercenary().size();

	for (int i = 0; i < mercenaryNum; ++i)
	{
		_name = _prinny->getMercenary()[i].c_str();
		loadMercenaryData();

		vector<string> vStr;

		vStr.push_back(_level);
		vStr.push_back(_counter);
		vStr.push_back(_mv);
		vStr.push_back(_jm);
		vStr.push_back(_hp);
		vStr.push_back(_sp);
		vStr.push_back(_atk);
		vStr.push_back(_int);
		vStr.push_back(_def);
		vStr.push_back(_spd);
		vStr.push_back(_hit);
		vStr.push_back(_res);
		vStr.push_back(std::to_string(0));
		vStr.push_back(std::to_string(100));
		vStr.push_back(std::to_string(0));

		if (strcmp(_name, "etna") == 0)
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
	}
}

void mercenaryStore::loadMercenaryData()
{
	vector<string> vStr;
	
	//용병의 기본 정보를 로드
	if (strcmp(_name, "etna") == 0)
	{
		vStr = TXTDATA->txtLoad("etnaStore.txt");
	}
	else if (strcmp(_name, "flonne") == 0)
	{
		vStr = TXTDATA->txtLoad("flonneStore.txt");
	}
	else if (strcmp(_name, "raspberyl") == 0)
	{
		vStr = TXTDATA->txtLoad("raspberylStore.txt");
	}

	int idx = 0;
	
	_level = vStr[idx++].c_str();
	_counter = vStr[idx++].c_str();
	_mv = vStr[idx++].c_str();
	_jm = vStr[idx++].c_str();
	_hp = vStr[idx++].c_str();
	_sp = vStr[idx++].c_str();
	_atk = vStr[idx++].c_str();
	_int = vStr[idx++].c_str();
	_def = vStr[idx++].c_str();
	_spd = vStr[idx++].c_str();
	_hit = vStr[idx++].c_str();
	_res = vStr[idx++].c_str();
	_price = vStr[idx++].c_str();
}
