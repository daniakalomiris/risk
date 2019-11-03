#include <iostream>
#include <string>
#include "Cards.h"
#include "Player.h"
using namespace std;


int main() {

	Map* map = new Map();
	
    Country* country1 = new Country();
        Country* country2 = new Country();
        Country* country3 = new Country();
        Country* country4 = new Country();
        Country* country5 = new Country();
        Country* country6 = new Country();
        Country* country7 = new Country();
     Country* country8 = new Country();

            country1->setCountryName("Canada");
            country2->setCountryName("USA");
            country3->setCountryName("Mexico");
            country4->setCountryName("Italy");
            country5->setCountryName("France");
            country6->setCountryName("Japan");
            country7->setCountryName("China");
            country8->setCountryName("Denmark");

            map->setCountry(country1);
            map->setCountry(country2);
            map->setCountry(country3);
            map->setCountry(country4);
            map->setCountry(country5);
            map->setCountry(country6);
            map->setCountry(country7);
            map->setCountry(country8);

	//new deck based on number of countries in map (size of deck should be 3)
	Deck* deck = new Deck(map);

	// print the type of each card
	for (int i = 0; i < deck->getCardsInDeck().size(); i++) {
		cout << "Type of card " << i+1 << " is: " << deck->getCardsInDeck().at(i)->getType() << endl;
	}

	Player* player = new Player();
    player->setName("pako");
	// drawing from the deck and placing card in player's hand
	
    
    deck->draw(player->getHand(), player->getName());
      deck->draw(player->getHand(), player->getName());
      deck->draw(player->getHand(), player->getName());
        deck->draw(player->getHand(), player->getName());
    deck->draw(player->getHand(), player->getName());
    deck->draw(player->getHand(), player->getName());
    deck->draw(player->getHand(), player->getName());
    deck->draw(player->getHand(), player->getName());
    deck->draw(player->getHand(), player->getName());


    
    cout << "\nCards in deck now: " << endl;
    for (int i = 0; i < deck->getCardsInDeck().size(); i++) {
        cout << "Type of card " << i+1 << " is: " << deck->getCardsInDeck().at(i)->getType() << endl;
    }
    
    cout << "\nCards in hand of player Pako: " << endl;
    for (int i = 0; i < player->getHand()->getCardsInHand().size(); i++) {
        cout << "Type of card " << i+1 << " is: " << player->getHand()->getCardsInHand().at(i)->getType() << endl;
    }
	//player->getHand()->getCardsInHand(deck);

	// exchange in return of armies
	//player->getHand()->exchange(deck, player->getHand());
    
    
    delete map;
    delete country1;
    delete country2;
    delete country3;
    delete country4;
    delete country5;
    delete country6;
    delete country7;
    delete country8;
    delete deck;
    
}

