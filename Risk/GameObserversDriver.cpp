#pragma once
#include "GameObservers.h"
#include "Player.h"
using namespace std;

int main(void) {	
	//Create a player to be the subject
	Player *player = new Player();
	
	//Create RObs that will be connected to the player
	RObs* robs = new RObs(player);
	//Create AObs that will be connected to the player
	AObs* aobs = new AObs(player);
	//Create FObs that will be connected to the player
	FObs* fobs = new FObs(player);
	
	player->reinforce();
	player->attack();
	player->fortify();
}
