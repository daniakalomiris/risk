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

vector<Country*> Player::getThisPlayerCountries() {
	return countries;
}

void Player::setThisPlayerCountry(Country* country) {
	countries.push_back(country);
}

int Player::controlContinent(vector<Country*> country) {
	int countryinContient = 0;
	int numContinent = 0; 
	for (int i = 0; i < getContinents().size(); i++) {
		for (int j = 0; j < getCountries.size(); j++) {
			for (int k = 0; k < getOwnerCountries(getID).size(); k++) {
				if (getCountries.at(j) == getcountries.at(k)) { //NEED TO CREATE = OPERATOR TO COMPARE OBJECTS 
					countryinContient += 1
						break;
				}
				else {
					continue;
				}
			}

			if (countryinContient = getCountries.size()) {
				numContinent += 1;
			}
		}
	}
	
	return numContinent;
}
/*
bool Map::equalCountries( vector<Country&> left, vector<Country&> right) {
	bool same = false;
	for (int i = 0, i < left.size(); i++) {
		if (left.at(i)== right.at(i)){
		return true }
		else {
		break;
		}
	}
	return same;
}
*/

//extra methods , reinforce, attack and fortify, will be implemented in next iteration
void Player::reinforce() {

	//for the total number of troops to add
	int armyAdd = 0;
	//for the number of troops to add due to continent control 
	int numContinent = 0; 
	// for the number of troops to add due to exchanged cards.
	int armyHand = 0;

	//Number of armies according to number of countries 
	//Min of 3 armies if less than 3 countries.
	if (getOwnerCountries(getID()).size() < 3) { 
		armyadd += 3;
	}
	// divide number of countries by 3 for number of armies to add
	else {
		armyAdd += (getOwnerCountries(getID()).size())/3
	}
	cout << " The number of troops added by the number of countries is " << armyAdd << "." << endl;

	// the number of continent controlled by player is added to the number of troops for reinforcement 
	numContinent = controlContinent(getOwnerCountries(getID()));
	cout << " The number of troops added by the number of controled continents is " << numContinent << "." << endl;
	armyAdd += numContinent;

	// cards may be exchanged or forced exchange (if more than 5) for troops for reinforcement 
	if (getCardsInHand().size > 5) {
		cout << "Since there is more than 5 cards in your hand, you must exchange them." << endl;
		armyHand = exchangeHand(deck, this->hand);
		armyAdd += armyHand;
	}
	else {
		cout << "Do you want to exchange your cards for extra reinforcement ? (y/n)" << endl;
		cin >> string answer;

		if (answer == "y") {
			armyHand+= exchangeHand(deck, this->hand);
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

//attack method
void Player::attack() {
	cout << "The player attacks" << endl;
}

//fortify method
void Player::fortify() {
	string nameSourceCountry;
	string nameTargetCountry;
	bool isSourceCountryValid = false;
	bool isTargetCountryValid = false;
	bool isNumOfArmiesValid = true;


	int numOfArmies;
	int indexOfSourceCountry;

	Country sourceCountry;
	Country targetCountry;

	cout << "Please write the name of the chosen source country (capitalize the first letter)" << endl;
	cin >> nameSourceCountry;


	//check if the player owns the source country
	for (int i = 0; i < this->getThisPlayerCountries().size(); i++) {
		if (nameSourceCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
			isSourceCountryValid = true;
			indexOfSourceCountry = i;
		}
	}

	cout << "Please enter the number of armies you would like to move" << endl;
	cin >> numOfArmies;


	if (numOfArmies < 1 || numOfArmies > this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() - 1) {
		isNumOfArmiesValid = false;
	}


	cout << "Please write the name of the chosen target country (capitalize the first letter)" << endl;
	cin >> nameTargetCountry;

	//check if the player owns the target country
	for (int i = 0; i < this->getThisPlayerCountries().size(); i++) {
		if (nameTargetCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
			isSourceCountryValid = true;
			indexOfSourceCountry = i;
		}
	}

	cout << "Is the source country valid? " << std::boolalpha << isSourceCountryValid << endl;

	cout << "Is the source number of armies valid? " << std::boolalpha << isNumOfArmiesValid << endl;
	cout << "The player fortify" << endl;

	//i still need to check if the source is adjacent to the target
	//if the number of armies is valid, i need to decrement the number of armies in source and increment in target
	//loop everything until all values are good
}
