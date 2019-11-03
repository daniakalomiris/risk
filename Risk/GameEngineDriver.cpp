#include "GameEngine.h"
#include "MapLoader.h"
#include <iostream>
using namespace std;

int main() {
    
    GameEngine* theGame = new GameEngine();
	MapLoader mapLoader; 
	Map* map = new Map(); 
	Deck* deck = new Deck(map); 

	
    
    theGame->askNumberOfPlayers();
	theGame->createPlayers();
	cout << "There are " << theGame->getNumberOfPlayers() << " players." << endl;

    

    theGame->selectMap();
	mapLoader.createMap();
	mapLoader.displayMap(); 

	cout << "There are " << deck->getNumOfCardsInDeck() << " cards in the deck" << endl; 
 

    theGame->mainGameLoop();
    
    delete theGame;
	delete mapLoader; 
}
