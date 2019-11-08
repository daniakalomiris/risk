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
    setType(typeNum);

};

//default constructor
Cards::Cards() {

};

// copy constructor
//Cards::Cards(const Cards & cards) {
//    cout << "Copy constructor called" << endl;
//    this->typeNum = make_unique<int>(cards.typeNum);
//    this->worth = make_unique<int>(cards.worth);
//}

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
void Hand::exchange() {

    //number of each type of cards
    int infantry;
    int artillery;
    int cavalry;

    //number of cards of each type that are exchanged
    int infantryExchanged;
    int artilleryExchanged;
    int cavalryExchanged;

    //tells if player wants to exchange cards or not
    bool exchangeOneOfEach;
    bool exchangeInfantry;
    bool exchangeCavalry;
    bool exchangeArtillery;
    bool exchangeAgain = true;
    
    while(exchangeAgain) {
        
        //resets all data
        infantry =0;
        artillery =0;
        cavalry = 0;
        exchangeOneOfEach = false;
        exchangeInfantry = false;
        exchangeArtillery = false;
        exchangeCavalry = false;
        infantryExchanged =0;
        artilleryExchanged = 0;
        cavalryExchanged =0;
        
    //check the amount of cards of each type
    for (int i = 0; i < this->getCardsInHand().size(); i++) {

        if (( this->getCardsInHand().at(i)->getType()).compare("Infantry") == 0) { //checks if of type of infantry
            infantry++;
        }
        else if ((this->getCardsInHand().at(i)->getType()).compare("Artillery") == 0) { //checks if of type artillery
            artillery++;
        }
        else if ((this->getCardsInHand().at(i)->getType()).compare("Cavalry") == 0) { //checks if of type cavalry
            cavalry++;
        }
    }
    
    
    //Prints the card in the hand of the player
    cout << "\n\nThese are the cards in your hand and their types" << endl;
    for (int i = 0; i < this->getCardsInHand().size(); i++) {
          cout << "Type of card " << i+1 << " is: " << this->getCardsInHand().at(i)->getType() << endl;
      }

    //if we have more than 3 cards of the same type, display that the player can exchange
    if(infantry >= 3 || artillery >= 3 || cavalry >= 3) {
        cout << "\n\nYou can exchange some cards" << endl;
        
        //if the player has more than 3 infantry cards, ask the player if he wants to exchange them
        if(infantry >=3) {
            cout << "You have at least a set of 3 infantry cards, do you want to exchange it? (y/n)" << endl;
            string answer;
            cin >> answer;
            
            if(answer.compare("y") == 0) {
                exchangeInfantry = true;
            }
        }
        
        //if the player has more than 3 cavalry cards, ask the player if he wants to exchange them
        else if(cavalry >=3) {
            cout << "You have at least a set of 3 cavalry cards, do you want to exchange it? (y/n)" << endl;
            string answer;
            cin >> answer;
            
            if(answer.compare("y") == 0) {
                exchangeCavalry = true;
            }

        }
        
        //if the player has more than 3 artillery cards, ask the player if he wants to exchange them
        else if(artillery >=3) {
                  cout << "You have at least a set of 3 artillery cards, do you want to exchange it? (y/n)" << endl;
                string answer;
                cin >> answer;
                
                if(answer.compare("y") == 0) {
                    exchangeArtillery = true;
                }
              }
    }

    //if the player has at least 1 card of each type, ask the player if he wants to exchange them
    else if(infantry >= 1 && artillery >= 1 && cavalry >= 1) {
        cout << "\n\nYou can exchange some cards" << endl;
        cout << "You have at least a set of 1 card of each type, do you want to exchange the it? (y/n)" << endl;
           string answer;
                     cin >> answer;
                     
                     if(answer.compare("y") == 0) {
                         exchangeOneOfEach = true;
                     }
                   }
   else {
       cout << "You cannot exchange any cards from your hand" << endl;
       exchangeAgain = false;
   }
    

    //if we have at leat 3 cards of type infantry and the player wants to exchange, exchange 3 cards
    if (exchangeInfantry) {

        while(infantryExchanged < 3) {
            for (int i = 0; i < this->getCardsInHand().size(); i++) { // remove 3 infantry cards from hand

                if ((this->getCardsInHand().at(i)->getType()).compare("Infantry") == 0) {

                    this->removeCard(i);
                    infantryExchanged++; // increment the number of infantry cards we have exchanged
                     
                }
            }
        }

        *exchangeCount = *exchangeCount +1;
        numArmiesExchanged += 5; //increments by 5 at each exchange
        this->addNumberOfArmies(numArmiesExchanged);
        cout << "Number of exchanges made so far: " << *exchangeCount << endl;
        cout << "You have exchanged 3 Infantry cards for " << numArmiesExchanged << " armies" << endl;
        infantry = infantry -3;
    }

    //if we have at leat 3 cards of type artillery and the player wants to exchange, exchange 3 cards
    else if (exchangeArtillery) { //if number of artillery type cards if greater or equal than 3

        while(artilleryExchanged < 3) {
            for (unsigned int i = 0; i < this->getCardsInHand().size(); i++) {

                if ((this->getCardsInHand().at(i)->getType()).compare("Artillery") == 0) {
                    this->removeCard(i);
                    artilleryExchanged++;
                }
            }
        }
        *exchangeCount = *exchangeCount +1;
        numArmiesExchanged += 5; //increments by 5 at each exchange
        this->addNumberOfArmies(numArmiesExchanged);
        cout << "Number of exchanges made so far: " << *exchangeCount << endl;
        cout << "You have exchanged 3 Artillery cards for " << numArmiesExchanged << " armies" << endl;
        artillery = artillery -3;
    }

    //if we have at leat 3 cards of type cavalry and the player wants to exchange, exchange 3 cards
    else if (exchangeCavalry) {
        while(cavalryExchanged < 3) {
            for (unsigned int i = 0; i < this->getCardsInHand().size(); i++) {

                if ((this->getCardsInHand().at(i)->getType()).compare("Cavalry") == 0) {
                    this->removeCard(i);
                    cavalryExchanged++;
                    
                }
            }
        }
       
        *exchangeCount = *exchangeCount +1;
        numArmiesExchanged += 5;
        this->addNumberOfArmies(numArmiesExchanged);
        cout << "Number of exchanges made so far: " << *exchangeCount << endl;
        cout << "You have exchanged 3 Cavalry cards for " << numArmiesExchanged << " armies" << endl;
        cavalry = cavalry - 3;

    }

    //if we have at leat 1 card of each type and the player wants to exchange. Exchange the set.
    else if (exchangeOneOfEach) {
        int i =0;
        bool allCardsFound = false;
        while(!allCardsFound) {

            for (int i = this->getCardsInHand().size()-1; i >= 0; i--) {

                if ((this->getCardsInHand().at(i)->getType()).compare("Infantry") == 0 && infantryExchanged != 1) {
                    this->removeCard(i);
                    infantryExchanged++;
                    i = 0;
                }
                else if ((this->getCardsInHand().at(i)->getType()).compare("Artillery") == 0 && artilleryExchanged != 1) {
                    this->removeCard(i);
                    artilleryExchanged++;
                    i = 0;
                }
                else if ((this->getCardsInHand().at(i)->getType()).compare("Cavalry") == 0 && cavalryExchanged != 1) {
                    this->removeCard(i);
                    cavalryExchanged++;
                    i = 0;
                }
            }

            if(infantryExchanged == 1 && artilleryExchanged == 1 && cavalryExchanged == 1) {
                allCardsFound = true;
            }
        }
        cavalry --;
        artillery --;
        infantry --;
        *exchangeCount = *exchangeCount +1;
        numArmiesExchanged += 5;
        this->addNumberOfArmies(numArmiesExchanged);
        cout << "Number of exchanges made so far: " << *exchangeCount << endl;
        cout << "You have exchanged " << infantryExchanged << " infantry card, " << artilleryExchanged << " artillery card and " << cavalryExchanged << " cavalry card for " << numArmiesExchanged << " armies" << endl;
    }
    else {
       // cout << "You didn't exchange any cards from your hand." << endl;
        exchangeAgain = false;
    }
        
        if(infantry >=3 || artillery >=3 || cavalry >=3) {
            cout << "You can exchange more cards. Do you want to do it? (y/n)" << endl;
                       string answer;
                      cin >> answer;
                      
                      if(answer.compare("y") != 0) {
                          exchangeAgain= false;
                      }

        }
        
        else if(infantry == 1 && artillery == 1 && cavalry == 1) {
            cout << "You can exchange more cards. Do you want to do it? (y/n)" << endl;
                                  string answer;
                                 cin >> answer;
                                 
                                 if(answer.compare("y") != 0) {
                                     exchangeAgain= false;
                                 }
        }
        
        
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
