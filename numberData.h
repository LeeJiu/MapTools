#pragma once
#include "singletonBase.h"
class numberData : public singletonBase<numberData>
{
private:
	int _selectStageNumber;


public:
	numberData();
	~numberData();

	int getSelectStageNumber() { return _selectStageNumber; }
	void setSElectStageNumber(int number) { _selectStageNumber = number; }
};

