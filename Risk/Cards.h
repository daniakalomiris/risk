#pragma once

#include "Map.h"
#include "Player.h"
#include <string>
#include <vector>
#include <memory>

class Deck;
class Hand;

class Cards {
public:
	Cards();
	~Cards();

	//type of card 
	std::string* getType();
	void setType(int typeNum);

	//worth in armies
	int getWorth();
	void setWorth(int worth);

	//location of card based on id of player 
	int getLocationId();
	void setLocationId(int locationId);

	//void setDeck(Deck* deck);

private:
	// //Type of card 0 -> infrantry, 1 -> artillery, 2 -> cavalry
	int* typeNum;

	// //Worth of each card in terms of armies infantry -> 1 army, cavalry -> 5 armies, artillery -> 10 armies
	int* worth;

	std::string* type;

	// -1 if in deck, otherwise increment when drawn to hand
	int locationId;

};

class Deck {
public:
	Deck(Map* map);
	~Deck();

	Cards* card;

	//returns vector of cards objects
	std::vector<Cards*> getCardsInDeck();
	void setCardInDeck(Cards* card);

	int* getNumOfCardsInDeck();

	//draw method that allows player to draw a card from the cards remaining in the deck
	void draw(int playerId, Hand* hand, Deck* deck);


private:
	//number of cards (= number of countries in the map)
	int* numOfCardsInDeck;

	//Same number of cards per each type (infantry, cava, art)
	int* cardsPerType;

	//declare vectors of card objects in deck
	std::vector<Cards*> cardsInDeck;
};

class Hand {
public:
	Hand();
	Hand(int id);
	~Hand();

	//Player *player; 

	void exchange(Deck* deck, Hand* hand);

	//card to be removed from hand during exchange
	// void removeCardFromHand(Cards* cardExchanged);

	void getCardsInHand(Deck* deck);
	void setCardInHand(Cards* card);

	int getNumOfArmies();
	void setNumOfArmies(int numOfArmies);


private:
	int id;
	int numOfArmies; // number of armies player has
	int armiesExchanged;
	int exchangeCount; // number of exchanges player has done
};