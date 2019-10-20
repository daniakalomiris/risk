#include <iostream>
#include <string>
#include "Cards.h"
#include "Player.h"
using namespace std;

/*
int main() {

	Map* map = new Map();
	
	Country* c1 = new Country();
	Country* c2 = new Country();
	Country* c3 = new Country();

	string c1Name = "Canada";
	c1->setCountryName(c1Name);

	string c2Name = "USA";
	c2->setCountryName(c2Name);

	string c3Name = "Mexico";
	c3->setCountryName(c3Name);

	map->setCountry(c1);
	map->setCountry(c2);
	map->setCountry(c3);


	//new deck based on number of countries in map (size of deck should be 3)
	Deck* deck = new Deck(map);

	// print the type of each card
	for (int i = 0; i < deck->getCardsInDeck().size(); i++) {
		cout << "Type of card " << deck->getCardsInDeck().at(i) << " is: " << deck->getCardsInDeck().at(i)->getType() << endl;
	}

	Player* player = new Player();

	// drawing from the deck and placing card in player's hand
	deck->draw(player->getID(), player->getHand(), deck);
	player->getHand()->getCardsInHand(deck);

	// exchange in return of armies
	player->getHand()->exchange(deck, player->getHand());
}
*/
