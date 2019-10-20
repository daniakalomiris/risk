#include <iostream>
#include "Player.h"
#include <vector>
#include <string>
#include <memory>
using namespace std;

//player constructor
Player::Player(string name) {
	this->dice = new Dice();
	this->hand = new Hand(counter); 
	this->setName(name);
	counter++;
    
    //sets the id to the counter of the player
    id = make_unique<int>(counter);
   
}

Player::Player() {
	this->dice = new Dice();
	this->hand = new Hand(counter);
	counter++;
	id = make_unique<int>(counter); //id of player generated
}

Player::~Player() {
	delete hand;
	delete dice;
}

//id counter starts at 0
int Player::counter = 0;

//Gets name of player
string Player::getName() {
	return name;
}

//gets id of player
int Player::getID() {
	return *id;
}

Hand* Player::getHand() {
	return hand;
}

Dice* Player::getDice() {
	return dice;
}


//Setters
void Player::setName(string name) {
	this->name = name;
}



//extra methods , reinforce, attack and fortify, will be implemented in next iteration
void Player::reinforce() {
	cout << "The player reinforce his troops" << endl;
}

//attack method
void Player::attack() {
	cout << "The player attacks" << endl;
}

//fortify method
void Player::fortify() {
	cout << "The player fortify" << endl;
}




