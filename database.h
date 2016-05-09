#pragma once

#include "singletonBase.h"

#include <vector>
#include <map>

class elements
{
public:
<<<<<<< HEAD
	int i, j;
	float drawX, drawY;
	float rectX, rectY;
	int number;
=======
	int number;
	int state;
>>>>>>> refs/remotes/origin/master

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

<<<<<<< HEAD
	//void setElementDatai(string str, int i);
	//void setElementDataj(string str, int j);
	void setElementDataDrawX(string str, float drX);
	void setElementDataDrawY(string str, float drY);
	void setElementDataRectX(string str, float rcX);
	void setElementDataRectY(string str, float rcY);
	void setElementDataNumber(string str, int number);
=======
	void setElementDataNumber(string str, int number);
	void setElementDataState(string str, int state);
>>>>>>> refs/remotes/origin/master
};

