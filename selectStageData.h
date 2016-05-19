#pragma once
#include "singletonBase.h"
class selectStageData : public singletonBase<selectStageData>
{
private:
	int _selectStageNumber;


public:
	selectStageData();
	~selectStageData();

	int getSelectStageNumber() { return _selectStageNumber; }
	void setSElectStageNumber(int number) { _selectStageNumber = number; }
};

