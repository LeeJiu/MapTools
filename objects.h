#pragma once
#include "gameObject.h"
class objects : public gameObject
{
private:
	RECT _rcSummon;

public:
	objects();
	~objects();

	HRESULT init();
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/

	RECT getRcSummon() { return _rcSummon; }
};

