#pragma once
#include "gameNode.h"
#include "character.h"

class battleScene : public gameNode
{
private:
	image* _imageSkillTitleBack;
	image* _imageStatusBack;
	image* _imageBottomStatusBack;
	image* _imageCharacterListBack;

	image* _imageOrderListTop;
	vector<image*> _imageOrderListBody;
	image* _imageOrderListBottom;
	
	image* _imageIconCharacter;

	RECT _rcStatus;
	RECT _rcBottomStatus;
	RECT _rcSkillTitle;
	RECT _rcCharacterList;

	RECT _rcOrderListTop;
	vector<RECT> _rcOrderListBody;
	RECT _rcOrderListBottom;

	RECT _rcIconCharacter;
	
	vector<char*> _vOrderList;
	vector<RECT> _rcOrderListStr;

	vector<character*> _vCharacter;	
	int _characterSize;
	int _orderListSize;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

