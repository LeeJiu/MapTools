#pragma once
#include "gameNode.h"


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
	
	bool _onCharacterList, _onSummary, _onAction, _onOrder, _onStatus;

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
};

