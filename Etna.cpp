#include "stdafx.h"
#include "etna.h"


etna::etna()
{
}


etna::~etna()
{
}

HRESULT etna::init()
{
	return S_OK;
}

HRESULT etna::init(vector<TagTile*> tile)
{
	_name = "etna";

	loadData();

	_isCharacter = true;
	_character = IMAGEMANAGER->findImage("prinny_idle");
	_characterState = IDLE;
	_characterDir = LB;
	_curFrameX = 0;
	_count = 0;

	_moveSpeed = 3;

	return S_OK;
}

void etna::release()
{
}

void etna::update()
{
}

void etna::render()
{
}

void etna::keyControl()
{
}

void etna::battleKeyControl()
{
}


void etna::setImage()
{
}

void etna::setFrame()
{
}

void etna::saveData()
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

	TXTDATA->txtSave("etna.txt", vStr);
}

void etna::loadData()
{
	vector<string> vStr;

	vStr = TXTDATA->txtLoad("etna.txt");

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

void etna::setItem(const char * itemName, bool isWear)
{
}

void etna::setMercenary(const char * characterName)
{
}

void etna::setHell(int hell)
{
}

int etna::getHell()
{
	return 0;
}
