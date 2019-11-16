#include <iostream>
#include "PlayerStrategies.h"
#include "time.h"

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
/*const Strategy& Strategy::operator=(const Strategy &s) {
	if (this == &s) {
		return *this;
	}
}*/

// constructor and destructor for ConcreteStrategy for human player
User::User() {
}

User::~User() {
}

// copy constructor (deep copy)
User::User(const User& orig) : Strategy() {
}

// overloading assignment operator
/*const User& User::operator=(const User& u) {
	if (this == &u) {
		return *this;
	}
}*/

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

string User::chooseAttack() {
	string input;
	cin >> input;
	return input;
}

int User::attackFrom(Player* player) {
	int input;
	cin >> input;
	return input;
}

int User::countryToAttack(Country* attackFrom) {
	int input;
	cin >> input;
	return input;
}

int User::attackerRoll() {
	int input;
	cin >> input;
	return input;
}

int User::armiesToMove(int armiesCanMove) {
	int input;
	cin >> input;
	return input;
}

string User::chooseFortify() {
	string input;
	cin >> input;
	return input;
}

string User::countryToFortifyFrom(Player* player) {
	string input;
	cin >> input;
	return input;
}

int User::armiesToFortify(int sourceCountryArmies) {
	int input;
	cin >> input;
	return input;
}

string User::countryToFortify(Player* player) {
	string input;
	cin >> input;
	return input;
}

// human players choose when to exchange
bool User::exchangeAutom() {
	return false;
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
/*const Aggressive& Aggressive::operator=(const Aggressive& a) {
	if (this == &a) {
		return *this;
	}
}*/

// aggressive player will always exchange again
string Aggressive::extraReinforcement() {
	return "y";
}

// aggressive playyer will select country with most armies on it
int Aggressive::countryToReinforce(Player* player) {
	
	// set max country to be first index in the list of player's countries
	int max = 0;

	for (unsigned int i = 1; i < player->getThisPlayerCountries().size(); i++) {
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

// aggressive player always attacks
string Aggressive::chooseAttack() {
	return "Y";
}

// aggressive player attacks from country with most armies on it
int Aggressive::attackFrom(Player* player) {
	// set max country to be first index in the list of player's countries
	int max = 0;

	for (unsigned int i = 1; i < player->getThisPlayerCountries().size(); i++) {
		if (player->getThisPlayerCountries().at(i)->getNumberOfArmies() > player->getThisPlayerCountries().at(max)->getNumberOfArmies()) {
			max = i; // assigning the index of the vector
		}
	}

	return max + 1; // returning the country number with the most armies
}

// aggressive player will attack random country from list of neighbors
int Aggressive::countryToAttack(Country* attackFrom) {
	
	// reset the random value
	srand(time(NULL));

	// generates random number from 1 to the number of adjacent countries
	return (rand() % (attackFrom->getAdjacentCountries().size()) + 1);
}

// aggressive player will roll a random number of dice
int Aggressive::attackerRoll() {

	// reset the random value
	srand(time(NULL));

	// generates random number from 1 to 3 (attack phase is in charge of verifying if 3 is not valid)
	return (rand() % 3 + 1); 
}

// aggressive player moves all armies that they can move
int Aggressive::armiesToMove(int armiesCanMove) {
	return armiesCanMove;
}

// aggressive player will fortify
string Aggressive::chooseFortify() {
	return "Y";
}

// aggressive player will fortify from country with least armies on it
string Aggressive::countryToFortifyFrom(Player* player) {
	// set min country to be first index in the list of player's countries
	int min = 0;

	for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
		if (player->getThisPlayerCountries().at(min)->getNumberOfArmies() > player->getThisPlayerCountries().at(i)->getNumberOfArmies()) {
			min = i; // assigning the index of the vector
		}
	}

	return player->getThisPlayerCountries().at(min)->getCountryName(); // returning the country number with the most armies
}

// aggressive player moves all armies from source country to target country
int Aggressive::armiesToFortify(int sourceCountryArmies) {
	return sourceCountryArmies;

}

// aggressive player will fortify country with most armies on it
string Aggressive::countryToFortify(Player* player) {
	// set max country to be first index in the list of player's countries
	int max = 0;

	for (unsigned int i = 1; i < player->getThisPlayerCountries().size(); i++) {
		if (player->getThisPlayerCountries().at(i)->getNumberOfArmies() > player->getThisPlayerCountries().at(max)->getNumberOfArmies()) {
			max = i; // assigning the index of the vector
		}
	}

	return player->getThisPlayerCountries().at(max)->getCountryName(); // returning the country number with the most armies
}

// computer players always exchange
bool Aggressive::exchangeAutom() {
	return true;
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
/*const Benevolent& Benevolent::operator=(const Benevolent& b) {
	if (this == &b) {
		return *this;
	}
}*/

// benevolent computer player will always exchange again
string Benevolent::extraReinforcement() {
	return "y";
}

// benevolent playyer will select country with least armies on it
int Benevolent::countryToReinforce(Player* player) {

	// set min country to be first index in the list of player's countries
	int min = 0;

	for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
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

// benevolent player never attacks (will always return n or 0)
string Benevolent::chooseAttack() {
	return "n";
}

int Benevolent::attackFrom(Player* player) {
	return 0;
}

int Benevolent::countryToAttack(Country* attackFrom) {
	return 0;
}

int Benevolent::attackerRoll() {
	return 0;
}

int Benevolent::armiesToMove(int armiesCanMove) {
	return 0;
}

// benevolent player will fortify
string Benevolent::chooseFortify() {
	return "Y";
}

// benevolent player will fortify from country with most armies on it
string Benevolent::countryToFortifyFrom(Player* player) {
	// set max country to be first index in the list of player's countries
	int max = 0;

	for (unsigned int i = 1; i < player->getThisPlayerCountries().size(); i++) {
		if (player->getThisPlayerCountries().at(i)->getNumberOfArmies() > player->getThisPlayerCountries().at(max)->getNumberOfArmies()) {
			max = i; // assigning the index of the vector
		}
	}

	return player->getThisPlayerCountries().at(max)->getCountryName(); // returning the country number with the most armies
}

// benevolent player moves all armies from source country to target country
int Benevolent::armiesToFortify(int sourceCountryArmies) {
	return sourceCountryArmies;
}

// benevolent player will fortify country with least armies on it
string Benevolent::countryToFortify(Player* player) {
	// set min country to be first index in the list of player's countries
	int min = 0;

	for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
		if (player->getThisPlayerCountries().at(min)->getNumberOfArmies() > player->getThisPlayerCountries().at(i)->getNumberOfArmies()) {
			min = i; // assigning the index of the vector
		}
	}

	return player->getThisPlayerCountries().at(min)->getCountryName(); // returning the country number with the most armies
}

// computer players always exchange
bool Benevolent::exchangeAutom() {
	return true;
}
