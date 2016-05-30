#pragma once
#include "gameNode.h"
#include "prinny.h"

class town : public gameNode
{
private:
	image* _town;		//마을 맵 이미지 (통짜 맵)
	image* _townPixel;
	image* _battlePortal;
	image* _storePortal;
	image* _etcPortal;

	image* _mercenaryNPC;
	image* _storeNPC;
	image* _mercenaryShadow;
	image* _storeShadow;

	RECT _rcStore, _rcMercenary, _rcBattle;

	int _proveX, _proveY;
	int _sourX, _sourY;
	int _count;
	
	bool _pixelDraw;

	gameObject* _prinny;

public:
	town();
	~town();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	void keyControl();
	void pixelCollision(RECT rc);
	void enterEntrance();
	void setFrame();
};

