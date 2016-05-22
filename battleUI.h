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

	//ĳ���� ����Ʈâ, �������â(name, hp, sp), ���â, ����â(������, �ߵ�����), ������â
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

	//uiâ�� ���� �Ѵ� �Լ�
	void onCharacterList(bool onOff) { _onCharacterList = onOff; }
	void onSummary(bool onOff) { _onSummary = onOff; }
	void onStatus(bool onOff) { _onStatus = onOff; }
	void onOrder(bool onOff) { _onOrder = onOff; }
	void onAction(bool onOff) { _onAction = onOff; }

	void clickCharList();
	void clickOrder();
	void clickAction();
};

