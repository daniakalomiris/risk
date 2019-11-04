#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
class GameEngine {

private:
		std::unique_ptr<int> numberOfPlayers;
		std::vector <Player*> allPlayers;
        Map* map;
        MapLoader* maploader;
        Deck* deck;
        std::unique_ptr<int> numberOfArmiesPerPlayer;


	public:

		GameEngine(); //constructor
		~GameEngine();

		int getNumberOfPlayers();
		void setNumberOfPlayers(int numberOfPlayers);
        void askNumberOfPlayers();
		void setNumberOfArmiesPerPlayer();
        int getNumberOfArmiesPerPlayer();
		void setArmiesToCountries();

		void setPlayer(Player* player);

		void createMap();
		void createPlayers();
		void setPlayerOrder();
		void showPlayerOrder();
        Map* getMap();
        void assignCountriesToPlayers();
        void displayCountriesOfPlayers();
        void mainGameLoop();

        std::vector <Player*> getAllPlayers();
        Deck* getDeck();
};
