#include "Solder.h"
#include "Constants.h"

/*
double Solder::get_mood() {
	return this->mood;
}

unsigned Solder::get_health() {
	return this->health;
}

unsigned Solder::get_damage() {
	return this->damage;
}

double Solder::get_accuracy() {
	return this->accuracy;
}
*/


void Solder::change_mood(double mult) {
	this->mood *= mult;
}

void Solder::change_health(unsigned delta) {
	this->health += delta;
}

void Solder::change_damage(unsigned delta) {
	this->damage += delta;
}

void Solder::change_accuracy(double mult) {
	this->accuracy *= mult;
}

double Solder::get_mood() {
	return this->mood;
}

unsigned Solder::get_health() {
	return this->health;
}

unsigned Solder::get_damage() {
	return this->damage;
}

double Solder::get_accuracy() {
	return this->accuracy * this->mood;
}

int Solder::count_solders() {
	return 1 - isRemoved;
}

void Solder::remove_solders(int) {
	isRemoved = 1;
}


Bowman::Bowman() {
	health = BOWMAN_HEALTH;
	damage = BOWMAN_DAMAGE;
	accuracy = BOWMAN_ACCURACY;
	mood = SOLDER_MOOD;
	type = BOWMAN_TYPE;
	isRemoved = 0;
}

Footman::Footman() {
	health = FOOTMAN_HEALTH;
	damage = FOOTMAN_DAMAGE;
	accuracy = FOOTMAN_ACCURACY;
	mood = SOLDER_MOOD;
	type = FOOTMAN_TYPE;
	isRemoved = 0;
}

Horseman::Horseman() {
	health = HORSEMAN_HEALTH;
	damage = HORSEMAN_DAMAGE;
	accuracy = HORSEMAN_ACCURACY;
	mood = SOLDER_MOOD;
	type = HORSEMAN_TYPE;
	isRemoved = 0;
}
