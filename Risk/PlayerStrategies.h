#pragma once
#include <string>
#include <memory>

class Player; 

class Human;
class Aggressive;
class Benevolent;


class Strategy {
	public:
		Strategy(Player* player);
		~Strategy();
		Strategy(const Strategy& orig);
		const Strategy& operator=(const Strategy& s);

		/* methods for reinforcement phase */
		virtual std::string extraReinforcement() = 0;
		virtual int countryToReinforce() = 0;
		virtual int armiesToPlace() = 0;
		
		/* methods for attack phase */
		virtual std::string chooseAttack() = 0;

	private:
		Player* player;
};

class User : public Strategy {
	public:
		User(Player* player);
		~User();
		User(const User& orig);
		const User& operator=(const User& u);

		std::string extraReinforcement();
		int countryToReinforce();
		int armiesToPlace();

		std::string chooseAttack();

	private:
		Player* player;

};

class Aggressive : public Strategy {
	public:
		Aggressive(Player* player);
		~Aggressive();
		Aggressive(const Aggressive& orig);
		const Aggressive& operator=(const Aggressive& a);

		std::string extraReinforcement();
		int countryToReinforce();
		int armiesToPlace();

		std::string chooseAttack();

	private:
		Player* player;
};

class Benevolent : public Strategy {
	public:
		Benevolent(Player* player);
		~Benevolent();
		Benevolent(const Benevolent& orig);
		const Benevolent& operator=(const Benevolent& u);

		std::string extraReinforcement();
		int countryToReinforce();
		int armiesToPlace();

		std::string chooseAttack();

	private:
		Player* player;
};


