#pragma once
#include "gameNode.h"
#include "character.h"

class battleUI : public gameNode
{
private:
	image* _imageSkillTitleBack;			 //스킬 타이틀 BACKGROUND IMAGE
	image* _imageStatusBack;				 //캐릭터 상태 창 BACKGROUND IMAGE
	image* _imageBottomStatusBack;			 //캐릭터 상태 창(바닥) BACKGROUND IMAGE
	image* _imageCharacterListBack;			 //캐릭터 소환 창 리스트 BACKGROUND IMAGE
	image* _imageIconCharacter;				 //캐릭터 상태 창(바닥) 캐릭터 아이콘 IMAGE

	image* _imageOrderListTop;				 //일반 오더 리스트 BACKGROUND IMAGE
	vector<image*> _imageOrderListBody;		 //일반 오더 리스트 BACKGROUND IMAGE
	image* _imageOrderListBottom;			 //일반 오더 리스트 BACKGROUND IMAGE

	image* _imageUnitOrderListTop;			 //캐릭터 오더 리스트 BACKGROUND IMAGE
	vector<image*> _imageUnitOrderListBody;	 //캐릭터 오더 리스트 BACKGROUND IMAGE
	image* _imageUnitOrderListBottom;		 //캐릭터 오더 리스트 BACKGROUND IMAGE

	RECT _rcStatus;							 //캐릭터 상태 창(좌)
	RECT _rcBottomStatus;					 //캐릭터 상태 창(바닥)
	RECT _rcSkillTitle;						 //캐릭터 스킬 타이틀(스킬 사용 시 나타남)
	RECT _rcCharacterList;					 //캐릭터 소환 리스트

	RECT _rcOrderListTop;					 //일반 오더 리스트 RECT
	vector<RECT> _rcOrderListBody;			 //일반 오더 리스트 RECT
	RECT _rcOrderListBottom;				 //일반 오더 리스트 RECT

	RECT _rcUnitOrderListTop;				 //캐릭터 오더 리스트 RECT
	vector<RECT> _rcUnitOrderListBody;		 //캐릭터 오더 리스트 RECT
	RECT _rcUnitOrderListBottom;			 //캐릭터 오더 리스트 RECT

	RECT _rcIconCharacter;
	vector<char*> _vOrderList;
	vector<char*> _vUnitOrderList;
	vector<RECT> _rcOrderListStr;
	vector<RECT> _rcUnitOrderListStr;

	vector<character*> _vCharacter;

	int _unitOrderListSize;
	int _characterSize;
	int _orderListSize;

	bool _isOnStatus;				  //상태 창 On/Off
	bool _isOnSkillTitle;			  //스킬 타이틀 On/Off
	bool _isOnBottomStatus;			  //상태 창(바닥) On/Off
	bool _isOnCharacterList;		  //캐릭터 리스트 On/Off
	bool _isOnOrderList;			  //명령 창 On/Off
	bool _isOnUnitOrderList;		  //캐릭터 명령 창 On/Off

public:
	battleUI();
	~battleUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void orderListClick(int orderNumber);
	void unitOrderListClick(int orderNumber);
};

