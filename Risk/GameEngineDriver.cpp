#include "GameEngine.h"
#include <iostream>
using namespace std;

void part1();
void part2();
void part3();



//int main() {
//    
//   // part1();
//    part2();
//}


//driver for part 1
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

//driver for part 2
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
    
}
