#include "Factory.h"
#include "Constants.h"


Bowman* AbstractFactory::makeBowman() {
	Bowman* newSolder = new Bowman();
	return newSolder;
}
Horseman* AbstractFactory::makeHorseman() {
	Horseman* newSolder = new Horseman();
	return newSolder;
}
Footman* AbstractFactory::makeFootman() {
	Footman* newSolder = new Footman();
	return newSolder;
}

Army* AbstractFactory::makeArmy(int h, int b, int f) {
	Army *new_army = new Army();
	for (int i = 0; i < h; ++i)
	{
		Horseman *one = this->makeHorseman();
		new_army->parts.push_back(one);
	}
	for (int i = 0; i < b; ++i)
	{
		Bowman *one = this->makeBowman();
		new_army->parts.push_back(one);
	}
	for (int i = 0; i < f; ++i)
	{
		Footman* one = this->makeFootman();
		new_army->parts.push_back(one);
	}
	return new_army;
}