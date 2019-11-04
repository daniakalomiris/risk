#pragma once
#include "Dice.h"
#include "Cards.h"
#include "Map.h"
#include <string>
#include <vector>
#include <memory> //for pointer class

class Player {
	public:
		Player(); // default constructor
		~Player();
		Player(std::string name); //constructor which takes a name


		//returns id of player that is generated during player object creation
		int getID();

		//set and get player's name
		void setName(std::string name);
		std::string getName();
		
		Dice* getDice();
		Hand* getHand();
		
        std::vector<Country* > getThisPlayerCountries();
        void setThisPlayerCountry(Country* country);

		//attack, fortify, reinforce methods
		void attack();
		void fortify();
		void reinforce();

	private:
		Dice* dice;
		Hand* hand;
		std::string name;

		std::unique_ptr<int> id;
		static int counter;
        std::vector<Country*> countries;
		Player* defender;
};
