#include <iostream>
#include "Player.h"
#include "PlayerStrategies.h"
#include <vector>
#include <string>
#include <memory>
using namespace std;

//Default Constructor
Player::Player() {
    this->dice = new Dice();
    this->hand = new Hand(counter);
	this->strategy = NULL;
    counter++;
    id = make_unique<int>(counter); //id of player generated
    numOfArmiesAtStartUpPhase = make_unique<int>(0);
    phaseStart = make_unique<bool>(false);
}

//player Constructor with name
Player::Player(string name) {
    this->dice = new Dice();
    this->hand = new Hand(counter);
    this->setName(name);
    this->strategy = NULL;
    counter++;
    id = make_unique<int>(counter); //sets the id to the counter of the player
    phaseStart = make_unique<bool>(false);
}

//copy constructor
Player::Player(const Player& orig) {
	this->dice = new Dice();
	*dice = *orig.dice;
	this->hand = new Hand(counter);
	*hand = *orig.hand;
	this->setName(orig.name);
	this->strategy = orig.strategy;
	orig.counter++;
	this->id = make_unique<int>(*orig.id);
	this->phaseStart = make_unique<bool>(false);
    this->strategyNum = make_unique<int>(*orig.strategyNum);
}

const Player& Player:: operator=(const Player &p) {
    if(&p!=this) {
        delete dice;
        delete hand;
        this->dice = new Dice();
        *dice = *p.dice;
        this->hand = new Hand(counter);
        *hand = *p.hand;
        this->setName(p.name);
        this->strategy = p.strategy;
        p.counter++;
        this->id = make_unique<int>(*p.id);
        this->phaseStart = make_unique<bool>(false);
        this->strategyNum = make_unique<int>(*p.strategyNum);
    }
    return *this;
}

//player constructor with parameters
Player::Player(string name, Map* map) {
    this->dice = new Dice();
    this->hand = new Hand(counter);
    this->setName(name);
    this->strategy = NULL;
    counter++;
    id = make_unique<int>(counter);//sets the id to the counter of the player
    this->map = map;//sets the map to the map passed in the constructor
    phaseStart = make_unique<bool>(false);
}


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

int Player::getNumOfArmiesForReinforcement() {
    return numOfArmiesForReinforcement;
}

void Player::setNumOfArmiesForReinforcement(int num) {
    numOfArmiesForReinforcement = num;
}

vector<Continent*> Player:: getThisPlayerContinents() {
    return thisPlayerContinents;
}
int Player:: getNumAttack() {
    return *numAttack;
}

void Player:: setNumAttack(int num) {
    numAttack.reset(new int(num));
}

Map* Player::getMap() {
    return map;
}
//getters for reinforce
int Player::getNumArmy1(){ //getter for reinforce method : army to add according to contries control
    return *numArmy1;
}

int Player::getNumArmy2() {//getter for reinforce method : army to add according to continent control
    return *numArmy2;
}


int Player::getNumArmy3() { //getter for reinforce method : army to add according to cards control
    return *numArmy3;
}

// Getters for Attack
std::string Player::getAttackerCountry() {
    return *attackerCountry;
}
std::string Player::getDefenderCountry() {
    return *defenderCountry;
}
//for the number of armies A= attacker , D=Deffender
int Player::getStartA(){
    return *startA;
}
int  Player::getStartD(){
    return *startD;
}

int  Player::getEndA(){
    return *endA;
}

int  Player::getEndD(){
    return *endD;
}

int Player::getDefenderId() {
    return *defenderId;
}

//getter for fortify
std::string Player::getFortifySourceCountry() {
    return *fortifySourceCountry;
}
std::string Player::getFortifyTargetCountry() {
    return *fortifyTargetCountry;
}

int Player::getSourceArmy() {
    return  *sourceArmy;
}
int Player::getTargetArmy() {
    return *targetArmy;
}
//Setters
void Player::setName(string name) {
    this->name = name;
}


void Player::setPhaseStart(bool start) {
    this->phaseStart.reset(new bool(start));
}

bool Player::getPhaseStart() {
    return *phaseStart;
}

void Player:: setThisPlayerContinents(Continent *continent) {
    thisPlayerContinents.push_back(continent);
}

void Player::setStrategyNum(int num) {
    strategyNum.reset(new int(num));
}

int Player::getStrategyNum() {
    return *strategyNum;
}

void Player:: deleteThisPlayerContinent(Continent *continent) {
    int indexOfContinentToDelete =0;


    for(int i = thisPlayerContinents.size()-1; i >=0; i--) {

        //check which continent we want to delete and set the index
        if(continent->getContinentName().compare(thisPlayerContinents.at(i)->getContinentName()) ==0) {
            indexOfContinentToDelete = i;



        }

    }

    //delete the continent on that index
    thisPlayerContinents.erase(thisPlayerContinents.begin() + indexOfContinentToDelete);


}

void Player:: deleteThisPlayerCountry(Country *country) {
    int indexOfCountryToDelete =0;


    for(int i = countries.size()-1; i >=0; i--) {

        //check which continent we want to delete and set the index
        if(country->getCountryName().compare(countries.at(i)->getCountryName()) ==0) {
            indexOfCountryToDelete = i;



        }

    }

    //delete the continent on that index
    countries.erase(countries.begin() + indexOfCountryToDelete);


}

void Player::setThisPlayerCountry(Country* country) {
    countries.push_back(country);
}

void Player::setMap(Map* map) {
    this->map = map;
}

void Player::setNumArmy1(int i) { //setter for reinforce method : army to add according to contries control
    numArmy1.reset(new int(i));
}

void Player::setNumArmy2(int i) { //setter for reinforce method : army to add according to continent control
    numArmy2.reset(new int(i));
}
void Player::setNumArmy3(int i) {  //setter for reinforce method : army to add according to cards control
    numArmy3.reset(new int(i));
}

//Setters for fortify method
void Player::setFortifySourceCountry(std::string fortifySourceCountry) { //to set the source country name of fortify
    this->fortifySourceCountry = make_unique<string>(fortifySourceCountry);
}
void Player::setFortifyTargetCountry(std::string fortifyTargetCountry) {//to set the target country name of fortify
    this->fortifyTargetCountry = make_unique<string>(fortifyTargetCountry);;
}

void Player::setSourceArmy(int sourceArmy) { // to set source army number of fortify
    this->sourceArmy = make_unique<int>(sourceArmy);
}
void Player::setTargetArmy(int targetArmy) {// to set target army number of fortify
    this->targetArmy = make_unique<int>(targetArmy);
}

//Setters for attack method
void Player::setAttackerCountry(std::string attackerCountry) {
    this->attackerCountry.reset(new string(attackerCountry));

}
void Player::setDefenderCountry(std::string defenderCountry) {
    this->defenderCountry.reset(new string(defenderCountry));
}
//for the number of armies A= attacker , D=Deffender
void  Player::setStartA(int startA) {
    this->startA = make_unique<int>(startA);
}
void  Player::setStartD(int startD) {
    this->startD = make_unique<int>(startD);
}
void  Player::setEndA(int endA) {
    this->endA = make_unique<int>(endA);
}
void  Player::setEndD(int endD) {
    this->endD = make_unique<int>(endD);
}
void Player::setDefenderId(int defenderId) {
    this->defenderId = make_unique<int>(defenderId);
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

void Player::setStrategy(Strategy* strategy) {
    this->strategy = strategy;
}

Strategy* Player::getStrategy() {
    return this->strategy;
}

string Player::executeExtraReinforcement() {
    return this->strategy->extraReinforcement();
}

int Player::executeCountryToReinforce() {
    return this->strategy->countryToReinforce(this);
}

int Player::executeArmiesToPlace() {
    return this->strategy->armiesToPlace(this);
}

void Player::executeHandleArmies(int country, int numArmies) {
	return this->strategy->handleArmies(this, country, numArmies);
}

string Player::executeChooseAttack() {
    return this->strategy->chooseAttack();
}

int Player::executeAttackFrom() {
    return this->strategy->attackFrom(this);
}

int Player::executeCountryToAttack(Country* attackFrom) {
    return this->strategy->countryToAttack(attackFrom);
}

int Player::executeAttackerRoll() {
    return this->strategy->attackerRoll();
}

int Player::executeDefenderRoll() {
	return this->strategy->defenderRoll();
}

void Player::executeSetNumberOfArmies(Country* country) {
	return this->strategy->setNumberOfArmies(country);
}

int Player::executeArmiesToMove(int armiesCanMove) {
    return this->strategy->armiesToMove(armiesCanMove);
}

void Player::executeSetArmiesEnd(int numOfArmiesToMove, Country* countryToAttack) {
	return this->strategy->setArmiesEnd(this, numOfArmiesToMove, countryToAttack);
}

string Player::executeAttackAgain() {
	return this->strategy->attackAgain();
}

string Player::executeChooseFortify() {
    return this->strategy->chooseFortify();
}

string Player::executeCountryToFortifyFrom() {
    return this->strategy->countryToFortifyFrom(this);
}

int Player::executeArmiesToFortify(int sourceCountryArmies) {
    return this->strategy->armiesToFortify(sourceCountryArmies);
}

string Player::executeCountryToFortify(Country* country) {
    return this->strategy->countryToFortify(this, country);
}

void Player::executeHandleFortification(int indexOfSourceCountry, int indexOfTargetCountry, int numOfArmies) {
	return this->strategy->handleFortification(this, indexOfSourceCountry, indexOfTargetCountry, numOfArmies);
}

bool Player::executeExchangeAutom() {
    return this->strategy->exchangeAutom();
}


//reinforce phase
void Player::reinforce() {
    setNumArmy1(0);
    setNumArmy2(0);
    setNumArmy3(0);

    this->setPhaseStart(false);
    cout << "\n~~~~~ Reinforcement Phase ~~~~~\n" << endl;
    numOfArmiesForReinforcement = 0; //for the total number of armies to add
    int ownedCountries = 0;
    int ownedContinent = 0; //for the number of armies to add due to continent control
    int armyHand = 0;// for the number of armies to add due to exchanged cards
    string answer; // for user input

    // number of armies according to number of countries
    // add a minimum of 3 armies if less than 9 countries
    if ((getThisPlayerCountries().size()/3) < 3) {
        ownedCountries = 3;
        numOfArmiesForReinforcement += ownedCountries;
    }

    // divide number of countries by 3 for number of armies to add
    else {
        ownedCountries += (getThisPlayerCountries().size())/ 3;
        numOfArmiesForReinforcement += ownedCountries;
    }
    cout << "The number of armies added by the number of controled countries is " << numOfArmiesForReinforcement << "." << endl;


    //check if the player owns continents
    if(checkControlContinents()) {

        //for each continent owns, we increment the number of armies to add
        for(unsigned int i=0; i < getThisPlayerContinents().size(); i++) {
            ownedContinent = ownedContinent + getThisPlayerContinents().at(i)->getNumberOfArmies();
        }
    }


    cout << "The number of armies added by the number of controlled continents is " << ownedContinent << "." << endl;
    numOfArmiesForReinforcement += ownedContinent;

    // cards may be exchanged or forced exchange (if more than 5) for armies for reinforcement
    if (hand->getCardsInHand().size() > 5) {

        cout << "\nSince there is more than 5 cards in your hand, you must exchange them." << endl;

        this->getHand()->setAutom(executeExchangeAutom()); // assign strategy to exchange method
        this->getHand()->exchange();
        armyHand = this->getHand()->getNumberOfArmiesToPlace();
        numOfArmiesForReinforcement += armyHand;

        //if the size of the hand is greater than 5 cards, keep asking the player to exchange cards
        while(hand->getCardsInHand().size() > 5) {
            cout << "\n\n ****** You didn't exchange enough cards, you still have more than 5 cards in your hand. You need to exchange your cards. ******" << endl;

            this->getHand()->setAutom(executeExchangeAutom()); // assign strategy to exchange method
            this->getHand()->exchange();
            armyHand = this->getHand()->getNumberOfArmiesToPlace();
            numOfArmiesForReinforcement += armyHand;
        }
    }
    else {
        cout << "Do you want to exchange your cards for extra reinforcement ? (y/n)" << endl;

        // returns response for this strategy
        answer = executeExtraReinforcement();

        cout << "You entered: " << answer << endl;

        if (answer == "y") {
            this->getHand()->setAutom(executeExchangeAutom()); // assign strategy to exchange method
            this->getHand()->exchange();
            armyHand+= hand->getNumberOfArmiesToPlace();
            numOfArmiesForReinforcement += armyHand;
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
    cout << "In total, " << numOfArmiesForReinforcement << " armies can be added for reinforcement." << endl;

    while(numOfArmiesForReinforcement !=0 ) {

        cout << "\nThese are your countries and their number of armies" << endl;

        for(unsigned int i = 0 ; i< getThisPlayerCountries().size(); i++) {
            cout << i+1 << ": " << getThisPlayerCountries().at(i)->getCountryName() << " " << getThisPlayerCountries().at(i)->getNumberOfArmies() << endl;
        }
        int country;
        cout << "\nPlease enter the number of the country you would like to reinforce" << endl;

        // returns response for this strategy
        country = executeCountryToReinforce();

        int numArmies;
        cout << "\nEnter the number of armies you would like to place on this country" << endl;

        // returns response for this strategy
        numArmies = executeArmiesToPlace();

        while(numArmies <= 0 || numArmies > numOfArmiesForReinforcement) {
            cout << "Please enter a valid number of armies to place on this country" << endl;
            // returns response for this strategy
            numArmies = executeArmiesToPlace(); // aggressive and benevolent players can't have an invalid input because armyAdd will always be <= armyAdd

            cout << "You entered: " << numArmies << endl;
        }

		executeHandleArmies(country, numArmies);

    }
	cout << "\n\n~~~~~ End of the reinforce phase for player " << this->getName() << " ~~~~~" << endl;
    this->setPhaseStart(true); //we start the phase
}

// attack method
void Player::attack(){
    string playerAttack;
    unsigned int selectAttackFrom, selectCountryToAttack, attackerMaxNumOfDice, defenderMaxNumOfDice, attackerRoll, defenderRoll, numOfPairs, numOfArmiesToMove;
    Country* attackFrom;
    Country* countryToAttack;
    vector<int> attackerDiceValues, defenderDiceValues;
    bool canAttack = false;
    cout << "\n~~~~~ Attack Phase ~~~~~\n" << endl;

    cout << "Player " << this->getID() << ", do you want to attack? (Press Y to attack or anything else to end attack phase)\n" << endl;
    // returns response for this strategy
    playerAttack = executeChooseAttack();

    cout << "You entered: " << playerAttack << endl;
    setNumAttack(0);

    //check if all player's countries has at least 2 armies, the player can't attack otherwise
      for(unsigned int i =0; i <getThisPlayerCountries().size(); i++) {

          if(getThisPlayerCountries().at(i)->getNumberOfArmies() >= 2) {
              canAttack = true;
          }

      }

    if(canAttack == false) {
        playerAttack = "N";
    }

    while (playerAttack == "Y") {

        setNumAttack(getNumAttack()+1);
        //we start the phase
        this->setPhaseStart(true);
        
        //if we are already inside in the while loop, still check if we have a country with more than 2 armies
        //check if all player's countries has at least 2 armies, the player can't attack otherwise
             for(unsigned int i =0; i <getThisPlayerCountries().size(); i++) {

                 if(getThisPlayerCountries().at(i)->getNumberOfArmies() >= 2) {
                     canAttack = true;
                 }

             }

           if(canAttack == false) {
               break; //exit while loop
           }
        
        
        cout << "These are the countries you own and the number of armies placed on them:" << endl;
        for (unsigned int i = 0; i < getThisPlayerCountries().size(); i++) {
            cout << "Country " << i + 1 << ": " << getThisPlayerCountries().at(i)->getCountryName() << " \tNumber of Armies: " << getThisPlayerCountries().at(i)->getNumberOfArmies() << endl;
        }



        cout << "Which country would you like to attack from? The country you select must have at least 2 armies placed on it. Please enter the country's number.\n" << endl;

        // returns response for this strategy
        selectAttackFrom = executeAttackFrom();

        cout << "You entered: " << selectAttackFrom << endl;

        // check if player enters a valid country number (not negative or bigger than number of owned countries)
        // check if country selected has at least 2 armies placed on it
        while (selectAttackFrom <= 0 || selectAttackFrom > getThisPlayerCountries().size() || getThisPlayerCountries().at(selectAttackFrom - 1)->getNumberOfArmies() < 2) {
			if (selectAttackFrom <= 0 || selectAttackFrom > getThisPlayerCountries().size()) {
				cout << "Please enter a valid country number." << endl;
                    
				// returns response for this strategy
				selectAttackFrom = executeAttackFrom();
			}
			else if (getThisPlayerCountries().at(selectAttackFrom - 1)->getNumberOfArmies() < 2) {
				cout << "Please select a country with at least 2 armies placed on it." << endl;
                    
				// returns response for this strategy
				selectAttackFrom = executeAttackFrom();
			}
		}
        
        
        // player attacks from the valid country they selected
        attackFrom = getThisPlayerCountries().at(selectAttackFrom - 1);

        setAttackerCountry(attackFrom->getCountryName()); //setting for obs method
        setStartA(attackFrom->getNumberOfArmies());

        cout << "These are the country's neighbors you can attack and the owners of them:" << endl;
        for (unsigned int i = 0; i < attackFrom->getAdjacentCountries().size(); i++) {
            cout << "Country " << i + 1 << ": " << attackFrom->getAdjacentCountries().at(i)->getCountryName() << "\t(" <<attackFrom->getAdjacentCountries().at(i)->getNumberOfArmies() << " armies)" << "\tBelongs to: Player " << attackFrom->getAdjacentCountries().at(i)->getCountryOwnerId() << endl;
        }

        bool ownNeighbors = true;
        // if country's neighbors all belong to this player, end this attack phase
        for (unsigned int i = 0; i < attackFrom->getAdjacentCountries().size(); i++) {
            if (attackFrom->getCountryOwnerId() != attackFrom->getAdjacentCountries().at(i)->getCountryOwnerId()) {
                ownNeighbors = false;
            }
        }

        if(ownNeighbors) {
            cout << "You own all your neighbors countries, you can't attack" << endl;
            break;
        }

        cout << "Which one of this country's neighbors would you like to attack?. The country you select must belong to another player. Please enter the country's number.\n" << endl;

        // returns response for this strategy
        selectCountryToAttack = executeCountryToAttack(attackFrom);

        cout << "You entered: " << selectCountryToAttack << endl;

        // check if player enters a valid country number (not negative or bigger than number of neighbor countries)
        // check if player selects a country that belongs to another player
        while (selectCountryToAttack <= 0 || selectCountryToAttack > attackFrom->getAdjacentCountries().size() || attackFrom->getAdjacentCountries().at(selectCountryToAttack - 1)->getCountryOwnerId() == this->getID()) {
            if (selectCountryToAttack <= 0 || selectCountryToAttack > attackFrom->getAdjacentCountries().size()) {
                cout << "Please enter a valid country number." << endl;

                // returns response for this strategy
                selectCountryToAttack = executeCountryToAttack(attackFrom);

                cout << "You entered: " << selectCountryToAttack << endl;
            }
            else if (attackFrom->getAdjacentCountries().at(selectCountryToAttack - 1)->getCountryOwnerId() == this->getID()) {
                cout << "Please select a country that is owned by another player." << endl;

                // returns response for this strategy
                selectCountryToAttack = executeCountryToAttack(attackFrom);

                cout << "You entered: " << selectCountryToAttack << endl;
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
        else if (attackerMaxNumOfDice < 1) {
            attackerMaxNumOfDice = 1;
        }

        cout << "Attacker (Player " << this->getID() << "), please select the number of dice to roll. You may only roll 1 to " << attackerMaxNumOfDice << " dice." << endl;

        // returns response for this strategy
        attackerRoll = executeAttackerRoll();

        cout << "You entered: " << attackerRoll << endl;

        // check if player selects a valid number of dice
        while (attackerRoll < 1 || attackerRoll > attackerMaxNumOfDice) {
            cout << "Attacker (Player " << this->getID() << "), please select a valid number of dice to roll. You may only roll 1 to " << attackerMaxNumOfDice << " dice." << endl;

            // returns response for this strategy
            attackerRoll = executeAttackerRoll();

            cout << "You entered: " << attackerRoll << endl;
        }

        cout << "Attacker (Player " << this->getID() << "), you will roll " << attackerRoll << " dice.\n" << endl;

        // defender chooses number of dice to roll
        defenderMaxNumOfDice = countryToAttack->getNumberOfArmies();
        if (defenderMaxNumOfDice > 2) {
            defenderMaxNumOfDice = 2;
        }

        cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), please select the number of dice to roll. You may only roll 1 to " << defenderMaxNumOfDice << " dice." << endl;
		defenderRoll = executeDefenderRoll();

		cout << "You entered: " << defenderRoll << endl;

        setDefenderId(countryToAttack->getCountryOwnerId()); //for observer

        // check if player selects a valid number of dice
        while (defenderRoll < 1 || defenderRoll > defenderMaxNumOfDice) {
            cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), please select a valid number of dice to roll. You may only roll 1 to " << defenderMaxNumOfDice << " dice." << endl;
			defenderRoll = executeDefenderRoll();

			cout << "You entered: " << defenderRoll << endl;
        }

        cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), you will roll " << defenderRoll << " dice.\n" << endl;

        // roll attacker's dice
        cout << "~ Attacker is rolling ~" << endl;
        dice->setDiceToRoll(attackerRoll);
        dice->rollDice();
        cout << "\n" << endl;

        for (unsigned int i = 0; i < attackerRoll; i++) {

            attackerDiceValues.push_back(dice->getValuesRolled().at(i));
        }
        dice->clearDiceRolled();

        // roll defender's dice
        cout << "~ Defender is rolling ~" << endl;
        dice->setDiceToRoll(defenderRoll);
        dice->rollDice();
        cout << "\n" << endl;


        for (unsigned int i = 0; i < defenderRoll; i++) {
            defenderDiceValues.push_back(dice->getValuesRolled().at(i)); //error
        }
        dice->clearDiceRolled();

        // determine how many comparisons we do depending on number of dice both players rolled
        if (attackerRoll < defenderRoll) {
            numOfPairs = 1;
        }
        else {
            numOfPairs = defenderRoll;
        }

        cout << "Number fo dice pairs to compare: " << numOfPairs << endl;
        cout << defenderDiceValues.at(0) << endl;
        // compare pairs of dice
        for (unsigned int i = 0; i < numOfPairs; i++) {
            cout << "~ Pair of dice comparison #" << (i + 1) << " ~\n" << endl;

            cout << "Attacker rolled a " << attackerDiceValues.at(i) << " and Defender rolled a " << defenderDiceValues.at(i) << ".\n" << endl;
            if (attackerDiceValues.at(i) == defenderDiceValues.at(i)) {
                cout << "Attacker's next highest dice and Defender's next highest dice are the same. Attacker lost this battle.\n" << endl;
                cout << "Attacker (Player " << this->getID() << "), you have lost 1 army in " << attackFrom->getCountryName() << ".\n" << endl;

				executeSetNumberOfArmies(attackFrom); // attacker loses one army from their country

                setEndA(attackFrom->getNumberOfArmies());  //set For Observer
                setEndD(countryToAttack->getNumberOfArmies());
            }
            else if (defenderDiceValues.at(i) > attackerDiceValues.at(i)) {
                cout << "Attacker's next highest dice is lower than Defender's next highest dice. Attacker lost this battle.\n" << endl;

                cout << "Attacker (Player " << this->getID() << "), you have lost 1 army in " << attackFrom->getCountryName() << ".\n" << endl;

				executeSetNumberOfArmies(attackFrom); // attacker loses one army from their country

                setEndA(attackFrom->getNumberOfArmies());  //set For Observer
                setEndD(countryToAttack->getNumberOfArmies());
            }
            else if (attackerDiceValues.at(i) > defenderDiceValues.at(i)) {
                cout << "Defender's next highest dice is lower than Defender's next highest dice. Defender lost this battle.\n" << endl;
                cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), you have lost 1 army in " << countryToAttack->getCountryName() << ".\n" << endl;

				executeSetNumberOfArmies(countryToAttack); // defender looses one army from their country

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

                    // returns response for this strategy
                    numOfArmiesToMove = executeArmiesToMove(attackFrom->getNumberOfArmies() - 1);

                    cout << "You entered: " << numOfArmiesToMove << endl;

                    // check if player selects a valid number of armies
                    while (numOfArmiesToMove < 1 || numOfArmiesToMove > attackFrom->getNumberOfArmies() - 1) {
                        cout << "Attacker (Player " << this->getID() << "), please select a valid number of armies to move from " << attackFrom->getCountryName() << ". You may move between 1 to " << attackFrom->getNumberOfArmies() - 1 << " armies." << endl;

                        // returns response for this strategy
                        numOfArmiesToMove = executeArmiesToMove(attackFrom->getNumberOfArmies() - 1);

                        cout << "You entered: " << numOfArmiesToMove << endl;
                    }
                    
					executeSetArmiesEnd(numOfArmiesToMove, countryToAttack);

                }


            }


        }

        // clear dice vectors at the end of each attack
        attackerDiceValues.clear();
        defenderDiceValues.clear();
        
        cout << "Player " << this->getID() << ", do you want to attack again? (Press Y to attack again or anything else to end attack phase)\n" << endl;

		playerAttack = executeAttackAgain();

        cout << "You entered: " << playerAttack << endl;
        
        
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
    bool sourceCountryEnoughArmies = false;
    //tells if the source countries has a neighbour that the user own
    bool neighbourCountries = false;

    //tells if the source countries has adjencent countries that the player own
    bool sourceCountriesNeighbours = false;
    int numOfArmies = 0;
    int indexOfSourceCountry = 0;
    int indexOfTargetCountry = 0;
    bool canfortify = false;
    cout << "\n~~~~~ Fortification Phase ~~~~~" << endl;

    cout << "\nPlayer " << getName() << ", do you want to fortify? (Press Y to fortify or anything else to end fortify phase)" << endl;
    string attack;

    // returns response for this strategy
    attack = executeChooseFortify();

    cout << "You entered: " << attack << endl;

    //check if all player's countries has only 1 army, the player can't fortify
    for(unsigned int i =0; i <getThisPlayerCountries().size(); i++) {

        if(getThisPlayerCountries().at(i)->getNumberOfArmies() != 1) {
            canfortify = true;
        }

    }



    if(canfortify == false) {
        attack = "N";
    }


    if(attack.compare("Y") == 0) {
        this->setPhaseStart(true); //we start the phase
        cout << "\nThese are your countries, their number of armies and their adjacent countries:" << endl;

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

            // returns response for this strategy
            nameSourceCountry = executeCountryToFortifyFrom();

            cout << "You entered: " << nameSourceCountry << endl;

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

            //check if the chosen country has more than 1 army
            for(unsigned int i =0; i < this->getThisPlayerCountries().size(); i++) {

                //find the country with the same name input by user
                if( nameSourceCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {

                    //check if the country owns more than 1 army
                    if(this->getThisPlayerCountries().at(i)->getNumberOfArmies() > 1) {
                        sourceCountryEnoughArmies = true;
                    }


                }

            }


            //asks the player again to enter a valid source country if it was not valid
            while(isSourceCountryValid == false || sourceCountriesNeighbours == false || sourceCountryEnoughArmies == false) {

                if(isSourceCountryValid == false) {
                    cout << "\nThe source country you choose is not own by you or doesn't exists.\nPlease choose a new source country" << endl;
                }

                else if(sourceCountriesNeighbours == false) {
                     cout << "\nThe source country you choose doesn't have adjacent countries your own. \nPlease choose a new source country" << endl;
                }

                else if(sourceCountryEnoughArmies == false) {
                    cout << "\nThe source country you choose doesn't have enough armies to move, it needs to have more than 1 army.\nPlease choose a new source country" << endl;
                }

                cout << "Please write the name of the chosen source country \n(capitalize the first letter)" << endl;

                // returns response for this strategy
                nameSourceCountry = executeCountryToFortifyFrom();


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

                //check if the chosen country has more than 1 army
                       for(unsigned int i =0; i < this->getThisPlayerCountries().size(); i++) {

                           //find the country with the same name input by user
                           if( nameSourceCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {

                               //check if the country owns more than 1 army
                               if(this->getThisPlayerCountries().at(i)->getNumberOfArmies() > 1) {
                                   sourceCountryEnoughArmies = true;
                               }


                           }

                       }

            }
            setFortifySourceCountry(nameSourceCountry);


            cout << "Please enter the number of armies you would like to move" << endl;

            // returns response for this strategy
            numOfArmies = executeArmiesToFortify((this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies()) - 1);

            cout << "You entered: " << numOfArmies << endl;

            //check if the number of armies entered is valid
            if(numOfArmies < 1 || numOfArmies > this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() -1 ) {
                isNumOfArmiesValid = false;
            }


            //prompts the player again to enter a valid number of armies if the number entered is not valid
            while(isNumOfArmiesValid == false) {
                cout << numOfArmies << endl;
                cout << "\nThe number of armies you enter is not valid.\nPlease enter a value in the range of [1 to (number of armies in the source country -1)]" << endl;
                cout << "Enter the number of armies you would like to move" << endl;

                // returns response for this strategy
                numOfArmies = executeArmiesToFortify((this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies())-1);

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

            // returns response for this strategy
            nameTargetCountry = executeCountryToFortify(getThisPlayerCountries().at(indexOfSourceCountry));

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

                }

            }

            //if the target country is not valid, ask again
            while(isTargetCountryValid == false || isTargetCountryNeighbour == false) {
                if(isTargetCountryValid == false) {
                     cout << "\nThe target country you choose is not own by you or doesn't exists.\nPlease choose a valid country" << endl;
                }

                else if(isTargetCountryNeighbour == false) {
                    cout << "\nThe target country you choose is not a neighbour of the source country. \nPlease choose a valid country" << endl;
                }

                cout << "Enter the name of a valid chosen target country" << endl;

                // returns response for this strategy
                nameTargetCountry = executeCountryToFortify(getThisPlayerCountries().at(indexOfSourceCountry));


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

			// the strategy will fortify the country/countries
			executeHandleFortification(indexOfSourceCountry, indexOfTargetCountry, numOfArmies);

			cout << "The fortification phase has ended." << endl;
        }
    }
    else {
        cout << "The fortification phase has ended." << endl;
    }
}
