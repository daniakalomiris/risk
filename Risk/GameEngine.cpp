#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin; 

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

	createPlayers(int &numberOfPlayers);

}


void GameEngine::createPlayers(int *numPlayers) {
	
	string playerName; 

	for (int min = 2; min <= *numOfPlayers; min++) {
		int i = 1; //player number

		cout << "Please enter the name of player " << i << endl;
		cin >> playerName; 

		//creates a player with name, dice, and hand 
		Player* player = new Player(playerName);
		player->setName(playerName);

		setPlayer(player);
		
	}
}

void GameEngine::setPlayer(Player* player) {
	cout << "adding player to list of players" << endl;
	allPlayers.push_back(player);
}



void GameEngine::selectMap() {
	int mapChoice;
	string mapFile; 


	cout << "Please enter the number associated with the map you would like to play on: \n"
		"Select 1 for Big Europe \n"
		"Select 2 for Geoscape \n"
		"Select 3 for LOTR \n"
		"Select 4 for Risk \n"
		"Select 5 for Solar \n" << endl; 

	cin >> mapChoice;

	//checks if entry is valid
	while(mapChoice<1 || mapChoice>5){
		cout << "Invalid entry please nter a valid choice: \n"
				"Select 1 for Big Europe \n"
				"Select 2 for Geoscape \n"
				"Select 3 for LOTR \n"
				"Select 4 for Risk \n"
				"Select 5 for Solar \n" << endl;

		cin >> mapChoice; 
	}

	if (mapChoice == 1) {
		cout >> "You selected Big Europe. We will load that up for you" << endl;
		mapFile = "bigeurope";
	}
	else if (mapChoice == 2) {
		cout >> "You selected Geoscape. We will load that up for you" << endl;
		mapFile = "geoscape";
	}
	else if (mapChoice == 3) {
		cout >> "You selected LOTR. We will load that up for you" << endl;
		mapFile = "lotr";
	}
	else if (mapChoice == 4) {
		cout >> "You selected Risk. We will load that up for you" << endl;
		mapFile = "risk";
	}
	else if (mapChoice == 5) {
		cout >> "You selected Solar. We will load that up for you" << endl;
		mapFile = "solar"; 
	}
		

	// return mapFile;
	void MapLoader::readMapFile(string mapFile);

}




//GameEngine::GameEngine() {
//
//	setNumberOfPlayers();
//	selectMap(); 
//
//
//}