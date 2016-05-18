#pragma once
#include "character.h"
class flonne : public character
{
public:
	flonne();
	~flonne();

	virtual HRESULT init();
	virtual HRESULT init(vector<TagTile*> tile);
	virtual void release();
	virtual void update();
	virtual void render();

	/*			�Լ� �߰�			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void setImage();
	virtual void setFrame();

	virtual void saveData();
	virtual void loadData();

	virtual void setItem(const char* itemName);
};

