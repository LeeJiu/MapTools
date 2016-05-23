#pragma once
#include "singletonBase.h"
class numberData : public singletonBase<numberData>
{
private:
	int _selectStageNumber;
	int _townSourX;
	int _townSourY;

public:
	numberData();
	~numberData();

	int getSelectStageNumber() { return _selectStageNumber; }
	void setSElectStageNumber(int number) { _selectStageNumber = number; }

	int getTownSourX() { return _townSourX; }
	int getTownSourY() { return _townSourY; }
	void setTownSourX(int x) { _townSourX = x; }
	void setTownSourY(int y) { _townSourY = y; }
};

