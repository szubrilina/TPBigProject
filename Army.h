#pragma once
#include "Solder.h"
#include <vector>

class Army : public Solder {
public:
	std::vector<Solder*> parts;

public:
	Army();
	unsigned get_health();	
	unsigned get_damage();
	double get_accuracy();
	double get_mood();
	int count_solders();

	void change_health(unsigned delta);
	void change_damage(unsigned delta);
	void change_accuracy(double delta);
	void change_mood(double delta);

	void add_solders(Solder* new_solder);
	void remove_solders(int cnt);
};
