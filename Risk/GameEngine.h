#pragma once

class GameEngine {

private:
		int* numberofplayers; 
		vector <Player*> allPlayers; 

		

	public:
		
		GameEngine(); //constructor
		~GameEngine(); 

		int getnumberofplayers();
		void setnumberofplayers(); 

		void setPlayer(Player* player);

		void selectmap();

		createplayers(int);

};