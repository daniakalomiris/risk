#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "GameObservers.h"
class GameEngine: public Subject{
    
private:
    std::unique_ptr<int> numberOfPlayers;
    std::vector <Player*> allPlayers;
    Map* map;
    MapLoader* maploader;
    Deck* deck;
    std::unique_ptr<int> numberOfArmiesPerPlayer;
    std::unique_ptr<bool> endGame; //tells if it is the end of the game
    
public:
    
    GameEngine(); //constructor
    ~GameEngine();
    
    
    //getter and setter methods
    int getNumberOfPlayers();
    void setNumberOfPlayers(int numberOfPlayers);
    void setNumberOfArmiesPerPlayer();
    int getNumberOfArmiesPerPlayer();
    void setArmiesToCountries();
    bool getEndGame();
    void setEndGame(bool value);
    void setPlayerOrder();
    void setPlayer(Player* player);
    Map* getMap();
    void setMap(Map* map);
    std::vector <Player*> getAllPlayers();
    Deck* getDeck();
    
    void askNumberOfPlayers();
    void createMap();
    void createPlayers();
    void showPlayerOrder();
    void assignCountriesToPlayers();
    void displayCountriesOfPlayers();
    void mainGameLoop();
    
    
};
