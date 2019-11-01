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
    for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {
        if( nameSourceCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
            isSourceCountryValid = true;
            indexOfSourceCountry = i;
        }
    }
    
    cout << "Please enter the number of armies you would like to move" << endl;
    cin >> numOfArmies;
    
    
    if(numOfArmies < 1 || numOfArmies > this->getThisPlayerCountries().at(indexOfSourceCountry)->getNumberOfArmies() -1 ) {
        isNumOfArmiesValid = false;
    }
    
    
    cout << "Please write the name of the chosen target country (capitalize the first letter)" << endl;
       cin >> nameTargetCountry;
    
    //check if the player owns the target country
       for(int i = 0; i < this->getThisPlayerCountries().size(); i++) {
           if( nameTargetCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
               isSourceCountryValid = true;
               indexOfSourceCountry = i;
           }
       }
    
    cout << "Is the source country valid? " <<  std::boolalpha << isSourceCountryValid << endl;
	    
    cout << "Is the source number of armies valid? " <<  std::boolalpha << isNumOfArmiesValid << endl;
    cout << "The player fortify" << endl;
    
    //i still need to check if the source is adjacent to the target
    //if the number of armies is valid, i need to decrement the number of armies in source and increment in target
    //loop everything until all values are good
}




