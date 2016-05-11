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
	char* _name;														//ĳ���� �̸�
	int _level, _counter, _mv, _jm;										//ĳ���� �ɷ�ġ 1
	int _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp, _next;		//ĳ���� �ɷ�ġ 2
	bool _isWeaponEquip, _isArmorEquip, _isArtifactEquip, _isEtcEquip;	//��� ��������
	
	WEAPON_TYPE _weaponType;											//���� ���� Ÿ��
	ARMOR_TYPE _armorType;												//���� ���� Ÿ��
	ARTIFACT_TYPE _artifactType;										//���� ��Ƽ��Ʈ Ÿ��

public:
	character();
	virtual ~character();

	HRESULT init();
	void release();
	void update();
	void render();


};

