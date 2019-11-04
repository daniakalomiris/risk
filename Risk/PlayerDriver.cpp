//Driver class to test the player object
#include <iostream>
#include "Player.h"
#include "Map.h"
using namespace std;


int main() {
	
	char answer;
	string name;
    
    Map* map = new Map();
    Country* country1 = new Country();
    Country* country2 = new Country();
    Country* country3 = new Country();
    Country* country4 = new Country();
    Country* country5 = new Country();
    Country* country6 = new Country();
    Country* country7 = new Country();
    
    
	cout << "what is the Player 1's name ?" << endl;
	cin >> name;
	Player* player = new Player(name);
	player->setName(name);

	cout << "what is the Player 2's name ?" << endl;
	cin >> name;
	Player* player2 = new Player(name);
	player2->setName(name);

	// add countries to map
	map->setCountry(country1);
	map->setCountry(country2);
	map->setCountry(country3);
	map->setCountry(country4);
	map->setCountry(country5);
	map->setCountry(country6);
	map->setCountry(country7);

	// setting country names
	country1->setCountryName("Canada");
	country2->setCountryName("USA");
	country3->setCountryName("Mexico");
	country4->setCountryName("Italy");
	country5->setCountryName("France");
    country6->setCountryName("Japan");
    country7->setCountryName("China");
        
    // setting neighbor countries
    country1->setAdjacentCountries(country2);
	country1->setAdjacentCountries(country3);
    country2->setAdjacentCountries(country1);
	country2->setAdjacentCountries(country3);
    country3->setAdjacentCountries(country1);
	country3->setAdjacentCountries(country2);
    country4->setAdjacentCountries(country5);
	country4->setAdjacentCountries(country6);
    country5->setAdjacentCountries(country4);
	country5->setAdjacentCountries(country6);
	country5->setAdjacentCountries(country7);
    country6->setAdjacentCountries(country4);
	country6->setAdjacentCountries(country5);
    country7->setAdjacentCountries(country5);
        
	// setting number of armies on each country
    country1->setNumberOfArmies(10);
    country2->setNumberOfArmies(5);
    country3->setNumberOfArmies(8);
    country4->setNumberOfArmies(1);
    country5->setNumberOfArmies(5);
    country6->setNumberOfArmies(3);
    country7->setNumberOfArmies(0);
       
	// setting owners of each country 
	 
    country1->setCountryOwnerId(player->getID());
    country2->setCountryOwnerId(player->getID());
	country4->setCountryOwnerId(player->getID());
	country6->setCountryOwnerId(player->getID());
    country3->setCountryOwnerId(player2->getID());
    country5->setCountryOwnerId(player2->getID()); 
    country7->setCountryOwnerId(player2->getID());
	player->setThisPlayerCountry(country1);
	player->setThisPlayerCountry(country2);
	player->setThisPlayerCountry(country4);
	player->setThisPlayerCountry(country6);
	player2->setThisPlayerCountry(country3);
	player2->setThisPlayerCountry(country5);
	player2->setThisPlayerCountry(country7);
 
       
	// initializing attack phase
	player->attack();

	// HAND
	//Cards* card1 = new Cards(0, 1);
	//Cards* card2 = new Cards(1, 5);
	//Cards* card3 = new Cards(2, 10);
	//	
	//Deck* deck = new Deck();
	//deck->setCardInDeck(card1);
	//deck->setCardInDeck(card2);
	//deck->setCardInDeck(card3);

	//add card2 to player's hand
	//player->getHand()->setCardInHand(card2);

	//print all cards in player's hand (should be card2)
	/*player->getHand()->getCardsInHand(deck);*/

	// DICE
	// player->getDice()->askRoll();
	/*player->getDice()->rollDice();
	player->getDice()->keepTracks();*/
    
    delete country1;
	country1 = NULL;
    delete country2;
	country2 = NULL;
    delete country3;
	country3 = NULL;
    delete country4;
	country4 = NULL;
    delete country5;
	country5 = NULL;
    delete country6;
	country6 = NULL;
    delete country7;
	country7 = NULL;
    delete map;
	map = NULL;
	delete player;
	player = NULL;
	delete player2;
	player2 = NULL;
}

