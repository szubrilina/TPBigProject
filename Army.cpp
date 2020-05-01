#include "Army.h"
#include "Constants.h"
#include <algorithm>

Army::Army() {
	health = 0;
	damage = 0;
	accuracy = 0.0;
	mood = 0.0;
	type = ARMY_TYPE;
}

unsigned Army::get_health() {
	unsigned sum = 0;

	for (int i = 0; i < parts.size(); ++i) {
		sum += parts[i]->get_health();
	}
	
	return sum;
}

unsigned Army::get_damage() {
	unsigned sum = 0;

	for (int i = 0; i < parts.size(); ++i) {
		sum += parts[i]->get_damage();
	}

	return sum;
}

double Army::get_accuracy() {
	double sum = 0;

	for (int i = 0; i < parts.size(); ++i) {
		sum += parts[i]->get_accuracy();
	}

	return sum;
}

double Army::get_mood() {
	double sum = 0;

	for (int i = 0; i < parts.size(); ++i) {
		sum += parts[i]->get_mood();
	}

	return sum;
}

void Army::recover() {
	for (int i = 0; i < parts.size(); ++i) {
		parts[i]->set_health(1);
		parts[i]->set_damage(1);
	}
}

void Army::set_health(unsigned delta) {
	for (int i = 0; i < parts.size(); ++i) {
		parts[i]->set_health(delta);
	}
}

void Army::set_damage(unsigned delta) {
	for (int i = 0; i < parts.size(); ++i) {
		parts[i]->set_damage(delta);
	}
}


void Army::add_solders(Solder* new_solder) {
	this->parts.push_back(new_solder);
}

int Army::count_solders() {
	int ans = 0;
	for (int i = 0; i < parts.size(); ++i) {
		ans += parts[i]->count_solders();
	}
	return ans;
}

void Army::remove_solders(int cnt) {
	int ind = parts.size() - 1;
	while (cnt > 0 || ind > 0) {
		int cur_kol = parts[ind]->count_solders();
		parts[ind]->remove_solders(std::min(cur_kol, cnt));
		cnt -= std::min(cur_kol, cnt);
		
		if (parts[ind]->count_solders() == 0) {
			parts.pop_back();
		}

		ind -= 1;
	}
}