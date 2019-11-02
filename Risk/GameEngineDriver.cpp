#include "GameEngine.h"
#include <iostream>
using namespace std;

int main() {
    
    GameEngine* theGame = new GameEngine();
    
    
    
    theGame->askNumberOfPlayers();
    theGame->createPlayers();
    theGame->selectMap();
    theGame->mainGameLoop();
    
    delete theGame;
}
