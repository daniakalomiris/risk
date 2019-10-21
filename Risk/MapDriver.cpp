#include "Map.h"
#include "Player.h"
#include <iostream>
#include <memory>

using namespace std;


//int main() {
//
//	Map* map1 = new Map();
//
//	Continent* northAmerica = new Continent();
//	Continent* europe = new Continent();
//
//	Country* c1 = new Country();
//	Country* c2 = new Country();
//	Country* c3 = new Country();
//	Country* c4 = new Country();
//	Country* c5 = new Country();
//	Country* c6 = new Country();
//
//	c1->setCountryName("Canada");
//	c2->setCountryName("USA");
//	c3->setCountryName("Mexico");
//	c4->setCountryName("France");
//	c5->setCountryName("Spain");
//	c6->setCountryName("Portugal");
//
//	c1->setContinentOfCountry(northAmerica);
//	c2->setContinentOfCountry(northAmerica);
//	c3->setContinentOfCountry(northAmerica);
//	c4->setContinentOfCountry(europe);
//	c5->setContinentOfCountry(europe);
//	c6->setContinentOfCountry(europe);
//
//	map1->setContinent(northAmerica);
//	map1->setContinent(europe);
//
//	map1->setCountry(c1);
//	map1->setCountry(c2);
//	map1->setCountry(c3);
//	map1->setCountry(c4);
//	map1->setCountry(c5);
//	map1->setCountry(c6);
//
//	northAmerica->setAdjacentContinents(europe);
//	europe->setAdjacentContinents(northAmerica);
//
//	c1->setAdjacentCountries(c2);
//	c2->setAdjacentCountries(c1);
//	c2->setAdjacentCountries(c3);
//	c4->setAdjacentCountries(c5);
//	c5->setAdjacentCountries(c4);
//	c5->setAdjacentCountries(c6);
//	c6->setAdjacentCountries(c5);
//	
//	/* VALID map */
//
//	map1->isValidMap();
//
//	// map is connected subgraph with adjacency between countries
//	map1->isCountrySubgraph();
//	for (int i = 0; i < map1->getCountries().size(); i++) {
//		cout << map1->getCountries().at(i)->getCountryName() << " has these adjacent countries: " << endl;
//		for (int j = 0; j < map1->getCountries().at(i)->getAdjacentCountries().size(); i++) {
//			cout << map1->getCountries().at(i)->getAdjacentCountries().at(j)->getCountryName() << endl;
//		}
//	}
//	
//	// continents are connected subgraphs
//	map1->isContinentSubgraph();
//	for (int i = 0; i < map1->getContinents().size(); i++) {
//		cout << map1->getContinents().at(i)->getContinentName() << " has these adjacent continents: " << endl;
//		for (int j = 0; j < map1->getContinents().at(i)->getAdjacentContinents().size(); i++) {
//			cout << map1->getContinents().at(i)->getAdjacentContinents().at(j)->getContinentName() << endl;
//		}
//	}
//
//	// each country belongs to only one continent
//	map1->isCountryInOneContinent();
//
//	// country owned by player and contains armies
//	Player* player = new Player();
//	player->setName("Dania");
//
//	c1->setCountryOwnerId(player->getID());
//	c1->setNumberOfArmies(1);
//
//	c2->setCountryOwnerId(player->getID());
//	c2->setNumberOfArmies(2);
//
//	c6->setCountryOwnerId(player->getID());
//	c6->setNumberOfArmies(3);
//
//	map1->getOwnerCountries(player->getID());
//
//	Map* map2 = new Map();
//
//	Continent* continent1M2 = new Continent();
//	Continent* continent2M2 = new Continent();
//	Continent* continent3M2 = new Continent();
//
//	Country* c1M2 = new Country();
//	Country* c2M2 = new Country();
//	Country* c3M2 = new Country();
//	Country* c4M2 = new Country();
//	Country* c5M2 = new Country();
//	Country* c6M2 = new Country();
//
//	map1->setContinent(continent1M2);
//	map1->setContinent(continent2M2);
//	map1->setContinent(continent3M2);
//
//	map1->setCountry(c1M2);
//	map1->setCountry(c2M2);
//	map1->setCountry(c3M2);
//	map1->setCountry(c4M2);
//	map1->setCountry(c5M2);
//	map1->setCountry(c6M2);
//
//	/* Test cases for INVALID maps */
//
//	/* Not all countries belong to only one continent */
//
//	c3M2->setContinentOfCountry(continent1M2);
//	c3M2->setContinentOfCountry(continent2M2);
//	map1->isCountryInOneContinent();
//
//
//	/* Not all continents have countries */
//	map1->isNotEmptyContinent();
//
//	/* Not all countries belong to a continent */
//
//	c1M2->setContinentOfCountry(continent1M2);
//	c2M2->setContinentOfCountry(continent1M2);
//	c6M2->setContinentOfCountry(continent2M2);
//	map1->countryHasContinent();
//}

