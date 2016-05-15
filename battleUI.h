#pragma once
#include "gameNode.h"
#include "character.h"
#include "button.h"
#include "enemy.h"

class gameObjectManager;
class battleUI : public gameNode
{
private:
	image* _imageSkillTitleBack;			 //��ų Ÿ��Ʋ BACKGROUND IMAGE
	image* _imageStatusBack;				 //ĳ���� ���� â BACKGROUND IMAGE
	image* _imageBottomStatusBack;			 //ĳ���� ���� â(�ٴ�) BACKGROUND IMAGE
	image* _imageCharacterListBack;			 //ĳ���� ��ȯ â ����Ʈ BACKGROUND IMAGE
	image* _imageIconCharacter;				 //ĳ���� ���� â(�ٴ�) ĳ���� ������ IMAGE

	image* _imageOrderListTop;				 //�Ϲ� ���� ����Ʈ BACKGROUND IMAGE TOP
	vector<image*> _imageOrderListBody;		 //�Ϲ� ���� ����Ʈ BACKGROUND IMAGE BODY
	image* _imageOrderListBottom;			 //�Ϲ� ���� ����Ʈ BACKGROUND IMAGE BOTTOM

	image* _imageUnitOrderListTop;			 //ĳ���� ���� ����Ʈ BACKGROUND IMAGE TOP
	vector<image*> _imageUnitOrderListBody;	 //ĳ���� ���� ����Ʈ BACKGROUND IMAGE BODY
	image* _imageUnitOrderListBottom;		 //ĳ���� ���� ����Ʈ BACKGROUND IMAGE BOTTOM

	RECT _rcStatus;							 //ĳ���� ���� â(��)
	RECT _rcBottomStatus;					 //ĳ���� ���� â(�ٴ�)
	RECT _rcSkillTitle;						 //ĳ���� ��ų Ÿ��Ʋ(��ų ��� �� ��Ÿ��)
	RECT _rcCharacterList;					 //ĳ���� ��ȯ ����Ʈ

	RECT _rcOrderListTop;					 //�Ϲ� ��� ����Ʈ RECT
	vector<RECT> _rcOrderListBody;			 //�Ϲ� ��� ����Ʈ RECT
	RECT _rcOrderListBottom;				 //�Ϲ� ��� ����Ʈ RECT

	RECT _rcUnitOrderListTop;				 //ĳ���� ��� ����Ʈ RECT
	vector<RECT> _rcUnitOrderListBody;		 //ĳ���� ��� ����Ʈ RECT
	RECT _rcUnitOrderListBottom;			 //ĳ���� ��� ����Ʈ RECT

	RECT _rcIconCharacter;					 //ĳ���� ���� â(�ٴ�) ĳ���� ����
	vector<char*> _vOrderList;				 //�Ϲ� ��� â char*
	vector<char*> _vUnitOrderList;			 //���� ��� â char*
	vector<RECT> _rcOrderListStr;			 //�Ϲ� ��� â STR�� RECT
	vector<RECT> _rcUnitOrderListStr;		 //���� ��� â STR�� RECT

	image* _imageTurnCountBackground;		 //���� �� ǥ��� BACKGROUND IMAGE
	RECT _rcTurnCountBack;					 //���� �� ǥ��� RECT
	char* _strTurnCount;					 //���� �� ǥ��� char*

	vector<character*> _vCharacter;			//character vector
	vector<enemy*> _vEnemy;					//Enemy vector

	int _characterSize;				  //ĳ���� Vector Size
	int _enemySize;					  //Enemy Vector Size
	int _orderListSize;				  //�Ϲ� ��� â Size
	int _unitOrderListSize;			  //���� ���â Size

	bool _isOnStatus;				  //���� â On/Off
	bool _isOnSkillTitle;			  //��ų Ÿ��Ʋ On/Off
	bool _isOnBottomStatus;			  //���� â(�ٴ�) On/Off
	bool _isOnCharacterList;		  //ĳ���� ����Ʈ On/Off
	bool _isOnOrderList;			  //��� â On/Off
	bool _isOnUnitOrderList;		  //ĳ���� ��� â On/Off

	bool _isTurnType;				  //���� TURN�� ������ ���ΰ�? TRUE = PLAYER, FALSE = ENEMY
	bool _isTurnShow;				  //TURN IMAGE�� SHOW ����� �ϴ°� ���ƾ��ϴ°�?
	bool _isFirstShow;				  //BATTLE SCENE�� ó�� ���Դ°�?
	bool _isTurnBackCenter;			  //TURN IMAGE�� �߾ӱ��� �Դ°�?
	RECT _rcTurnBack;				  //TURN IMAGE�� �� ��� RECT
	image* _imageTurnStr;			  //TURN IMAGE STR
	image* _imageTurnBack;			  //TURN IMAGE BACKGROUND
	int _turnBackPosX;				  //TURN RECT�� LEFT ��ġ
	float _turnShowTime;			  //TURN IMAGE�� �߾ӱ��� ���� �� 1�ʰ� ���� ��ų �뵵�� TIME


	image* _imageSelectTile;		  //���� �� Ÿ���� �׵θ� �̹���
	RECT _rcSelectTile;				  //���� �� Ÿ���� �׵θ� ��¿� RECT


	gameObjectManager* _gameObjMgr;

public:
	battleUI();
	~battleUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void orderListClick(int orderNumber);
	void unitOrderListClick(int unitOrderNumber);
	void turnChange(bool turn);

	void setObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
};

