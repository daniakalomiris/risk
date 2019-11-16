#include <iostream>
#include "PlayerStrategies.h"

using namespace std;

int main() {

	Player* player = new Player();

	/* before calling each reinforce, attack and fortify phase */
	int strategy;
	cout << "Which strategy would you like to use? Please enter the number of the strategy to make your choice." << endl;
	cout << "(1) User Strategy" << endl;
	cout << "(2) Aggressive Strategy" << endl;
	cout << "(3) Benevolent Strategy" << endl;
	cin >> strategy;

	while (strategy < 0 || strategy > 3) {
		cout << "Please select a valid strategy from the list of strategies." << endl;
	}

	User* user = new User();
	Aggressive* aggressive = new Aggressive();
	Benevolent* benevolent = new Benevolent();

	switch (strategy) {
		case 1: 
			player->setStrategy(user);
		case 2:
			player->setStrategy(aggressive);
		case 3:
			player->setStrategy(benevolent);
	}

}
