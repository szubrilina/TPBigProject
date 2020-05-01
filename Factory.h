#pragma once

#include "Solder.h"
#include "Army.h"

class AbstractFactory {
public:
	AbstractFactory() {}

	virtual Horseman* makeHorseman();
	virtual Bowman* makeBowman();
	virtual Footman* makeFootman();

	virtual Army* makeArmy(int cnt_Horse, int cntBow, int cntFoot);
};

class FranceFactory : virtual public AbstractFactory {
public:
	FranceFactory() {};
};

class EnglandFactory : virtual public AbstractFactory {
public:
	EnglandFactory() {};
};
