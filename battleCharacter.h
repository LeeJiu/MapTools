#pragma once
#include "gameNode.h"

enum CHARACTER_DIRECTION
{
	LEFT_TOP, RIGHT_TOP,
	LEFT_BOTTOM, RIGHT_BOTTOM
};

struct tagAbility
{
	int _hp;
	int _sp;
	int _atk;
	int _int;
	int _def;
	int _spd;
	int _hit;
	int _res;
	int _exp;
	int _next;
};

struct tagBattleCharacter
{
	TagTile tile;
	image* imageCharacter;
	RECT rcCharacter;
	char* name;
	int level, counter, mv, jm;
	tagAbility ability;
	bool isWeaponEquip, isArmorEquip, isArtifactEquip, isEtcEquip;
	CHARACTER_DIRECTION _direction;
};

class battleCharacter : public gameNode
{
private:
	tagBattleCharacter _character;


public:
	battleCharacter();
	~battleCharacter();

	HRESULT init();
	void release();
	void update();
	void render();

	void characterMoveFrameSet(CHARACTER_DIRECTION direction);

	tagBattleCharacter getCharacter() { return _character; }
};

