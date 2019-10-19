#pragma once
#include "Dice.h"
#include "Map.h"
#include "Cards.h"
#include <string>

#include <memory> //for pointer class

class Player {
	public:
		Player(); // default constructor
		~Player();
		Player(std::string name); //constructor which takes a name


		//returns id of player that is generated during player object creation
		int getID();

		//player's countries
		void setPlayerCountries(Country* country);
		std::vector<Country*> getPlayerCountries();


		//set and get player's name
		void setName(std::string name);
		std::string getName();

		void display();

		//attack, fortify, reinforce methods
		void attack();
		void fortify();
		void reinforce();

	private:
		Dice* dice;
		Hand* hand;
		std::string name;

		std::vector<Country*> playerCountries;

		std::unique_ptr<int> id;
		static int counter;
};
