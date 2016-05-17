#pragma once
#include "gameNode.h"
#include "character.h"
#include "button.h"
#include "enemy.h"
#include "battleCamera.h"

class battleManager;
class gameObjectManager;
class battleUI : public gameNode
{
private:
	bool _isFirstInit;

	image* _imageSkillTitleBack;			 //��ų Ÿ��Ʋ BACKGROUND IMAGE
	image* _imageStatusBack;				 //ĳ���� ���� â BACKGROUND IMAGE
	image* _imageBottomStatusBack;			 //ĳ���� ���� â(�ٴ�) BACKGROUND IMAGE
	
	image* _imageIconCharacter;				 //ĳ���� ���� â(�ٴ�) ĳ���� ������ IMAGE

	image* _imageOrderListTop;				 //�Ϲ� ���� ����Ʈ BACKGROUND IMAGE TOP
	vector<image*> _imageOrderListBody;		 //�Ϲ� ���� ����Ʈ BACKGROUND IMAGE BODY
	image* _imageOrderListBottom;			 //�Ϲ� ���� ����Ʈ BACKGROUND IMAGE BOTTOM

	image* _imageUnitOrderListTop;			 //ĳ���� ���� ����Ʈ BACKGROUND IMAGE TOP
	vector<image*> _imageUnitOrderListBody;	 //ĳ���� ���� ����Ʈ BACKGROUND IMAGE BODY
	image* _imageUnitOrderListBottom;		 //ĳ���� ���� ����Ʈ BACKGROUND IMAGE BOTTOM

	image* _imageCharacterListTop;			 //ĳ���� ��ȯ ����Ʈ BACKGROUND IMAGE TOP
	vector<image*> _imageCharacterListBody;	 //ĳ���� ��ȯ ����Ʈ BACKGROUND IMAGE BODY
	image* _imageCharacterListBottom;		 //ĳ���� ��ȯ ����Ʈ BACKGROUND IMAGE BOTTOM

	image* _imageListArrow;
	RECT _rcListArrow;
	bool _IsOnListArrow;

	RECT _rcStatus;							 //ĳ���� ���� â(��)
	RECT _rcBottomStatus;					 //ĳ���� ���� â(�ٴ�)
	RECT _rcSkillTitle;						 //ĳ���� ��ų Ÿ��Ʋ(��ų ��� �� ��Ÿ��)

	RECT _rcCharacterListTop;				 //ĳ���� ��ȯ ����Ʈ TOP
	vector<RECT> _rcCharacterListBody;		 //ĳ���� ��ȯ ����Ʈ BODY
	RECT _rcCharacterListBottom;			 //ĳ���� ��ȯ ����Ʈ BOTTOM

	RECT _rcOrderListTop;					 //�Ϲ� ��� ����Ʈ RECT TOP
	vector<RECT> _rcOrderListBody;			 //�Ϲ� ��� ����Ʈ RECT BODY
	RECT _rcOrderListBottom;				 //�Ϲ� ��� ����Ʈ RECT BOTTOM

	RECT _rcUnitOrderListTop;				 //ĳ���� ��� ����Ʈ RECT TOP
	vector<RECT> _rcUnitOrderListBody;		 //ĳ���� ��� ����Ʈ RECT BODY
	RECT _rcUnitOrderListBottom;			 //ĳ���� ��� ����Ʈ RECT BOTTOM

	RECT _rcIconCharacter;					 //ĳ���� ���� â(�ٴ�) ĳ���� ����
	vector<char*> _vOrderList;				 //�Ϲ� ��� â char*
	vector<char*> _vUnitOrderList;			 //���� ��� â char*
	vector<string> _vCharacterList;			 //ĳ���� ��ȯ ����Ʈ char*
	vector<RECT> _rcOrderListStr;			 //�Ϲ� ��� â STR�� RECT
	vector<RECT> _rcUnitOrderListStr;		 //���� ��� â STR�� RECT
	vector<RECT> _rcCharacterListStr;		 //ĳ���� ��ȯ ����Ʈ STR�� RECT

	image* _imageTurnCountBackground;		 //���� �� ǥ��� BACKGROUND IMAGE
	RECT _rcTurnCountBack;					 //���� �� ǥ��� RECT
	RECT _rcTurnCountStr;				     //���� �� ǥ�� STR�� RECT
	char* _strTurnCount;					 //���� �� ǥ��� char*

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
	bool _isOnSelectTile;			  //����ƮŸ�� On/off

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
	battleManager* _battleMgr;
	battleCamera* _battleCamera;
	int _count;						  // Select Tile Arrow Motion Count

	bool _isSelectCharacter;
	int _isSelectCharacterNumber;

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
	void initCharacterList();

	void setTurnShow() { _isTurnShow = true; }

	void orderListClick(int orderNumber);
	void unitOrderListClick(int unitOrderNumber);
	void turnChange();

	//Ŭ�� �̺�Ʈ
	void LButtonClick();
	void RButtonClick();
	void checkMouseOverList();
	void checkMouseOverCharacter();
	
	void setTurnTypeChangeToPlayer() { _isTurnType = true; }			//ENEMY���� PLAYER TURN���� �Ѿ �� ȣ���ؼ� PLAYER TURN IMAGE�� ȣ��

	void setArrowFrame();
	void setCamera();
	void setGameObjectSize();
	void setObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
	void setBattleManagerMemoryLink(battleManager* battleMgr) { _battleMgr = battleMgr; }
};

