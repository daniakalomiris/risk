#pragma once
#include "Player.h"
#include <memory>

class Human;
class Aggressive;
class Benevolent;

class Strategy {
	public:
		Strategy(Player* player);
		~Strategy();
	private:
		Player* player;
};

class User : public Strategy {
	public:
		User(Player* player);
		~User();
};

class Aggressive : public Strategy {
	public:
		Aggressive(Player* player);
		~Aggressive();
};

class Benevolent : public Strategy {
	public:
		Benevolent(Player* player);
		~Benevolent();
};




