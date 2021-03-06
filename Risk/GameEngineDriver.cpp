#include "GameEngine.h"
#include <iostream>

using namespace std;

//declare 3 functions that will serve as drivers for part1, part2 and part 3 of assignment 2
void part1();
void part2();
void part3();

//declare 3 functions to to test part 2 of assignment 4
void tournamentMode(bool isTournamentOn);
void singleGameMode(bool isTournamentOn);
bool isTournamentModeOn();

int main() {
    
    //if the tournament mode is on, played tournatement mode
    if(isTournamentModeOn()) {
        cout << "\n********* TOURNAMENT MODE *********\n" << endl;
        tournamentMode(true);
    }
    
    //else play single game mode
    else {
        cout << "\n********* SINGLE GAME MODE *********\n" << endl;
        singleGameMode(false);
    }
}


//driver for part 1 Game Start of assignment 2
void part1() {
    GameEngine* theGame = new GameEngine();
    
    theGame->createMap();
    theGame->askNumberOfPlayers();
    theGame->createPlayers();
    cout << "There are " << theGame->getNumberOfPlayers() << " players." << endl;
    
    delete theGame;
    theGame = NULL;
}

//driver for part 2 Game Play startup phase of assignment 2
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
        cout << "\nPlayer " << theGame->getAllPlayers().at(i)->getName() << " countries and armies" << endl;
        
        for(int j = 0; j<theGame->getAllPlayers().at(i)->getThisPlayerCountries().size(); j++) {
            cout << theGame->getAllPlayers().at(i)->getThisPlayerCountries().at(j)->getCountryName() << " "  << theGame->getAllPlayers().at(i)->getThisPlayerCountries().at(j)->getNumberOfArmies() << endl;
        }
    }
    
    delete theGame;
    theGame = NULL;
}

//driver for part 3 Game play main loop of assignment 2
void part3() {
    GameEngine* theGame = new GameEngine();
    theGame->createMap();
    theGame->askNumberOfPlayers();
    theGame->createPlayers();
    theGame->assignCountriesToPlayers();
    theGame->displayCountriesOfPlayers();
    
    //assign 5 armies to all countries of each player, just for testing
    for(int i =0; i < theGame->getAllPlayers().size(); i++) {
        for(int j = 0; j < theGame->getAllPlayers().at(i)->getThisPlayerCountries().size(); j++) {
            theGame->getAllPlayers().at(i)->getThisPlayerCountries().at(j)->setNumberOfArmies(5);      
        }
    }
    
    //sets all countries to player Id 0, to pretend player at index 0 won the game
    for(int i =0; i < theGame->getMap()->getCountries().size(); i++) {
        theGame->getMap()->getCountries().at(i)->setCountryOwnerId(0);
    }
    
    theGame->mainGameLoop();
    delete theGame;
    theGame = NULL;
}


//method to select the single mode vs tournamenent mode
bool isTournamentModeOn() {
    int choice; //choice input of user

    cout << "Please select the game mode" << endl;
    cout << "(1) Single Game Mode" << endl;
    cout << "(2) Tournament Mode" << endl;
    
    cin >> choice;
    
    while(choice <1 || choice >2) {
        cout << "Invalid entry." << endl;
        cout << "Please select the game mode" << endl;
        cout << "(1) Single Game Mode" << endl;
        cout << "(2) Tournament Mode" << endl;
        cin >> choice;
    }
    
    //set gameMode to true if tournament mode is selected
    if(choice==1) {
        cout << "We will load up single player mode for you!\n" << endl;
        return false;
    }
    else if(choice == 2) {
        cout << "We will load up tournament mode for you!\n" << endl;
        return true;
    }
    return NULL;
};


//driver for displaying the menu of the computer game
void tournamentMode(bool isTournamentOn) {
    Tournament* theTournament = new Tournament();
    theTournament -> tournamentSettings();
    theTournament->createGames(isTournamentOn);
    
    //play the game for each games in the tournament
    for(int i =0; i < theTournament->getGames().size(); i++) {
        theTournament->getGames().at(i)->mainGameLoop();
    }
    
    theTournament->displayGamesResults();
    delete theTournament;
    theTournament = NULL;
}

void singleGameMode(bool isTournamentOn) {
    GameEngine* theGame = new GameEngine();
    theGame->createMap();
    theGame->askNumberOfPlayers();
    theGame->createPlayers();
    theGame->assignCountriesToPlayers();
    theGame->displayCountriesOfPlayers();
    theGame->setNumberOfArmiesPerPlayer();
    theGame->setArmiesToCountries();
    theGame->setGameMode(false);
    theGame->mainGameLoop();
    delete theGame;
    theGame = NULL;
}
