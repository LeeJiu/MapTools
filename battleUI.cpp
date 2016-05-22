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
	_characterList = IMAGEMANAGER->addImage("character_list", "image/ui/ui_characterList.bmp", 250, 250, false, false);
	_summary = IMAGEMANAGER->addImage("summary", "image/ui/ui_summary.bmp", 420, 150, true, 0xff00ff);
	_order = IMAGEMANAGER->addImage("order_list", "image/ui/ui_orderList.bmp", 250, 250, false, false);
	_status = IMAGEMANAGER->addImage("character_status", "image/ui/ui_status.bmp", 300, 500, true, 0xff00ff);
	_action = IMAGEMANAGER->addImage("action", "image/ui/ui_action.bmp", 250, 150, false, false);

	//ui창 상태 = off
	_onCharacterList = _onSummary = _onStatus = _onOrder = _onAction = false;

	/*			rect set			*/
	_rcCharacterList = RectMake(980, 50, 250, 250);
	_rcSummary = RectMake(50, 520, 450, 150);
	_rcOrder = RectMake(980, 50, 250, 250);
	_rcStatus = RectMake(50, 50, 300, 500);
	_rcAction = RectMakeCenter(CENTERX, CENTERY, 250, 150);

	return S_OK;
}

void battleUI::release()
{
}

void battleUI::update()
{
	keyControl();
}

void battleUI::render()
{
	if (_onCharacterList)
		_characterList->render(getMemDC(), _rcCharacterList.left, _rcCharacterList.top);

	if (_onSummary)
		_summary->render(getMemDC(), _rcSummary.left, _rcSummary.top);

	if (_onStatus)
		_status->render(getMemDC(), _rcStatus.left, _rcStatus.top);

	if (_onOrder)
		_order->render(getMemDC(), _rcOrder.left, _rcOrder.top);

	if (_onAction)
		_action->render(getMemDC(), _rcAction.left, _rcAction.top);


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

	if (_onAction)
	{
		clickAction();
	}
}

void battleUI::clickCharList()
{
}

void battleUI::clickOrder()
{
}

void battleUI::clickAction()
{
}
