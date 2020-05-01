#pragma once

#include <string>

class Solder {
public:

	unsigned health;
	unsigned damage;
	double accuracy;
	double mood;
	std::string type;
	bool isRemoved;

	virtual unsigned get_health();
	virtual unsigned get_damage();
	virtual double get_accuracy();
	virtual double get_mood();

	virtual void set_health(unsigned delta);
	virtual void set_damage(unsigned delta);
	virtual void set_accuracy(double mult);
	virtual void set_mood(double mult);

	virtual int count_solders();
	virtual void remove_solders(int);
};

//Лучник
class Bowman : public Solder {
public:
	Bowman();
};

//Пехотинец
class Footman : public Solder {
public:
	Footman();
};

//Наездник
class Horseman : public Solder {
public:
	Horseman();
};
