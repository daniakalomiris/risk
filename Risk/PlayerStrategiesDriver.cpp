#include <iostream>
#include "PlayerStrategies.h"

using namespace std;

// declare method for the start of each play
void selectStrategy(Player* player);

//int main() {
//
//	Map* map = new Map();
//	Country* country1 = new Country();
//	Country* country2 = new Country();
//	Country* country3 = new Country();
//	Country* country4 = new Country();
//	Country* country5 = new Country();
//	Country* country6 = new Country();
//	Country* country7 = new Country();
//	Country* country8 = new Country();
//	Country* country9 = new Country();
//	Country* country10 = new Country();
//	Country* country11 = new Country();
//
//	// setting country names
//	country1->setCountryName("Canada");
//	country2->setCountryName("USA");
//	country3->setCountryName("Mexico");
//	country4->setCountryName("Italy");
//	country5->setCountryName("France");
//	country6->setCountryName("Japan");
//	country7->setCountryName("China");
//	country8->setCountryName("Venezuela");
//	country9->setCountryName("Peru");
//	country10->setCountryName("Brazil");
//	country11->setCountryName("Argentina");
//
//	// setting number of armies on each country
//	country1->setNumberOfArmies(10);
//	country2->setNumberOfArmies(1);
//	country3->setNumberOfArmies(3);
//	country4->setNumberOfArmies(8);
//	country5->setNumberOfArmies(14);
//	country6->setNumberOfArmies(1);
//	country7->setNumberOfArmies(19);
//	country8->setNumberOfArmies(2);
//	country9->setNumberOfArmies(4);
//	country10->setNumberOfArmies(1);
//	country11->setNumberOfArmies(9);
//
//	// add countries to map
//	map->setCountry(country1);
//	map->setCountry(country2);
//	map->setCountry(country3);
//	map->setCountry(country4);
//	map->setCountry(country5);
//	map->setCountry(country6);
//	map->setCountry(country7);
//	map->setCountry(country8);
//	map->setCountry(country9);
//	map->setCountry(country10);
//	map->setCountry(country11);
//
//	// setting neighbor countries
//	country1->setAdjacentCountries(country2);
//	country1->setAdjacentCountries(country3);
//	country2->setAdjacentCountries(country1);
//	country2->setAdjacentCountries(country3);
//	country3->setAdjacentCountries(country1);
//	country3->setAdjacentCountries(country2);
//	country4->setAdjacentCountries(country5);
//	country4->setAdjacentCountries(country6);
//	country5->setAdjacentCountries(country4);
//	country5->setAdjacentCountries(country6);
//	country5->setAdjacentCountries(country7);
//	country6->setAdjacentCountries(country4);
//	country6->setAdjacentCountries(country5);
//	country7->setAdjacentCountries(country5);
//	country7->setAdjacentCountries(country8);
//	country8->setAdjacentCountries(country7);
//	country8->setAdjacentCountries(country9);
//	country8->setAdjacentCountries(country10);
//	country9->setAdjacentCountries(country11);
//	country9->setAdjacentCountries(country8);
//	country10->setAdjacentCountries(country8);
//	country11->setAdjacentCountries(country9);
//
//
//	Continent* continent1 = new Continent();
//	Continent* continent2 = new Continent();
//	Continent* continent3 = new Continent();
//	Continent* continent4 = new Continent();
//
//	continent1->setContinentName("North America");
//	continent2->setContinentName("South America");
//	continent3->setContinentName("Europe");
//	continent4->setContinentName("Asia");
//
//	continent1->setNumberOfArmies(10);
//	continent2->setNumberOfArmies(15);
//	continent3->setNumberOfArmies(7);
//	continent4->setNumberOfArmies(8);
//
//	map->setContinent(continent1);
//	map->setContinent(continent2);
//	map->setContinent(continent3);
//	map->setContinent(continent4);
//
//	continent1->setCountriesOfContinent(country1);
//	continent1->setCountriesOfContinent(country2);
//	continent2->setCountriesOfContinent(country3);
//	continent2->setCountriesOfContinent(country8);
//	continent2->setCountriesOfContinent(country9);
//	continent2->setCountriesOfContinent(country10);
//	continent2->setCountriesOfContinent(country11);
//
//	continent3->setCountriesOfContinent(country4);
//	continent3->setCountriesOfContinent(country5);
//	continent4->setCountriesOfContinent(country6);
//	continent4->setCountriesOfContinent(country7);
//
//	Player* player = new Player("Bob", map);
//	Player* player2 = new Player("Joe", map);
//
//	// setting owners of each country
//	country1->setCountryOwnerId(player->getID());
//	country2->setCountryOwnerId(player->getID());
//	country3->setCountryOwnerId(player->getID());
//	country4->setCountryOwnerId(player->getID());
//	country5->setCountryOwnerId(player->getID());
//	country6->setCountryOwnerId(player2->getID());
//	country7->setCountryOwnerId(player2->getID());
//	country8->setCountryOwnerId(player2->getID());
//	country9->setCountryOwnerId(player->getID());
//	country10->setCountryOwnerId(player->getID());
//	country11->setCountryOwnerId(player2->getID());
//	player->setThisPlayerCountry(country1);
//	player->setThisPlayerCountry(country2);
//	player->setThisPlayerCountry(country3);
//	player->setThisPlayerCountry(country4);
//	player->setThisPlayerCountry(country5);
//	player2->setThisPlayerCountry(country6);
//	player2->setThisPlayerCountry(country7);
//	player2->setThisPlayerCountry(country8);
//	player->setThisPlayerCountry(country9);
//	player->setThisPlayerCountry(country10);
//	player2->setThisPlayerCountry(country11);
//
//	//new deck based on number of countries in map (size of deck should be 3)
//	Deck* deck = new Deck(map);
//
//	deck->draw(player->getHand(), player->getName());
//	deck->draw(player->getHand(), player->getName());
//	deck->draw(player->getHand(), player->getName());
//
//	deck->draw(player2->getHand(), player2->getName());
//	deck->draw(player2->getHand(), player2->getName());
//	deck->draw(player2->getHand(), player2->getName());
//	deck->draw(player2->getHand(), player2->getName());
//	deck->draw(player2->getHand(), player2->getName());
//	deck->draw(player2->getHand(), player2->getName());
//
//	Cards* card1 = new Cards(0, 1);
//	Cards* card2 = new Cards(1, 5);
//	Cards* card3 = new Cards(2, 10);
//
//	deck->setCardInDeck(card1);
//	deck->setCardInDeck(card2);
//	deck->setCardInDeck(card3);
//
//	player->getHand()->setCardInHand(card1);
//	player->getHand()->setCardInHand(card2);
//	player2->getHand()->setCardInHand(card3);
//
//	/* reinforcement phase with Strategy pattern */
//	cout << "\nThis is the reinforcement phase of the turn." << endl;
//	selectStrategy(player); // player can choose which strategy to use before each play
//
//	player->reinforce();
//
//	/* attack phase with Strategy pattern */
//	cout << "\nThis is the attack phase of the turn." << endl;
//	selectStrategy(player); // player can choose which strategy to use before each play
//
//	player->attack();
//
//	/* fortification phase with Strategy pattern */
//	cout << "\nThis is the fortification phase of the turn." << endl;
//	selectStrategy(player); // player can choose which strategy to use before each play
//
//	player->fortify();
//
//	delete player;
//	player = NULL;
//	delete map;
//	map = NULL;
//	delete country1;
//	country2 = NULL;
//	delete country2;
//	country2 = NULL;
//	delete country3;
//	country3 = NULL;
//	delete country4;
//	country4 = NULL;
//	delete country5;
//	country5 = NULL;
//	delete country6;
//	country6 = NULL;
//	delete country7;
//	country7 = NULL;
//	delete country8;
//	country8 = NULL;
//	delete country9;
//	country9 = NULL;
//	delete country10;
//	country10 = NULL;
//	delete country11;
//	country11 = NULL;
//	delete deck;
//	deck = NULL;
//
//}

// asks user which strategy to use
void selectStrategy(Player* player) {

	int strategy;
	cout << "Which strategy would you like to use for this play? Please enter the number of the strategy to make your choice." << endl;
	cout << "(1) User Strategy" << endl;
	cout << "(2) Aggressive Strategy" << endl;
	cout << "(3) Benevolent Strategy" << endl;
	cout << "(4) Random Strategy" << endl;
	cout << "(5) Cheater Strategy" << endl;
	cin >> strategy;

	while (strategy < 0 || strategy > 5) {
		cout << "Please select a valid strategy from the list of strategies." << endl;
		cin >> strategy;
	}
	
	User* user = new User();
	Aggressive* aggressive = new Aggressive();
	Benevolent* benevolent = new Benevolent();
	Random* random = new Random();
	Cheater* cheater = new Cheater();

	switch (strategy) {
		case 1:
			cout << "You will play this phase as a User." << endl;
			player->setStrategy(user);
            player->setStrategyNum(5);
			break;
		case 2:
			cout << "You will play this phase as an Aggressive computer player." << endl;
			player->setStrategy(aggressive);
            player->setStrategyNum(1);
			break;
		case 3:
			cout << "You will play this phase as a Benevolent computer player." << endl;
			player->setStrategy(benevolent);
            player->setStrategyNum(2);
			break;
		case 4:
			cout << "You will play this phase as a Random computer player." << endl;
			player->setStrategy(random);
            player->setStrategyNum(4);
			break;
		case 5:
			cout << "You will play this phase as a Cheater computer player." << endl;
			player->setStrategy(cheater);
            player->setStrategyNum(3);
			break;
		default:
			break;
	}
}
