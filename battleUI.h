#pragma once
#include "gameNode.h"

struct tagCharList
{
	string name;
	RECT rc;
	int idx;
};

class battleUI : public gameNode
{
private:
	image* _characterList;
	image* _summary;
	image* _order;
	image* _action;
	image* _status;

	//캐릭터 리스트창, 요약정보창(name, hp, sp), 명령창, 실행창(턴종료, 중도포기), 상세정보창
	RECT _rcCharacterList, _rcSummary, _rcOrder, _rcAction, _rcStatus;

	RECT _rcActionList[2];
	RECT _rcOrderList[5];


	bool _onCharacterList, _onSummary, _onAction, _onOrder, _onStatus;
	
	vector<tagCharList> _vCharList;	//캐릭터 리스트
	int _charIdx;					//objectMgr에서 캐릭터에 접근할 인덱스
	int _orderNumber;				//유닛명령클릭시 어떤것인지 판단할 변수

public:
	battleUI();
	~battleUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();

	//ui창을 끄고 켜는 함수
	void onCharacterList(bool onOff) { _onCharacterList = onOff; }
	void onSummary(bool onOff) { _onSummary = onOff; }
	void onStatus(bool onOff) { _onStatus = onOff; }
	void onOrder(bool onOff) { _onOrder = onOff; }
	void onAction(bool onOff) { _onAction = onOff; }

	void clickCharList();
	void clickOrder();
	void clickAction();

	void removeVCharList(int arrNum);

	void setCharList(vector<string>& charName);
	void setCharIdx(int charIdx) { _charIdx = charIdx; }

	vector<tagCharList>& getVCharList() { return _vCharList; }
	int getCharIdx() { return _charIdx; }
	int getOrderNumber() { return _orderNumber; }
	bool isOnCharList() { return _onCharacterList; }
};

