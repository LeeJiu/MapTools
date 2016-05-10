#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{
}

HRESULT database::init()
{
	//loadDatabase("database.txt");

	return S_OK;
}

void database::release()
{
	iterElement mIter = _mTotalElement.begin();

	for (; mIter != _mTotalElement.end(); ++mIter)
	{
		SAFE_DELETE(mIter->second);
	}

	_mTotalElement.clear();
}

void database::loadDatabase(string name)
{
	//데이터 읽어온다
	arrElements vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;

	//|,number,state,|,number,state,
	for (unsigned int i = 0; i < vTemp.size(); i++)
	{
		if (vTemp[i] == "|")
		{
			elements* em = new elements;
			str = vTemp[i + 1];
			_mTotalElement.insert(pair<string, elements*>(vTemp[i + 1], em));
			if (i != 0) count += 6;

			continue;
		}

		iterElement mIter = _mTotalElement.find(str);

		//읽어올 데이터들
		if (i == count + 1) mIter->second->number = atoi(vTemp[i].c_str());
		else if (i == count + 2) mIter->second->state = atoi(vTemp[i].c_str());
		else if (i == count + 3) mIter->second->x = atoi(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->y = atoi(vTemp[i].c_str());
		else if (i == count + 5) mIter->second->imageNum = atoi(vTemp[i].c_str());
	}

	vTemp.clear();
}

void database::setElementDataNumber(string str, int number)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->number = number;
}

void database::setElementDataState(string str, int state)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->state = state;
}

void database::setElementDataX(string str, int x)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->x = x;
}

void database::setElementDataY(string str, int y)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->y = y;
}

void database::setElementDataImageNum(string str, int imageNum)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->number = imageNum;
}
