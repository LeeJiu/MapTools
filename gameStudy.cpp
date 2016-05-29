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
	IMAGEMANAGER->addFrameImage("flonne_pain", "image/character/flonne_pain.bmp.bmp", 826, 612, 7, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("flonne_etc", "image/character/flonne_etc.bmp", 236, 620, 2, 4, true, 0xff00ff);

	//raspberyl
	IMAGEMANAGER->addFrameImage("raspberyl_idle", "image/character/raspberyl_idle.bmp", 396, 576, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("raspberyl_walk", "image/character/raspberyl_walk.bmp", 552, 580, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("raspberyl_attack", "image/character/raspberyl_attack.bmp", 460, 592, 5, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("raspberyl_pain", "image/character/raspberyl_pain.bmp", 728, 488, 7, 4, true, 0xff00ff);

	//etna
	IMAGEMANAGER->addFrameImage("etna_idle", "image/character/etna_idle.bmp", 588, 656, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("etna_walk", "image/character/etna_walk.bmp", 588, 700, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("etna_attack", "image/character/etna_attack.bmp", 720, 660, 4, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("etna_pain", "image/character/etna_pain.bmp", 103, 596, 1, 4, true, 0xff00ff);

	//배틀씬에서 사용될 이미지 추가
	IMAGEMANAGER->addImage("walkable", "image/battle/walkable_tile.bmp", 128, 64, true, 0xff00ff);
	IMAGEMANAGER->addImage("attackable", "image/battle/attackable_tile.bmp", 128, 64, true, 0xff00ff);
	IMAGEMANAGER->addImage("turnback", "image/battleUI/ui_turnback_black.bmp", WINSIZEX, 100, false, false);
	IMAGEMANAGER->addImage("playerTurn", "image/battleUI/ui_turnback_player.bmp", 489, 53, true, 0xff00ff);
	IMAGEMANAGER->addImage("enemyTurn", "image/battleUI/ui_turnback_enemy.bmp", 476, 53, true, 0xff00ff);
	IMAGEMANAGER->addImage("stageStart", "image/battleUI/ui_turnback_start.bmp", 461, 53, true, 0xff00ff);
	
	//오브젝트 이미지 추가
	IMAGEMANAGER->addImage("tree1", "image/mapTool/object_tree.bmp", 222, 265, true, 0xff00ff);
	IMAGEMANAGER->addImage("tree2", "image/mapTool/object_tree2.bmp", 180, 185, true, 0xff00ff);
	IMAGEMANAGER->addImage("woods", "image/mapTool/object_wood.bmp", 128, 118, true, 0xff00ff);
	IMAGEMANAGER->addImage("mushiroom", "image/mapTool/object_mushiroom.bmp", 63, 65, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("zenPoint", "image/mapTool/object_zen.bmp", 2583, 76, 21, 1, true, 0xff00ff);

	//씬 추가
	SCENEMANAGER->addScene("town", new town);
	SCENEMANAGER->addScene("selectStage", new selectStage);
	SCENEMANAGER->addScene("battleScene", new battleScene);
	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->addScene("store", new store);
	SCENEMANAGER->addScene("mercenaryStore", new mercenaryStore);

	//케릭터 이미지 추가
	//프리니
	IMAGEMANAGER->addFrameImage("prinny_idle", "image/character/prinny_idle.bmp", 714, 484, 7, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_walk", "image/character/prinny_walk.bmp", 776, 492, 8, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_attack", "image/character/prinny_attack.bmp", 780, 484, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_lift", "image/character/prinny_lift.bmp", 720, 524, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_pain", "image/character/prinny_pain.bmp", 819, 528, 7, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("prinny_etc", "image/character/prinny_etc.bmp", 468, 528, 4, 4, true, 0xff00ff);

	//오크
	IMAGEMANAGER->addFrameImage("orc_idle", "image/character/orc_idle.bmp", 1080, 668, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("orc_walk", "image/character/orc_walk.bmp", 534, 668, 6, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("orc_attack", "image/character/orc_attack.bmp", 1694, 716, 7, 4, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("orc_pain", "image/character/orc_pain.bmp", 1323, 596, 7, 4, true, 0xff00ff);


	//그림자
	IMAGEMANAGER->addImage("shadow", "image/character/shadow.bmp", 128, 64, true, 0xff00ff);
	
	//셀렉트 타일 이미지
	IMAGEMANAGER->addImage("select_tile", "image/battle/select_tile.bmp", 128, 64, true, 0xff00ff);

	//셀렉트 에로우 이미지
	IMAGEMANAGER->addFrameImage("ui_arrow_blue", "image/battleUI/ui_arrow_blue.bmp", 711, 100, 9, 1, true, 0xff00ff);

	//캐릭터 아이콘
	IMAGEMANAGER->addImage("prinny_icon", "image/icon/icon_prinny.bmp", 110, 110, false, false);
	IMAGEMANAGER->addImage("etna_icon", "image/icon/icon_etna.bmp", 110, 110, false, false);
	IMAGEMANAGER->addImage("flonne_icon", "image/icon/icon_flonne.bmp", 110, 110, false, false);
	IMAGEMANAGER->addImage("raspberyl_icon", "image/icon/icon_raspberyl.bmp", 110, 110, false, false);
	
	//사운드
	//배경음
	SOUNDMANAGER->addSound("town_bg", "sound/town_bg.mp3", true, true);
	//SOUNDMANAGER->addSound("town_bg", "sound/town.mp3", true, true);
	SOUNDMANAGER->addSound("title_bg", "sound/title.mp3", true, true);
	SOUNDMANAGER->addSound("battleScene_bg", "sound/battleScene.mp3", true, true);
	SOUNDMANAGER->addSound("selectStage_bg", "sound/selectStage_bg.mp3", true, true);
	SOUNDMANAGER->addSound("store_bg", "sound/store.mp3", true, true);
	SOUNDMANAGER->addSound("mer_store_bg", "sound/mer_store.mp3", true, true);
	
	//효과음
	SOUNDMANAGER->addSound("step", "sound/step.wav", true, true);
	SOUNDMANAGER->addSound("f_step", "sound/step.wav", true, true);
	SOUNDMANAGER->addSound("e_step", "sound/step.wav", true, true);
	SOUNDMANAGER->addSound("r_step", "sound/step.wav", true, true);
	SOUNDMANAGER->addSound("sell", "sound/sell.wav", false, false);
	SOUNDMANAGER->addSound("equip", "sound/equip.wav", false, false);
	SOUNDMANAGER->addSound("ban", "sound/ban.wav", false, false);
	SOUNDMANAGER->addSound("button", "sound/button.wav", false, false);
	SOUNDMANAGER->addSound("click", "sound/click.wav", false, false);
	SOUNDMANAGER->addSound("pain", "sound/pain.wav", false, false);
	SOUNDMANAGER->addSound("heal", "sound/heal.wav", false, false);
	SOUNDMANAGER->addSound("heal2", "sound/heal2.wav", false, false);
	SOUNDMANAGER->addSound("prinny_on", "sound/prinny_on.wav", false, false);
	SOUNDMANAGER->addSound("etna_on", "sound/etna_on.wav", false, false);
	SOUNDMANAGER->addSound("flonne_on", "sound/flonne_on.mp3", false, false);
	SOUNDMANAGER->addSound("razberyl_on", "sound/razberyl_on.mp3", false, false);
	SOUNDMANAGER->addSound("prinny_go", "sound/prinny_go.wav", false, false);
	SOUNDMANAGER->addSound("stage_clear", "sound/stage_clear.wav", false, false);
	SOUNDMANAGER->addSound("stage_fail", "sound/stage_fail.wav", false, false);
	SOUNDMANAGER->addSound("skill_cut", "sound/skill_cut.wav", false, false);


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
	SOUNDMANAGER->update();
	SCENEMANAGER->update();

	gameNode::update();
}

void gameStudy::render()
{
	//백버퍼에서 뿌려준다
	
	PatBlt(getMemDC(), 0, 0, WINSIZEX + (TILENUM - 1) * WIDTH, WINSIZEY + (TILENUM - 1) * WIDTH / 2, WHITENESS);
	//======================
	//이 사이에서 그려주면 됨.

	SCENEMANAGER->render();

	//======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0, WINSIZEX, WINSIZEY, _cameraX, _cameraY, _sourWidth, _sourHeight);
}


