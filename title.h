#pragma once
#include "gameNode.h"

class title : public gameNode
{
private:
	float _volume, _buttonVolume;

	int _alpha;
	int _x, _y;

	bool _showAlpha;
	bool _show;
	bool _showMenu;

	RECT _button[3];
	RECT _draw[3];

	bool _startButton;
	bool _maptoolButton;
	bool _exitButton;

public:
	title();
	~title();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			함수 추가			*/
	void showLogo();
	void showArrow();
	void clickMenu();
};

