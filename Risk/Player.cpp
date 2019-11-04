#include <iostream>
#include "Player.h"
#include <vector>
#include <string>
#include <memory>
using namespace std;

//player constructor
Player::Player(string name) {
	this->dice = new Dice();
	this->hand = new Hand(counter); 
	this->setName(name);
	counter++;
    
    //sets the id to the counter of the player
    id = make_unique<int>(counter);
   
}

Player::Player() {
	this->dice = new Dice();
	this->hand = new Hand(counter);
	counter++;
	id = make_unique<int>(counter); //id of player generated
}

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

Hand* Player::getHand() {
	return hand;
}

Dice* Player::getDice() {
	return dice;
}


//Setters
void Player::setName(string name) {
	this->name = name;
}

vector<Country*> Player:: getThisPlayerCountries() {
    return countries;
}

void Player:: setThisPlayerCountry(Country* country) {
    countries.push_back(country);
}

//extra methods , reinforce, attack and fortify, will be implemented in next iteration
void Player::reinforce() {
	cout << "The player reinforce his troops" << endl;
}

// attack method
void Player::attack() {
	string playerAttack;
	int selectAttackFrom, selectCountryToAttack, attackerMaxNumOfDice, defenderMaxNumOfDice, attackerRoll, defenderRoll, numOfPairs, numOfArmiesToMove;
	Country* attackFrom;
	Country* countryToAttack;
	vector<int> attackerDiceValues, defenderDiceValues;

	cout << "~~~~~ Attack Phase ~~~~~\n" << endl;

	cout << "Player " << this->getID() << ", do you want to attack? (Press Y to attack or anything else to end attack phase)\n" << endl;
	cin >> playerAttack;

	while (playerAttack == "Y") {
		cout << "These are the countries you own and the number of armies placed on them:" << endl;
		for (int i = 0; i < getThisPlayerCountries().size(); i++) {
			cout << "Country " << i + 1 << ": " << getThisPlayerCountries().at(i)->getCountryName() << " \tNumber of Armies: " << getThisPlayerCountries().at(i)->getNumberOfArmies() << endl;
			cout << "\n" << endl;
		}

		cout << "Which country would you like to attack from? The country you select must have at least 2 armies placed on it. Please enter the country's number.\n" << endl;
		cin >> selectAttackFrom;

		// check if player enters a valid country number (not negative or bigger than number of owned countries)
		while (selectAttackFrom <= 0 || selectAttackFrom > getThisPlayerCountries().size()) {
			cout << "Please enter a valid country number." << endl;
			cin >> selectAttackFrom;
		}

		// check if country selected has at least 2 armies placed on it
		while (getThisPlayerCountries().at(selectAttackFrom - 1)->getNumberOfArmies() < 2) {
			cout << "Please select a country with at least 2 armies placed on it." << endl;
			cin >> selectAttackFrom;
		}

		// player attacks from the valid country they selected
		attackFrom = getThisPlayerCountries().at(selectAttackFrom - 1);

		cout << "You will be attacking from " << attackFrom->getCountryName() << " with " << attackFrom->getNumberOfArmies() << " armies.\n" << endl;

		cout << "These are the country's neighbors you can attack and the owners of them:" << endl;
		for (int i = 0; i < attackFrom->getAdjacentCountries().size(); i++) {
			cout << "Country " << i + 1 << ": " << attackFrom->getAdjacentCountries().at(i)->getCountryName() << "\tBelongs to: Player " << attackFrom->getCountryOwnerId() << endl;
			cout << "\n" << endl;
		}

		cout << "Which one of this country's neighbors would you like to attack?. The country you select must belong to another player. Please enter the country's number.\n" << endl;
		cin >> selectCountryToAttack;

		// check if player enters a valid country number (not negative or bigger than number of neighbor countries)
		while (selectCountryToAttack <= 0 || selectCountryToAttack > attackFrom->getAdjacentCountries().size()) {
			cout << "Please enter a valid country number." << endl;
			cin >> selectCountryToAttack;
		}

		// check if player selects a country that belongs to another player
		while (attackFrom->getAdjacentCountries().at(selectCountryToAttack - 1)->getCountryOwnerId() == this->getID()) {
			cout << "Please select a country that is owned by another player." << endl;
			cin >> selectCountryToAttack;
		}

		// player attacks the valid country they selected
		countryToAttack = attackFrom->getAdjacentCountries().at(selectCountryToAttack - 1);

		cout << "You will be attacking " << countryToAttack->getCountryName() << " which belongs to Player " << countryToAttack->getCountryOwnerId() << ".\n" << endl;

		// attacker chooses number of dice to roll
		attackerMaxNumOfDice = countryToAttack->getNumberOfArmies() - 1;
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

		cout << "Attacker (Player " << this->getID() << "), you will roll " << attackerRoll << " dice." << endl;

		// defender chooses number of dice to roll
		defenderMaxNumOfDice = countryToAttack->getNumberOfArmies();
		if (defenderMaxNumOfDice > 2) {
			attackerMaxNumOfDice = 2;
		}

		cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), please select the number of dice to roll. You may only roll 1 to " << defenderMaxNumOfDice << " dice." << endl;
		cin >> defenderRoll;

		// check if player selects a valid number of dice
		while (defenderRoll < 1 || defenderRoll > defenderMaxNumOfDice) {
			cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), please select a valid number of dice to roll. You may only roll 1 to " << defenderMaxNumOfDice << " dice." << endl;
			cin >> defenderRoll;
		}

		cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), you will roll " << defenderRoll << " dice." << endl;
 
		// roll attacker's dice
		cout << "~ Attacker is rolling ~" << endl;
		dice->setDiceToRoll(attackerRoll);
		dice->rollDice();
		for (int i = 0; i < attackerRoll; i++) {
			attackerDiceValues.push_back(dice->getValuesRolled().at(attackerRoll));
		}

		// roll defender's dice
		cout << "~ Defender is rolling ~" << endl;
		dice->setDiceToRoll(defenderRoll);
		dice->rollDice();
		for (int i = 0; i < defenderRoll; i++) {
			defenderDiceValues.push_back(dice->getValuesRolled().at(defenderRoll));
		}

		// determine how many comparisons we do depending on number of dice both players rolled
		if (attackerRoll < defenderRoll) {
			numOfPairs = 1;
		}
		else {
			numOfPairs = defenderRoll;
		}

		// compare pairs of dice
		for (int i = 0; i < numOfPairs; i++) {
			if (attackerDiceValues.at(i) == defenderDiceValues.at(i) || defenderDiceValues.at(i) > attackerDiceValues.at(i)) {
				cout << "Attacker (Player " << this->getID() << "), you have lost 1 army in " << attackFrom->getCountryName() << "." << endl;
				attackFrom->setNumberOfArmies(attackFrom->getNumberOfArmies() - 1); // attacker loses one army from their country
			}
			if (attackerDiceValues.at(i) > defenderDiceValues.at(i)) {
				cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), you have lost 1 army in " << countryToAttack->getCountryName() << "." << endl;
				countryToAttack->setNumberOfArmies(countryToAttack->getNumberOfArmies() - 1); // defender looses one army from their country
				
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
    bool isNumOfArmiesValid = true;
    
 
    int numOfArmies = 0;
    int indexOfSourceCountry = 0;
    int indexOfTargetCountry = 0;

//    Country sourceCountry;
//    Country targetCountry;
    
    cout << "***** Fortification Phase *******" << endl;
    
    //Prompts the user for the source country
    cout << "Please write the name of the chosen source country \n(capitalize the first letter)" << endl;
    
        cin >> nameSourceCountry;
    
    
    //check if the player owns the source country
    for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {
        if( nameSourceCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
            isSourceCountryValid = true;
            indexOfSourceCountry = i;
        }
    }
    
    
    //asks the player again to enter a valid source country if it was not valid
    while(isSourceCountryValid == false) {
        cout << "\nThe source country you choose is not own by you (or doesn't exist) \nPlease choose a country you own as the source country" << endl;
       cout << "Please write the name of the chosen source country \n(capitalize the first letter)" << endl;

            cin >> nameSourceCountry;
        
        
        //check if the player owns the source country
        for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {
            if( nameSourceCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
                isSourceCountryValid = true;
                indexOfSourceCountry = i;
            }
        }
    }
    
    
    cout << "Please enter the number of armies you would like to move" << endl;
    cin >> numOfArmies;
    
    
    if(numOfArmies < 1 || numOfArmies > this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() -1 ) {
        isNumOfArmiesValid = false;
    }
    
    
    //asks the player again to enter a valid number of armies
    while(isNumOfArmiesValid == false) {
        cout << numOfArmies << endl;
        cout << "\nThe number of armies you enter is not valid.\nPlease enter a value in the range of [1 to (number of armies in the source country -1)]" << endl;
        cout << "Enter the number of armies you would like to move" << endl;

        cin >> numOfArmies;
           
           
           if(numOfArmies < 1 || numOfArmies > this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() -1 ) {
               isNumOfArmiesValid = false;
           }
        
           else {
               isNumOfArmiesValid = true;
           }
        }

    

      
    
    cout << "Please write the name of the chosen target country \n(capitalize the first letter)" << endl;
       cin >> nameTargetCountry;
    
    //check if the player owns the target country
       for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {
           if( nameTargetCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
               isTargetCountryValid = true;
               indexOfTargetCountry = i;
           }
       }
    
    
    //check if the country is a neighboring country of the source country
    for(int i =0; i< this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); i++) {
        if(nameTargetCountry.compare(this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().at(i)->getCountryName()) != 0) {
             isTargetCountryValid = false;
        }
        
        else {
             isTargetCountryValid= true;
        }
    }
    
    while(isTargetCountryValid == false) {
           cout << "\nThe target country you choose is not own by you or doesn't exists or is not a neighbour of the source country \nPlease choose a valid country" << endl;
            cout << "Enter the name of a valid chosen target country" << endl;
           cin >> nameTargetCountry;
        
        //check if the player owns the target country
           for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {
               if( nameTargetCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
                   isTargetCountryValid = true;
                   indexOfTargetCountry = i;
               }
           }
        
        
        //check if the country is a neighboring country of the source country
        for(int i =0; i< this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); i++) {
            if(nameTargetCountry.compare(this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().at(i)->getCountryName()) != 0) {
                 isTargetCountryValid = false;
            }
            
            else {
                 isTargetCountryValid= true;
            }
        }
        
    }
    
    //set the new number of armies for the source country
    int numberOfArmiesSourceCountry = this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
    this->getThisPlayerCountries().at(indexOfSourceCountry)->setNumberOfArmies(numberOfArmiesSourceCountry - numOfArmies);
    
    //set the new number of armies for the target country
    int numberOfArmiesTargetCountry = this->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
    this->getThisPlayerCountries().at(indexOfTargetCountry)->setNumberOfArmies(numberOfArmiesTargetCountry + numOfArmies);
    
//    cout << "Is the source country valid? " <<  std::boolalpha << isSourceCountryValid << endl;
//
//    cout << "Is the source number of armies valid? " <<  std::boolalpha << isNumOfArmiesValid << endl;
//
//    cout << "Is the target country valid? " <<  std::boolalpha << isTargetCountryValid << endl;
    
    
    cout << "The player fortified succesfully the country: " << nameTargetCountry  << endl;
    cout << nameSourceCountry << " has now " << this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() << " armies"  << endl;
     cout << nameTargetCountry << " has now " << this->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies() << " armies"  << endl;
    
    
    //if the number of armies is valid, i need to decrement the number of armies in source and increment in target
    //loop everything until all values are good
}




