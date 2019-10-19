#include <iostream>
#include "Player.h"
#include "Dice.h"
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
	*id = counter; //id of player generated 
}
Player::Player() {
	this->dice = new Dice();
	this->hand = new Hand(counter);
	counter++;
	*id = counter; //id of player generated
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


//returns vector of player countries
vector<Country*> Player::getPlayerCountries() {
	return playerCountries;
}

//gets id of player
int Player::getID() {
	return *id;
}

//Setters
void Player::setName(string name) {
	this->name = name;
}

//pushes player's countries to vector 
void Player::setPlayerCountries(Country* country) {
	playerCountries.push_back(country);
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

//to call players information in driver TO MODIFY 
void Player::display() {
	cout << " Player, " << name << " owns the following countries : " << endl;
	/*cout << playerCountries <<
	 ". The current rice roll is " << dice << ", and the current cards are " << hand << ". " << endl;*/
}

