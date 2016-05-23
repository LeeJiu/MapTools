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

	//ĳ���� ����Ʈâ, �������â(name, hp, sp), ���â, ����â(������, �ߵ�����), ������â
	RECT _rcCharacterList, _rcSummary, _rcOrder, _rcAction, _rcStatus;

	RECT _rcActionList[2];
	RECT _rcOrderList[5];


	bool _onCharacterList, _onSummary, _onAction, _onOrder, _onStatus;
	
	vector<tagCharList> _vCharList;	//ĳ���� ����Ʈ
	int _charIdx;					//objectMgr���� ĳ���Ϳ� ������ �ε���
	int _orderNumber;				//���ָ��Ŭ���� ������� �Ǵ��� ����

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

	void removeVCharList(int arrNum);

	void setCharList(vector<string>& charName);
	void setCharIdx(int charIdx) { _charIdx = charIdx; }

	vector<tagCharList>& getVCharList() { return _vCharList; }
	int getCharIdx() { return _charIdx; }
	int getOrderNumber() { return _orderNumber; }
	bool isOnCharList() { return _onCharacterList; }
};

