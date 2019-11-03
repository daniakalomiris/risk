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
		std::vector <Player*> orderedPlayers;
        Map* map;
        MapLoader* maploader;
        Deck* deck; 

	public:
		
		GameEngine(); //constructor
		~GameEngine(); 

		int getNumberOfPlayers();
		void setNumberOfPlayers(int numberOfPlayers);
        void askNumberOfPlayers();
        Deck* getDeck();    
		void setPlayer(Player* player);
		void createMap();
		void createPlayers();
		void playerOrder(std::vector<Player*>allPlayers);
		void showPlayerOrder(std::vector<Player*>orderedPlayers);
    
        void mainGameLoop();
    
        std::vector <Player*> getAllPlayers();
};
