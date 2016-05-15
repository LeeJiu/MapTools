#pragma once
#include "singletonBase.h"

class battleManager : public singletonBase<battleManager>
{
private:
	int _turnCount;
	
public:
	battleManager();
	~battleManager();


	void setUnitMove();
	void setUnitAttack();
	void setUnitDefence();
	void setUnitPain();

	void setActionAttack();
	void setTurnChange();


};

