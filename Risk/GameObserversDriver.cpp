
#include "GameObservers.h"
#include "GameEngine.h"
#include "Player.h"

using namespace std;

//Function that will act like drivers for part2 and part3 of assignment 3
void A3part2();
void A3part3();

//call the driver for part2 or part3
//uncomment the driver you want to test
int main() {
    
   // A3part2();
    A3part3();
}


//THIS IS THE DRIVER FOR PART 2 OF ASSIGNMENT 3
void A3part2() {

    //create a new GameEngine
    GameEngine* theGame = new GameEngine();
    theGame->createMap();
    theGame->askNumberOfPlayers();
    theGame->createPlayers();
    theGame->assignCountriesToPlayers();
    theGame->displayCountriesOfPlayers();


    //assign 5 armies to all countries of each player, just for testing
    for (int i = 0; i < theGame->getAllPlayers().size(); i++) {

        for (int j = 0; j < theGame->getAllPlayers().at(i)->getThisPlayerCountries().size(); j++) {
            theGame->getAllPlayers().at(i)->getThisPlayerCountries().at(j)->setNumberOfArmies(5);

        }
    }

    //Create PhaseObs that will be connected to the GameEngine
    PhaseObs* phaseObs = new PhaseObs(theGame);

    theGame->mainGameLoop();


    delete theGame;
    theGame = NULL;
}

//

//THIS IS THE DRIVER FOR PART 3 OF ASSIGNMENT 3
//You need to play the game on a smaller map to remove a player and win the game
void A3part3() {

	//create a new GameEngine
	GameEngine* theGame = new GameEngine();
	//theGame->createMap();

    //create own fictive map for testing the driver
    Map* map = new Map();

	//creates new continent objects
    Continent* continent1 = new Continent();
    Continent* continent2 = new Continent();
    Continent* continent3 = new Continent();

    continent1->setContinentName("North America");
    continent2->setContinentName("Central America");
    continent3->setContinentName("South America");

	//set number of armies per continent
    continent1->setNumberOfArmies(10);
    continent2->setNumberOfArmies(7);
    continent3->setNumberOfArmies(9);


    continent1->setAdjacentContinents(continent2);
    continent2->setAdjacentContinents(continent1);
    continent2->setAdjacentContinents(continent3);

    //creating countries
    Country* country1 = new Country();
    Country* country2 = new Country();
    Country* country3 = new Country();
    Country* country4 = new Country();
    Country* country5 = new Country();
    Country* country6 = new Country();

    country1->setCountryName("Canada");
    country2->setCountryName("USA");
    country3->setCountryName("Panama");
    country4->setCountryName("Costa Rica");
    country5->setCountryName("Peru");
    country6->setCountryName("Brazil");

	//setting adjacent countries
    country1->setAdjacentCountries(country2);
    country1->setAdjacentCountries(country6);
    country2->setAdjacentCountries(country1);
    country2->setAdjacentCountries(country3);
    country3->setAdjacentCountries(country2);
    country3->setAdjacentCountries(country4);
    country4->setAdjacentCountries(country3);
    country4->setAdjacentCountries(country5);
    country5->setAdjacentCountries(country4);
    country5->setAdjacentCountries(country6);
    country6->setAdjacentCountries(country5);
      country6->setAdjacentCountries(country1);


	//setting countries to continents
    continent1->setCountriesOfContinent(country1);
    continent1->setCountriesOfContinent(country2);
    continent2->setCountriesOfContinent(country3);
    continent2->setCountriesOfContinent(country4);
    continent3->setCountriesOfContinent(country5);
    continent3->setCountriesOfContinent(country6);

	//setting continents to countries
    country1->setContinentOfCountry(continent1);
    country2->setContinentOfCountry(continent1);
    country3->setContinentOfCountry(continent2);
    country4->setContinentOfCountry(continent2);
    country5->setContinentOfCountry(continent3);
    country6->setContinentOfCountry(continent3);

	//creating continents and maps
    map->setContinent(continent1);
    map->setContinent(continent2);
    map->setContinent(continent3);
    map->setCountry(country1);
    map->setCountry(country2);
    map->setCountry(country3);
    map->setCountry(country4);
    map->setCountry(country5);
    map->setCountry(country6);

	//passing the created map, countries, players to the concrete subject (game engine)
    theGame->setMap(map);
	theGame->askNumberOfPlayers();
	theGame->createPlayers();
	theGame->assignCountriesToPlayers();
	theGame->displayCountriesOfPlayers();


	//assign 1 army to all countries of each player, just for testing
	for (int i = 0; i < theGame->getAllPlayers().size(); i++) {

		for (int j = 0; j < theGame->getAllPlayers().at(i)->getThisPlayerCountries().size(); j++) {
			theGame->getAllPlayers().at(i)->getThisPlayerCountries().at(j)->setNumberOfArmies(1);

		}
	}

	//passing concrete subject to observer
    PlayerDominationView* pdv = new PlayerDominationView(theGame);

    theGame->mainGameLoop();

//deallocating pointers
delete theGame;
delete map;
delete continent1;
delete continent2;
delete continent3;
delete country1;
delete country2;
delete country3;
delete country4;
delete country5;
delete country6;


theGame = NULL;
map = NULL;
continent1 = NULL;
continent2 = NULL;
continent3 = NULL;
country1 = NULL;
country2 = NULL;
country3 = NULL;
country4 = NULL;
country5 = NULL;
country6 = NULL;

}

