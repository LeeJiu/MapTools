#include "stdafx.h"
#include "battleUI.h"


battleUI::battleUI()
{
}


battleUI::~battleUI()
{
}

HRESULT battleUI::init()
{
	//ui 이미지 추가
	_characterList = IMAGEMANAGER->addImage("character_list", "image/ui/ui_characterList.bmp", 250, 300, false, false);
	_summary = IMAGEMANAGER->addImage("summary", "image/ui/ui_summary.bmp", 420, 150, true, 0xff00ff);
	_order = IMAGEMANAGER->addImage("order_list", "image/ui/ui_orderList.bmp", 250, 213, false, false);
	_status = IMAGEMANAGER->addImage("character_status", "image/ui/ui_status.bmp", 300, 500, true, 0xff00ff);

	//ui창 상태 = off
	_onCharacterList = _onSummary = _onStatus = _onOrder = false;

	/*			rect set			*/
	_rcCharacterList = RectMake(_cameraX + 980, _cameraY + 50, 250, 250);
	_rcSummary = RectMake(_cameraX + 50, _cameraY + 520, 450, 150);
	_rcOrder = RectMake(_cameraX + 980, _cameraY + 50, 250, 250);
	_rcStatus = RectMake(_cameraX + 50, _cameraY + 50, 300, 500);

	_charIdx = 100;		//캐릭터 선택 안 되어있다.
	
		
	return S_OK;
}

void battleUI::release()
{
}

void battleUI::update()
{
	/*			rect update			*/
	_rcCharacterList = RectMake(_cameraX + 980, _cameraY + 50, 250, 250);
	_rcSummary = RectMake(_cameraX + 50, _cameraY + 520, 450, 150);
	_rcOrder = RectMake(_cameraX + 980, _cameraY + 50, 250, 250);
	_rcStatus = RectMake(_cameraX + 50, _cameraY + 50, 300, 500);

	int size = _vCharList.size();
	for (int i = 0; i < size; ++i)
	{
		_vCharList[i].rc = RectMake(_rcCharacterList.left + 20, _rcCharacterList.top + 50 + (i * 50), 200, 50);
	}

	// 유닛 오더창의 렉트들
	for (int i = 0; i < 5; i++)
	{
		_rcOrderList[i] = RectMake(_rcOrder.left + 20, _rcOrder.top + 25 + (i * 34), 200, 30);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		keyControl();
	}
}

void battleUI::render()
{
	HFONT font, oldFont;
	font = CreateFont(30, 0, 0, 0, 800, false, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	if (_onCharacterList)
	{
		_characterList->render(getMemDC(), _rcCharacterList.left, _rcCharacterList.top);
		
		int size = _vCharList.size();
		for (int i = 0; i < size; ++i)
		{
			DrawText(getMemDC(), _vCharList[i].name.c_str(), -1,
				&_vCharList[i].rc, DT_LEFT | DT_VCENTER);
		}
	}

	if (_onSummary)
		_summary->render(getMemDC(), _rcSummary.left, _rcSummary.top);

	if (_onStatus)
		_status->render(getMemDC(), _rcStatus.left, _rcStatus.top);

	if (_onOrder)
		_order->render(getMemDC(), _rcOrder.left, _rcOrder.top);

	// 유닛 오더창의 렉트들
	for (int i = 0; i < 5; i++)
	{
		Rectangle(getMemDC(), _rcOrderList[i].left, _rcOrderList[i].top, _rcOrderList[i].right, _rcOrderList[i].bottom);
	}

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}

void battleUI::keyControl()
{
	if (_onCharacterList)
	{
		clickCharList();
	}

	if (_onOrder)
	{
		clickOrder();
	}
}

void battleUI::clickCharList()
{
	int size = _vCharList.size();
	for (int i = 0; i < size; ++i)
	{
		if (PtInRect(&_vCharList[i].rc, _click))
		{
			_charIdx = _vCharList[i].idx;
			removeVCharList(i);
			break;
		}
	}
}

void battleUI::clickOrder()
{
	for (int i = 0; i < 5; ++i)
	{
		if (PtInRect(&_rcOrderList[i], _click))
		{
			_orderNumber = i + 1;
			break;
		}
	}
}

void battleUI::removeVCharList(int arrNum)
{
	_vCharList.erase(_vCharList.begin() + arrNum);
}

void battleUI::setCharList(vector<string>& charName)
{
	tagCharList list;
	list.idx = 0;
	list.name = "prinny";
	list.rc = RectMake(_rcCharacterList.left + 20, _rcCharacterList.top + 50, 200, 50);
	_vCharList.push_back(list);

	int size = charName.size();
	for (int i = 0; i < size; ++i)
	{
		list.idx = i + 1;
		list.name = charName[i];
		list.rc = RectMake(_rcCharacterList.left + 20, _rcCharacterList.top + 100 + (i * 50), 200, 50);
		_vCharList.push_back(list);
	}
}
