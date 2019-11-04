#include "GameEngine.h"
#include <iostream>
using namespace std;


void part1();
void part2();
void part3();

int main() {

    part2();

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
    cout << "There are " << theGame->getNumberOfPlayers() << " players." << endl;


        cout << "We will now output the turn of each player: " << endl;
        theGame->setPlayerOrder();
        theGame->showPlayerOrder();

    cout << "We will now assign countries to each player" << endl;
    theGame->assignCountriesToPlayers();
    theGame->displayCountriesOfPlayers();
    theGame->setNumberOfArmiesPerPlayer();
    cout << "\n\nThis is the number of armies each player will have to place on the game: " << theGame->getNumberOfArmiesPerPlayer() << " armies" << endl;;

    theGame->setArmiesToCountries();

    cout << "\n\nThis the countries of each players and their number of armies after army placement" << endl;

    for(int i =0; i <theGame->getAllPlayers().size(); i++) {
        cout << "Player " << theGame->getAllPlayers().at(i)->getName() << " countries and armies" << endl;

        for(int j = 0; j<theGame->getAllPlayers().at(i)->getThisPlayerCountries().size(); j++) {
            cout << theGame->getAllPlayers().at(i)->getThisPlayerCountries().at(j)->getCountryName() << " "  << theGame->getAllPlayers().at(i)->getThisPlayerCountries().at(j)->getNumberOfArmies() << endl;
        }


    }


}


void part3() {
    GameEngine* theGame = new GameEngine();
    theGame->createMap();
    theGame->askNumberOfPlayers();
    theGame->createPlayers();
    theGame->mainGameLoop();
    delete theGame;
    theGame = NULL;
}
