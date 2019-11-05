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
        //***************PART ADDED BY LOUJAIN ***************
        //Deck and map should not be there
		Deck* getDeck();
		Map getMap();
		//***************PART ADDED BY LOUJAIN END ***************

        
        int getNumOfArmiesAdd();

        std::vector<Country* > getThisPlayerCountries();
        void setThisPlayerCountry(Country* country);


        int getNumOfArmiesAtStartUpPhase();
        void setNumOfArmiesAtStartUpPhase(int num);


		//attack, fortify, reinforce methods
		void attack();
		void fortify();
		void reinforce();

	private:
		Dice* dice;
		Hand* hand;
		Deck* deck;
		Map map;
		std::string name;
		std::string answer;
		std::unique_ptr<int> id;
		static int counter;
        std::vector<Country*> countries;
        int armyAdd;
        std::unique_ptr<int> numOfArmiesAtStartUpPhase;

		Player* defender;
};
