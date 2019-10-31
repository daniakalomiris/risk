#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include <iostream>


const int MIN_PLAYERS = 2; 
const int MAX_PLAYERS = 6;

GameEngine::setNumberOfPlayers() {
	int* numberOfPlayers;

	cout << "Please enter the number of players (between 2 and 6): " << endl; 
	
	int numPlayersEntered;
	cin >> numPlayersEntered; 

	while (numPlayersEntered<MIN_PLAYERS || numPlayersEntered > MAX_PLAYERS) {
		cout << "Invalid entry. Please enter a number between 2 and 6" << endl;
		cin >> numPlayersEntered; 
	}

	numberOfPlayers = &numPlayersEntered;
	cout << "Ok, there will be " << *numberOfPlayers << " players" << endl; 
	
	
}


GameEngine::GameEngine() {


}