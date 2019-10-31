#pragma once

class GameEngine {
		int* numberOfPlayers; 

	public:
		
		GameEngine(); //constructor
		~GameEngine(); 

		int getNumberOfPlayers();
		void setNumberOfPlayers(); 

		void selectMap();

};