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
	// ------------ 캐릭터 상태 창(바닥) ------------
	image* _imageIconCharacter;             //캐릭터 상태 창(바닥) 캐릭터 아이콘 IMAGE
	RECT _rcBottomStatus;					//캐릭터 상태 창(바닥)
	RECT _rcIconCharacter;					//캐릭터 상태 창(바닥) 캐릭터 사진
	image* _imageBottomStatusBack;          //캐릭터 상태 창(바닥) BACKGROUND IMAGE


											// ------------ 일반 명령창 리스트 ------------
	image* _imageOrderListTop;				//일반 오더 리스트 BACKGROUND IMAGE TOP
	vector<image*> _imageOrderListBody;		//일반 오더 리스트 BACKGROUND IMAGE BODY
	image* _imageOrderListBottom;			//일반 오더 리스트 BACKGROUND IMAGE BOTTOM
	RECT _rcOrderListTop;					//일반 명령 리스트 RECT TOP
	vector<RECT> _rcOrderListBody;          //일반 명령 리스트 RECT BODY
	RECT _rcOrderListBottom;				//일반 명령 리스트 RECT BOTTOM
	vector<char*> _vOrderList;				//일반 명령 창 char*
	vector<RECT> _rcOrderListStr;			//일반 명령 창 STR용 RECT


											// ------------ 캐릭터 명령창 리스트 ------------
	image* _imageUnitOrderListTop;			//캐릭터 오더 리스트 BACKGROUND IMAGE TOP
	vector<image*> _imageUnitOrderListBody;	//캐릭터 오더 리스트 BACKGROUND IMAGE BODY
	image* _imageUnitOrderListBottom;		//캐릭터 오더 리스트 BACKGROUND IMAGE BOTTOM
	RECT _rcUnitOrderListTop;				//캐릭터 명령 리스트 RECT TOP
	vector<RECT> _rcUnitOrderListBody;		//캐릭터 명령 리스트 RECT BODY
	RECT _rcUnitOrderListBottom;			//캐릭터 명령 리스트 RECT BOTTOM
	vector<char*> _vUnitOrderList;			//유닛 명령 창 char*
	vector<RECT> _rcUnitOrderListStr;		//유닛 명령 창 STR용 RECT


											// ------------ 캐릭터 소환용 리스트 ------------
	image* _imageCharacterListTop;			//캐릭터 소환 리스트 BACKGROUND IMAGE TOP
	vector<image*> _imageCharacterListBody;	//캐릭터 소환 리스트 BACKGROUND IMAGE BODY
	image* _imageCharacterListBottom;		//캐릭터 소환 리스트 BACKGROUND IMAGE BOTTOM
	RECT _rcCharacterListTop;				//캐릭터 소환 리스트 TOP
	vector<RECT> _rcCharacterListBody;		//캐릭터 소환 리스트 BODY
	RECT _rcCharacterListBottom;			//캐릭터 소환 리스트 BOTTOM
	vector<string> _vCharacterList;			//캐릭터 소환 리스트 char*
	vector<RECT> _rcCharacterListStr;		//캐릭터 소환 리스트 STR용 RECT


											// ------------ 공격할 캐릭터(타겟) 리스트 ------------
	image* _imageAttackListTop;				//공격할 타겟 리스트 BACKGROUND IMAGE TOP
	vector<image*> _imageAttackListBody;	//공격할 타겟 리스트 BACKGROUND IMAGE BODY
	image* _imageAttackListBottom;			//공격할 타겟 리스트 BACKGROUND IMAGE BOTTOM
	RECT _rcAttackListTop;					//공격할 타겟 리스트 TOP
	vector<RECT> _rcAttackListBody;			//공격할 타겟 리스트 BODY
	RECT _rcAttackListBottom;				//공격할 타겟 리스트 BOTTOM
	vector<RECT> _rcAttackListStr;			//공격할 타겟 리스트 char*
	vector<char*> _vAttackList;				//공격할 타겟 리스트 STR용 RECT


											// ------------ 리스트 화살표 ------------ 
	image* _imageListArrow;
	RECT _rcListArrow;
	bool _IsOnListArrow;


	// ------------ 캐릭터 상태 창(좌) ------------
	image* _imageStatusBack;             //캐릭터 상태 창 BACKGROUND IMAGE
	RECT _rcStatus;                      //캐릭터 상태 창(좌)	


										 // ------------ 현재 턴 표기용 변수들 ------------
	image* _imageTurnCountBackground;       //현재 턴 표기용 BACKGROUND IMAGE
	RECT _rcTurnCountBack;					//현재 턴 표기용 RECT
	RECT _rcTurnCountStr;					//현재 턴 표기 STR용 RECT
	char* _strTurnCount;					//현재 턴 표기용 char*


											// ------------ 턴 표기용 변수들 ------------
	bool _isTurnType;				//현재 TURN이 누구의 턴인가? TRUE = PLAYER, FALSE = ENEMY
	bool _isTurnShow;				//TURN IMAGE를 SHOW 해줘야 하는가 말아야하는가?
	bool _isFirstShow;				//BATTLE SCENE에 처음 들어왔는가?
	bool _isTurnBackCenter;			//TURN IMAGE가 중앙까지 왔는가?
	RECT _rcTurnBack;				//TURN IMAGE의 뒷 배경 RECT
	image* _imageTurnStr;           //TURN IMAGE STR
	image* _imageTurnBack;          //TURN IMAGE BACKGROUND
	int _turnBackPosX;              //TURN RECT의 LEFT 위치
	float _turnShowTime;			//TURN IMAGE가 중앙까지 왔을 때 1초간 지연 시킬 용도의 TIME


									// ------------ 마우스 오버 랩 된 SELECT TILE 출력용 변수 ------------
	image* _imageSelectTile;        //선택 한 타일의 테두리 이미지
	RECT _rcSelectTile;				//선택 한 타일의 테두리 출력용 RECT
	int _count;						// Select Tile Arrow Motion Count


									// ------------ 상태 창(바닥) 변수들 ------------
	RECT _rcStatusBottomName;			//RECT 캐릭터 NAME
	const char* _statusBottomName;		//char* 캐릭터 NAME
	progressBar* _progressBarHp;		//ProgressBar HP
	progressBar* _progressBarSp;		//ProgressBar SP


										// ------------ UI 각 창들 On/Off 체크용 BOOL 변수들 ------------
	bool _isOnStatus;				//상태 창 On/Off
	bool _isOnSkillTitle;           //스킬 타이틀 On/Off
	bool _isOnBottomStatus;         //상태 창(바닥) On/Off
	bool _isOnCharacterList;        //캐릭터 리스트 On/Off
	bool _isOnOrderList;			//명령 창 On/Off
	bool _isOnUnitOrderList;        //캐릭터 명령 창 On/Off
	bool _isOnSelectTile;           //셀렉트타일 On/off
	bool _isOnSelectTarget;			//공격 타일을 출력해야하는지 여부
	bool _isSelectCharacter;		//어떤 캐릭터를 선택했는지 여부


									// ------------ 기타 ------------
	RECT _rcSkillTitle;                 //캐릭터 스킬 타이틀(스킬 사용 시 나타남)	
	image* _imageSkillTitleBack;        //스킬 타이틀 BACKGROUND IMAGE
	int _characterSize;					//캐릭터 Vector Size
	int _enemySize;						//Enemy Vector Size
	int _orderListSize;					//일반 명령 창 Size
	int _unitOrderListSize;				//유닛 명령창 Size
	int _selectTargetNumber;			//선택한 타겟 넘버(공격 시)
	int _selectCharacterNumber;			//선택한 플레이어 캐릭터 넘버


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

	void setTurnShow() { _isTurnShow = true; }	//외부에서 Turn Show를 시켜야 할 때 이 함수를 이용하여 Turn을 Show 시킨다
	void renderOverlapSelectTile();				//마우스 오버 랩 된 타일에 SelectTile Image를 출력
	void renderOverlapAttackSelectTile();		//마우스 오버 랩 된 공격 타일에 SelectTile Image를 출력

	bool checkTileOnCharacter(int i, int j);
	void orderListClick(int orderNumber);
	void unitOrderListClick(int unitOrderNumber);
	void turnChange();

	void updateRectPos();

	//클릭 이벤트
	void LButtonClick();
	void RButtonClick();
	void checkMouseOverList();
	void checkMouseOverCharacter();

	void setTurnTypeChangeToPlayer() { _isTurnType = true; }         //ENEMY에서 PLAYER TURN으로 넘어갈 떄 호출해서 PLAYER TURN IMAGE를 호출

	void setArrowFrame();
	void setCamera();
	void setGameObjectSize();
	void setObjectManagerMemoryLink(gameObjectManager* gameObjMgr) { _gameObjMgr = gameObjMgr; }
	void setBattleManagerMemoryLink(battleManager* battleMgr) { _battleMgr = battleMgr; }
};
