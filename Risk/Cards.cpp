#include "Cards.h"
#include "Map.h"
#include <iostream>
#include <memory>
#include <vector>
#include <time.h>
#include <string> 


using namespace std;

Cards::Cards(int typeNum, int worth) {
	this->typeNum = make_unique<int>(typeNum);
	this->worth = make_unique<int>(worth);
	this->locationId = -1; // when card is created, it is initially put in the deck
};

Cards::Cards() {
	this->locationId = -1;
};



Cards::~Cards() {

}

void Cards::setWorth(int worth) {
    this->worth = make_unique<int>(worth);
}
int Cards::getWorth() {
    return *worth;
}

// -1 for cards in deck, otherwise it corresponds to the player's id if it's in their hand
int Cards::getLocationId() {
    return locationId;
}

//sets location of the card based on the player who has drawn the card
void Cards::setLocationId(int locationId) {
    this->locationId = locationId;
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
		card->setLocationId(-1); // -1 for cards in deck
		setCardInDeck(card);
	}

	for (int i = 0; i < *cardsPerType; i++) {
		Cards* card = new Cards();
		card->setType(1);
		card->setWorth(5);
		card->setLocationId(-1);
		setCardInDeck(card);
	}

	for (int i = 0; i < *cardsPerType; i++) {
		Cards* card = new Cards();
		card->setType(2);
		card->setWorth(10);
		card->setLocationId(-1);
		setCardInDeck(card);
	}
    
    if(numCountriesDivisible3 == false) {
      
        
        for(int i = 0; i < remainder; i++) {
        Cards* card = new Cards();
        card->setType(i);
        card->setLocationId(-1);
            
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
    
    
    if(cardsInDeck.size() == 0) {
        cout << "No more cards in the deck. The player can't draw" << endl;
    }
    
    else {
    
    cout << "\nPlayer " << playerName << " draw a card" << endl;
	Cards* cardDrawn;
    int temp;
	
    srand(time(NULL)); // randomize
    temp = rand() % (*numOfCardsInDeck);
    cardDrawn = cardsInDeck.at(temp);
    
    
    //remove the card in deck
    this->cardsInDeck.erase(cardsInDeck.begin() + temp);
    *numOfCardsInDeck = *numOfCardsInDeck - 1;
	hand->setCardInHand(cardDrawn);
    }
    
    //cout << "num of cards in deck " << *numOfCardsInDeck << endl;
}

//method to exchange cards
void Hand::exchange(Deck* deck, Hand* hand) {

	//number of each type of cards
	int infantry = 0;
	int artillery = 0;
	int cavalry = 0;

	//number of cards of each type that are exchanged
	int infantryExchanged = 0;
	int artilleryExchanged = 0;
	int cavalryExchanged = 0;

	for (unsigned int i = 0; i < deck->getCardsInDeck().size(); i++) {
		if (deck->getCardsInDeck().at(i)->getLocationId() == hand->id) { // get all cards in this hand
			if ((deck->getCardsInDeck().at(i)->getType()).compare("Infantry") == 0) { //checks if of type of infantry
				infantry++;
			}
			else if ((deck->getCardsInDeck().at(i)->getType()).compare("Artillery") == 0) { //checks if of type artillery
				artillery++;
			}
			else if ((deck->getCardsInDeck().at(i)->getType()).compare("Cavalry") == 0) { //checks if of type cavalry
				cavalry++;
			}
		}
	}

	//worth of armies depends on the number of cards in the hand
	if (infantry >= 3) {
		for (unsigned int i = 0; i < deck->getCardsInDeck().size() && infantryExchanged < 3; i++) { // remove 3 infantry cards from hand
			if (deck->getCardsInDeck().at(i)->getLocationId() == hand->id) {
				if ((deck->getCardsInDeck().at(i)->getType()).compare("Infantry") == 0) {
					deck->getCardsInDeck().at(i)->setLocationId(-1); // put card back in deck
					infantryExchanged++; // increment the number of infantry cards we have exchanged
				}
			}
		}
		*exchangeCount++;
		*armiesExchanged += 5; //increments by 5 at each exchange
		cout << "Number of exchanges made so far: " << *exchangeCount << endl;
		cout << "You have exchanged 3 Infantry cards for " << *armiesExchanged << " armies" << endl;
	}

	else if (artillery >= 3) { //if number of artillery type cards if greater or equal than 3
		for (unsigned int i = 0; i < deck->getCardsInDeck().size() && artilleryExchanged < 3; i++) {
			if (deck->getCardsInDeck().at(i)->getLocationId() == hand->id) {
				if ((deck->getCardsInDeck().at(i)->getType()).compare("Artillery") == 0) {
					deck->getCardsInDeck().at(i)->setLocationId(-1);
					artilleryExchanged++;
				}
			}
		}
		*exchangeCount++;
		*armiesExchanged += 5; //increments by 5 at each exchange
		cout << "Number of exchanges made so far: " << *exchangeCount << endl;
		cout << "You have exchanged 3 Artillery cards for " << *armiesExchanged << " armies" << endl;
	}

	else if (cavalry >= 3) {
		for (unsigned int i = 0; i < deck->getCardsInDeck().size() && cavalryExchanged < 3; i++) {
			if (deck->getCardsInDeck().at(i)->getLocationId() == hand->id) {
				if ((deck->getCardsInDeck().at(i)->getType()).compare("Cavalry") == 0) {
					deck->getCardsInDeck().at(i)->setLocationId(-1);
					cavalryExchanged++;
				}
			}
		}
		*exchangeCount++;
		*armiesExchanged += 5;
		cout << "Number of exchanges made so far: " << *exchangeCount << endl;
		cout << "You have exchanged 3 Cavalry cards for " << *armiesExchanged << " armies" << endl;

	}
	else if (infantry > 1 || artillery > 1 || cavalry > 1) {
		for (unsigned int i = 0; i < deck->getCardsInDeck().size() && infantryExchanged < 1 && artilleryExchanged < 1 && cavalryExchanged < 1; i++) {
			if (deck->getCardsInDeck().at(i)->getLocationId() == hand->id) {
				if ((deck->getCardsInDeck().at(i)->getType()).compare("Infantry") == 0) {
					deck->getCardsInDeck().at(i)->setLocationId(-1);
					infantryExchanged++;
				}
				else if ((deck->getCardsInDeck().at(i)->getType()).compare("Artillery") == 0) {
					deck->getCardsInDeck().at(i)->setLocationId(-1);
					artilleryExchanged++;
				}
				else if ((deck->getCardsInDeck().at(i)->getType()).compare("Cavalry") == 0) {
					deck->getCardsInDeck().at(i)->setLocationId(-1);
					cavalryExchanged++;
				}
			}
		}
		*exchangeCount++;
		*armiesExchanged += 5;
		cout << "Number of exchanges made so far: " << *exchangeCount << endl;
		cout << "You have exchanged " << infantryExchanged << " infantry cards, " << artilleryExchanged << " artillery cards and " << cavalryExchanged << " cavalry cards for " << *armiesExchanged << " armies" << endl;
	}
	else {
		cout << "You can not exchange any cards from your hand." << endl;
	}
	*numOfArmies += *armiesExchanged;
}



Hand::Hand() {
    delete numOfArmies;
    delete armiesExchanged;
    delete exchangeCount;
}

// Takes player's id
Hand::Hand(int id) {
	this->id = id;
    numOfArmies = new int(0);
	armiesExchanged = new int(0);
	exchangeCount = new int(0);
}

Hand::~Hand() {
    delete exchangeCount;
}

void Hand:: setCardInHand(Cards* card) {
    cardsInHand.push_back(card);
}

vector<Cards*> Hand:: getCardsInHand() {
    return cardsInHand;
}

//returns number of armies 
int Hand::getNumOfArmies() {
	return *numOfArmies;
}

//sets number of armies 
void Hand::setNumOfArmies(int numOfArmies) {
	*this->numOfArmies = numOfArmies;
}
