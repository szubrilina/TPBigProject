

#include "Factory.h"
#include "Army.h"
#include "Factory.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <time.h>

using namespace std;

bool is_index_correct(int ind, vector<Army*> my_armies) {
	if (ind < 0 || ind >= my_armies.size()) {
		printf("Index is incorrect. Please, try this command again\n");
		return 1;
	}
	return 0;
}

// second army is default
pair<int, int> buttle(Army* first, Army* second)  //returns (p1, p2) where p1 = {1, 2} - the number of winner army. p2 - is a persantage of wasted health
{
	double h1 = first->get_health();
	double h2 = second->get_health();
	double starth1 = h1, starth2 = h2;

	double d1 = first->get_damage();
	double d2 = second->get_damage();

	double ac1 = first->get_accuracy() ;
	double ac2 = second->get_accuracy();

	int n1 = first->count_solders();
	int n2 = second->count_solders();

	ac1 /= n1;
	ac2 /= n2;

	while (h1 > 0 && h2 > 0)
	{
		h2 -= d1 * ac1;
		h1 -= d2 * ac2;
	}

	if (h2 > 0) {
		return { 2, 100 * (starth2 - h2) / starth2 };
	}
	if (h1 > 0) {
		return {1, 100 * (starth1 - h1) / starth1 };
	}
	return { 0, 100};
}

bool attack(std::vector< Army*> &my_armies, Army *default_army) {

	bool is_non_default_win = 0;

	printf("you have following armies:\n");
	for (int i = 0; i < my_armies.size(); ++i) {
		std::cout << to_string(i + 1) << " with";
		std::cout << " total damage: " << my_armies[i]->get_damage();
		std::cout << ", total health: " << my_armies[i]->get_health();
		std::cout << ", average accuracy: " << my_armies[i]->get_accuracy() / max(1, my_armies[i]->count_solders());
		printf("\n");
	}
	printf("Chose one of them and print number: ");

	int num1, num2 = -1;
	std::cin >> num1;
	num1 -= 1;

	if (is_index_correct(num1, my_armies)) {
		return 0;
	}

	printf("You've choosen army  number %d!\n\n", num1 + 1);

	printf("Would you like to fight with another army you have? (print Y or N) ");
	char c;
	cin >> c;

	if (c == 'Y') {
		printf("Chose one army and print its number: ");
		cin >> num2;
		num2 -= 1;

		if (is_index_correct(num2, my_armies)) {
			return 0;
		}

		printf("You've choosen army  number %d!\n\n", num2 + 1);
	}
	else {
		printf("You will fight with default enemy");
	}

	pair<int, int> res = buttle(my_armies[num1], (num2 == -1 ? default_army : my_armies[num2]));

	if (res.first == 1) {
		printf("The first army has WIN the battle! But it've lost %d per cent of solders\n", res.second);
		is_non_default_win = 1;
	}
	else {

		if (num2 != -1) {
			printf("The second army has WIN the battle! But it've lost %d per cent of solders\n", res.second);
			is_non_default_win = 1;
		}
		else {
			printf("You've LOST the battle! And all your solders died :(");
		}
	}

	my_armies[num1]->remove_solders(my_armies[num1]->count_solders() * res.second / 100);
	if (my_armies[num1]->count_solders() == 0) {
		my_armies.erase(my_armies.begin() + num1);
	}

	if (num2 != -1 && num1 != num2) {
		if (num1 < num2) {
			num2 -= 1;
		}

		my_armies[num2]->remove_solders(my_armies[num2]->count_solders() * res.second / 100);
		if (my_armies[num2]->count_solders() == 0) {
			my_armies.erase(my_armies.begin() + num2);
		}
	}
	return is_non_default_win;
}

void try_to_happen_addirion_force(std::vector<Army*> &my_armies, AbstractFactory *myFactory) {

	if (rand() % FREQUENCY_OF_ADDITION_FORCE == 0) {
		int h = rand() % ADDITION_FORCE;
		int b = rand() % ADDITION_FORCE;
		int f = rand() % ADDITION_FORCE;
		Army* add_force = myFactory->makeArmy(h, b, f);

		printf("\n----------\n");
		printf("Congrats! You've been received additional force. \n");
		printf("Your new regiment consits of %d horsemen, %d bowmen and %d footmen\n", h, b, f);
		printf("----------\n");

		my_armies.push_back(add_force);
	}
}

void try_to_happen_depression(std::vector<Army*> &my_armies, double currecnt_probability_of_depression) {

	float random_number = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	if (random_number < currecnt_probability_of_depression && my_armies.size() > 0) {

		int index = rand() % my_armies.size();

		my_armies[index]->change_mood(DEPRESSION_MOOD_DICREASE);

		
		printf("\n----------\n");
		printf("Solders in the army number %d have fallen in depression :(\nTheir mood and accuracy has decreased!\n", index + 1);
		printf("----------\n");
	}
}

void command_help() {
	ifstream in;
	in.open("help.txt");

	string s;
	while (getline(in, s)) {
		cout << s << '\n';
	}
	in.close();
}

void command_add(std::vector<Army*> &my_armies, AbstractFactory* myFactory) {

	int h, b, f;
	cin >> h >> b >> f;

	if (std::min(h, min(b, f)) < 0) {
		printf("Number of solders must be positive! Please try this command again.");
		return;
	}
	my_armies.push_back(myFactory->makeArmy(h, b, f));
	printf("new army created!\n");
}

void command_observe(std::vector<Army*> &my_armies) {
	printf("you have following armies:\n");
	for (int i = 0; i < my_armies.size(); ++i) {
		std::cout << to_string(i + 1) << " with";
		std::cout << " total damage: " << my_armies[i]->get_damage();
		std::cout << ", total health: " << my_armies[i]->get_health();
		std::cout << ", average accuracy: " << my_armies[i]->get_accuracy() / max(1, my_armies[i]->count_solders());
		printf("\n");
	}
}

void command_attack(std::vector<Army*> &my_armies, Army* default_army) {

	bool isWin = attack(my_armies, default_army);

	if (isWin) {
		for (int i = 0; i < my_armies.size(); ++i) {
			if (rand() % 3 == 0) {
				my_armies[i]->change_accuracy(1.5);
				printf("Solders from army number %d are glab the win! Their accuracy have increased.\n", i);
			}
		}
	}
}

void command_merge(std::vector<Army*> &my_armies) {
	int ind1, ind2;

	cin >> ind1 >> ind2;
	ind1 -= 1;
	ind2 -= 1;

	if (is_index_correct(ind1, my_armies) || is_index_correct(ind2, my_armies)) {
		return;
	}

	my_armies[ind1]->parts.push_back(my_armies[ind2]);
	my_armies.erase(my_armies.begin() + ind2);

	printf("Army with index %d was merged into army with index  %d\n", ind2 + 1, ind1 + 1);
}

AbstractFactory* make_factory() {

	printf("Choose the country you want to play: England (write E) or Franch (write F): ");
	std::string ans;
	getline(cin, ans);

	AbstractFactory* myFactory;

	if (ans == "E") {
		myFactory = new EnglandFactory();
		printf("You've choosen England!\nGame starts!\n");
	}
	else {
		myFactory = new FranceFactory();
		printf("You've choosen Franch!\nGame starts!\n");
	}

	return myFactory;
}

string lower_case(string &command) {
	for (int i = 0; i < command.size(); ++i) {
		if (command[i] >= 'A' and command[i] <= 'Z') {
			command[i] += (-'A' + 'a');
		}
	}
	return command;
}


void game()
{
	srand(time(NULL));

	AbstractFactory* myFactory = make_factory();

	std::vector<Army*> my_armies;
	Army* default_army = myFactory->makeArmy(rand() % ADDITION_FORCE, rand() % ADDITION_FORCE, rand() % ADDITION_FORCE);
	double currecnt_probability_of_depression = DEFAULT_PROBABILITY_OF_DEPRESSION;
	
	while (true) {

		try_to_happen_addirion_force(my_armies, myFactory);

		try_to_happen_depression(my_armies, currecnt_probability_of_depression);

		printf("\nyour next command?\n");
		string command;
		std::cin >> command;

		if (command == "help") {
			command_help();
		}
		else if (command == "add") {
			command_add(my_armies, myFactory);
		}
		else if (command == "observe") {
			command_observe(my_armies);
		}
		else if (command == "attack") {
			command_attack(my_armies, default_army);
		}
		else if (command == "merge") {
			command_merge(my_armies);
		}
		else if (command == "finish") {
			printf("Game over!\n");
			return;
		}
		else {
			printf("Unknown command. Please try again\n");
		}
	}
}

int main()
{
	game();

	return 0;
}