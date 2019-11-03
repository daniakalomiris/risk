
#include <iostream>
#include <string>
#include "GameEngine.h"
#include "time.h"
//using std::cout;
//using std::endl;
//using std::cin;
using namespace std;
const int MIN_PLAYERS = 2; 
const int MAX_PLAYERS = 6;


GameEngine:: GameEngine() {
    maploader = new MapLoader();
}

GameEngine:: ~GameEngine() {
    delete maploader;
    delete deck;
}


void GameEngine::askNumberOfPlayers() {
    int numPlayersEntered;
	
    cout << "\nPlease enter the number of players (between 2 and 6): " << endl;
	
	cin >> numPlayersEntered;

	while (numPlayersEntered<MIN_PLAYERS || numPlayersEntered > MAX_PLAYERS) {
		cout << "Invalid entry. Please enter a number between 2 and 6" << endl;
		cin >> numPlayersEntered; 
	}

	//numberOfPlayers = &numPlayersEntered;
	cout << "Ok, there will be " << numPlayersEntered << " players" << endl;

	
    //sets the numberOfPlayers
    this->setNumberOfPlayers(numPlayersEntered);
    //createPlayers(numberOfPlayers);

}

void GameEngine::setNumberOfPlayers(int numberOfPlayers) {
    this->numberOfPlayers = make_unique<int>(numberOfPlayers);
}

int GameEngine::getNumberOfPlayers() {
    return *numberOfPlayers;
}

Deck* GameEngine::getDeck() {
    return deck;
}

void GameEngine::createPlayers() {
	
	string playerName; 

	for (int i = 0; i < this->getNumberOfPlayers(); i++) {
		
		cout << "\nPlease enter the name of player " << i +1 << endl;
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

vector<Player*> GameEngine::getAllPlayers() {
    return allPlayers;
}


void GameEngine::playerOrder(vector<Player*>allPlayers) {
	vector<Player*>orderedPlayers; 

	for (int i = 0; i < allPlayers.size(); i++) {
		int random = rand() % allPlayers.size() + 1;
		//ordered vector of players based on their turn
		orderedPlayers.push_back(allPlayers[random]); 

	}
	
}


void GameEngine::showPlayerOrder(vector<Player*>orderedPlayers) {
	for (int i = 0; i<orderedPlayers.size(); i++) {
		cout << "Player " << orderedPlayers[i]->getName() << " is at position " << (i + 1) << endl; 
	}

}
void GameEngine::createMap() {
	int mapChoice;
	string mapFile; 


	cout << "\nPlease enter the number associated with the map you would like to play on: \n"
		"Select 1 for Big Europe \n"
		"Select 2 for Geoscape \n"
		"Select 3 for LOTR \n"
		"Select 4 for Risk \n"
		"Select 5 for Solar \n"
        "Select 6 for notvalid2 \n" << endl; 

	cin >> mapChoice;

	//checks if entry is valid
	while(mapChoice<1 || mapChoice>6){
		cout << "Invalid entry please nter a valid choice: \n"
				"Select 1 for Big Europe \n"
				"Select 2 for Geoscape \n"
				"Select 3 for LOTR \n"
				"Select 4 for Risk \n"
				"Select 5 for Solar \n"
                "Select 6 for notvalid2 \n"<< endl;

		cin >> mapChoice; 
	}

	if (mapChoice == 1) {
		cout << "You selected Big Europe. We will load that up for you" << endl;
		mapFile = "bigeurope";
	}
	else if (mapChoice == 2) {
		cout << "You selected Geoscape. We will load that up for you" << endl;
		mapFile = "geoscape";
	}
	else if (mapChoice == 3) {
		cout << "You selected LOTR. We will load that up for you" << endl;
		mapFile = "lotr";
	}
	else if (mapChoice == 4) {
		cout << "You selected Risk. We will load that up for you" << endl;
		mapFile = "risk";
	}
	else if (mapChoice == 5) {
		cout << "You selected Solar. We will load that up for you" << endl;
		mapFile = "solar"; 
	}
    
    else if (mapChoice == 6) {
        cout << "You selected notvalid2. We will load that up for you" << endl;
        mapFile = "notvalid2";
    }
    
    maploader->readMapFile("maps/" + mapFile+ ".map");
    maploader->createMap();
    maploader->displayMap();
    map = maploader->getMap();
    //create a new deck
    deck = new Deck(map);
}




//part 3 main game loop
void GameEngine:: mainGameLoop() {
    
    cout << "\n\n****** Main Game Loop *******" << endl;
    bool gameEnd = false;
    
    while (gameEnd == false) {
        
        for(int i = 0; i< this->getNumberOfPlayers(); i++) {
            
            cout << "Player " <<  i+1 << " turn" << endl;
            
            Player* tempPlayer = this->getAllPlayers().at(i);
            
            tempPlayer->reinforce();
            tempPlayer->attack();
            tempPlayer->fortify();
        
            
            
        }
        
        //Need to add an end, when one player controls all the countries
        gameEnd = true;
        
    }
    
    
    
    
    
}


//GameEngine::GameEngine() {
//
//	setNumberOfPlayers();
//	selectMap(); 
//
//
//}
