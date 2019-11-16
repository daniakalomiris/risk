#include <iostream>
#include "PlayerStrategies.h"

using namespace std;

// constructor and destructor for Strategy class
Strategy::Strategy(Player* player) {
	this->player = player;
 }

Strategy::~Strategy() {
	delete player;
}

// copy constructor (deep copy)
Strategy::Strategy(const Strategy &orig) {
	if (orig.player) {
		player = new Player();
		player->setMap(orig.player->getMap());
		player->setName(orig.player->getName());
	}
	else {
		player = NULL;
	} 
}

// overloading assignment operator
const Strategy& Strategy::operator=(const Strategy &s) {
	if (this == &s) {
		return *this;
	}

	delete player;

	if (s.player) {
		player = new Player();
		player->setMap(s.player->getMap());
		player->setName(s.player->getName());
	}
	else {
		player = NULL;
	}
}
// constructor and destructor for ConcreteStrategy for human player
User::User(Player* player) : Strategy(player) {
	this->player = player;
}

User::~User() {
	delete player;
}



// all user inputs are chosen by the player

string User::extraReinforcement() {
	string input;
	cin >> input;
	return input;
}

// constructor and destructor for ConcreteStrategy for aggressive computer player
Aggressive::Aggressive(Player* player) : Strategy(player) {
	this->player = player;
}

Aggressive::~Aggressive() {
	delete player;
}

// aggressive computer player will always exchange again
string Aggressive::extraReinforcement() {
	return "y";
}

// constructor and destructor for ConcreteStrategy for benevolent computer player
Benevolent::Benevolent(Player* player) : Strategy(player) {
	this->player = player;
}

Benevolent::~Benevolent() {
	delete player;
}

// benevolent computer player will always exchange again
string Benevolent::extraReinforcement() {
	return "y";
}