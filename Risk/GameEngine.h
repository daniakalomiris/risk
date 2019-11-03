#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "Map.h"
class GameEngine {

private:
		std::unique_ptr<int> numberOfPlayers;
		std::vector <Player*> allPlayers;
		std::vector <Player*> orderedPlayers;
        std::unique_ptr<Map> map;
		

	public:
		
		GameEngine(); //constructor
		~GameEngine(); 

		int getNumberOfPlayers();
		void setNumberOfPlayers(int numberOfPlayers);
        void askNumberOfPlayers();

		void setPlayer(Player* player);
        
		void selectMap();

		void createPlayers();
		void playerOrder(vector<Player*>allPlayers);
		void showPlayerOrder(vector<Player*>orderedPlayers);
        
        void mainGameLoop();
    
        std::vector <Player*> getAllPlayers();
};
