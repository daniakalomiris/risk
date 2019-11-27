#include <iostream>
#include "PlayerStrategies.h"
#include "time.h"

using namespace std;

// constructor and destructor for Strategy class
Strategy::Strategy() {
}

Strategy::~Strategy() {
}


// constructor and destructor for ConcreteStrategy for human player
User::User() {
}

User::~User() {
}


// all user inputs are chosen by the player
string User::extraReinforcement() {
    string input;
    cin >> input;
    return input;
}

int User::countryToReinforce(Player* player) {
    int input;
    cin >> input;
    return input;
}

int User::armiesToPlace(Player* player) {
    int input;
    cin >> input;
    return input;
}

string User::chooseAttack() {
    string input;
    cin >> input;
    return input;
}

int User::attackFrom(Player* player) {
    int input;
    cin >> input;
    return input;
}

int User::countryToAttack(Country* attackFrom) {
    int input;
    cin >> input;
    return input;
}

int User::attackerRoll() {
    int input;
    cin >> input;
    return input;
}

int User::armiesToMove(int armiesCanMove) {
    int input;
    cin >> input;
    return input;
}

string User::chooseFortify() {
    string input;
    cin >> input;
    return input;
}

string User::countryToFortifyFrom(Player* player) {
    string input;
    cin.ignore();
    getline(cin, input);
    return input;
}

int User::armiesToFortify(int sourceCountryArmies) {
    int input;
    cin >> input;
    return input;
}

string User::countryToFortify(Player* player, Country* country) {
    string input;
    cin.ignore();
    getline(cin, input);
    return input;
}

// human players choose when to exchange
bool User::exchangeAutom() {
    return false;
}

// constructor and destructor for ConcreteStrategy for aggressive computer player
Aggressive::Aggressive() {
}

Aggressive::~Aggressive() {
}


// aggressive player will always exchange again
string Aggressive::extraReinforcement() {
    return "y";
}

// aggressive playyer will select country with most armies on it
int Aggressive::countryToReinforce(Player* player) {
    
    // set max country to be first index in the list of player's countries
    int max = 0;
    
    for (unsigned int i = 1; i < player->getThisPlayerCountries().size(); i++) {
        if (player->getThisPlayerCountries().at(i)->getNumberOfArmies() > player->getThisPlayerCountries().at(max)->getNumberOfArmies()) {
            max = i; // assigning the index of the vector
        }
    }
    
    return max + 1; // returning the country number with the most armies
}

// aggressive player will put all of armies that can be added to their chosen country
int Aggressive::armiesToPlace(Player* player) {
    return player->getNumOfArmiesForReinforcement();
}

// aggressive player always attacks
string Aggressive::chooseAttack() {
    return "Y";
}

// aggressive player attacks from country with most armies on it
int Aggressive::attackFrom(Player* player) {
    // set max country to be first index in the list of player's countries
    int max = 0;
    
    for (unsigned int i = 1; i < player->getThisPlayerCountries().size(); i++) {
        if (player->getThisPlayerCountries().at(i)->getNumberOfArmies() > player->getThisPlayerCountries().at(max)->getNumberOfArmies()) {
            max = i; // assigning the index of the vector
        }
    }
    
    return max + 1; // returning the country number with the most armies
}

// aggressive player will attack random country from list of neighbors
int Aggressive::countryToAttack(Country* attackFrom) {
    
    // reset the random value
    srand(time(NULL));
    
    // generates random number from 1 to the number of adjacent countries
    // note that the random function will continuously try a number until it eventually returns a valid one verified by the attack phase
    // thus is may appear as though the computer player is in an infinite loop but this is not the case (it will stop at a number after many tries)
    return (rand() % (attackFrom->getAdjacentCountries().size() + 1));
}

// aggressive player will roll a random number of dice
int Aggressive::attackerRoll() {
    
    // reset the random value
    srand(time(NULL));
    
    // generates random number from 1 to 3 (attack phase is in charge of verifying if 3 is not valid)
    // note that the random function will continuously try a number until it eventually returns a valid one verified by the attack phase
    // thus is may appear as though the computer player is in an infinite loop but this is not the case (it will stop at a number after many tries)
    return (rand() % 3 + 1);
}

// aggressive player moves all armies that they can move
int Aggressive::armiesToMove(int armiesCanMove) {
    return armiesCanMove;
}

// aggressive player will fortify
string Aggressive::chooseFortify() {
    return "Y";
}

// aggressive player will fortify from country with least armies on it
string Aggressive::countryToFortifyFrom(Player* player) {
    // set min country to be first index in the list of player's countries
    int min = 0;
    
    
    //loop through all the countries
    for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
        int max = 0;
        
        //if the country has more armies than the next player owned cuntry
        if (player->getThisPlayerCountries().at(min)->getNumberOfArmies() > player->getThisPlayerCountries().at(i)->getNumberOfArmies()) {
            
            //if the country has 1 army, don't choose that country
            if (player->getThisPlayerCountries().at(i)->getNumberOfArmies() == 1) {
                continue;
            }
            else {
                
                
                //loop through the countries again
                for (unsigned int j = 1; j < player->getThisPlayerCountries().size(); j++) {
                    
                    
                    //if the country has more armies than the max country, max will get assign to j
                    if (player->getThisPlayerCountries().at(j)->getNumberOfArmies() > player->getThisPlayerCountries().at(max)->getNumberOfArmies()) {
                        
                        max = j;
                        
                        //loop through the adjacent countries of the max country
                        for(unsigned int k =0; k< player->getThisPlayerCountries().at(max)->getAdjacentCountries().size(); k++) {
                            
                            
                            //if the country with the leeast armies is a neighbor of the country with the most armies
                            if(player->getThisPlayerCountries().at(i)->getCountryName().compare(player->getThisPlayerCountries().at(max)->getAdjacentCountries().at(k)->getCountryName()) == 0) {
                                min = i; // assigning the index of the vector
                                
                                
                                
                                
                            }
                            else {
                                
                                continue;
                            }
                            continue;
                        }
                        
                    }
                    
                    
                }
                
                
                
                
            }
        }
    }
    
    return player->getThisPlayerCountries().at(min)->getCountryName(); // returning the country number with the most armies
    
}

// aggressive player moves all armies from source country to target country
int Aggressive::armiesToFortify(int sourceCountryArmies) {
    
    return sourceCountryArmies;
    
}

// aggressive player will fortify country with most armies on it
string Aggressive::countryToFortify(Player* player, Country* country) {
    // set max country to be first index in the list of player's countries
    int max = 0;
    
    for (unsigned int i = 1; i < player->getThisPlayerCountries().size(); i++) {
        if (player->getThisPlayerCountries().at(i)->getNumberOfArmies() > player->getThisPlayerCountries().at(max)->getNumberOfArmies()) {
            max = i; // assigning the index of the vector
        }
    }
    
    return player->getThisPlayerCountries().at(max)->getCountryName(); // returning the country number with the most armies
}

// computer players always exchange
bool Aggressive::exchangeAutom() {
    return true;
}

// constructor and destructor for ConcreteStrategy for benevolent computer player
Benevolent::Benevolent() {
}

Benevolent::~Benevolent() {
}


// benevolent computer player will always exchange again
string Benevolent::extraReinforcement() {
    return "y";
}

// benevolent player will select country with least armies on it
int Benevolent::countryToReinforce(Player* player) {
    
    // set min country to be first index in the list of player's countries
    int min = 0;
    
    for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
        if (player->getThisPlayerCountries().at(min)->getNumberOfArmies() > player->getThisPlayerCountries().at(i)->getNumberOfArmies()) {
            min = i; // assigning the index of the vector
        }
    }
    
    return min + 1; // returning the country number with the least armies
}

// benevolent player will put all of armies that can be added to their chosen country
int Benevolent::armiesToPlace(Player* player) {
    return player->getNumOfArmiesForReinforcement();
}

// benevolent player never attacks (will always return n or 0)
string Benevolent::chooseAttack() {
    return "n";
}

int Benevolent::attackFrom(Player* player) {
    return 0;
}

int Benevolent::countryToAttack(Country* attackFrom) {
    return 0;
}

int Benevolent::attackerRoll() {
    return 0;
}

int Benevolent::armiesToMove(int armiesCanMove) {
    return 0;
}

// benevolent player will fortify
string Benevolent::chooseFortify() {
    return "Y";
}

// benevolent player will fortify from country with most armies on it
string Benevolent::countryToFortifyFrom(Player* player) {
    
    // set min country to be first index in the list of player's countries
    int max = 0;
    
    
    //loop through all the countries
    for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
        int min = 0;
        
        //if the country has more armies than the next player owned cuntry
        if (player->getThisPlayerCountries().at(max)->getNumberOfArmies() < player->getThisPlayerCountries().at(i)->getNumberOfArmies()) {
            
            //if the country has 1 army, don't choose that country
            if (player->getThisPlayerCountries().at(i)->getNumberOfArmies() == 1) {
                continue;
            }
            else {
                
                
                //loop through the countries again
                for (unsigned int j = 1; j < player->getThisPlayerCountries().size(); j++) {
                    
                    
                    //if the country has more armies than the min country, min will get assign to j
                    if (player->getThisPlayerCountries().at(j)->getNumberOfArmies() < player->getThisPlayerCountries().at(min)->getNumberOfArmies()) {
                        
                        min = j;
                        
                        //loop through the adjacent countries of the min country
                        for(unsigned int k =0; k< player->getThisPlayerCountries().at(min)->getAdjacentCountries().size(); k++) {
                            
                            
                            //if the country with the most armies is a neighbor of the country with the least armies
                            if(player->getThisPlayerCountries().at(i)->getCountryName().compare(player->getThisPlayerCountries().at(min)->getAdjacentCountries().at(k)->getCountryName()) == 0) {
                                max = i; // assigning the index of the vector
                                
                                
                                
                                
                            }
                            else {
                                
                                continue;
                            }
                            continue;
                        }
                        
                    }
                    
                    
                }
                
                
                
                
            }
        }
    }
    return player->getThisPlayerCountries().at(max)->getCountryName(); // returning the country number with the most armies
}

// benevolent player moves all armies from source country to target country
int Benevolent::armiesToFortify(int sourceCountryArmies) {
    return sourceCountryArmies;
}

// benevolent player will fortify country with least armies on it
string Benevolent::countryToFortify(Player* player, Country* country) {
    
    // set min country to be first index in the list of player's countries
    int min = 0;
    
    for (unsigned int i = 0; i < country->getAdjacentCountries().size(); i++) {
        if (country->getAdjacentCountries().at(min)->getNumberOfArmies() > country->getAdjacentCountries().at(i)->getNumberOfArmies()) {
            min = i; // assigning the index of the vector
        }
    }
    return country->getAdjacentCountries().at(min)->getCountryName(); // returning the country number with the most armies
}

// computer players always exchange
bool Benevolent::exchangeAutom() {
    return true;
}

Random::Random() {
}

Random::~Random() {
}

// random player will randomly choose to exchange again 
string Random::extraReinforcement() {
	srand(time(NULL));
	string choices[] = { "y", "n" };
	return choices[rand() % 2];
}

// random player will randomly select one of their countries
int Random::countryToReinforce(Player* player) {
	srand(time(NULL));
	return (rand() % (player->getThisPlayerCountries().size() + 1));
}

// random player will place a random number of armies
int Random::armiesToPlace(Player* player) {
	srand(time(NULL));
	return (rand() % player->getNumOfArmiesForReinforcement());
}

// random player always attacks
string Random::chooseAttack() {
	return "Y";
}

// random player will randomly select one of their countries
int Random::attackFrom(Player* player) {
	srand(time(NULL));
	return (rand() % (player->getThisPlayerCountries().size() + 1));
}

// random player will attack random country from list of neighbors
int Random::countryToAttack(Country* attackFrom) {
	srand(time(NULL));
	return (rand() % (attackFrom->getAdjacentCountries().size() + 1));
}

// random player will roll a random number of dice
int Random::attackerRoll() {
	srand(time(NULL));
	return (rand() % 3 + 1);
}

// random player will move a random number of armies
int Random::armiesToMove(int armiesCanMove) {
	srand(time(NULL));
	return (rand() % armiesCanMove);
}

// random player will fortify
string Random::chooseFortify() {
	return "Y";
}

// random player will randomly select one of their countries 
string Random::countryToFortifyFrom(Player* player) {
	srand(time(NULL));
	return player->getThisPlayerCountries().at(rand() % player->getThisPlayerCountries().size())->getCountryName();
}

// random player moves a random number of armies
int Random::armiesToFortify(int sourceCountryArmies) {
	srand(time(NULL));
	return (rand() % sourceCountryArmies);
}

// random player will randomly select one of the source country's neighbors 
string Random::countryToFortify(Player* player, Country* country) {
	srand(time(NULL));
	return country->getAdjacentCountries().at(rand() % country->getAdjacentCountries().size())->getCountryName();
}

// computer players always exchange
bool Random::exchangeAutom() {
	return true;
} 


//
//
//
//Cheater::Cheater() {
//}
//
//Cheater::~Cheater() {
//}
//
//// computer players always exchange
//bool Cheater::exchangeAutom() {
//	return true;
//}