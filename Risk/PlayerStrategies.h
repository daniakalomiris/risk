#pragma once
#include "Player.h"
#include <string>
#include <memory>

class Human;
class Aggressive;
class Benevolent;

class Strategy {
	public:
		Strategy(Player* player);
		~Strategy();
		Strategy(const Strategy &orig);
		const Strategy& operator=(const Strategy &s);

		virtual string extraReinforcement() = 0;
		virtual int countryToReinforce() = 0;

	private:
		Player* player;
};

class User : public Strategy {
	public:
		User(Player* player);
		~User();

		std::string extraReinforcement();
		int countryToReinforce();

	private:
		Player* player;

};

class Aggressive : public Strategy {
	public:
		Aggressive(Player* player);
		~Aggressive();

		std::string extraReinforcement();
		int countryToReinforce();

	private:
		Player* player;
};

class Benevolent : public Strategy {
	public:
		Benevolent(Player* player);
		~Benevolent();

		std::string extraReinforcement();
		int countryToReinforce();

	private:
		Player* player;
};




