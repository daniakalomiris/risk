#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "GameObservers.h"

class Tournament;

class GameEngine: public Subject{
private:
    std::unique_ptr<int> numberOfPlayers;
    std::unique_ptr<int> phase;
    std::vector <Player*> allPlayers;
    Map* map;
    MapLoader* maploader;
    Deck* deck;
    std::unique_ptr<int> numberOfArmiesPerPlayer;
    std::unique_ptr<bool> endGame; //tells if it is the end of the game
    std::unique_ptr<int> maxNumTurn; //maximum number of turns
    std::unique_ptr<bool>gameMode; //tells if the game mode is a tournament
    std::unique_ptr<std::string> winner; //contains the name of the winner
public:
    GameEngine(); //constructor
    GameEngine(const GameEngine& orig); //copy constructor
    const GameEngine& operator=(const GameEngine& g);
    ~GameEngine();
    int currentPlayerIndex;
    int currentDefenderIndex;
    int getNumberOfPlayers();
    void setNumberOfPlayers(int numberOfPlayers);
    void setNumberOfArmiesPerPlayer();
    int getNumberOfArmiesPerPlayer();
    void setArmiesToCountries();
    bool getEndGame();
    int getPhase();
    void setEndGame(bool value);
    void setPlayerOrder();
    void setPlayer(Player* player);
    void setPhase(int phase);
    Map* getMap();
    void setMap(Map* map);
    void setGameMode(bool mode);
    bool getGamemode();
    string getWinner();
    void setWinner(std::string name);
    std::vector <Player*> getAllPlayers();
    Deck* getDeck();
    int getMaxNumTurn();
    void setMaxNumTurn(int max);
    void askNumberOfPlayers();
    void createMap(std::string mapFile);
     void createMap();
    void createPlayers();
    void showPlayerOrder();
    void assignCountriesToPlayers();
    void displayCountriesOfPlayers();
    void mainGameLoop();
};

class Tournament {
public:
    Tournament();
    Tournament(const Tournament& orig); //copy constructor
    ~Tournament();
    void tournamentSettings(); //display menu to prompts the user for tournament settings
    void mapSelection();//selecting the different maps to play on
    void createGames(bool isTournamentOn); //create the different games according to user input
    void playerSelection(); //selecting the strategy for each players
    void displayGamesResults();
    int getNumMaps();
    void setNumMaps(int num);
    int getNumGames();
    void setNumGames(int num);
    int getNumTurns();
    void setNumTurns(int num);
    int getNumComps();
    void setNumComps(int num);
    std::vector<GameEngine*> getGames();
    vector<std::string> getTournamentMaps();
    void setTournamentMaps(std::string map);
private:
    unique_ptr<int> numMaps;
    unique_ptr<int> numComps; //number of computers;
    unique_ptr<int> numGames;
    unique_ptr<int> numTurns;
    std::vector<GameEngine*> games; //vector of gameEngines objects
    std::vector<Player*> allCompPlayers; //vector of computers
    std::vector<std::string> tournamentMaps;
};
