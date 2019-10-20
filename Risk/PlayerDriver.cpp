//Driver class to test the player object
#include <iostream>
#include "Player.h"
#include "Map.h"
using namespace std;


int main() {
	
	char answer;
	string name;
	cout << "Do you want to create a new player Y/N ? " << endl;
	cin >> answer;
	if (answer == 'Y') {
		cout << "what is the players name ?" << endl;
		cin >> name;
		Player* player = new Player(name);
		player->setName(name);

		// COUNTRIES
		Map* map = new Map();
		Country* country1 = new Country();
		Country* country2 = new Country();
		Country* country3 = new Country();
		Country* country4 = new Country();
		Country* country5 = new Country();

		country1->setCountryName("Canada");
		country2->setCountryName("USA");
		country3->setCountryName("France");
		country4->setCountryName("Italy");
		country5->setCountryName("Japan");

		map->setCountry(country1);
		map->setCountry(country2);
		map->setCountry(country3);
		map->setCountry(country4);
		map->setCountry(country5);

		int playerID = player->getID();

		country1->setCountryOwnerId(playerID);
		country3->setCountryOwnerId(playerID); // stops here
		country5->setCountryOwnerId(playerID);

		map->getOwnerCountries(playerID);

		delete map;

		// HAND
		//Cards* card1 = new Cards(0, 1);
		//Cards* card2 = new Cards(1, 5);
		//Cards* card3 = new Cards(2, 10);
		
		//Deck* deck = new Deck();
		//deck->setCardInDeck(card1);
		//deck->setCardInDeck(card2);
		//deck->setCardInDeck(card3);

		// add card2 to player's hand
		//player->getHand()->setCardInHand(card2);

		// print all cards in player's hand (should be card2)
		//player->getHand()->getCardsInHand(deck);

		// DICE
		player->getDice()->askRoll();
		player->getDice()->rollDice();
		player->getDice()->keepTracks();


		// FORTIFY, ATTACK AND REINFORCE
		player->fortify();
		player->attack();
		player->reinforce();
	}
	else {
		cout << "Thank you for playing, Have a good day" << endl;
	}
	
}
