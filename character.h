#pragma once
#include "gameObject.h"

enum WEAPON_TYPE
{
	WEAPON_NONE, WEAPON_SWORD, WEAPON_WAND, WEAPON_STAFT, WEAPON_BOW
};

enum ARMOR_TYPE
{
	ARMOR_NONE, ARMOR_LADDER, ARMOR_ROBE, ARMOR_CHAINMAIL
};

enum ARTIFACT_TYPE
{
	ARTIFACT_NONE, ARTIFACT_NECKLESS, ARTIFACT_RING
};

class character : public gameObject
{
public:
	const char* _fileName;
	image* _character;
	RECT _rc;
	char* _name;														//캐릭터 이름
	int _level, _counter, _mv, _jm;										//캐릭터 능력치 1
	int _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next;		//캐릭터 능력치 2
	bool _isWeaponEquip, _isArmorEquip, _isArtifactEquip, _isEtcEquip;	//장비 장착여부
	
	WEAPON_TYPE _weaponType;											//장착 무기 타입
	ARMOR_TYPE _armorType;												//장착 갑옷 타입
	ARTIFACT_TYPE _artifactType;										//장착 아티팩트 타입

public:
	character();
	virtual ~character();

	HRESULT init();
	void release();
	void update();
	void render();


};

