#pragma once
#include "gameObject.h"

class objects : public gameObject
{
private:

	int _count, _curFrameX;

	RECT _rcSommon;
	int _imageNum;
	int _width, _height;

	bool _isFrame;
public:
	objects();
	~objects();

	virtual HRESULT init(const char* strkey, int x, int y, int imageNum, gameObjectManager* gom);
	void release();
	void update();
	void render();

	/*			�Լ� �߰�			*/

	RECT getRcSummon() { return _rcSommon; }

	virtual void previousState();							// �������� ���ư��� �Լ�
	virtual void showPossibleMoveTile();				// �̵������� Ÿ�� �����ִ� �Լ�

	virtual void setItem(const char* itemName, bool isWear);
	virtual void setMercenary(const char* characterName);
	virtual int getHell();
	virtual void setHell(int hell);
};

