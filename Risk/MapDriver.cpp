#include "Map.h"
#include "Player.h"
#include <iostream>
#include <memory>

using namespace std;


int main() {
	/* creating VALID map */
	Map* map1 = new Map();

	Continent* northAmerica = new Continent();
	Continent* europe = new Continent();

	Country* c1 = new Country();
	Country* c2 = new Country();
	Country* c3 = new Country();
	Country* c4 = new Country();
	Country* c5 = new Country();
	Country* c6 = new Country();

	c1->setCountryName("Canada");
	c2->setCountryName("USA");
	c3->setCountryName("Mexico");
	c4->setCountryName("France");
	c5->setCountryName("Spain");
	c6->setCountryName("Portugal");

	northAmerica->setContinentName("North America");
	europe->setContinentName("Europe");

	c1->setContinentOfCountry(northAmerica);
	c2->setContinentOfCountry(northAmerica);
	c3->setContinentOfCountry(northAmerica);
	c4->setContinentOfCountry(europe);
	c5->setContinentOfCountry(europe);
	c6->setContinentOfCountry(europe);
	northAmerica->setCountriesOfContinent(c1);
	northAmerica->setCountriesOfContinent(c2);
	northAmerica->setCountriesOfContinent(c3);
	europe->setCountriesOfContinent(c4);
	europe->setCountriesOfContinent(c5);
	europe->setCountriesOfContinent(c6);

	map1->setContinent(northAmerica);
	map1->setContinent(europe);

	map1->setCountry(c1);
	map1->setCountry(c2);
	map1->setCountry(c3);
	map1->setCountry(c4);
	map1->setCountry(c5);
	map1->setCountry(c6);

	northAmerica->setAdjacentContinents(europe);
	europe->setAdjacentContinents(northAmerica);

	c1->setAdjacentCountries(c2);
	c2->setAdjacentCountries(c1);
	c2->setAdjacentCountries(c3);
	c4->setAdjacentCountries(c5);
	c5->setAdjacentCountries(c4);
	c5->setAdjacentCountries(c6);
	c6->setAdjacentCountries(c5);

	cout << "~~~~~ Testing VALID map ~~~~~" << endl;
	map1->isValidMap();

	// country owned by player and contains armies
	Player* player1 = new Player();
	player1->setName("Dania");

	Player* player2 = new Player();
	player2->setName("Not Dania");

	c1->setCountryOwnerId(player1->getID());
	c1->setNumberOfArmies(1);
	c2->setCountryOwnerId(player1->getID());
	c2->setNumberOfArmies(2);
	c6->setCountryOwnerId(player1->getID());
	c6->setNumberOfArmies(3);
	c3->setCountryOwnerId(player2->getID());
	c3->setNumberOfArmies(3);
	c4->setCountryOwnerId(player2->getID());
	c4->setNumberOfArmies(2);
	c5->setCountryOwnerId(player2->getID());
	c5->setNumberOfArmies(1);

	map1->getOwnerCountries(player1->getID());
	map1->getOwnerCountries(player2->getID());

	// deallocate all pointers for map1
	delete map1;
	map1 = NULL;
	delete northAmerica;
	northAmerica = NULL;
	delete europe;
	europe = NULL;
	delete c1;
	c1 = NULL;
	delete c2;
	c2 = NULL;
	delete c3;
	c3 = NULL;
	delete c4;
	c4 = NULL;
	delete c5;
	c5 = NULL;
	delete c6;
	c6 = NULL;


	/* creating INVALID map */
	Map* map2 = new Map();

	Continent* continent1M2 = new Continent();
	Continent* continent2M2 = new Continent();
	Continent* continent3M2 = new Continent();

	Country* c1M2 = new Country();
	Country* c2M2 = new Country();
	Country* c3M2 = new Country();

	c1M2->setCountryName("Country 1");
	c2M2->setCountryName("Country 2");
	c3M2->setCountryName("Country 3");

	continent1M2->setContinentName("Continent 1");
	continent2M2->setContinentName("Continent 2");
	continent3M2->setContinentName("Continent 3");

	map2->setContinent(continent1M2);
	map2->setContinent(continent2M2);
	map2->setContinent(continent3M2);

	map2->setCountry(c1M2);
	map2->setCountry(c2M2);
	map2->setCountry(c3M2);

	cout << "\n~~~~~ Testing INVALID map ~~~~~" << endl;

	/* Not all countries belong to only one continent */
	c1M2->setContinentOfCountry(continent1M2);
	c2M2->setContinentOfCountry(continent1M2);
	c2M2->setContinentOfCountry(continent1M2);
	continent1M2->setCountriesOfContinent(c1M2);
	continent1M2->setCountriesOfContinent(c2M2);
	continent1M2->setCountriesOfContinent(c2M2);
	map2->isCountryInOneContinent(); // Country 2 belongs to Continent 1 and Continent 2

	/* Not all continents have countries */
	map2->isNotEmptyContinent(); // Continent 2 has no countries

	/* Not all countries belong to a continent */
	map2->countryHasContinent(); // Country 3 has no continent

	// deallocate all pointers for map2
	delete map2;
	map2 = NULL;
	delete continent1M2;
	continent1M2 = NULL;
	delete continent2M2;
	continent2M2 = NULL;
	delete continent3M2;
	continent3M2 = NULL;
	delete c1M2;
	c1M2 = NULL;
	delete c2M2;
	c2M2 = NULL;
	delete c3M2;
	c3M2 = NULL;
}
