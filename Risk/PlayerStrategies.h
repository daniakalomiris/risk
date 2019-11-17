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
		// const Strategy& operator=(const Strategy& s);

		/* methods for reinforcement phase */
		virtual std::string extraReinforcement() = 0;
		virtual int countryToReinforce(Player* player) = 0;
		virtual int armiesToPlace(Player* player) = 0;
		
		/* methods for attack phase */
		virtual std::string chooseAttack() = 0;
		virtual int attackFrom(Player* player) = 0;
		virtual int countryToAttack(Country* attackFrom) = 0;
		virtual int attackerRoll() = 0;
		virtual int armiesToMove(int armiesCanMove) = 0;

		/* methods for fortify phase */
		virtual std::string chooseFortify() = 0;
		virtual std::string countryToFortifyFrom(Player* player) = 0;
		virtual int armiesToFortify(int sourceCounrtyArmies) = 0;
		virtual std::string countryToFortify(Player* player) = 0;

		// determines how exchange is handled for each strategy
		virtual bool exchangeAutom() = 0;
};

class User : public Strategy {
	public:
		User();
		~User();
		User(const User& orig);
		// const User& operator=(const User& u);

		std::string extraReinforcement();
		int countryToReinforce(Player* player);
		int armiesToPlace(Player* player);

		std::string chooseAttack();
		int attackFrom(Player* player);
		int countryToAttack(Country* attackFrom);
		int attackerRoll();
		int armiesToMove(int armiesCanMove);

		std::string chooseFortify();
		std::string countryToFortifyFrom(Player* player);
		int armiesToFortify(int sourceCounrtyArmies);
		std::string countryToFortify(Player* player);

		bool exchangeAutom();
};

class Aggressive : public Strategy {
	public:
		Aggressive();
		~Aggressive();
		Aggressive(const Aggressive& orig);
		// const Aggressive& operator=(const Aggressive& a);

		std::string extraReinforcement();
		int countryToReinforce(Player* player);
		int armiesToPlace(Player* player);

		std::string chooseAttack();
		int attackFrom(Player* player);
		int countryToAttack(Country* attackFrom);
		int attackerRoll();
		int armiesToMove(int armiesCanMove);

		std::string chooseFortify();
		std::string countryToFortifyFrom(Player* player);
		int armiesToFortify(int sourceCounrtyArmies);
		std::string countryToFortify(Player* player);

		bool exchangeAutom();
};

class Benevolent : public Strategy {
	public:
		Benevolent();
		~Benevolent();
		Benevolent(const Benevolent& orig);
		// const Benevolent& operator=(const Benevolent& u);

		std::string extraReinforcement();
		int countryToReinforce(Player* player);
		int armiesToPlace(Player* player);

		std::string chooseAttack();
		int attackFrom(Player* player);
		int countryToAttack(Country* attackFrom);
		int attackerRoll();
		int armiesToMove(int armiesCanMove);

		std::string chooseFortify();
		std::string countryToFortifyFrom(Player* player);
		int armiesToFortify(int sourceCounrtyArmies);
		std::string countryToFortify(Player* player);

		bool exchangeAutom();
};


