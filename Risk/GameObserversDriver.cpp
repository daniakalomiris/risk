
#include "GameObservers.h"
#include "GameEngine.h"
#include "Player.h"
using namespace std;

int main() {

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

    PlayerDominationView* pdv = new PlayerDominationView(theGame);
    theGame->mainGameLoop();
//	//Create RObs that will be connected to the GameEngine
//	RObs* robs = new RObs(theGame);
//	//Create AObs that will be connected to the GameEngine
//	AObs* aobs = new AObs(theGame);
//	//Create FObs that will be connected to the GameEngine
//	FObs* fobs = new FObs(theGame);
//
//	theGame->mainGameLoop();
//
//
//	delete theGame;
//	theGame = NULL;
}
