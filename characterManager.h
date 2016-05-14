#pragma once
#include "gameNode.h"
class characterManager : public gameNode
{
private:
	image* _imagePlayer;
	RECT _rcPlayer;
	int x, y;
		


public:
	characterManager();
	~characterManager();
};

