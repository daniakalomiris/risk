#include "Cards.h"
#include "Map.h"
#include <iostream>
#include <memory>
#include <vector>
#include <time.h>
#include <string> 


using namespace std;

//constructor with parameters
Cards::Cards(int typeNum, int worth) {
    this->typeNum = make_unique<int>(typeNum);
    this->worth = make_unique<int>(worth);
};

//default constructor
Cards::Cards() {
   
};

Cards::~Cards() {
    
}

void Cards::setWorth(int worth) {
    this->worth = make_unique<int>(worth);
}
int Cards::getWorth() {
    return *worth;
}


//sets the type of the card
void Cards::setType(int typeNum) {
    if (typeNum == 0) {
        type = make_unique<string>("Infantry");
    }
    else if (typeNum == 1) {
        type = make_unique<string>("Cavalry");
    }
    else if (typeNum == 2) {
        type = make_unique<string>("Artillery");
    }
}

//gets the type of the card
std::string Cards::getType() {
    return *type;
}

Deck::Deck() {
    
}

//constructor of the deck
Deck::Deck(Map* map) {
    
    cout << "\nInitializing Deck" << endl;
    
    //gets the number of cards from the countries
    vector<Country*> temp;
    temp = map->getCountries();
    int numCountries = temp.size();
    int remainder;
    bool numCountriesDivisible3 = true;
    numOfCardsInDeck = make_unique<int>(numCountries);
    
    
    //check if number of countries is divisible by 3
    if( (numCountries % 3) != 0) {
        numCountriesDivisible3 = false;
        remainder = *numOfCardsInDeck % 3;
    }
    
    //equal amount of cards per type
    cardsPerType = make_unique<int>(*numOfCardsInDeck / 3);
    
    cout << "There are a total of " << numCountries << " countries in the map." << endl;
    cout << "There will be " << *numOfCardsInDeck << " cards in the deck." << endl;
    cout << "There will be " << *cardsPerType << " cards per type." << endl;
    
    
    //creates card objects of type infantry, sets worth to 1, sets location, pushes card to deck (based on the number of countries/3)
    for (int i = 0; i < *cardsPerType; i++) {
        Cards* card = new Cards();
        card->setType(0);
        card->setWorth(1);
        setCardInDeck(card);
    }
    
    for (int i = 0; i < *cardsPerType; i++) {
        Cards* card = new Cards();
        card->setType(1);
        card->setWorth(5);
        setCardInDeck(card);
    }
    
    for (int i = 0; i < *cardsPerType; i++) {
        Cards* card = new Cards();
        card->setType(2);
        card->setWorth(10);
        setCardInDeck(card);
    }
    
    //if the number of countries is not divisible by 3, create the remaining cards with its type. We won't have the same amount of types.
    if(numCountriesDivisible3 == false) {
        
        for(int i = 0; i < remainder; i++) {
            Cards* card = new Cards();
            card->setType(i);
            
            if(i == 0) {
                card->setWorth(1);
            }
            
            if(i == 1) {
                card->setWorth(5);
            }
            
            setCardInDeck(card);
        }
    }
}

Deck::~Deck() {
    
}

//returns number of cards in the deck
int Deck::getNumOfCardsInDeck() {
    return *numOfCardsInDeck;
}

//returns vectors of cards in the deck
vector<Cards*> Deck::getCardsInDeck() {
    return cardsInDeck;
}

//adds card object to deck
void Deck::setCardInDeck(Cards* card) {
    //cout << "Adding card to deck." << endl;
    cardsInDeck.push_back(card);
}

//random card will be drawn from the deck
void Deck::draw(Hand* hand, string playerName) {
    
    //if the deck is empty
    if(cardsInDeck.size() == 0) {
        cout << "No more cards in the deck. The player can't draw" << endl;
    }
    
    else {
        
        cout << "\nPlayer " << playerName << " draw a card" << endl;
        Cards* cardDrawn;
        int temp;
        
        //choose a random card to draw
        srand(time(NULL)); // randomize
        temp = rand() % (*numOfCardsInDeck);
        cardDrawn = cardsInDeck.at(temp);
        
        
        //remove the card in deck, decrease the amount of card in deck, add the card to the hand
        this->cardsInDeck.erase(cardsInDeck.begin() + temp);
        *numOfCardsInDeck = *numOfCardsInDeck - 1;
        hand->setCardInHand(cardDrawn);
    }
}

void Hand::removeCard(int i) {
    this->cardsInHand.erase(cardsInHand.begin() + i);
}

//method to exchange cards
void Hand::exchange(Hand* hand) {
    
    //number of each type of cards
    int infantry = 0;
    int artillery = 0;
    int cavalry = 0;
    
    //number of cards of each type that are exchanged
    int infantryExchanged = 0;
    int artilleryExchanged = 0;
    int cavalryExchanged = 0;
    
    
    bool canExchange = false;
   
    //check the amount of cards of each type
    for (int i = 0; i < hand->getCardsInHand().size(); i++) {
        
        if ((hand->getCardsInHand().at(i)->getType()).compare("Infantry") == 0) { //checks if of type of infantry
            infantry++;
        }
        else if ((hand->getCardsInHand().at(i)->getType()).compare("Artillery") == 0) { //checks if of type artillery
            artillery++;
        }
        else if ((hand->getCardsInHand().at(i)->getType()).compare("Cavalry") == 0) { //checks if of type cavalry
            cavalry++;
        }
        
    }
    
    //if we have more than 3 cards of the same type, display that the player can exchange
    if(infantry >= 3 || artillery >= 3 || cavalry >= 3) {
        cout << "\n\nYou have at least a set of card you can exchange" << endl;
        
        if(infantry >=3) {
           // cout << "You have at a set of 3 infantry cards do you want to exchange it ?" << endl;
            
        }
        
        canExchange = true;
    }
    
    else if(infantry > 1 && artillery > 1 && cavalry > 1) {
        cout << "\n\nYou have at least a set of card you can exchange" << endl;
        canExchange = true;
    }
    
    //if we have at leat 3 cards of type infantry, exchange 3 cards
    if (infantry >= 3) {
        
        while(infantryExchanged < 3) {
            for (int i = 0; i < hand->getCardsInHand().size(); i++) { // remove 3 infantry cards from hand
                
                if ((hand->getCardsInHand().at(i)->getType()).compare("Infantry") == 0) {
                    
                    hand->removeCard(i);
                    infantryExchanged++; // increment the number of infantry cards we have exchanged
                }
            }
        }
        
        
        *exchangeCount = *exchangeCount +1;
        numArmiesExchanged += 5; //increments by 5 at each exchange
        this->addNumberOfArmies(numArmiesExchanged);
        cout << "Number of exchanges made so far: " << *exchangeCount << endl;
        cout << "You have exchanged 3 Infantry cards for " << numArmiesExchanged << " armies" << endl;
    }
    
    //if we have at leat 3 cards of type artillery, exchange 3 cards
    else if (artillery >= 3) { //if number of artillery type cards if greater or equal than 3
        
        while(artilleryExchanged < 3) {
            for (unsigned int i = 0; i < hand->getCardsInHand().size(); i++) {
                
                if ((hand->getCardsInHand().at(i)->getType()).compare("Artillery") == 0) {
                    hand->removeCard(i);
                    artilleryExchanged++;
                }
            }
        }
        *exchangeCount = *exchangeCount +1;
        numArmiesExchanged += 5; //increments by 5 at each exchange
        this->addNumberOfArmies(numArmiesExchanged);
        cout << "Number of exchanges made so far: " << *exchangeCount << endl;
        cout << "You have exchanged 3 Artillery cards for " << numArmiesExchanged << " armies" << endl;
    }
    
    //if we have at leat 3 cards of type cavalry, exchange 3 cards
    else if (cavalry >= 3) {
        while(cavalryExchanged < 3) {
            for (unsigned int i = 0; i < hand->getCardsInHand().size(); i++) {
                
                if ((hand->getCardsInHand().at(i)->getType()).compare("Cavalry") == 0) {
                    hand->removeCard(i);
                    cavalryExchanged++;
                }
            }
        }
        *exchangeCount = *exchangeCount +1;
        numArmiesExchanged += 5;
        this->addNumberOfArmies(numArmiesExchanged);
        cout << "Number of exchanges made so far: " << *exchangeCount << endl;
        cout << "You have exchanged 3 Cavalry cards for " << numArmiesExchanged << " armies" << endl;
        
    }
    
    //if we have at leat 1 card of each type. Exchange the set.
    else if (infantry >= 1 && artillery >= 1 && cavalry >= 1) {
        int i =0;
        bool allCardsFound = false;
        while(!allCardsFound) {
            
            for (int i = hand->getCardsInHand().size()-1; i >= 0; i--) {
                
                if ((hand->getCardsInHand().at(i)->getType()).compare("Infantry") == 0 && infantryExchanged != 1) {
                    hand->removeCard(i);
                    // cout << "remove infantry at " << i << endl;
                    infantryExchanged++;
                    i = 0;
                }
                else if ((hand->getCardsInHand().at(i)->getType()).compare("Artillery") == 0 && artilleryExchanged != 1) {
                    hand->removeCard(i);
                    // cout << "remove artillery at " << i << endl;
                    artilleryExchanged++;
                    i = 0;
                }
                else if ((hand->getCardsInHand().at(i)->getType()).compare("Cavalry") == 0 && cavalryExchanged != 1) {
                    hand->removeCard(i);
                    // cout << "remove cavalry at " << i << endl;
                    cavalryExchanged++;
                    i = 0;
                }
            }
            
            if(infantryExchanged == 1 && artilleryExchanged == 1 && cavalryExchanged == 1) {
                allCardsFound = true;
            }
        }
        *exchangeCount = *exchangeCount +1;
        numArmiesExchanged += 5;
        this->addNumberOfArmies(numArmiesExchanged);
        cout << "Number of exchanges made so far: " << *exchangeCount << endl;
        cout << "You have exchanged " << infantryExchanged << " infantry cards, " << artilleryExchanged << " artillery cards and " << cavalryExchanged << " cavalry cards for " << numArmiesExchanged << " armies" << endl;
    }
    else {
        cout << "You can not exchange any cards from your hand." << endl;
    }
    
    
}

void Hand:: addNumberOfArmies(int number) {
    *numOfArmiesToPlace = *numOfArmiesToPlace + number;
    
}

void Hand:: deleteNumberOfArmies(int number) {
    *numOfArmiesToPlace = *numOfArmiesToPlace - number;
}

Hand::Hand() {
    
}

// Takes player's id
Hand::Hand(int id) {
    this->id = id;
    numOfArmiesToPlace = make_unique<int>(0);
    
}

Hand::~Hand() {
    
}

int Hand:: numArmiesExchanged = 0;
int* Hand:: exchangeCount = new int(0);
void Hand:: setCardInHand(Cards* card) {
    cardsInHand.push_back(card);
}

vector<Cards*> Hand:: getCardsInHand() {
    return cardsInHand;
}


int Hand:: getNumberOfArmiesToPlace() {
    return *numOfArmiesToPlace;
}

void Hand:: setNumberOfArmiesToPlace(int num) {
    numOfArmiesToPlace = make_unique<int>(num);
}
