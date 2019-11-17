#pragma once
#include <iostream>
#include "Player.h"
#include <vector>
#include <string>
#include <memory>
using namespace std;

//Default Constructor
Player::Player() {
	this->dice = new Dice();
	this->hand = new Hand(counter);
	counter++;
	id = make_unique<int>(counter); //id of player generated
	numOfArmiesAtStartUpPhase = make_unique<int>(0);
}

//player Constructor with name
Player::Player(string name) {
    this->dice = new Dice();
    this->hand = new Hand(counter);
    this->setName(name);
    counter++;
    id = make_unique<int>(counter); //sets the id to the counter of the player
}

//player constructor with parameters
Player::Player(string name, Map* map) {
    this->dice = new Dice();
    this->hand = new Hand(counter);
    this->setName(name);
    counter++;
	id = make_unique<int>(counter);//sets the id to the counter of the player
    this->map = map;//sets the map to the map passed in the constructor
}

////copy constructor
//Player::Player(const Player& orig) {
//    dice = new Dice(*orig.dice);
//	hand = new Hand(*orig.hand);
//    this-> setName(*orig.name);
//	counter = *orig.counter;
//	id = *orig.id;
//	map = new Map(*orig.map);
//} 
//
////Equal operator method
//Player& Player::operator=(const Player& orig) {
//	dice = orig.dice;
//	hand = orig.hand;
//	name = orig.name;
//	return *this;
//}

//Destructor
Player::~Player() {
    delete hand;
    delete dice;
}

//id counter starts at 0
int Player::counter = 0;

//Gets name of player
string Player::getName() {
    return name;
}

//gets id of player
int Player::getID() {
    return *id;
}

//Getters
Hand* Player::getHand() {
    return hand;
}

Dice* Player::getDice() {
    return dice;
}

int Player::getNumOfArmiesAtStartUpPhase() {
    return *numOfArmiesAtStartUpPhase;
}

void Player::setNumOfArmiesAtStartUpPhase(int num) {
    numOfArmiesAtStartUpPhase.reset(new int(num));
}

vector<Country*> Player::getThisPlayerCountries() {
    return countries;
}

vector<Continent*> Player:: getThisPlayerContinents() {
    return thisPlayerContinents;
}

Map* Player::getMap() {
	return map;
}
//getters for reinforce 
int Player::getNumArmy1(){ //getter for reinforce method : army to add according to contries control
	return numArmy1;
}

int Player::getNumArmy2() {//getter for reinforce method : army to add according to continent control
	return numArmy2;
}


int Player::getNumArmy3() { //getter for reinforce method : army to add according to cards control
	return numArmy3;
}

// Getters for Attack 
std::string Player::getAttackerCountry() {
	return attackerCountry;
}
std::string Player::getDefenderCountry() {
	return defenderCountry;
}
//for the number of armies A= attacker , D=Deffender
int Player::getStartA(){
	return startA;
}
int  Player::getStartD(){
	return startD;
}

int  Player::getEndA(){
	return endA;
}

int  Player::getEndD(){
	return endD;
}

int Player::getDefenderId() {
	return defenderId;
}

//getter for fortify 
std::string Player::getFortifySourceCountry() {
	return fortifySourceCountry;
}
std::string Player::getFortifyTargetCountry() {
	return fortifyTargetCountry;
}

int Player::getSourceArmy() {
	return  sourceArmy;
}
int Player::getTargetArmy() {
	return targetArmy;
}
//Setters
void Player::setName(string name) {
	this->name = name;
}

void Player:: setThisPlayerContinents(Continent *continent) {
    thisPlayerContinents.push_back(continent);
}

void Player::setThisPlayerCountry(Country* country) {
	countries.push_back(country);
}

void Player::setMap(Map* map) {
	this->map = map;
}

void Player::setNumArmy1(int i) { //setter for reinforce method : army to add according to contries control
	numArmy1 = i;
}

void Player::setNumArmy2(int i) { //setter for reinforce method : army to add according to continent control
	numArmy2 = i;
}
void Player::setNumArmy3(int i) {  //setter for reinforce method : army to add according to cards control
	numArmy3 = i;
}

//Setters for fortify method 
void Player::setFortifySourceCountry(std::string fortifySourceCountry) { //to set the source country name of fortify
	this->fortifySourceCountry = fortifySourceCountry;
}
void Player::setFortifyTargetCountry(std::string fortifyTargetCountry) {//to set the target country name of fortify
	this->fortifyTargetCountry = fortifyTargetCountry;
}

void Player::setSourceArmy(int sourceArmy) { // to set source army number of fortify 
	this->sourceArmy = sourceArmy;
}
void Player::setTargetArmy(int targetArmy) {// to set target army number of fortify 
	this->targetArmy = targetArmy;
}

//Setters for attack method
void Player::setAttackerCountry(std::string attackerCountry) {
	this->attackerCountry = attackerCountry;

}
void Player::setDefenderCountry(std::string defenderCountry) {
	this->defenderCountry = defenderCountry;
}
//for the number of armies A= attacker , D=Deffender
void  Player::setStartA(int startA) {
	this->startA = startA;
}
void  Player::setStartD(int startD) {
	this->startD = startD;
}
void  Player::setEndA(int endA) {
	this->endA = endA;
}
void  Player::setEndD(int endD) {
	this->endD = endD;
}
void Player::setDefenderId(int defenderId) {
	this->defenderId = defenderId;
}
//Other methods 
bool Player:: checkControlContinents() { //method to verify if player owns a continent for reinforce phase
    bool ownContinents = false;
    
    //check each continents
    for(unsigned int i = 0; i <this->map->getContinents().size(); i++) {
        
        //if the continent is own by a player
        if(this->map->getContinents().at(i)->continentOwnByAPlayer()) {
            
            //get the id of the player who owns the continent
            int idOfOwner = this->map->getContinents().at(i)->getOwnerId();
            
            //if the id of the player is the same as the id of the owner of the continent,
            //set the continent as own by the player
            if(this->getID() == idOfOwner) {
                setThisPlayerContinents(map->getContinents().at(i));
                cout << "The player owns the continent " << map->getContinents().at(i)->getContinentName() << endl;
                ownContinents = true;
            }
        }
        
    }
    return ownContinents;
}

//reinforce phase
void Player::reinforce() {
	setNumArmy1(0);
	setNumArmy2(0);
	setNumArmy3(0);
    
    cout << "\n~~~~~ Reinforcement Phase ~~~~~\n" << endl;
    int armyAdd = 0; //for the total number of armies to add
    int ownedCountries = 0;
    int ownedContinent = 0; //for the number of armies to add due to continent control
    int armyHand = 0;// for the number of armies to add due to exchanged cards
    string answer; // for user input
    
    // number of armies according to number of countries
    // add a minimum of 3 armies if less than 9 countries
    if ((getThisPlayerCountries().size()/3) < 3) {
        ownedCountries = 3;
        armyAdd += ownedCountries;
    }
    
    // divide number of countries by 3 for number of armies to add
    else {
        ownedCountries += (getThisPlayerCountries().size())/ 3;
        armyAdd += ownedCountries;
    }
    cout << "The number of armies added by the number of controled countries is " << armyAdd << "." << endl;
    
    
    //check if the player owns continents
    if(checkControlContinents()) {
        
        //for each continent owns, we increment the number of armies to add
        for(unsigned int i=0; i < getThisPlayerContinents().size(); i++) {
            ownedContinent = ownedContinent + getThisPlayerContinents().at(i)->getNumberOfArmies();
        }
    }
    
    
    cout << "The number of armies added by the number of controlled continents is " << ownedContinent << "." << endl;
    armyAdd += ownedContinent;
    
    // cards may be exchanged or forced exchange (if more than 5) for armies for reinforcement
    if (hand->getCardsInHand().size() > 5) {
        
        cout << "\nSince there is more than 5 cards in your hand, you must exchange them." << endl;
        this->getHand()->exchange();
        armyHand = this->getHand()->getNumberOfArmiesToPlace();
        armyAdd += armyHand;
        
        //if the size of the hand is greater than 5 cards, keep asking the player to exchange cards
        while(hand->getCardsInHand().size() > 5) {
            cout << "\n\n ****** You didn't exchange enough cards, you still have more than 5 cards in your hand. You need to exchange your cards. ******" << endl;
            this->getHand()->exchange();
            armyHand = this->getHand()->getNumberOfArmiesToPlace();
            armyAdd += armyHand;
        }
    }
    else {
        cout << "Do you want to exchange your cards for extra reinforcement ? (y/n)" << endl;
        cin >> answer;
        
        if (answer == "y") {
            this->getHand()->exchange();
            armyHand+= hand->getNumberOfArmiesToPlace();
            armyAdd += armyHand;
        }
        else {
            cout << "No cards are exchanged." << endl;
        }

		

    }
	setNumArmy1(ownedCountries);
	setNumArmy2(ownedContinent);
	setNumArmy3(armyHand);
    
    //Conclusion
    cout << "\nNumber of armies added by exchanging cards is " << armyHand << "." << endl;
    cout << "Number of armies for controlled countries: " << ownedCountries << endl;
    cout << "Number of armies for controlled continents: " << ownedContinent  << endl;
    cout << "In total, " << armyAdd << " armies can be added for reinforcement." << endl;
    
    while(armyAdd !=0 ) {
        
        cout << "\nThese are your countries and their number of armies" << endl;
        
        for(unsigned int i = 0 ; i< getThisPlayerCountries().size(); i++) {
            cout << i+1 << ": " << getThisPlayerCountries().at(i)->getCountryName() << " " << getThisPlayerCountries().at(i)->getNumberOfArmies() << endl;
        }
        int country;
        cout << "\nPlease enter the number of the country you would like to reinforce" << endl;
        cin >> country;
        int numArmies;
        cout << "\nEnter the number of armies you would like to place on this country" << endl;
        cin >> numArmies;
        
        while(numArmies <= 0 || numArmies > armyAdd) {
            cout << "Please enter a valid number of armies to place on this country" << endl;
            cin >> numArmies;
        }
        
        //increment the number of armies on the chosen country
        int newNumArmies = getThisPlayerCountries().at(country-1)->getNumberOfArmies() + numArmies;
        getThisPlayerCountries().at(country-1)->setNumberOfArmies(newNumArmies);
        
        //decrement the number of army to add
        armyAdd = armyAdd - numArmies;
        
        cout << "The country " << getThisPlayerCountries().at(country-1)->getCountryName() << " has now " << getThisPlayerCountries().at(country-1)->getNumberOfArmies() << " armies" << endl;
        cout << "You still have " << armyAdd << " armies to place" << endl;
        
    }
    
    cout << "\n\n~~~~~ End of the reinforce phase for player " << this->getName() << " ~~~~~" << endl;
	
}

// attack method
void Player::attack(){
    string playerAttack;
    int selectAttackFrom, selectCountryToAttack, attackerMaxNumOfDice, defenderMaxNumOfDice, attackerRoll, defenderRoll, numOfPairs, numOfArmiesToMove;
    Country* attackFrom;
    Country* countryToAttack;
    vector<int> attackerDiceValues, defenderDiceValues;
    
    cout << "\n~~~~~ Attack Phase ~~~~~\n" << endl;
    
    cout << "Player " << this->getID() << ", do you want to attack? (Press Y to attack or anything else to end attack phase)\n" << endl;
    cin >> playerAttack;
    
    while (playerAttack == "Y") {
        cout << "These are the countries you own and the number of armies placed on them:" << endl;
        for (unsigned int i = 0; i < getThisPlayerCountries().size(); i++) {
            cout << "Country " << i + 1 << ": " << getThisPlayerCountries().at(i)->getCountryName() << " \tNumber of Armies: " << getThisPlayerCountries().at(i)->getNumberOfArmies() << endl;
        }
        
        cout << "Which country would you like to attack from? The country you select must have at least 2 armies placed on it. Please enter the country's number.\n" << endl;
        cin >> selectAttackFrom;
        
        // check if player enters a valid country number (not negative or bigger than number of owned countries)
        // check if country selected has at least 2 armies placed on it
        while (selectAttackFrom <= 0 || selectAttackFrom > getThisPlayerCountries().size() || getThisPlayerCountries().at(selectAttackFrom - 1)->getNumberOfArmies() < 2) {
            if (selectAttackFrom <= 0 || selectAttackFrom > getThisPlayerCountries().size()) {
                cout << "Please enter a valid country number." << endl;
                cin >> selectAttackFrom;
            }
            else if (getThisPlayerCountries().at(selectAttackFrom - 1)->getNumberOfArmies() < 2) {
                cout << "Please select a country with at least 2 armies placed on it." << endl;
                cin >> selectAttackFrom;
            }
        }
        
        // player attacks from the valid country they selected
        attackFrom = getThisPlayerCountries().at(selectAttackFrom - 1);
        
        cout << "You will be attacking from " << attackFrom->getCountryName() << " with " << attackFrom->getNumberOfArmies() << " armies.\n" << endl;
		
		setAttackerCountry(attackFrom->getCountryName()); //setting for obs method
		setStartA(attackFrom->getNumberOfArmies());

        cout << "These are the country's neighbors you can attack and the owners of them:" << endl;
        for (unsigned int i = 0; i < attackFrom->getAdjacentCountries().size(); i++) {
            cout << "Country " << i + 1 << ": " << attackFrom->getAdjacentCountries().at(i)->getCountryName() << "\tBelongs to: Player " << attackFrom->getAdjacentCountries().at(i)->getCountryOwnerId() << endl;
        }

        cout << "Which one of this country's neighbors would you like to attack?. The country you select must belong to another player. Please enter the country's number.\n" << endl;
        cin >> selectCountryToAttack;
        
        // check if player enters a valid country number (not negative or bigger than number of neighbor countries)
        // check if player selects a country that belongs to another player
        while (selectCountryToAttack <= 0 || selectCountryToAttack > attackFrom->getAdjacentCountries().size() || attackFrom->getAdjacentCountries().at(selectCountryToAttack - 1)->getCountryOwnerId() == this->getID()) {
            if (selectCountryToAttack <= 0 || selectCountryToAttack > attackFrom->getAdjacentCountries().size()) {
                cout << "Please enter a valid country number." << endl;
                cin >> selectCountryToAttack;
            }
            else if (attackFrom->getAdjacentCountries().at(selectCountryToAttack - 1)->getCountryOwnerId() == this->getID()) {
                cout << "Please select a country that is owned by another player." << endl;
                cin >> selectCountryToAttack;
            }
        }
        
        // player attacks the valid country they selected
        countryToAttack = attackFrom->getAdjacentCountries().at(selectCountryToAttack - 1);
        
        cout << "You will be attacking " << countryToAttack->getCountryName() << " which belongs to Player " << countryToAttack->getCountryOwnerId() << ".\n" << endl;
        
		setDefenderCountry(countryToAttack->getCountryName()); // setting for the obs method
		setStartD(countryToAttack->getNumberOfArmies());

        // attacker chooses number of dice to roll
        attackerMaxNumOfDice = attackFrom->getNumberOfArmies() - 1;
        if (attackerMaxNumOfDice > 3) {
            attackerMaxNumOfDice = 3;
        }
        
        cout << "Attacker (Player " << this->getID() << "), please select the number of dice to roll. You may only roll 1 to " << attackerMaxNumOfDice << " dice." << endl;
        cin >> attackerRoll;
        
        // check if player selects a valid number of dice
        while (attackerRoll < 1 || attackerRoll > attackerMaxNumOfDice) {
            cout << "Attacker (Player " << this->getID() << "), please select a valid number of dice to roll. You may only roll 1 to " << attackerMaxNumOfDice << " dice." << endl;
            cin >> attackerRoll;
        }
        
        cout << "Attacker (Player " << this->getID() << "), you will roll " << attackerRoll << " dice.\n" << endl;
        
        // defender chooses number of dice to roll
        defenderMaxNumOfDice = countryToAttack->getNumberOfArmies();
        if (defenderMaxNumOfDice > 2) {
            defenderMaxNumOfDice = 2;
        }
        
        cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), please select the number of dice to roll. You may only roll 1 to " << defenderMaxNumOfDice << " dice." << endl;
        cin >> defenderRoll;

        
		setDefenderId(countryToAttack->getCountryOwnerId()); //for observer
        
        // check if player selects a valid number of dice
        while (defenderRoll < 1 || defenderRoll > defenderMaxNumOfDice) {
            cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), please select a valid number of dice to roll. You may only roll 1 to " << defenderMaxNumOfDice << " dice." << endl;
            cin >> defenderRoll;
        }
        
        cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), you will roll " << defenderRoll << " dice.\n" << endl;
        
        // roll attacker's dice
        cout << "~ Attacker is rolling ~" << endl;
        dice->setDiceToRoll(attackerRoll);
        dice->rollDice();
        cout << "\n" << endl;
        for (int i = 0; i < attackerRoll; i++) {
            attackerDiceValues.push_back(dice->getValuesRolled().at(i));
        }
		dice->clearDiceRolled();
        
        // roll defender's dice
        cout << "~ Defender is rolling ~" << endl;
        dice->setDiceToRoll(defenderRoll);
        dice->rollDice();
        cout << "\n" << endl;
        for (int i = 0; i < defenderRoll; i++) {
            defenderDiceValues.push_back(dice->getValuesRolled().at(i));
        }
		dice->clearDiceRolled();
        
        // determine how many comparisons we do depending on number of dice both players rolled
        if (attackerRoll < defenderRoll) {
            numOfPairs = 1;
        }
        else {
            numOfPairs = defenderRoll;
        }
        
        // compare pairs of dice
        for (int i = 0; i < numOfPairs; i++) {
            cout << "~ Pair of dice comparison #" << (i + 1) << " ~\n" << endl;
            cout << "Attacker rolled a " << attackerDiceValues.at(i) << " and Defender rolled a " << defenderDiceValues.at(i) << ".\n" << endl;
            if (attackerDiceValues.at(i) == defenderDiceValues.at(i)) {
                cout << "Attacker's next highest dice and Defender's next highest dice are the same. Attacker lost this battle.\n" << endl;
                cout << "Attacker (Player " << this->getID() << "), you have lost 1 army in " << attackFrom->getCountryName() << ".\n" << endl;
                attackFrom->setNumberOfArmies(attackFrom->getNumberOfArmies() - 1); // attacker loses one army from their country
                
                setEndA(attackFrom->getNumberOfArmies());  //set For Observer
                setEndD(countryToAttack->getNumberOfArmies());
            }
            else if (defenderDiceValues.at(i) > attackerDiceValues.at(i)) {
                cout << "Attacker's next highest dice is lower than Defender's next highest dice. Attacker lost this battle.\n" << endl;
                
                cout << "Attacker (Player " << this->getID() << "), you have lost 1 army in " << attackFrom->getCountryName() << ".\n" << endl;
                attackFrom->setNumberOfArmies(attackFrom->getNumberOfArmies() - 1); // attacker loses one army from their country
                
                setEndA(attackFrom->getNumberOfArmies());  //set For Observer
                setEndD(countryToAttack->getNumberOfArmies());
            }
            else if (attackerDiceValues.at(i) > defenderDiceValues.at(i)) {
                cout << "Defender's next highest dice is lower than Defender's next highest dice. Defender lost this battle.\n" << endl;
                cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), you have lost 1 army in " << countryToAttack->getCountryName() << ".\n" << endl;
                countryToAttack->setNumberOfArmies(countryToAttack->getNumberOfArmies() - 1); // defender looses one army from their country
                
                setEndA(attackFrom->getNumberOfArmies());  //set For Observer
                setEndD(countryToAttack->getNumberOfArmies());
               
                // check if defender has been defeated (no more armies left)
                if (countryToAttack->getNumberOfArmies() == 0) {
                    cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), you have lost all armies in " << countryToAttack->getCountryName() << "." << endl;
                    cout << "Attacker (Player " << this->getID() << ") now owns " << countryToAttack->getCountryName() << "." << endl;
                    
                    // assign attacked country to attacker
                    countryToAttack->setCountryOwnerId(this->getID());
                    this->setThisPlayerCountry(countryToAttack);
                    
                    // attacker moves number of armies to attacked country
                    cout << "Attacker (Player " << this->getID() << "), please select the number armies you want to move to " << countryToAttack->getCountryName() << " from " << attackFrom->getCountryName() << "." << endl;
                    cout << "You may move between 1 to " << attackFrom->getNumberOfArmies() - 1 << " armies." << endl;
                    cin >> numOfArmiesToMove;
                    
                    // check if player selects a valid number of armies
                    while (numOfArmiesToMove < 1 || numOfArmiesToMove > attackFrom->getNumberOfArmies() - 1) {
                        cout << "Attacker (Player " << this->getID() << "), please select a valid number of armies to move from " << attackFrom->getCountryName() << ". You may move between 1 to " << attackFrom->getNumberOfArmies() - 1 << " armies." << endl;
                        cin >> numOfArmiesToMove;
                    }
                    // numOfArmiesToMove
                    countryToAttack->setNumberOfArmies(numOfArmiesToMove);
                    
                    cout << "Attacker (Player " << this->getID() << "), you have decided to move " << numOfArmiesToMove << " armies to " << countryToAttack->getCountryName() << "." << endl;
                    cout << countryToAttack->getCountryName() << " now has " << numOfArmiesToMove << " armies." << endl;
                    
                   
                }
               
				 
            }
            
            
        }
        
        // clear dice vectors at the end of each attack
        attackerDiceValues.clear();
        defenderDiceValues.clear();
        
        cout << "Player " << this->getID() << ", do you want to attack again? (Press Y to attack again or anything else to end attack phase)\n" << endl;
        cin >> playerAttack;
    };
    
    cout << "Player " << this->getID() << "'s attack phase is over." << endl;
	
}

//fortify method
void Player::fortify() {
    
    string nameSourceCountry;
    string nameTargetCountry;
    bool isSourceCountryValid = false;
    bool isTargetCountryValid = false;
    bool isTargetCountryNeighbour = false;
    bool isNumOfArmiesValid = true;
	
    //tells if the source countries has a neighbour that the user own
    bool neighbourCountries = false;
    
    //tells if the source countries has adjencent countries that the player own
    bool sourceCountriesNeighbours = false;
    int numOfArmies = 0;
    int indexOfSourceCountry = 0;
    int indexOfTargetCountry = 0;
    
    cout << "\n~~~~~ Fortification Phase ~~~~~" << endl;
    
    cout << "\nPlayer " << getName() << ", do you want to fortify? (Press Y to fortify or anything else to end fortify phase)" << endl;
    string attack;
    cin >> attack;
    
    if(attack.compare("Y") == 0) {
    
    cout << "\nThis is your countries, their number of armies and their adjacent countries" << endl;
    
    for(unsigned int i = 0 ; i < getThisPlayerCountries().size(); i++) {
        cout << getThisPlayerCountries().at(i)->getCountryName() << " " << getThisPlayerCountries().at(i)->getNumberOfArmies();
        
        cout << " (";
        for(unsigned int j =0; j < getThisPlayerCountries().at(i)->getAdjacentCountries().size(); j++) {
            cout << getThisPlayerCountries().at(i)->getAdjacentCountries().at(j)->getCountryName() << " ";
        }
        cout << ") " << endl;
    }
    
    
    //check if there are countries adjacent to each other, if not, the player can't fortify
    string nameCountry;
    for(unsigned int i =0; i< this->getThisPlayerCountries().size(); i++) {
        
        for(unsigned int j = 0; j < this->getThisPlayerCountries().size(); j++) {
            
            nameCountry = getThisPlayerCountries().at(i)->getCountryName();
            
            for(unsigned int k = 0; k < this->getThisPlayerCountries().at(j)->getAdjacentCountries().size(); k++ ) {
                
                if(nameCountry.compare( this->getThisPlayerCountries().at(j)->getAdjacentCountries().at(k)->getCountryName() ) == 0) {
                    neighbourCountries = true;
                }
            }
        }
        
    }
    //if the player owns no neighbour countries, end the fortify phase
    if(neighbourCountries == false) {
        cout << "There are no neightbour countries. You cannot fortify" << endl;
    }
    
    //else fortify
    else {
        
        //Prompts the user for the source country
        cout << "\nPlease write the name of the chosen source country \n(capitalize the first letter)" << endl;
        
        cin >> nameSourceCountry;
        
        
        //check if the player owns the source country
        for(unsigned int i = 0; i < this->getThisPlayerCountries().size(); i++) {
            if( nameSourceCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
                isSourceCountryValid = true;
                indexOfSourceCountry = i;
            }
        }
        
        //check if the country chosen has neighbours in the countries of the player
        for(unsigned int i = 0; i < this->getThisPlayerCountries().size(); i++) {
            
            for(unsigned int j = 0; j < this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); j++) {
                
                //compare the adjacent countries of the source countries with the list of countries own by the player
                if((getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().at(j)->getCountryName()).compare(getThisPlayerCountries().at(i)->getCountryName()) == 0 ) {
                    sourceCountriesNeighbours = true;
                }
            }
        }
        
        
        //asks the player again to enter a valid source country if it was not valid
        while(isSourceCountryValid == false || sourceCountriesNeighbours == false) {
            cout << "\nThe source country you choose is not own by you or doesn't exists or doesn't have adjacent countries your own \nPlease choose a new source country" << endl;
            cout << "Please write the name of the chosen source country \n(capitalize the first letter)" << endl;
            
            cin >> nameSourceCountry;
            
            
            //check if the player owns the source country
            for(unsigned int i = 0; i < this->getThisPlayerCountries().size(); i++) {
                if( nameSourceCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
                    isSourceCountryValid = true;
                    indexOfSourceCountry = i;
                }
            }
            
            //check if the country chosen has neighbours in the countries of the player
            for(unsigned int i = 0; i < this->getThisPlayerCountries().size(); i++) {
                
                
                for(unsigned int j = 0; j < this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); j++) {
                    
                    
                    //compare the adjacent countries of the source countries with the list of countries own by the player
                    if((getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().at(j)->getCountryName()).compare(getThisPlayerCountries().at(i)->getCountryName()) == 0 ) {
                        sourceCountriesNeighbours = true;
                    }
                    
                }
                
            }
            
        }
        
        
        cout << "Please enter the number of armies you would like to move" << endl;
        cin >> numOfArmies;
        
        //check if the number of armies entered is valid
        if(numOfArmies < 1 || numOfArmies > this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() -1 ) {
            isNumOfArmiesValid = false;
        }
        
        
        //prompts the player again to enter a valid number of armies if the number entered is not valid
        while(isNumOfArmiesValid == false) {
            cout << numOfArmies << endl;
            cout << "\nThe number of armies you enter is not valid.\nPlease enter a value in the range of [1 to (number of armies in the source country -1)]" << endl;
            cout << "Enter the number of armies you would like to move" << endl;
            
            cin >> numOfArmies;
            
            //if number of armies enter is not in the range, set isNumberArmiesValid to false
            if(numOfArmies < 1 || numOfArmies > this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() -1 ) {
                isNumOfArmiesValid = false;
            }
            
            else {
                isNumOfArmiesValid = true;
            }
        }
        
        //Prompts the user for a target country
        cout << "Please write the name of the chosen target country \n(capitalize the first letter)" << endl;
        cin >> nameTargetCountry;
        
        //check if the player owns the target country
        for(unsigned int i = 0; i < this->getThisPlayerCountries().size(); i++) {
            if(nameTargetCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
                isTargetCountryValid = true;
                indexOfTargetCountry = i;
            }
        }
        
        
        //check if the target country is a neighboring country of the source country
        for(unsigned int i =0; i< this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); i++) {
            if(nameTargetCountry.compare(this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().at(i)->getCountryName()) == 0) {
                isTargetCountryNeighbour =true;
                // cout << "The country is a neighbour" << endl;
            }
            
        }
        
        //if the target country is not valid, ask again
        while(isTargetCountryValid == false || isTargetCountryNeighbour == false) {
            cout << "\nThe target country you choose is not own by you or doesn't exists or is not a neighbour of the source country \nPlease choose a valid country" << endl;
            cout << "Enter the name of a valid chosen target country" << endl;
            cin >> nameTargetCountry;
            
            //check if the player owns the target country
            for(unsigned int i = 0; i < this->getThisPlayerCountries().size(); i++) {
                if(nameTargetCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
                    isTargetCountryValid = true;
                    indexOfTargetCountry = i;
                }
            }
            
            
            //check if the country is a neighboring country of the source country
            for(unsigned int i =0; i< this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); i++) {
                if(nameTargetCountry.compare(this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().at(i)->getCountryName()) == 0) {
                    isTargetCountryNeighbour =true;
                }
                
            }
            
        }
        
        //set the new number of armies for the source country
        int numberOfArmiesSourceCountry = this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
        this->getThisPlayerCountries().at(indexOfSourceCountry)->setNumberOfArmies(numberOfArmiesSourceCountry - numOfArmies);
        
	
        //set the new number of armies for the target country
        int numberOfArmiesTargetCountry = this->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
        this->getThisPlayerCountries().at(indexOfTargetCountry)->setNumberOfArmies(numberOfArmiesTargetCountry + numOfArmies);
        
		setFortifySourceCountry(nameSourceCountry);
		setFortifyTargetCountry(nameTargetCountry);
		int sourceArmy = this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
		int targetArmy = this->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
		setSourceArmy(sourceArmy);
		setTargetArmy(targetArmy);
        //Display the new number of armies for source country and target country
        cout << "The player fortified succesfully the country: " << nameTargetCountry  << endl;
        cout << nameSourceCountry << " has now " << this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() << " armies"  << endl;
        cout << nameTargetCountry << " has now " << this->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies() << " armies"  << endl;
        
    }
    }

}
