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
	loadDatabase("database.txt");

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

	//|,battle,0.3,2.0,0.0,2000,2000,|,carrier,0.4,1.0,0.0,3000,3000
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
		if (i == count + 1) mIter->second->drawX = (float)atof(vTemp[i].c_str());
		else if (i == count + 2) mIter->second->drawY = (float)atof(vTemp[i].c_str());
		else if (i == count + 3) mIter->second->rectX = (float)atof(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->rectY = (float)atof(vTemp[i].c_str());
		else if (i == count + 5) mIter->second->number = atoi(vTemp[i].c_str());
	}

	vTemp.clear();
}

void database::setElementDataDrawX(string str, float drX)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->drawX = drX;
}

void database::setElementDataDrawY(string str, float drY)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->drawY = drY;
}

void database::setElementDataRectX(string str, float rcX)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->rectX = rcX;
}

void database::setElementDataRectY(string str, float rcY)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->rectY = rcY;
}

void database::setElementDataNumber(string str, int number)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->number = number;
}

