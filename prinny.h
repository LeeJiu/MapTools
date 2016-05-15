#pragma once
#pragma warning(disable : 4996)
#include "character.h"
#include "inventory.h"

class prinny : public character
{
private:
	int _hell;

	inventory* _inventory;

	RECT _invenExit;

	bool _isbattle;

public:
	prinny();
	~prinny();

	virtual HRESULT init();
	virtual HRESULT init(vector<TagTile*>& tile);
	virtual void release();
	virtual void update();
	virtual void render();
	 
	 /*			�Լ� �߰�			*/
	virtual void keyControl();
	virtual void battleKeyControl();
	virtual void move(int endX, int endY);
	virtual void setImage();
	virtual void setFrame();
	virtual void previousState();								// �������� ���ư��� �Լ�
	virtual void showPossibleMoveTile();						// �̵������� Ÿ�� �����ִ� �Լ�

	virtual void saveData();
	virtual void loadData();
	 
	virtual void setItem(const char* itemName);
	virtual void setHell(int hell) { _hell = hell; }
	 
	virtual int getHell() { return _hell; }
};

