#pragma once

#include "singletonBase.h"

#include <vector>
#include <map>

class elements
{
public:
	int number;
	int state;
	int x;
	int y;
	int imageNum;

	//오브젝트

	elements() {};
	~elements() {};
};

class database : public singletonBase<database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	typedef map<string, elements*> arrElement;
	typedef map<string, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;

public:
	database();
	~database();

	HRESULT init();
	void release();

	void loadDatabase(string name);

	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	void setElementDataNumber(string str, int number);
	void setElementDataState(string str, int state);
	void setElementDataX(string str, int x);
	void setElementDataY(string str, int y);
	void setElementDataImageNum(string str, int imageNum);
};
