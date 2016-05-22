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

	/*			함수 추가			*/

	RECT getRcSummon() { return _rcSommon; }

	virtual void previousState();							// 이전으로 돌아가는 함수
	virtual void showPossibleMoveTile();				// 이동가능한 타일 보여주는 함수

	virtual void setItem(const char* itemName, bool isWear);
	virtual void setMercenary(const char* characterName);
	virtual int getHell();
	virtual void setHell(int hell);
};

