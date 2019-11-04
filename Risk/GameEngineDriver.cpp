#include "GameEngine.h"
#include <iostream>
using namespace std;


void part1();
void part2();
void part3();

int main() {
    
    part3();
	
//    mapLoader.createMap();
//    theGame->askNumberOfPlayers();
//	theGame->createPlayers();
//	cout << "There are " << theGame->getNumberOfPlayers() << " players." << endl;
//	cout << "We will now output the turn of each player: " << endl;
//	theGame->playerOrder(vector<Player*>allPlayers);
//	theGame->showPlayerOrder(vector<Player*>orderedPlayers);
//	theGame->numberOfArmiesPerPlayer(int numberOfPlayers);
//
//
//
//
//
//
//	cout << "We will now assign countries to each player" << endl;
	//theGame->assignCountriesToPlayers(vector<Player*>orderedPlayers);
	//theGame->displayCountriesOfPlayers(vector<Player*>orderedPlayers);
	//theGame->setArmiesToCountries(vector<Player*>orderedPlayers, int A);


    

//	cout << "There are " << deck->getNumOfCardsInDeck() << " cards in the deck" << endl;
//
//
//    theGame->mainGameLoop();
//
//    delete theGame;
//	//delete mapLoader;
}


void part1() {
        GameEngine* theGame = new GameEngine();

       
       theGame->createMap();
       theGame->askNumberOfPlayers();
       theGame->createPlayers();
       cout << "There are " << theGame->getNumberOfPlayers() << " players." << endl;

       
       //cout << "There are " << theGame->getDeck()->getNumOfCardsInDeck() << " cards in the deck" << endl;
        
       
       delete theGame;
       theGame = NULL;
       
}

void part2() {
    GameEngine* theGame = new GameEngine();
    theGame->createMap();
    theGame->askNumberOfPlayers();
    theGame->createPlayers();
    theGame->mainGameLoop();
    delete theGame;
    theGame = NULL;
}


void part3() {
    GameEngine* theGame = new GameEngine();

    
    theGame->createMap();
    theGame->askNumberOfPlayers();
    theGame->createPlayers();
    cout << "There are " << theGame->getNumberOfPlayers() << " players." << endl;
    
    
        cout << "We will now output the turn of each player: " << endl;
        theGame->setPlayerOrder();
        theGame->showPlayerOrder();
}
