#include <iostream>
#include "PlayerStrategies.h"

using namespace std;

Strategy::Strategy(Player* player) {
	this->player = player;
 }

Strategy::~Strategy() {
	delete player;
}

User::User(Player* player) : Strategy(player) {
}

User::~User() {
}

Aggressive::Aggressive(Player* player) : Strategy(player) {
}

Aggressive::~Aggressive() {
}

Benevolent::Benevolent(Player* player) : Strategy(player) {
}

Benevolent::~Benevolent() {
}