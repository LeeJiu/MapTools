#pragma once

#include "singletonBase.h"

#include <vector>
#include <map>

class elements
{
public:
	int i, j;
	float drawX, drawY;
	float rectX, rectY;
	int number;

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

	//void setElementDatai(string str, int i);
	//void setElementDataj(string str, int j);
	void setElementDataDrawX(string str, float drX);
	void setElementDataDrawY(string str, float drY);
	void setElementDataRectX(string str, float rcX);
	void setElementDataRectY(string str, float rcY);
	void setElementDataNumber(string str, int number);
};

