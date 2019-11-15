#pragma once
#include "Dice.h"
#include "Cards.h"
#include "Map.h"
#include "GameObservers.h"
#include <string>
#include <vector>
#include <memory> //for pointer class

class Player : public Subject {
	public:
		Player(); // default constructor
		~Player();
        Player(const Player&); //copy constructor
		Player(std::string name); //constructor which takes a name
        Player(std::string name, Map* map); //constructor which takes a name and a map
		Player& operator=(const Player& orig); //equaloperator 
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

		//attack, fortify, reinforce methods
		void attack();
		void fortify();
        void reinforce();

        Map* getMap();
        void setMap(Map* map);
    
        void setThisPlayerContinents(Continent* continent);
        std::vector<Continent* > getThisPlayerContinents();
        bool checkControlContinents();
    
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
        

		Player* defender;
        Map* map;

};
