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
    numOfArmiesAtStartUpPhase = make_unique<int>(0);
}

Player::~Player() {
    delete hand;
    delete dice;
}

//id counter starts at 0
int Player::counter = 0;
//initialize variable for number of army to add for future method
int armyAdd = 0;
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

Hand Player::getNotPointerHand() {
	return handNP;
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
Deck* Player::getDeck() {
	return deck;
}

Map Player::getMap() {
	return map;
}

//gets num of army
int Player::getArmyAdd() {
	return armyAdd;
}

//Setters
void Player::setName(string name) {
    this->name = name;
}

vector<Country*> Player::getThisPlayerCountries() {
	return countries;
}

void Player::setThisPlayerCountry(Country* country) {
	countries.push_back(country);
}




//extra methods , reinforce, attack and fortify, will be implemented in next iteration

void Player::reinforce() {

	int armyAdd = 0;//for the total number of troops to add
	int ownedContinent = 0; //for the number of troops to add due to continent control
	int armyHand = 0;// for the number of troops to add due to exchanged cards.
	string answer; // for user input

	//Number of armies according to number of countries
	//add a minimum of 3 armies if less than 9 countries
	if ((countries.size()/3) < 3) {
		armyAdd += 3;
	}

	// divide number of countries by 3 for number of armies to add
	else {
		armyAdd += (countries.size()) / 3;
	}
	cout << " The number of troops added by the number of countries is " << armyAdd << "." << endl;

	// the number of continent controlled by player is added to the number of troops for reinforcement
	ownedContinent = map.controlContinent(countries);
	cout << " The number of troops added by the number of controled continents is " << ownedContinent << "." << endl;
	armyAdd += ownedContinent;

	// cards may be exchanged or forced exchange (if more than 5) for troops for reinforcement
	if (handNP.getCardsInHand(deck).size > 5) {
		cout << "Since there is more than 5 cards in your hand, you must exchange them." << endl;
		armyHand = handNP.exchange(deck, hand);
		armyAdd += armyHand;
	}
	else {
		cout << "Do you want to exchange your cards for extra reinforcement ? (y/n)" << endl;
		cin >> answer;

		if (answer == "y") {
			armyHand+= handNP.exchange(deck, hand);
			armyAdd += armyHand;
		}
		else {
			cout << "No cards are exchange." << endl;
		}

	}
	cout << " The number of troops added by exchanging cards is  " << armyHand << "." << endl;

	//Conclusion
	cout << "In total, " << armyAdd << " troops  can be added for reinforcement." << endl;
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
            if (getThisPlayerCountries().at(selectAttackFrom - 1)->getNumberOfArmies() < 2) {
                cout << "Please select a country with at least 2 armies placed on it." << endl;
                cin >> selectAttackFrom;
            }
        }

        // player attacks from the valid country they selected
        attackFrom = getThisPlayerCountries().at(selectAttackFrom - 1);

        cout << "You will be attacking from " << attackFrom->getCountryName() << " with " << attackFrom->getNumberOfArmies() << " armies.\n" << endl;

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
            if (attackFrom->getAdjacentCountries().at(selectCountryToAttack - 1)->getCountryOwnerId() == this->getID()) {
                cout << "Please select a country that is owned by another player." << endl;
                cin >> selectCountryToAttack;
            }
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

        cout << "Attacker (Player " << this->getID() << "), you will roll " << attackerRoll << " dice.\n" << endl;

        // defender chooses number of dice to roll
        defenderMaxNumOfDice = countryToAttack->getNumberOfArmies();
        if (defenderMaxNumOfDice > 2) {
            defenderMaxNumOfDice = 2;
        }

        cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), please select the number of dice to roll. You may only roll 1 to " << defenderMaxNumOfDice << " dice." << endl;
        cin >> defenderRoll;

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

        // roll defender's dice
        cout << "~ Defender is rolling ~" << endl;
        dice->setDiceToRoll(defenderRoll);
        dice->rollDice();
        cout << "\n" << endl;
        for (int i = 0; i < defenderRoll; i++) {
            defenderDiceValues.push_back(dice->getValuesRolled().at(i));
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
            cout << "~ Pair of dice comparison #" << (i + 1) << " ~\n" << endl;
            cout << "Attacker rolled a " << attackerDiceValues.at(i) << " and Defender rolled a " << defenderDiceValues.at(i) << ".\n" << endl;
            if (attackerDiceValues.at(i) == defenderDiceValues.at(i)) {
                cout << "Attacker's next highest dice and Defender's next highest dice are the same. Attacker lost this battle.\n" << endl;
                cout << "Attacker (Player " << this->getID() << "), you have lost 1 army in " << attackFrom->getCountryName() << ".\n" << endl;
                attackFrom->setNumberOfArmies(attackFrom->getNumberOfArmies() - 1); // attacker loses one army from their country
            }
            else if (defenderDiceValues.at(i) > attackerDiceValues.at(i)) {
                cout << "Attacker's next highest dice is lower than Defender's next highest dice. Attacker lost this battle.\n" << endl;

                cout << "Attacker (Player " << this->getID() << "), you have lost 1 army in " << attackFrom->getCountryName() << ".\n" << endl;
                attackFrom->setNumberOfArmies(attackFrom->getNumberOfArmies() - 1); // attacker loses one army from their country
            }
            else if (attackerDiceValues.at(i) > defenderDiceValues.at(i)) {
                cout << "Defender's next highest dice is lower than Defender's next highest dice. Defender lost this battle.\n" << endl;
                cout << "Defender (Player " << countryToAttack->getCountryOwnerId() << "), you have lost 1 army in " << countryToAttack->getCountryName() << ".\n" << endl;
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

    cout << "\n\n***** Fortification Phase *******" << endl;

    cout << "This is your country, its number of armies and its adjacent countries" << endl;

    for(int i = 0 ; i < getThisPlayerCountries().size(); i++) {
        cout << getThisPlayerCountries().at(i)->getCountryName() << " " << getThisPlayerCountries().at(i)->getNumberOfArmies();

        cout << " (";
        for(int j =0; j < getThisPlayerCountries().at(i)->getAdjacentCountries().size(); j++) {
            cout << getThisPlayerCountries().at(i)->getAdjacentCountries().at(j)->getCountryName() << " ";
        }
        cout << ") " << endl;
    }


    //check if there are countries adjacent to each other, if not, the player can't fortify
    //check if the country is a neighboring country of the source country
    string nameCountry;
    for(int i =0; i< this->getThisPlayerCountries().size(); i++) {

        for(int j = 0; j < this->getThisPlayerCountries().size(); j++) {

            nameCountry = getThisPlayerCountries().at(i)->getCountryName();

            for(int k = 0; k < this->getThisPlayerCountries().at(j)->getAdjacentCountries().size(); k++ ) {

                if(nameCountry.compare( this->getThisPlayerCountries().at(j)->getAdjacentCountries().at(k)->getCountryName() ) == 0) {
                    neighbourCountries = true;
                }
            }
        }

    }
    //if the player owns no neighbour countries, end the fortify
    if(neighbourCountries == false) {
        cout << "There are no neightbour countries. You cannot fortify" << endl;
    }

    //else fortify
    else {

        //Prompts the user for the source country
        cout << "\nPlease write the name of the chosen source country \n(capitalize the first letter)" << endl;

        cin >> nameSourceCountry;


        //check if the player owns the source country
        for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {
            if( nameSourceCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
                isSourceCountryValid = true;
                indexOfSourceCountry = i;
            }
        }

        //check if the country chosen has neighbours in the countries of the player

        for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {


            for(int j = 0; j < this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); j++) {


                //compare the adjacent countries of the source countries with the list of countries own by the player
                if((getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().at(j)->getCountryName()).compare(getThisPlayerCountries().at(i)->getCountryName()) == 0 ) {
                    sourceCountriesNeighbours = true;
                }


            }


        }


        //        cout << "source country neighbour " << std::boolalpha << sourceCountriesNeighbours << endl;

        //asks the player again to enter a valid source country if it was not valid
        while(isSourceCountryValid == false || sourceCountriesNeighbours == false) {
            cout << "\nThe source country you choose is not own by you or doesn't exists or doesn't have adjacent countries your own \nPlease choose a new source country" << endl;
            cout << "Please write the name of the chosen source country \n(capitalize the first letter)" << endl;

            cin >> nameSourceCountry;


            //check if the player owns the source country
            for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {
                if( nameSourceCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
                    isSourceCountryValid = true;
                    indexOfSourceCountry = i;
                }
            }

            //check if the country chosen has neighbours in the countries of the player

            for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {


                for(int j = 0; j < this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); j++) {


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


        //prompts the player again to enter a valid number of armies
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
        for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {
            if(nameTargetCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {

                // cout << "The country is own by the player" << endl;
                isTargetCountryValid = true;
                indexOfTargetCountry = i;
            }
        }


        //check if the country is a neighboring country of the source country
        for(int i =0; i< this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); i++) {
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
            for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {
                if(nameTargetCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
                    isTargetCountryValid = true;
                    indexOfTargetCountry = i;
                }
            }


            //check if the country is a neighboring country of the source country
            for(int i =0; i< this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); i++) {
                if(nameTargetCountry.compare(this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().at(i)->getCountryName()) == 0) {
                    isTargetCountryNeighbour =true;
                    // cout << "The country is a neighbour" << endl;
                }

            }

        }

        //set the new number of armies for the source country
        int numberOfArmiesSourceCountry = this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies();
        this->getThisPlayerCountries().at(indexOfSourceCountry)->setNumberOfArmies(numberOfArmiesSourceCountry - numOfArmies);

        //set the new number of armies for the target country
        int numberOfArmiesTargetCountry = this->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies();
        this->getThisPlayerCountries().at(indexOfTargetCountry)->setNumberOfArmies(numberOfArmiesTargetCountry + numOfArmies);


        //Display the new number of armies for source country and target country
        cout << "The player fortified succesfully the country: " << nameTargetCountry  << endl;
        cout << nameSourceCountry << " has now " << this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() << " armies"  << endl;
        cout << nameTargetCountry << " has now " << this->getThisPlayerCountries().at(indexOfTargetCountry)->getNumberOfArmies() << " armies"  << endl;

    }

}
