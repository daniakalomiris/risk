#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
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
		int numberOfArmiesPerPlayer(int numberOfPlayers);
		//void setArmiesToCountries(vector<Player*>orderedPlayers, int A);

		void setPlayer(Player* player);
        
		void createMap();

		void createPlayers();
		void setPlayerOrder();
		void showPlayerOrder();
        
    void assignCountriesToPlayers();
	//	void displayCountriesOfPlayers(vector<Player*>orderedPlayers)
        void mainGameLoop();
		
        std::vector <Player*> getAllPlayers();
        Deck* getDeck();
};
