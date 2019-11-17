#pragma once
#include "Dice.h"
#include "Cards.h"
#include "Map.h"
#include <string>
#include <vector>
#include <memory> //for pointer class

class Player{
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
		//attack returns DefenderID
		void attack();
		void fortify();
        void reinforce();

        Map* getMap();
        void setMap(Map* map);
    
        void setThisPlayerContinents(Continent* continent);
        std::vector<Continent* > getThisPlayerContinents();
        bool checkControlContinents();

		//getters and setters for reinforce method
		int getNumArmy1();
		int getNumArmy2();
		int getNumArmy3();
		void setNumArmy1(int i);
		void setNumArmy2(int i);
		void setNumArmy3(int i);
		//getters and setters for attack methid 
		std::string getAttackerCountry();
		std::string getDefenderCountry();
		void setAttackerCountry(std::string attackerCountry);
		void setDefenderCountry(std::string defenderCountry);
		int getStartA();
		void setStartA(int startA);
		int getStartD();
		void setStartD(int startD);
		int getEndA();
		void setEndA(int endA);
		int getEndD();
		void setEndD(int endD);
		int getDefenderId();
		void setDefenderId(int defenderId);
		//set and getters for fortify method
		std::string getFortifySourceCountry();
		void setFortifySourceCountry(std::string fortifySourceCountry);
		std::string getFortifyTargetCountry();
		void setFortifyTargetCountry(std::string fortifyTargetCountry);
		int getSourceArmy();
		void setSourceArmy(int SourceArmy);
		int getTargetArmy();
		void setTargetArmy(int targetArmy);
    
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

		//variables for getters and setter player
		int numArmy1;
		int numArmy2;
		int numArmy3;
    
		//variable for attack
		std::string attackerCountry;
		std::string defenderCountry;
		int startA;
		int startD;
		int endA;
		int endD;
		int defenderId;
    
		//variable for fortify
		std::string fortifySourceCountry;
		std::string fortifyTargetCountry;
		int sourceArmy;
		int targetArmy;
		
};
