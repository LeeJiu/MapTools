#include "stdafx.h"
#include "characterDatabase.h"


characterDatabase::characterDatabase()
{
}


characterDatabase::~characterDatabase()
{
}

HRESULT characterDatabase::init()
{
	//loadDatabase("database.txt");

	return S_OK;
}

void characterDatabase::release()
{
	iterElement mIter = _mTotalElement.begin();

	for (; mIter != _mTotalElement.end(); ++mIter)
	{
		SAFE_DELETE(mIter->second);
	}

	_mTotalElement.clear();
}

void characterDatabase::loadDatabase(string name)
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
			character* em = new character;
			str = vTemp[i + 1];
			_mTotalElement.insert(pair<string, character*>(vTemp[i + 1], em));
			if (i != 0) count += 26;

			continue;
		}

		iterElement mIter = _mTotalElement.find(str);

		//읽어올 데이터들
		if (i == count + 1) mIter->second->_fileName = vTemp[i].c_str();
		
	}

	vTemp.clear();
}
