#pragma once
#include <string>
#include <memory>
#include "Player.h"

class User;
class Aggressive;
class Benevolent;

class Strategy {
	public:
		Strategy();
		~Strategy();
		Strategy(const Strategy& orig);
		const Strategy& operator=(const Strategy& s);

		/* methods for reinforcement phase */
		virtual std::string extraReinforcement() = 0;
		virtual int countryToReinforce(Player* player) = 0;
		virtual int armiesToPlace(Player* player) = 0;
		
		/* methods for attack phase */
		virtual std::string chooseAttack(Player* player) = 0;
};

class User : public Strategy {
	public:
		User();
		~User();
		User(const User& orig);
		const User& operator=(const User& u);

		std::string extraReinforcement();
		int countryToReinforce(Player* player);
		int armiesToPlace(Player* player);

		std::string chooseAttack(Player* player);
};

class Aggressive : public Strategy {
	public:
		Aggressive();
		~Aggressive();
		Aggressive(const Aggressive& orig);
		const Aggressive& operator=(const Aggressive& a);

		std::string extraReinforcement();
		int countryToReinforce(Player* player);
		int armiesToPlace(Player* player);

		std::string chooseAttack(Player* player);
};

class Benevolent : public Strategy {
	public:
		Benevolent();
		~Benevolent();
		Benevolent(const Benevolent& orig);
		const Benevolent& operator=(const Benevolent& u);

		std::string extraReinforcement();
		int countryToReinforce(Player* player);
		int armiesToPlace(Player* player);

		std::string chooseAttack(Player* player);
};


