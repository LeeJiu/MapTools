#pragma once
#include "gameNode.h"
#include "progressBar.h"

class gameObjectManager;

class gameObject : public gameNode
{
protected:
	vector<TagTile*> _vRoute;

	const char* _name;																//ĳ���� �̸�
	int _level, _counter, _mv, _jm;													//ĳ���� �ɷ�ġ 1
	int _maxHp, _maxSp, _hp, _sp, _atk, _int, _def, _spd, _hit, _res, _exp;			//ĳ���� �ɷ�ġ 2
	int _curFrameX, _curFrameY, _count;
	int _currentMoveCount;

	image* _character;
	image* _shadow;
	RECT _rc;
	int _x, _y;							// �̹���(��Ʈ) ����x ����y
	int _oldX, _oldY;					// �������� ������ x, y �ε���
	int _indexX, _indexY;				// �������� ������ x, y �ε���
	int _destX, _destY;					// �������� ������ x, y �ε���
	int _targetX, _targetY;				// ������ ĳ���� ��ġ x, y (���ʹ� -> �÷��̾�)
	int _targetIdx;

	float _pivotY;

	vector<string> _mercenary;

	int _idx;							// �̵��� vRoute���� ���� �ε���
	int _moveSpeed;
	int _attackCnt;						// ���� �������� 2�� ���� �ϱ� ���� ����

	bool _isUp, _isRight;
	bool _isShow;
	bool _isCharacter;					// ĳ�������� ������
	bool _isMove;						// �����̰� �ִ��� ����
	bool _isShowPossibleMoveTile;		// �̵������� Ÿ�� �����ִ��� ����
	bool _isShowPossibleAttackTile;		// ���ݰ����� Ÿ�� �����ִ��� ����
	bool _isAction;						// ��ɹ��� �׼��� �ִ��� �Ǵ� ����

	CHARACTER_STATE _characterState;
	CHARACTER_DIRECTION _characterDir;

	progressBar* _hpBar;

	gameObjectManager* _gameObjMgr;

public:
	gameObject();
	~gameObject();

	//������ init
	virtual HRESULT init();

	//������ init
	virtual HRESULT init(int x, int y, gameObjectManager* gom);
	virtual HRESULT init(const char* strkey, int x, int y, int imageNum, gameObjectManager* gom);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			�Լ� �߰�			*/
	
	// ���� �ٽ� ����������ϴ� �Լ���
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void setImage();
	virtual void saveData();
	virtual void loadData();

	// �ɸ��� �������� ���� �Լ���
	virtual void showPossibleMoveTile();					// �̵������� Ÿ�� �����ִ� �Լ�
	virtual void showPossibleAttackTile();					// ���ݰ����� Ÿ�� �����ִ� �Լ�
	virtual void previousState();							// �������� ���ư��� �Լ�
	virtual void attack(int targetX, int targetY);
	virtual void pain(int x, int y, int damage);
	virtual void move();
	virtual void setDirectionImage();
	virtual void setEnemyMove(int targetIdx, int targetX, int targetY, int endX, int endY, vector<TagTile*>& vRoute);
	virtual void setCharacterMove(int endX, int endY, vector<TagTile*>& vRoute);
	virtual void setFrame();

	// set�Լ�
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

	// get�Լ�
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
