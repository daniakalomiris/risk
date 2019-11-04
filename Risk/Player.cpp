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

int Player::getNumOfArmiesAtStartUpPhase() {
    return *numOfArmiesAtStartUpPhase;
}

void Player::setNumOfArmiesAtStartUpPhase(int num) {
    numOfArmiesAtStartUpPhase.reset(new int(num));
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
    bool isTargetCountryNeighbour = false;
    bool isNumOfArmiesValid = true;
    bool neighbourCountries = false;
 
    int numOfArmies = 0;
    int indexOfSourceCountry = 0;
    int indexOfTargetCountry = 0;

//    Country sourceCountry;
//    Country targetCountry;
    
    cout << "\n\n***** Fortification Phase *******" << endl;
    
    cout << "This is your country, its number of armies and its adjacent countries" << endl;
  
    for(int i = 0 ; i < getThisPlayerCountries().size(); i++) {
        cout << getThisPlayerCountries().at(i)->getCountryName() << " " << getThisPlayerCountries().at(i)->getNumberOfArmies();

        cout << " (";
        for(int j =0; j < getThisPlayerCountries().at(i)->getAdjacentCountries().size(); j++) {
            cout << getThisPlayerCountries().at(i)->getAdjacentCountries().at(j)->getCountryName() << ",";
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
           if(nameTargetCountry.compare(this->getThisPlayerCountries().at(i)->getCountryName()) == 0) {
               
               cout << "The country is own by the player" << endl;
               isTargetCountryValid = true;
               indexOfTargetCountry = i;
           }
       }
    
    
    //check if the country is a neighboring country of the source country
    for(int i =0; i< this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().size(); i++) {
        if(nameTargetCountry.compare(this->getThisPlayerCountries().at(indexOfSourceCountry)->getAdjacentCountries().at(i)->getCountryName()) == 0) {
            isTargetCountryNeighbour =true;
            cout << "The country is a neighbour" << endl;
        }
      
    }
    
    while(isTargetCountryValid == false && isTargetCountryNeighbour == false) {
           cout << "\nThe target country you choose is not own by you or doesn't exists or is not a neighbour of the source country \nPlease choose a valid country" << endl;
            cout << "Enter the name of a valid chosen target country" << endl;
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

}


