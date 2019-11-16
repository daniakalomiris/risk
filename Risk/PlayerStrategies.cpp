#include <iostream>
#include "PlayerStrategies.h"

using namespace std;

// constructor and destructor for Strategy class
Strategy::Strategy() {
 }

Strategy::~Strategy() {
}

// copy constructor (deep copy)
Strategy::Strategy(const Strategy &orig) {
}

// overloading assignment operator
const Strategy& Strategy::operator=(const Strategy &s) {
	if (this == &s) {
		return *this;
	}
}

// constructor and destructor for ConcreteStrategy for human player
User::User() {
}

User::~User() {
}

// copy constructor (deep copy)
User::User(const User& orig) : Strategy() {
}

// overloading assignment operator
const User& User::operator=(const User& u) {
	if (this == &u) {
		return *this;
	}
}

// all user inputs are chosen by the player
string User::extraReinforcement() {
	string input;
	cin >> input;
	return input;
}

int User::countryToReinforce(Player* player) {
	int input;
	cin >> input;
	return input;
}

int User::armiesToPlace(Player* player) {
	int input;
	cin >> input;
	return input;
}

string User::chooseAttack(Player* player) {
	string input;
	cin >> input;
	return input;
}


// constructor and destructor for ConcreteStrategy for aggressive computer player
Aggressive::Aggressive() {
}

Aggressive::~Aggressive() {
}

// copy constructor (deep copy)
Aggressive::Aggressive(const Aggressive& orig) : Strategy(orig) {
}

// overloading assignment operator
const Aggressive& Aggressive::operator=(const Aggressive& a) {
	if (this == &a) {
		return *this;
	}
}

// aggressive player will always exchange again
string Aggressive::extraReinforcement() {
	return "y";
}

// aggressive playyer will select country with most armies on it
int Aggressive::countryToReinforce(Player* player) {
	
	// set max country to be first index in the list of player's countries
	int max = 0;

	for (int i = 1; i < player->getThisPlayerCountries().size(); i++) {
		if (player->getThisPlayerCountries().at(i)->getNumberOfArmies() > player->getThisPlayerCountries().at(max)->getNumberOfArmies()) {
			max = i; // assigning the index of the vector
		}
	}

	return max + 1; // returning the country number with the most armies
}

// aggressive player will put all of armies that can be added to their chosen country
int Aggressive::armiesToPlace(Player* player) {
	return player->getNumOfArmiesForReinforcement();
}

// constructor and destructor for ConcreteStrategy for benevolent computer player
Benevolent::Benevolent() {
}

Benevolent::~Benevolent() {
}

// copy constructor (deep copy)
Benevolent::Benevolent(const Benevolent& orig) : Strategy(orig) {
}

// overloading assignment operator
const Benevolent& Benevolent::operator=(const Benevolent& b) {
	if (this == &b) {
		return *this;
	}
}

// benevolent computer player will always exchange again
string Benevolent::extraReinforcement() {
	return "y";
}

// benevolent playyer will select country with least armies on it
int Benevolent::countryToReinforce(Player* player) {

	// set min country to be first index in the list of player's countries
	int min = 0;

	for (int i = 0; i < player->getThisPlayerCountries().size(); i++) {
		if (player->getThisPlayerCountries().at(min)->getNumberOfArmies() > player->getThisPlayerCountries().at(i)->getNumberOfArmies()) {
			min = i; // assigning the index of the vector
		}
	}

	return min + 1; // returning the country number with the least armies
}

// benevolent player will put all of armies that can be added to their chosen country
int Benevolent::armiesToPlace(Player* player) {
	return player->getNumOfArmiesForReinforcement();
}
