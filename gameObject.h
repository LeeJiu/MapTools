#pragma once
#include "gameNode.h"
#include "progressBar.h"

class gameObjectManager;

class gameObject : public gameNode
{
protected:
	vector<TagTile*> _vRoute;

	const char* _name;																//캐릭터 이름
	int _level, _counter, _mv, _jm;													//캐릭터 능력치 1
	int _maxHp, _maxSp, _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp;			//캐릭터 능력치 2
	int _curFrameX, _curFrameY, _count;
	int _currentMoveCount;

	image* _character;
	image* _shadow;
	RECT _rc;
	int _x, _y;							// 이미지(렉트) 센터x 센터y
	int _oldX, _oldY;					// 전투맵의 이전의 x, y 인덱스
	int _indexX, _indexY;				// 전투맵의 현재의 x, y 인덱스
	int _destX, _destY;					// 전투맵의 목적지 x, y 인덱스
	int _targetX, _targetY;				// 공격할 캐릭터 위치 x, y (에너미 -> 플레이어)
	int _targetIdx;

	float _pivotY;

	vector<string> _mercenary;

	int _idx;							// 이동시 vRoute에서 사용될 인덱스
	int _moveSpeed;
	int _attackCnt;						// 어텍 프레임이 2번 돌게 하기 위한 변수

	bool _isUp, _isRight;
	bool _isShow;
	bool _isCharacter;					// 캐릭터인지 적인지
	bool _isMove;						// 움직이고 있는지 유무
	bool _isShowPossibleMoveTile;		// 이동가능한 타일 보여주는지 유무
	bool _isShowPossibleAttackTile;		// 공격가능한 타일 보여주는지 유무
	bool _isAction;						// 명령받은 액션이 있는지 판단 변수

	CHARACTER_STATE _characterState;
	CHARACTER_DIRECTION _characterDir;

	progressBar* _hpBar;

	gameObjectManager* _gameObjMgr;

public:
	gameObject();
	~gameObject();

	//마을맵 init
	virtual HRESULT init();

	//전투맵 init
	virtual HRESULT init(int x, int y, gameObjectManager* gom);
	virtual HRESULT init(const char* strkey, int x, int y, int imageNum, gameObjectManager* gom);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			함수 추가			*/
	
	// 각각 다시 정의해줘야하는 함수들
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void setImage();
	virtual void saveData();
	virtual void loadData();

	// 케릭터 공통으로 쓰는 함수들
	virtual void showPossibleMoveTile();					// 이동가능한 타일 보여주는 함수
	virtual void showPossibleAttackTile();					// 공격가능한 타일 보여주는 함수
	virtual void previousState();							// 이전으로 돌아가는 함수
	virtual void attack(int targetX, int targetY);
	virtual void pain(int x, int y, int damage);
	virtual void move();
	virtual void setDirectionImage();
	virtual void setEnemyMove(int targetIdx, int targetX, int targetY, int endX, int endY, vector<TagTile*>& vRoute);
	virtual void setCharacterMove(int endX, int endY, vector<TagTile*>& vRoute);
	virtual void setFrame();

	// set함수
	virtual void setItem(const char* itemName, bool isWear) = 0;
	virtual void setMercenary(const char* characterName) = 0;
	virtual void setHell(int hell) = 0;
	virtual void setIsShowPossibleMoveTile(bool isShowPossibleMoveTile) { _isShowPossibleMoveTile = isShowPossibleMoveTile; }
	virtual void setIsShowPossibleAttackTile(bool isSHowPossibleAttackTile) { _isShowPossibleAttackTile = isSHowPossibleAttackTile; }
	virtual void setVRoute(vector<TagTile*>& tile) { _vRoute = tile; }
	virtual void setIsMove(bool isMove) { _isMove = isMove; }
	virtual void setIsShow(bool isShow) { _isShow = isShow; }
	virtual void setHp(int damage) { _hp -= damage; if (_hp < 0) _hp = 0; }
	virtual void setSp(int consume) { _sp -= consume; if (_sp < 0) _sp = 0; }
	virtual void setIsAction(bool isAction) { _isAction = isAction; }

	// get함수
	virtual const char* getName() { return _name; }
	virtual RECT getRect() { return _rc; }
	virtual int getHell() = 0;
	virtual int getLevel() { return _level; }
	virtual int getCounter() { return _counter; }
	virtual int getMv() { return _mv; }
	virtual int getJm() { return _jm; }
	virtual int getMaxHp() { return _maxHp; }
	virtual int getMaxSp() { return _maxSp; }
	virtual int getHp() { return _hp; }
	virtual int getSp() { return _sp; }
	virtual int getAtk() { return _atk; }
	virtual int getInt() { return _int; }
	virtual int getDef() { return _def; }
	virtual int getSpd() { return _spd; }
	virtual int getHit() { return _hit; }
	virtual int getRes() { return _res; }
	virtual int getExp() { return _exp; }
	virtual int getIndexX() { return _indexX; }
	virtual int getIndexY() { return _indexY; }
	virtual float getPivotY() { return _pivotY; }
	virtual RECT getCharacterRect() { return _rc; }
	virtual bool getIsShow() { return _isShow; }
	virtual bool getIsAction() { return _isAction; }
	virtual vector<string>& getMercenary() { return _mercenary; }
	virtual bool getIsShowPossibleMoveTile() { return _isShowPossibleMoveTile; }
	virtual bool getIsShowPossibleAttackTile() { return _isShowPossibleAttackTile; }
};
