#include <iostream>
#include "PlayerStrategies.h"
#include "time.h"
#include <vector>;

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
	cout << "You entered: " << input << endl;
    return input;
}

int User::armiesToPlace(Player* player) {
    int input;
    cin >> input;
	cout << "You entered: " << input << endl;
    return input;
}

void User::handleArmies(Player* player, int country, int numArmies) {
	//increment the number of armies on the chosen country
	int newNumArmies = player->getThisPlayerCountries().at(country - 1)->getNumberOfArmies() + numArmies;
	player->getThisPlayerCountries().at(country - 1)->setNumberOfArmies(newNumArmies);

	//decrement the number of army to add
	player->setNumOfArmiesForReinforcement(player->getNumOfArmiesForReinforcement() - numArmies);

	cout << "The country " << player->getThisPlayerCountries().at(country - 1)->getCountryName() << " has now " << player->getThisPlayerCountries().at(country - 1)->getNumberOfArmies() << " armies." << endl;
	cout << "\nYou still have " << player->getNumOfArmiesForReinforcement() << " armies to place." << endl;
}

string User::chooseAttack() {
    string input;
    cin >> input;
    return input;
}

int User::attackFrom(Player* player) {
    int input;
    cin >> input;
	cout << "You entered: " << input << endl;
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

int User::defenderRoll() {
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

void User::handleFortification(Player* player, int indexOfSourceCountry, int indexOfTargetCountry, int numOfArmies) {
	//set the new number of armies for the source country
	int numberOfArmiesSourceCountry = player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
	player->getThisPlayerCountries().at(indexOfSourceCountry)->setNumberOfArmies(numberOfArmiesSourceCountry - numOfArmies);
			
	//set the new number of armies for the target country
	int numberOfArmiesTargetCountry = player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
	player->getThisPlayerCountries().at(indexOfTargetCountry)->setNumberOfArmies(numberOfArmiesTargetCountry + numOfArmies);

	player->setFortifySourceCountry(player->getThisPlayerCountries().at(indexOfSourceCountry)->getCountryName());
	player->setFortifyTargetCountry(player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName());
	int sourceArmy = player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
	int targetArmy = player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
	player->setSourceArmy(sourceArmy);
	player->setTargetArmy(targetArmy);

	//Display the new number of armies for source country and target country
	cout << "The player fortified succesfully the country: " << player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName() << endl;
	cout << player->getThisPlayerCountries().at(indexOfSourceCountry)->getCountryName() << " has now " << player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() << " armies." << endl;
	cout << player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName() << " has now " << player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies() << " armies." << endl;
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
    
	cout << "You entered: " << max + 1 << endl;
    return max + 1; // returning the country number with the most armies
}

// aggressive player will put all of armies that can be added to their chosen country
int Aggressive::armiesToPlace(Player* player) {
	cout << "You entered: " << player->getNumOfArmiesForReinforcement() << endl;
    return player->getNumOfArmiesForReinforcement();
}

void Aggressive::handleArmies(Player* player, int country, int numArmies) {
	//increment the number of armies on the chosen country
	int newNumArmies = player->getThisPlayerCountries().at(country - 1)->getNumberOfArmies() + numArmies;
	player->getThisPlayerCountries().at(country - 1)->setNumberOfArmies(newNumArmies);

	//decrement the number of army to add
	player->setNumOfArmiesForReinforcement(player->getNumOfArmiesForReinforcement() - numArmies);

	cout << "The country " << player->getThisPlayerCountries().at(country - 1)->getCountryName() << " has now " << player->getThisPlayerCountries().at(country - 1)->getNumberOfArmies() << " armies." << endl;
	cout << "\nYou still have " << player->getNumOfArmiesForReinforcement() << " armies to place." << endl;
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
    
	cout << "You entered: " << max + 1 << endl;
    return max + 1; // returning the country number with the most armies
}

// aggressive player will attack random country from list of neighbors
int Aggressive::countryToAttack(Country* attackFrom) {
    
    // reset the random value
    srand(time(NULL));
    
    // generates random number from 1 to the number of adjacent countries
    // note that the random function will continuously try a number until it eventually returns a valid one verified by the attack phase
	int choice = (rand() % attackFrom->getAdjacentCountries().size() + 1);
	cout << "You entered: " << choice << endl;
	return choice;
}

// aggressive player will roll a random number of dice
int Aggressive::attackerRoll() {
    
    // reset the random value
    srand(time(NULL));
    
    // generates random number from 1 to 3 (attack phase is in charge of verifying if 3 is not valid)
    // note that the random function will continuously try a number until it eventually returns a valid one verified by the attack phase
    return (rand() % 3 + 1);
}

// all computer strategies have no user interaction 
// defender will always roll 1 to 2 dice
int Aggressive::defenderRoll() {
	srand(time(NULL));
	return (rand() % 2 + 1);
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

void Aggressive::handleFortification(Player* player, int indexOfSourceCountry, int indexOfTargetCountry, int numOfArmies) {
	//set the new number of armies for the source country
	int numberOfArmiesSourceCountry = player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
	player->getThisPlayerCountries().at(indexOfSourceCountry)->setNumberOfArmies(numberOfArmiesSourceCountry - numOfArmies);

	//set the new number of armies for the target country
	int numberOfArmiesTargetCountry = player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
	player->getThisPlayerCountries().at(indexOfTargetCountry)->setNumberOfArmies(numberOfArmiesTargetCountry + numOfArmies);

	player->setFortifySourceCountry(player->getThisPlayerCountries().at(indexOfSourceCountry)->getCountryName());
	player->setFortifyTargetCountry(player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName());
	int sourceArmy = player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
	int targetArmy = player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
	player->setSourceArmy(sourceArmy);
	player->setTargetArmy(targetArmy);

	//Display the new number of armies for source country and target country
	cout << "The player fortified succesfully the country: " << player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName() << endl;
	cout << player->getThisPlayerCountries().at(indexOfSourceCountry)->getCountryName() << " has now " << player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() << " armies." << endl;
	cout << player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName() << " has now " << player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies() << " armies." << endl;
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
    
	cout << "You entered: " << min + 1 << endl;
    return min + 1; // returning the country number with the least armies
}

// benevolent player will put all of armies that can be added to their chosen country
int Benevolent::armiesToPlace(Player* player) {
	cout << "You entered: " << player->getNumOfArmiesForReinforcement() << endl;
    return player->getNumOfArmiesForReinforcement();
}

void Benevolent::handleArmies(Player* player, int country, int numArmies) {
	//increment the number of armies on the chosen country
	int newNumArmies = player->getThisPlayerCountries().at(country - 1)->getNumberOfArmies() + numArmies;
	player->getThisPlayerCountries().at(country - 1)->setNumberOfArmies(newNumArmies);

	//decrement the number of army to add
	player->setNumOfArmiesForReinforcement(player->getNumOfArmiesForReinforcement() - numArmies);

	cout << "The country " << player->getThisPlayerCountries().at(country - 1)->getCountryName() << " has now " << player->getThisPlayerCountries().at(country - 1)->getNumberOfArmies() << " armies." << endl;
	cout << "\nYou still have " << player->getNumOfArmiesForReinforcement() << " armies to place." << endl;
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

// all computer strategies have no user interaction 
// benevolent player never attacks
int Benevolent::defenderRoll() {
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

void Benevolent::handleFortification(Player* player, int indexOfSourceCountry, int indexOfTargetCountry, int numOfArmies) {
	//set the new number of armies for the source country
	int numberOfArmiesSourceCountry = player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
	player->getThisPlayerCountries().at(indexOfSourceCountry)->setNumberOfArmies(numberOfArmiesSourceCountry - numOfArmies);

	//set the new number of armies for the target country
	int numberOfArmiesTargetCountry = player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
	player->getThisPlayerCountries().at(indexOfTargetCountry)->setNumberOfArmies(numberOfArmiesTargetCountry + numOfArmies);

	player->setFortifySourceCountry(player->getThisPlayerCountries().at(indexOfSourceCountry)->getCountryName());
	player->setFortifyTargetCountry(player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName());
	int sourceArmy = player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
	int targetArmy = player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
	player->setSourceArmy(sourceArmy);
	player->setTargetArmy(targetArmy);

	//Display the new number of armies for source country and target country
	cout << "The player fortified succesfully the country: " << player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName() << endl;
	cout << player->getThisPlayerCountries().at(indexOfSourceCountry)->getCountryName() << " has now " << player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() << " armies." << endl;
	cout << player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName() << " has now " << player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies() << " armies." << endl;
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
	int choice = (rand() % player->getThisPlayerCountries().size() + 1);
	cout << "You entered: " << choice << endl;
	return choice;
}

// random player will place a random number of armies
int Random::armiesToPlace(Player* player) {
	srand(time(NULL));
	int choice = (rand() % player->getNumOfArmiesForReinforcement() + 1);
	cout << "You entered: " << choice << endl;
	return choice;
}

void Random::handleArmies(Player* player, int country, int numArmies) {
	//increment the number of armies on the chosen country
	int newNumArmies = player->getThisPlayerCountries().at(country - 1)->getNumberOfArmies() + numArmies;
	player->getThisPlayerCountries().at(country - 1)->setNumberOfArmies(newNumArmies);

	//decrement the number of army to add
	player->setNumOfArmiesForReinforcement(player->getNumOfArmiesForReinforcement() - numArmies);

	cout << "The country " << player->getThisPlayerCountries().at(country - 1)->getCountryName() << " has now " << player->getThisPlayerCountries().at(country - 1)->getNumberOfArmies() << " armies." << endl;
	cout << "\nYou still have " << player->getNumOfArmiesForReinforcement() << " armies to place." << endl;
}

// random player always attacks
string Random::chooseAttack() {
	return "Y";
}

// random player will randomly select one of their countries
int Random::attackFrom(Player* player) {
	srand(time(NULL));
    rand(); rand(); //help randomize more
	int choice = (rand() % player->getThisPlayerCountries().size() + 1);
	cout << "You entered: " << choice << endl;
	return choice;
}

// random player will attack random country from list of neighbors
int Random::countryToAttack(Country* attackFrom) {
	srand(time(NULL));
    rand(); rand(); //help randomize more
	return (rand() % attackFrom->getAdjacentCountries().size() + 1);
}

// random player will roll a random number of dice
int Random::attackerRoll() {
	srand(time(NULL));
    rand(); rand(); //help randomize more
	return (rand() % 3 + 1);
}

// all computer strategies have no user interaction 
// defender will always roll 1 to 2 dice
int Random::defenderRoll() {
	srand(time(NULL));
    rand(); rand(); //help randomize more
	return (rand() % 2 + 1);
}

// random player will move a random number of armies
int Random::armiesToMove(int armiesCanMove) {
	srand(time(NULL));
    rand(); rand(); //help randomize more
	return (rand() % armiesCanMove);
}

// random player will fortify
string Random::chooseFortify() {
	return "Y";
}

// random player will randomly select one of their countries 
string Random::countryToFortifyFrom(Player* player) {
	srand(time(NULL));
    rand(); rand(); //help randomize more
    int indexChosenCountry = rand() % player->getThisPlayerCountries().size();
    bool hasAdjacentCountries = false;
    
    //check if the country has more than 1 army, if not choose another country
    while(player->getThisPlayerCountries().at(indexChosenCountry)->getNumberOfArmies() == 1) {
        srand(time(NULL));
        rand(); rand(); //help randomize more
        indexChosenCountry = rand() % player->getThisPlayerCountries().size();
    }
    
    
    
    //check if the country chosen has adjacent countries own by the player
    while(hasAdjacentCountries == false) {
        
        //loop through the adjacent countries of the country chosen
        for(int i=0; i < player->getThisPlayerCountries().at(indexChosenCountry)->getAdjacentCountries().size(); i++) {
            
            string nameAdjacentCountry = player->getThisPlayerCountries().at(indexChosenCountry)->getAdjacentCountries().at(i)->getCountryName();
            
            //loop through the countries owned by the player
            for(int j =0; j <player->getThisPlayerCountries().size(); j++) {
                if(nameAdjacentCountry.compare(player->getThisPlayerCountries().at(j)->getCountryName()) ==0) {
                    hasAdjacentCountries = true;
                }
            }
            
        }
        
        //select a new country if the chosen countries doesn't have neighbour owns by the player
        if(hasAdjacentCountries == false) {
            srand(time(NULL));
            rand(); rand(); //help randomize more
            indexChosenCountry = rand() % player->getThisPlayerCountries().size();
        }
    
    }
    
    return player->getThisPlayerCountries().at(indexChosenCountry)->getCountryName();
}

// random player moves a random number of armies
int Random::armiesToFortify(int sourceCountryArmies) {
	srand(time(NULL));
    rand(); rand(); //help randomize more
	return (rand() % sourceCountryArmies + 1);
}

// random player will randomly select one of the source country's neighbors 
string Random::countryToFortify(Player* player, Country* country) {
	srand(time(NULL));
    rand(); rand(); //help randomize more
	return country->getAdjacentCountries().at(rand() % country->getAdjacentCountries().size())->getCountryName();
}

void Random::handleFortification(Player* player, int indexOfSourceCountry, int indexOfTargetCountry, int numOfArmies) {
	//set the new number of armies for the source country
	int numberOfArmiesSourceCountry = player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
	player->getThisPlayerCountries().at(indexOfSourceCountry)->setNumberOfArmies(numberOfArmiesSourceCountry - numOfArmies);

	//set the new number of armies for the target country
	int numberOfArmiesTargetCountry = player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
	player->getThisPlayerCountries().at(indexOfTargetCountry)->setNumberOfArmies(numberOfArmiesTargetCountry + numOfArmies);

	player->setFortifySourceCountry(player->getThisPlayerCountries().at(indexOfSourceCountry)->getCountryName());
	player->setFortifyTargetCountry(player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName());
	int sourceArmy = player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
	int targetArmy = player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
	player->setSourceArmy(sourceArmy);
	player->setTargetArmy(targetArmy);

	//Display the new number of armies for source country and target country
	cout << "The player fortified succesfully the country: " << player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName() << endl;
	cout << player->getThisPlayerCountries().at(indexOfSourceCountry)->getCountryName() << " has now " << player->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() << " armies." << endl;
	cout << player->getThisPlayerCountries().at(indexOfTargetCountry)->getCountryName() << " has now " << player->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies() << " armies." << endl;
}

// computer players always exchange
bool Random::exchangeAutom() {
	return true;
} 

Cheater::Cheater() {
}

Cheater::~Cheater() {
}

//Cheater will automatically get twice the amount of soldiers, so it is not necessary to exchange cards. 
string Cheater::extraReinforcement() {
	return "N";
}

// cheater will make a fake selection of the first country they own from the list
int Cheater::countryToReinforce(Player* player) {
	cout << "You entered: " << 1 << endl;
	return 1;
}

// cheater will make a fake selection of 1
int Cheater::armiesToPlace(Player* player) {
	cout << "You entered: " << 1 << endl;
	return 1;
}

// cheater will double the number of armies on all of its countries
void Cheater::handleArmies(Player* player, int country, int numArmies) {	
	for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
		int currentArmy = player->getThisPlayerCountries().at(i)->getNumberOfArmies();
		int cheaterArmy = (currentArmy * 2); // double armies
		player->getThisPlayerCountries().at(i)->setNumberOfArmies(cheaterArmy); // add new armies to each country
	}

	cout << "The following countries will be reinforced:" << endl;

	for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
		string name = player->getThisPlayerCountries().at(i)->getCountryName();
		int army = player->getThisPlayerCountries().at(i)->getNumberOfArmies();
		cout << name << " will now have " << army << " armies." << endl;
	}

	// remove whatever previous armies the cheater had and set it to 0
	player->setNumOfArmiesForReinforcement(0);
	cout << "\nYou still have " << player->getNumOfArmiesForReinforcement() << " armies to place." << endl;
}

// cheater will always attack
string Cheater::chooseAttack() {
	return "Y";
}
	
int Cheater::attackFrom(Player* player) {
	cout << "You will be attacking from all your bordering countries" << endl;

	vector<Country*> neighbors;

	for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
		if (player->getThisPlayerCountries().at(i)->getEnemies().size() > 0) {
			for (unsigned int j = 0; j < player->getThisPlayerCountries().at(i)->getEnemies().size(); j++) {
				neighbors.push_back(player->getThisPlayerCountries().at(i)->getEnemies().at(j));
			}
		}
	}

	// cheater owns all neighbors of all its countries
	for (unsigned int i = 0; i < neighbors.size(); i++) {
		neighbors.at(i)->setCountryOwnerId(player->getID());  
		player->setThisPlayerCountry(neighbors.at(i)); 
	}

	// this is only displayed for cheater
	cout << "These are the countries you now own and the number of armies placed on them:" << endl;
	for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
		cout << "Country " << i + 1 << ": " << player->getThisPlayerCountries().at(i)->getCountryName() << " \tNumber of Armies: " << player->getThisPlayerCountries().at(i)->getNumberOfArmies() << endl;
	}

	srand(time(NULL));
	return (rand() % player->getThisPlayerCountries().size() + 1); // return random country (does not matter since all neighbored countries are attacked regardless)
}

int Cheater::countryToAttack(Country* attackFrom) {
	srand(time(NULL));
	return (rand() % attackFrom->getAdjacentCountries().size() + 1); // return random country (does not matter since all neighbored countries are attacked regardless)
}

int Cheater::attackerRoll() {
	return 1; // returning guaranteed valid number since it will not be used as player will automatically own neighbors 
}

int Cheater::defenderRoll() {
	return 1; // returning guaranteed valid number since it will not be used as player will automatically own neighbors  
}

int Cheater::armiesToMove(int armiesCanMove) {
	return 1; // returning guaranteed valid number since it will not be used as player will automatically own neighbors 
}

// cheater will always fortify 
string Cheater::chooseFortify() {
	return "Y";
}

string Cheater::countryToFortifyFrom(Player* player) {
	srand(time(NULL));
	return player->getThisPlayerCountries().at(rand() % player->getThisPlayerCountries().size())->getCountryName(); // return random owned country since we will fortify all countries with enemies
}

// cheater will be doubling the armies so we can return a random number which will not be used
int Cheater::armiesToFortify(int sourceCountryArmies) {
	srand(time(NULL));
	return (rand() % sourceCountryArmies + 1); 
}

// cheater will select random owned country which will not be used
string Cheater::countryToFortify(Player* player, Country* country) {
	srand(time(NULL));
	return country->getAdjacentCountries().at(rand() % country->getAdjacentCountries().size())->getCountryName();  
}

// cheater will fortify all of its countries that have enemy neighbors by doubling their armies
void Cheater::handleFortification(Player* player, int indexOfSourceCountry, int indexOfTargetCountry, int numOfArmies) {
	for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
		player->getThisPlayerCountries().at(i)->setEnemies(); // assign enemies of each owned country
	}

	for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
		if (player->getThisPlayerCountries().at(i)->getEnemies().size() > 0) { // if each owned country has at least one enemy neighbor
			int prevArmies = player->getThisPlayerCountries().at(i)->getNumberOfArmies();
			player->getThisPlayerCountries().at(i)->setNumberOfArmies(prevArmies * 2);// double this country's armies
		}
	}

	cout << "\nThese are your countries and their number of armies after fortifying them." << endl;

	for (unsigned int i = 0; i < player->getThisPlayerCountries().size(); i++) {
		cout << player->getThisPlayerCountries().at(i)->getCountryName() << " " << player->getThisPlayerCountries().at(i)->getNumberOfArmies() << endl;
	}

}

bool Cheater::exchangeAutom() {
	return true;
}


