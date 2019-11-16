#pragma once
#include "Dice.h"
#include "Cards.h"
#include "Map.h"
#include <string>
#include <vector>
#include <memory> //for pointer class

class Strategy;

class Player {
	public:
		Player(); // default constructor
		~Player();
        Player(const Player&); //copy constructor
		Player(std::string name); //constructor which takes a name
        Player(std::string name, Map* map); //constructor which takes a name and a map

		//returns id of player that is generated during player object creation
		int getID();

		//set and get player's name
		void setName(std::string name);
		std::string getName();

		Dice* getDice();
		Hand* getHand();

   
        std::vector<Country* > getThisPlayerCountries();
        void setThisPlayerCountry(Country* country);


        int getNumOfArmiesAtStartUpPhase();
        void setNumOfArmiesAtStartUpPhase(int num);

		int getNumOfArmiesForReinforcement();
		void setNumOfArmiesForReinforcement(int num);

		//attack, fortify, reinforce methods
		void attack();
		void fortify();
        void reinforce();

        Map* getMap();
        void setMap(Map* map);
    
        void setThisPlayerContinents(Continent* continent);
        std::vector<Continent* > getThisPlayerContinents();
        bool checkControlContinents();

		void setStrategy(Strategy* strategy);
		Strategy* getStrategy();

		/* methods that execute a different strategy depending on what strategy was chosen */
		std::string executeExtraReinforcement();
		int executeCountryToReinforce();
		int executeArmiesToPlace();

		std::string executeChooseAttack();
		int executeAttackFrom();
		int executeCountryToAttack(Country* country);
		int executeAttackerRoll();
		int executeArmiesToMove(int armiesCanMove);

	private:
		Dice* dice;
		Hand* hand;
		Deck* deck;
		std::string name;
		std::string answer;
		std::unique_ptr<int> id;
		static int counter;
        std::vector<Country*> countries;
        std:: vector<Continent*> thisPlayerContinents;
        std::unique_ptr<int> numOfArmiesAtStartUpPhase;
		int numOfArmiesForReinforcement;
       
		Player* defender;
        Map* map; 

		// declare Strategy class
		Strategy* strategy;
};
