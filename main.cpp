

#include "Factory.h"
#include "Army.h"
#include "Factory.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


pair<int, int> buttle(Army* first, Army* second)
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
		return { 2, 100 };
	}
	if (h1 > 0) {
		return {1, 100 * (starth1 - h1) / starth1 };
	}
	return { 0, 100};
}



void game()
{
	printf("Choose the country you want to play: England (write E) or Franch (write F): ");
	std::string ans;
	std::cin >> ans;

	AbstractFactory* myFactory;

	if (ans == "E") {
		myFactory = new EnglandFactory();
		printf("You've choosen England!\nGame starts!\n");
	}
	else {
		myFactory = new FranceFactory();
		printf("You've choosen Franch!\nGame starts!\n");
	}

	std::vector<Army*> my_armies;
	Army* default_army = myFactory->makeArmy(rand() % 100, rand() % 100, rand() % 100);

	int time = 0;
	while (true) {
		time += 1;
		if (time % (rand() % 6) == 0) {
			int h = rand() % 100;
			int b = rand() % 100;
			int f = rand() % 100;
			Army *add_force = myFactory->makeArmy(h, b, f);
			printf("Congrats! You've been received additional force. \nYour new regiment consits of %d horsemen, %d bowmen and %d footmen\n", h, b, f);
			my_armies.push_back(add_force);
		}
		printf("\nyour next command?\n");
		std::cin >> ans;

		if (ans == "help") {
			///!!!!
		}
		else if (ans == "add") {
			int h, b, f;
			std::cin >> h >> b >> f;

			my_armies.push_back(myFactory->makeArmy(h, b, f));
			printf("new army created!\n");
		}
		else if (ans == "observe") {
			printf("you have following armies:\n");
			for (int i = 0; i < my_armies.size(); ++i) {
				std::cout << to_string(i + 1) << " with";
				std::cout << " total damage: " << my_armies[i]->get_damage();
				std::cout << ", total health: " << my_armies[i]->get_health();
				std::cout << ", average accuracy: " << my_armies[i]->get_accuracy() / max(1, my_armies[i]->count_solders());
				printf("\n");
			}
		}
		else if (ans == "attack") {
			printf("you have following armies:\n");
			for (int i = 0; i < my_armies.size(); ++i) {
				std::cout << to_string(i + 1) << " with";
				std::cout << " total damage: " << my_armies[i]->get_damage();
				std::cout << ", total health: " << my_armies[i]->get_health();
				std::cout << ", average accuracy: " << my_armies[i]->get_accuracy() / max(1, my_armies[i]->count_solders());
				printf("\n");
			}
			printf("Chose one of them and print number: ");

			int num;
			std::cin >> num;
			printf("You've choosen army  number %d!\n", num);
			num -= 1;

			pair<int, int> res = buttle(my_armies[num], default_army);

			if (res.first == 1) 
				printf("You've WIN the battle! But you lose %d per cent of army\n", res.second);
			else 
				printf("You've LOSE the battle! And all solders from army number %d died :(\n", num + 1);

			my_armies[num]->remove_solders(my_armies[num]->count_solders() * res.second / 100);
			if (my_armies[num]->count_solders() == 0) {
				my_armies.erase(my_armies.begin() + num);
			}

		}
		else if (ans == "merge") {
			int ind1, ind2;

			cin >> ind1 >> ind2;

			ind1 -= 1;
			ind2 -= 1;

			if (!(std::max(ind1, ind2) < my_armies.size() && std::min(ind1, ind2) >= 0)) {
				printf("Indexes are incorrect! Try this command adain\n");
			}

			my_armies[ind1]->parts.push_back(my_armies[ind2]);
			my_armies.erase(my_armies.begin() + ind2);

			printf("Army with index %d was merged into army with index  %d\n", ind2 + 1, ind1 + 1);
		}
		else if (ans == "finish") {
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

	/*std::unique_ptr<AbstractFactory> my_factory(new EnglandFactory);
	//AbstractFactory* my_factory = new EnglandFactory();

	Bowman *b = my_factory->makeBowman();

	Horseman *h = my_factory->makeHorseman();
	//std::cout << b.get_accuracy();

	Army *a2 = my_factory->makeArmy(1, 0, 0);
	std::cout << a2->get_health();

	Army* a3 = my_factory->makeArmy(0, 0, 0);
	a3->add_solders(b);
	a3->add_solders(h);
	std::cout << a3->get_health();

	a2->add_solders(a3);
	std::cout << a2->get_health();*/

	//std::cout << buttle(a2, a3);

	/*Army a = Army();
	a.parts.push_back(b);
	std::cout << a.get_health();

	a.parts.push_back(&a2);
	std::cout << a.get_health();

	a.recover();

	std::cout << a.get_health() << std::endl;*/
	return 0;
}