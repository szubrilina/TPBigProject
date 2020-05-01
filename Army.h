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

	void set_health(unsigned delta);
	void set_damage(unsigned delta);
	
	void recover();
	void add_solders(Solder* new_solder);
	void remove_solders(int cnt);
};
