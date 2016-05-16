#pragma once
#include "gameNode.h"
<<<<<<< HEAD
class town : public gameNode
{
=======
#include "prinny.h"

class town : public gameNode
{
private:
	image* _town;		//마을 맵 이미지 (통짜 맵)
	image* _townPixel;
	image* _battlePortal;
	image* _storePortal;
	image* _etcPortal;

	RECT _rcStore, _rcBattle;

	int _proveX, _proveY;
	int _sourX, _sourY;
	int _count;
	
	gameObject* _prinny;

>>>>>>> refs/remotes/origin/development
public:
	town();
	~town();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
<<<<<<< HEAD

=======
	void keyControl();
	void pixelCollision(RECT rc);
	void enterEntrance();
	void setFrame();
>>>>>>> refs/remotes/origin/development
};

