#pragma once
#include "gameNode.h"
#include "character.h"
#include "button.h"
#include "enemy.h"
#include "battleCamera.h"
#include "progressBar.h"

class battleManager;
class gameObjectManager;
class battleUI : public gameNode
{
private:
	// ------------ ĳ���� ���� â(�ٴ�) ------------
	image* _imageIconCharacter;             //ĳ���� ���� â(�ٴ�) ĳ���� ������ IMAGE
	RECT _rcBottomStatus;					//ĳ���� ���� â(�ٴ�)
	RECT _rcIconCharacter;					//ĳ���� ���� â(�ٴ�) ĳ���� ����
	image* _imageBottomStatusBack;          //ĳ���� ���� â(�ٴ�) BACKGROUND IMAGE


											// ------------ �Ϲ� ���â ����Ʈ ------------
	image* _imageOrderListTop;				//�Ϲ� ���� ����Ʈ BACKGROUND IMAGE TOP
	vector<image*> _imageOrderListBody;		//�Ϲ� ���� ����Ʈ BACKGROUND IMAGE BODY
	image* _imageOrderListBottom;			//�Ϲ� ���� ����Ʈ BACKGROUND IMAGE BOTTOM
	RECT _rcOrderListTop;					//�Ϲ� ��� ����Ʈ RECT TOP
	vector<RECT> _rcOrderListBody;          //�Ϲ� ��� ����Ʈ RECT BODY
	RECT _rcOrderListBottom;				//�Ϲ� ��� ����Ʈ RECT BOTTOM
	vector<char*> _vOrderList;				//�Ϲ� ��� â char*
	vector<RECT> _rcOrderListStr;			//�Ϲ� ��� â STR�� RECT


											// ------------ ĳ���� ���â ����Ʈ ------------
	image* _imageUnitOrderListTop;			//ĳ���� ���� ����Ʈ BACKGROUND IMAGE TOP
	vector<image*> _imageUnitOrderListBody;	//ĳ���� ���� ����Ʈ BACKGROUND IMAGE BODY
	image* _imageUnitOrderListBottom;		//ĳ���� ���� ����Ʈ BACKGROUND IMAGE BOTTOM
	RECT _rcUnitOrderListTop;				//ĳ���� ��� ����Ʈ RECT TOP
	vector<RECT> _rcUnitOrderListBody;		//ĳ���� ��� ����Ʈ RECT BODY
	RECT _rcUnitOrderListBottom;			//ĳ���� ��� ����Ʈ RECT BOTTOM
	vector<char*> _vUnitOrderList;			//���� ��� â char*
	vector<RECT> _rcUnitOrderListStr;		//���� ��� â STR�� RECT


											// ------------ ĳ���� ��ȯ�� ����Ʈ ------------
	image* _imageCharacterListTop;			//ĳ���� ��ȯ ����Ʈ BACKGROUND IMAGE TOP
	vector<image*> _imageCharacterListBody;	//ĳ���� ��ȯ ����Ʈ BACKGROUND IMAGE BODY
	image* _imageCharacterListBottom;		//ĳ���� ��ȯ ����Ʈ BACKGROUND IMAGE BOTTOM
	RECT _rcCharacterListTop;				//ĳ���� ��ȯ ����Ʈ TOP
	vector<RECT> _rcCharacterListBody;		//ĳ���� ��ȯ ����Ʈ BODY
	RECT _rcCharacterListBottom;			//ĳ���� ��ȯ ����Ʈ BOTTOM
	vector<string> _vCharacterList;			//ĳ���� ��ȯ ����Ʈ char*
	vector<RECT> _rcCharacterListStr;		//ĳ���� ��ȯ ����Ʈ STR�� RECT


											// ------------ ������ ĳ����(Ÿ��) ����Ʈ ------------
	image* _imageAttackListTop;				//������ Ÿ�� ����Ʈ BACKGROUND IMAGE TOP
	vector<image*> _imageAttackListBody;	//������ Ÿ�� ����Ʈ BACKGROUND IMAGE BODY
	image* _imageAttackListBottom;			//������ Ÿ�� ����Ʈ BACKGROUND IMAGE BOTTOM
	RECT _rcAttackListTop;					//������ Ÿ�� ����Ʈ TOP
	vector<RECT> _rcAttackListBody;			//������ Ÿ�� ����Ʈ BODY
	RECT _rcAttackListBottom;				//������ Ÿ�� ����Ʈ BOTTOM
	vector<RECT> _rcAttackListStr;			//������ Ÿ�� ����Ʈ char*
	vector<char*> _vAttackList;				//������ Ÿ�� ����Ʈ STR�� RECT


											// ------------ ����Ʈ ȭ��ǥ ------------ 
	image* _imageListArrow;
	RECT _rcListArrow;
	bool _IsOnListArrow;


	// ------------ ĳ���� ���� â(��) ------------
	image* _imageStatusBack;             //ĳ���� ���� â BACKGROUND IMAGE
	RECT _rcStatus;                      //ĳ���� ���� â(��)	


										 // ------------ ���� �� ǥ��� ������ ------------
	image* _imageTurnCountBackground;       //���� �� ǥ��� BACKGROUND IMAGE
	RECT _rcTurnCountBack;					//���� �� ǥ��� RECT
	RECT _rcTurnCountStr;					//���� �� ǥ�� STR�� RECT
	char* _strTurnCount;					//���� �� ǥ��� char*


											// ------------ �� ǥ��� ������ ------------
	bool _isTurnType;				//���� TURN�� ������ ���ΰ�? TRUE = PLAYER, FALSE = ENEMY
	bool _isTurnShow;				//TURN IMAGE�� SHOW ����� �ϴ°� ���ƾ��ϴ°�?
	bool _isFirstShow;				//BATTLE SCENE�� ó�� ���Դ°�?
	bool _isTurnBackCenter;			//TURN IMAGE�� �߾ӱ��� �Դ°�?
	RECT _rcTurnBack;				//TURN IMAGE�� �� ��� RECT
	image* _imageTurnStr;           //TURN IMAGE STR
	image* _imageTurnBack;          //TURN IMAGE BACKGROUND
	int _turnBackPosX;              //TURN RECT�� LEFT ��ġ
	float _turnShowTime;			//TURN IMAGE�� �߾ӱ��� ���� �� 1�ʰ� ���� ��ų �뵵�� TIME


									// ------------ ���콺 ���� �� �� SELECT TILE ��¿� ���� ------------
	image* _imageSelectTile;        //���� �� Ÿ���� �׵θ� �̹���
	RECT _rcSelectTile;				//���� �� Ÿ���� �׵θ� ��¿� RECT
	int _count;						// Select Tile Arrow Motion Count


									// ------------ ���� â(�ٴ�) ������ ------------
	RECT _rcStatusBottomName;			//RECT ĳ���� NAME
	const char* _statusBottomName;		//char* ĳ���� NAME
	progressBar* _progressBarHp;		//ProgressBar HP
	progressBar* _progressBarSp;		//ProgressBar SP


										// ------------ UI �� â�� On/Off üũ�� BOOL ������ ------------
	bool _isOnStatus;				//���� â On/Off
	bool _isOnSkillTitle;           //��ų Ÿ��Ʋ On/Off
	bool _isOnBottomStatus;         //���� â(�ٴ�) On/Off
	bool _isOnCharacterList;        //ĳ���� ����Ʈ On/Off
	bool _isOnOrderList;			//��� â On/Off
	bool _isOnUnitOrderList;        //ĳ���� ��� â On/Off
	bool _isOnSelectTile;           //����ƮŸ�� On/off
	bool _isOnSelectTarget;			//���� Ÿ���� ����ؾ��ϴ��� ����
	bool _isSelectCharacter;		//� ĳ���͸� �����ߴ��� ����


									// ------------ ��Ÿ ------------
	RECT _rcSkillTitle;                 //ĳ���� ��ų Ÿ��Ʋ(��ų ��� �� ��Ÿ��)	
	image* _imageSkillTitleBack;        //��ų Ÿ��Ʋ BACKGROUND IMAGE
	int _characterSize;					//ĳ���� Vector Size
	int _enemySize;						//Enemy Vector Size
	int _orderListSize;					//�Ϲ� ��� â Size
	int _unitOrderListSize;				//���� ���â Size
	int _selectTargetNumber;			//������ Ÿ�� �ѹ�(���� ��)
	int _selectCharacterNumber;			//������ �÷��̾� ĳ���� �ѹ�


	gameObjectManager* _gameObjMgr;
	battleManager* _battleMgr;
	battleCamera* _battleCamera;

public:
	battleUI();
	~battleUI();

	HRESULT init();
	void release();
	void update();
	void render();
	void setCharacterList();

	void initOrderList();
	void initUnitOrderList();

	void setTurnShow() { _isTurnShow = true; }	//�ܺο��� Turn Show�� ���Ѿ� �� �� �� �Լ��� �̿��Ͽ� Turn�� Show ��Ų��
	void renderOverlapSelectTile();				//���콺 ���� �� �� Ÿ�Ͽ� SelectTile Image�� ���
	void renderOverlapAttackSelectTile();		//���콺 ���� �� �� ���� Ÿ�Ͽ� SelectTile Image�� ���

	bool checkTileOnCharacter(int i, int j);
	void orderListClick(int orderNumber);
	void unitOrderListClick(int unitOrderNumber);
	void turnChange();

	void updateRectPos();

	//Ŭ�� �̺�Ʈ
	void LButtonClick();
	void RButtonClick();
	void checkMouseOverList();
	void checkMouseOverCharacter();

	void setTurnTypeChangeToPlayer() { _isTurnType = true; }         //ENEMY���� PLAYER TURN���� �Ѿ �� ȣ���ؼ� PLAYER TURN IMAGE�� ȣ��

	void setArrowFrame();
	void setCamera();
	void setGameObjectSize();
	void setObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
	void setBattleManagerMemoryLink(battleManager* battleMgr) { _battleMgr = battleMgr; }
};
