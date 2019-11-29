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
    Player(const Player& orig); //copy constructor
    Player(std::string name); //constructor which takes a name
    Player(std::string name, Map* map); //constructor which takes a name and a map
    const Player& operator=(const Player &p);
    //returns id of player that is generated during player object creation
    int getID();
    
    //set and get player's name
    void setName(std::string name);
    std::string getName();
    
    
    Dice* getDice();
    Hand* getHand();
    
    
    std::vector<Country* > getThisPlayerCountries();
    void setThisPlayerCountry(Country* country);
    void deleteThisPlayerCountry(Country* country);
    
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
    void deleteThisPlayerContinent(Continent* continent);
    
    std::vector<Continent* > getThisPlayerContinents();
    bool checkControlContinents();
    
    //getters and setters for reinforce method
    int getNumArmy1();
    int getNumArmy2();
    int getNumArmy3();
    void setNumArmy1(int i);
    void setNumArmy2(int i);
    void setNumArmy3(int i);
    
    //getters and setters for attack method
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
    int getNumAttack();
    void setNumAttack(int num);
    //setters and getters for fortify method
    std::string getFortifySourceCountry();
    void setFortifySourceCountry(std::string fortifySourceCountry);
    std::string getFortifyTargetCountry();
    void setFortifyTargetCountry(std::string fortifyTargetCountry);
    int getSourceArmy();
    void setSourceArmy(int SourceArmy);
    int getTargetArmy();
    void setTargetArmy(int targetArmy);
    
    
    //setter and getter for the bool phaseStart
    bool getPhaseStart();
    void setPhaseStart(bool start);
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
    
    std::string executeChooseFortify();
    std::string executeCountryToFortifyFrom();
    int executeArmiesToFortify(int sourceCountryArmies);
    std::string executeCountryToFortify(Country* country);
    
    bool executeExchangeAutom();
private:
    Dice* dice;
    Hand* hand;
    Deck* deck;
    std::string name;
    std::unique_ptr<int> id;
    static int counter;
    std::vector<Country*> countries;
    std:: vector<Continent*> thisPlayerContinents;
    std::unique_ptr<int> numOfArmiesAtStartUpPhase;
    int numOfArmiesForReinforcement;
    
    Player* defender;
    Map* map;
    
    //variables for getters and setter player
    
    //boolean that tells you if a phase has start
    std::unique_ptr<bool> phaseStart;
    
    
    //variable for reinforce
    std::unique_ptr<int> numArmy1;
    std::unique_ptr<int>  numArmy2;
    std::unique_ptr<int>  numArmy3;
    
    //variable for attack
    std::unique_ptr<std::string> attackerCountry;
    std::unique_ptr<std::string> defenderCountry;
    std::unique_ptr<int> startA;
    std::unique_ptr<int> startD;
    std::unique_ptr<int> endA;
    std::unique_ptr<int> endD;
    std::unique_ptr<int> defenderId;
    std::unique_ptr<int> numAttack;
   
    //variable for fortify
    std::unique_ptr<std::string> fortifySourceCountry;
    std::unique_ptr<std::string> fortifyTargetCountry;
    std::unique_ptr<int> sourceArmy;
    std::unique_ptr<int> targetArmy;
    Strategy* strategy;
    
};
