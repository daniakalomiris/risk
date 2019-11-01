//Driver class to test the player object
#include <iostream>
#include "Player.h"
#include "Map.h"
using namespace std;

<<<<<<< HEAD
//int main() {
//	
//	char answer;
//	string name;
//	cout << "Do you want to create a new player Y/N ? " << endl;
//	cin >> answer;
//	if (answer == 'Y') {
//		cout << "what is the players name ?" << endl;
//		cin >> name;
//		Player* player = new Player(name);
//		player->setName(name);
//
//		// COUNTRIES
//		Map* map = new Map();
//		Country* country1 = new Country();
//		Country* country2 = new Country();
//		Country* country3 = new Country();
//		Country* country4 = new Country();
//		Country* country5 = new Country();
//
//		country1->setCountryName("Canada");
//		country2->setCountryName("USA");
//		country3->setCountryName("France");
//		country4->setCountryName("Italy");
//		country5->setCountryName("Japan");
//        
//        country1->setNumberOfArmies(1);
//        country2->setNumberOfArmies(2);
//        country3->setNumberOfArmies(3);
//        country4->setNumberOfArmies(4);
//        country5->setNumberOfArmies(5);
//        
//        country1->setCountryOwnerId(player->getID());
//         country2->setCountryOwnerId(player->getID());
//         country3->setCountryOwnerId(player->getID());
//         country4->setCountryOwnerId(player->getID());
//         country5->setCountryOwnerId(player->getID());
//        
//        
//		map->setCountry(country1);
//		map->setCountry(country2);
//		map->setCountry(country3);
//		map->setCountry(country4);
//		map->setCountry(country5);
//
//		int playerID = player->getID();
//
//		country1->setCountryOwnerId(playerID);
//		country3->setCountryOwnerId(playerID); // stops here
//		country5->setCountryOwnerId(playerID);
//
//		map->getOwnerCountries(playerID);
//
//		delete map;
//
//		// HAND
//		Cards* card1 = new Cards(0, 1);
//		Cards* card2 = new Cards(1, 5);
//		Cards* card3 = new Cards(2, 10);
//		
//		Deck* deck = new Deck();
//		deck->setCardInDeck(card1);
//		deck->setCardInDeck(card2);
//		deck->setCardInDeck(card3);
//
//		 //add card2 to player's hand
//		player->getHand()->setCardInHand(card2);
//
//		 //print all cards in player's hand (should be card2)
//		player->getHand()->getCardsInHand(deck);
//
//		// DICE
//		player->getDice()->askRoll();
//		player->getDice()->rollDice();
//		player->getDice()->keepTracks();
//
//
//		// FORTIFY, ATTACK AND REINFORCE
//		player->fortify();
//		player->attack();
//		player->reinforce();
//	}
//	else {
//		cout << "Thank you for playing, Have a good day" << endl;
//	}
//	
//}
=======

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
        Country* country6 = new Country();
        Country* country7 = new Country();

		country1->setCountryName("Canada");
		country2->setCountryName("USA");
		country3->setCountryName("Mexico");
		country4->setCountryName("Italy");
		country5->setCountryName("France");
        country6->setCountryName("Japan");
        country7->setCountryName("China");
        
        
        country1->setAdjacentCountries(country2);
        country2->setAdjacentCountries(country1);
        country2->setAdjacentCountries(country3);
        country4->setAdjacentCountries(country5);
        country5->setAdjacentCountries(country4);
        country6->setAdjacentCountries(country7);
        country7->setAdjacentCountries(country6);
        
        
        
        
        country1->setNumberOfArmies(10);
        country2->setNumberOfArmies(5);
        country3->setNumberOfArmies(8);
        country4->setNumberOfArmies(4);
        country5->setNumberOfArmies(5);
          country6->setNumberOfArmies(3);
          country7->setNumberOfArmies(9);
        
        country1->setCountryOwnerId(player->getID());
        country2->setCountryOwnerId(player->getID());
        country3->setCountryOwnerId(player->getID());
        country4->setCountryOwnerId(player->getID());
        country5->setCountryOwnerId(player->getID());
         country6->setCountryOwnerId(player->getID());
         country7->setCountryOwnerId(player->getID());
        
        
		map->setCountry(country1);
		map->setCountry(country2);
		map->setCountry(country3);
		map->setCountry(country4);
		map->setCountry(country5);
        map->setCountry(country6);
        map->setCountry(country7);

		int playerID = player->getID();


		map->getOwnerCountries(playerID);
        
        
        player->setThisPlayerCountry(country1);
        player->setThisPlayerCountry(country2);
        player->setThisPlayerCountry(country3);
        player->setThisPlayerCountry(country4);
        player->setThisPlayerCountry(country5);
         player->setThisPlayerCountry(country6);
         player->setThisPlayerCountry(country7);
        
//        for(int i = 0; i <player->getThisPlayerCountries().size() ; i++) {
//            cout << player->getThisPlayerCountries().at(i)->getCountryName() << " " <<  player->getThisPlayerCountries().at(i)->getNumberOfArmies() <<    endl;
//        }
        
        
		delete map;

		// HAND
		Cards* card1 = new Cards(0, 1);
		Cards* card2 = new Cards(1, 5);
		Cards* card3 = new Cards(2, 10);
		
		Deck* deck = new Deck();
		deck->setCardInDeck(card1);
		deck->setCardInDeck(card2);
		deck->setCardInDeck(card3);

		 //add card2 to player's hand
		player->getHand()->setCardInHand(card2);

		 //print all cards in player's hand (should be card2)
		player->getHand()->getCardsInHand(deck);

		// DICE
		//player->getDice()->askRoll();
		//player->getDice()->rollDice();
		//player->getDice()->keepTracks();


		// FORTIFY, ATTACK AND REINFORCE
		player->fortify();
		player->attack();
		player->reinforce();
	}
	else {
		cout << "Thank you for playing, Have a good day" << endl;
	}
	
}
>>>>>>> dca3588b34152b4352c87f0e44a20441699da17d

