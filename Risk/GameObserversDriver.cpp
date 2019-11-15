#pragma once
#include "GameObservers.h"
#include "GameEngine.h"
#include "Player.h"
using namespace std;

int main() {
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

	//Create a player to be the subject
	Player* player = new Player();

	//Create RObs that will be connected to the player
	RObs* robs = new RObs(player);
	//Create AObs that will be connected to the player
	AObs* aobs = new AObs(player);
	//Create FObs that will be connected to the player
	FObs* fobs = new FObs(player);

	player->reinforce();
	//player->attack();
	//player->fortify();

	theGame->mainGameLoop();
	delete theGame;
	theGame = NULL;
}
