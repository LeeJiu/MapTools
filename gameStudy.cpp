#include "stdafx.h"
#include "gameStudy.h"


gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::init()
{
	gameNode::init(true);
	
	//공통으로 사용하는 아이템 이미지 추가
	IMAGEMANAGER->addImage("sword", "image/item/sword.bmp", 256, 256, true, 0xff00ff);
	IMAGEMANAGER->addImage("staff", "image/item/staff.bmp", 256, 256, true, 0xff00ff);
	IMAGEMANAGER->addImage("wand", "image/item/wand.bmp", 256, 256, true, 0xff00ff);
	IMAGEMANAGER->addImage("bow", "image/item/bow.bmp", 256, 256, true, 0xff00ff);

	//스토어 배경 이미지 추가
	IMAGEMANAGER->addImage("store_background", "image/background/store_background.bmp", WINSIZEX, WINSIZEY, false, false);

	//스토어 ui 이미지 추가
	IMAGEMANAGER->addImage("store_title", "image/ui/store_title.bmp", 162, 65, false, false);
	IMAGEMANAGER->addImage("store_exit", "image/ui/store_exit.bmp", 162, 65, false, false);
	IMAGEMANAGER->addImage("store_list_title", "image/ui/store_list_title.bmp", 100, 50, true, 0xff00ff);
	IMAGEMANAGER->addImage("store_list", "image/ui/dialog_type_List.bmp", 300, 389, false, false);
	IMAGEMANAGER->addImage("store_status", "image/ui/store_ui_item_status.bmp", 700, 389, false, false);
	IMAGEMANAGER->addImage("store_info", "image/ui/dialog_type_bottom.bmp", 1182, 65, false, false);
	IMAGEMANAGER->addImage("store_hell", "image/ui/store_hell.bmp", 300, 50, false, false);
	IMAGEMANAGER->addImage("store_buy", "image/ui/store_buy.bmp", 200, 50, false, false);
	
	//용병 상점 ui
	IMAGEMANAGER->addImage("store_list_mercenary", "image/ui/store_ui_mercenary.bmp", 300, 389, false, false);
	IMAGEMANAGER->addImage("store_status_mercenary", "image/ui/store_character_status.bmp", 400, 389, false, false);
	IMAGEMANAGER->addImage("store_character_title", "image/ui/store_character_title.bmp", 200, 50, true, 0xff00ff);
	IMAGEMANAGER->addImage("store_hire", "image/ui/store_hire.bmp", 200, 50, false, false);
	IMAGEMANAGER->addImage("store_mylist", "image/ui/store_ui_mylist.bmp", 300, 389, false, false);

	//용병 이미지 추가
	//flonne
	IMAGEMANAGER->addFrameImage("flonne_idle", "image/character/flonne_idle.bmp", 588, 664, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("flonne_walk", "image/character/flonne_walk.bmp", 624, 664, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("flonne_attack", "image/character/flonne_attack.bmp", 824, 612, 4, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("flonne_lift", "image/character/flonne_lift.bmp", 396, 664, 4, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("flonne_etc", "image/character/flonne_etc.bmp", 236, 620, 2, 4, true, 0xff00ff);

	//배틀씬에서 사용될 이미지 추가
	IMAGEMANAGER->addImage("walkable", "image/battle/walkable_tile.bmp", 128, 64, true, 0xff00ff);
	IMAGEMANAGER->addImage("attackable", "image/battle/attackable_tile.bmp", 128, 64, true, 0xff00ff);
	
	//씬 추가
	SCENEMANAGER->addScene("town", new town);
	SCENEMANAGER->addScene("selectStage", new selectStage);
	SCENEMANAGER->addScene("battleScene", new battleScene);
	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->addScene("store", new store);
	SCENEMANAGER->addScene("mercenaryStore", new mercenaryStore);

	//케릭터 이미지 추가
	IMAGEMANAGER->addFrameImage("prinny_idle", "image/character/prinny_idle.bmp", 714, 484, 7, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_walk", "image/character/prinny_walk.bmp", 776, 492, 8, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_attack", "image/character/prinny_attack.bmp", 780, 484, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_lift", "image/character/prinny_lift.bmp", 720, 524, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_etc", "image/character/prinny_etc.bmp", 468, 528, 4, 4, true, 0xff00ff);


	SCENEMANAGER->changeScene("title");

	return S_OK;
}

void gameStudy::release()
{
	SCENEMANAGER->release();

	gameNode::release();
}

void gameStudy::update()
{
	SCENEMANAGER->update();

	gameNode::update();
}

void gameStudy::render()
{
	//백버퍼에서 뿌려준다
	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//======================
	//이 사이에서 그려주면 됨.

	SCENEMANAGER->render();

	//======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);
}


