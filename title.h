#pragma once
#include "gameNode.h"
<<<<<<< HEAD
=======

>>>>>>> refs/remotes/origin/development
class title : public gameNode
{
private:
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

	/*			�Լ� �߰�			*/
	void showLogo();
	void showArrow();
	void clickMenu();
};

