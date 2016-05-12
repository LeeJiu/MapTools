#pragma once
#include "gameNode.h"
#include "character.h"

class battleUI : public gameNode
{
private:
	image* _imageSkillTitleBack;			 //��ų Ÿ��Ʋ BACKGROUND IMAGE
	image* _imageStatusBack;				 //ĳ���� ���� â BACKGROUND IMAGE
	image* _imageBottomStatusBack;			 //ĳ���� ���� â(�ٴ�) BACKGROUND IMAGE
	image* _imageCharacterListBack;			 //ĳ���� ��ȯ â ����Ʈ BACKGROUND IMAGE
	image* _imageIconCharacter;				 //ĳ���� ���� â(�ٴ�) ĳ���� ������ IMAGE

	image* _imageOrderListTop;				 //�Ϲ� ���� ����Ʈ BACKGROUND IMAGE
	vector<image*> _imageOrderListBody;		 //�Ϲ� ���� ����Ʈ BACKGROUND IMAGE
	image* _imageOrderListBottom;			 //�Ϲ� ���� ����Ʈ BACKGROUND IMAGE

	image* _imageUnitOrderListTop;			 //ĳ���� ���� ����Ʈ BACKGROUND IMAGE
	vector<image*> _imageUnitOrderListBody;	 //ĳ���� ���� ����Ʈ BACKGROUND IMAGE
	image* _imageUnitOrderListBottom;		 //ĳ���� ���� ����Ʈ BACKGROUND IMAGE

	RECT _rcStatus;							 //ĳ���� ���� â(��)
	RECT _rcBottomStatus;					 //ĳ���� ���� â(�ٴ�)
	RECT _rcSkillTitle;						 //ĳ���� ��ų Ÿ��Ʋ(��ų ��� �� ��Ÿ��)
	RECT _rcCharacterList;					 //ĳ���� ��ȯ ����Ʈ

	RECT _rcOrderListTop;					 //�Ϲ� ���� ����Ʈ RECT
	vector<RECT> _rcOrderListBody;			 //�Ϲ� ���� ����Ʈ RECT
	RECT _rcOrderListBottom;				 //�Ϲ� ���� ����Ʈ RECT

	RECT _rcUnitOrderListTop;				 //ĳ���� ���� ����Ʈ RECT
	vector<RECT> _rcUnitOrderListBody;		 //ĳ���� ���� ����Ʈ RECT
	RECT _rcUnitOrderListBottom;			 //ĳ���� ���� ����Ʈ RECT

	RECT _rcIconCharacter;
	vector<char*> _vOrderList;
	vector<char*> _vUnitOrderList;
	vector<RECT> _rcOrderListStr;
	vector<RECT> _rcUnitOrderListStr;

	vector<character*> _vCharacter;

	int _unitOrderListSize;
	int _characterSize;
	int _orderListSize;

	bool _isOnStatus;				  //���� â On/Off
	bool _isOnSkillTitle;			  //��ų Ÿ��Ʋ On/Off
	bool _isOnBottomStatus;			  //���� â(�ٴ�) On/Off
	bool _isOnCharacterList;		  //ĳ���� ����Ʈ On/Off
	bool _isOnOrderList;			  //��� â On/Off
	bool _isOnUnitOrderList;		  //ĳ���� ��� â On/Off

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

