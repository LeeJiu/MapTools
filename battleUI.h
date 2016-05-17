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

	image* _imageSkillTitleBack;			 //스킬 타이틀 BACKGROUND IMAGE
	image* _imageStatusBack;				 //캐릭터 상태 창 BACKGROUND IMAGE
	image* _imageBottomStatusBack;			 //캐릭터 상태 창(바닥) BACKGROUND IMAGE
	
	image* _imageIconCharacter;				 //캐릭터 상태 창(바닥) 캐릭터 아이콘 IMAGE

	image* _imageOrderListTop;				 //일반 오더 리스트 BACKGROUND IMAGE TOP
	vector<image*> _imageOrderListBody;		 //일반 오더 리스트 BACKGROUND IMAGE BODY
	image* _imageOrderListBottom;			 //일반 오더 리스트 BACKGROUND IMAGE BOTTOM

	image* _imageUnitOrderListTop;			 //캐릭터 오더 리스트 BACKGROUND IMAGE TOP
	vector<image*> _imageUnitOrderListBody;	 //캐릭터 오더 리스트 BACKGROUND IMAGE BODY
	image* _imageUnitOrderListBottom;		 //캐릭터 오더 리스트 BACKGROUND IMAGE BOTTOM

	image* _imageCharacterListTop;			 //캐릭터 소환 리스트 BACKGROUND IMAGE TOP
	vector<image*> _imageCharacterListBody;	 //캐릭터 소환 리스트 BACKGROUND IMAGE BODY
	image* _imageCharacterListBottom;		 //캐릭터 소환 리스트 BACKGROUND IMAGE BOTTOM

	image* _imageListArrow;
	RECT _rcListArrow;
	bool _IsOnListArrow;

	RECT _rcStatus;							 //캐릭터 상태 창(좌)
	RECT _rcBottomStatus;					 //캐릭터 상태 창(바닥)
	RECT _rcSkillTitle;						 //캐릭터 스킬 타이틀(스킬 사용 시 나타남)

	RECT _rcCharacterListTop;				 //캐릭터 소환 리스트 TOP
	vector<RECT> _rcCharacterListBody;		 //캐릭터 소환 리스트 BODY
	RECT _rcCharacterListBottom;			 //캐릭터 소환 리스트 BOTTOM

	RECT _rcOrderListTop;					 //일반 명령 리스트 RECT TOP
	vector<RECT> _rcOrderListBody;			 //일반 명령 리스트 RECT BODY
	RECT _rcOrderListBottom;				 //일반 명령 리스트 RECT BOTTOM

	RECT _rcUnitOrderListTop;				 //캐릭터 명령 리스트 RECT TOP
	vector<RECT> _rcUnitOrderListBody;		 //캐릭터 명령 리스트 RECT BODY
	RECT _rcUnitOrderListBottom;			 //캐릭터 명령 리스트 RECT BOTTOM

	RECT _rcIconCharacter;					 //캐릭터 상태 창(바닥) 캐릭터 사진
	vector<char*> _vOrderList;				 //일반 명령 창 char*
	vector<char*> _vUnitOrderList;			 //유닛 명령 창 char*
	vector<string> _vCharacterList;			 //캐릭터 소환 리스트 char*
	vector<RECT> _rcOrderListStr;			 //일반 명령 창 STR용 RECT
	vector<RECT> _rcUnitOrderListStr;		 //유닛 명령 창 STR용 RECT
	vector<RECT> _rcCharacterListStr;		 //캐릭터 소환 리스트 STR용 RECT

	image* _imageTurnCountBackground;		 //현재 턴 표기용 BACKGROUND IMAGE
	RECT _rcTurnCountBack;					 //현재 턴 표기용 RECT
	RECT _rcTurnCountStr;				     //현재 턴 표기 STR용 RECT
	char* _strTurnCount;					 //현재 턴 표기용 char*

	int _characterSize;				  //캐릭터 Vector Size
	int _enemySize;					  //Enemy Vector Size
	int _orderListSize;				  //일반 명령 창 Size
	int _unitOrderListSize;			  //유닛 명령창 Size

	bool _isOnStatus;				  //상태 창 On/Off
	bool _isOnSkillTitle;			  //스킬 타이틀 On/Off
	bool _isOnBottomStatus;			  //상태 창(바닥) On/Off
	bool _isOnCharacterList;		  //캐릭터 리스트 On/Off
	bool _isOnOrderList;			  //명령 창 On/Off
	bool _isOnUnitOrderList;		  //캐릭터 명령 창 On/Off
	bool _isOnSelectTile;			  //셀렉트타일 On/off

	bool _isTurnType;				  //현재 TURN이 누구의 턴인가? TRUE = PLAYER, FALSE = ENEMY
	bool _isTurnShow;				  //TURN IMAGE를 SHOW 해줘야 하는가 말아야하는가?
	bool _isFirstShow;				  //BATTLE SCENE에 처음 들어왔는가?
	bool _isTurnBackCenter;			  //TURN IMAGE가 중앙까지 왔는가?
	RECT _rcTurnBack;				  //TURN IMAGE의 뒷 배경 RECT
	image* _imageTurnStr;			  //TURN IMAGE STR
	image* _imageTurnBack;			  //TURN IMAGE BACKGROUND
	int _turnBackPosX;				  //TURN RECT의 LEFT 위치
	float _turnShowTime;			  //TURN IMAGE가 중앙까지 왔을 때 1초간 지연 시킬 용도의 TIME

	image* _imageSelectTile;		  //선택 한 타일의 테두리 이미지
	RECT _rcSelectTile;				  //선택 한 타일의 테두리 출력용 RECT


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

	//클릭 이벤트
	void LButtonClick();
	void RButtonClick();
	void checkMouseOverList();
	void checkMouseOverCharacter();
	
	void setTurnTypeChangeToPlayer() { _isTurnType = true; }			//ENEMY에서 PLAYER TURN으로 넘어갈 떄 호출해서 PLAYER TURN IMAGE를 호출

	void setArrowFrame();
	void setCamera();
	void setGameObjectSize();
	void setObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
	void setBattleManagerMemoryLink(battleManager* battleMgr) { _battleMgr = battleMgr; }
};

