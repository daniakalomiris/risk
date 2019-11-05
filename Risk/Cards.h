#pragma once

#include "Map.h"
#include <string>
#include <vector>
#include <memory>

class Deck;
class Hand;

class Cards {
public:
	Cards();
	Cards(int typeNum, int worth);
	~Cards();

	//type of card 
    std::string getType();
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
	std::unique_ptr<int> typeNum;

	// //Worth of each card in terms of armies infantry -> 1 army, cavalry -> 5 armies, artillery -> 10 armies
	std::unique_ptr<int> worth;

	std::unique_ptr<std::string> type;

	// -1 if in deck, otherwise increment when drawn to hand
	int locationId;

};

class Deck {
public:
	Deck();
	Deck(Map* map);
	~Deck();

	Cards* card;

	//returns vector of cards objects
	std::vector<Cards*> getCardsInDeck();
	void setCardInDeck(Cards* card);

	int getNumOfCardsInDeck();

	//draw method that allows player to draw a card from the cards remaining in the deck
	void draw(Hand* hand, std::string playerName);


private:
	//number of cards (= number of countries in the map)
	std::unique_ptr<int> numOfCardsInDeck;

	//Same number of cards per each type (infantry, cava, art)
	std::unique_ptr<int> cardsPerType;

	//declare vectors of card objects in deck
	std::vector<Cards*> cardsInDeck;
};

class Hand {
public:
	Hand();
	Hand(int id);
	~Hand();
    
    //exchange cards in hand in returns of armies
    void exchange(Hand* hand);
    
    void removeCard(int index);
    void setCardInHand(Cards* card);
    std::vector<Cards*> getCardsInHand();
    int getNumberOfArmiesToPlace();
    void setNumberOfArmiesToPlace(int num);
    void addNumberOfArmies(int num);
    void deleteNumberOfArmies(int num);

private:
	int id;
    
    //number of armies a player will get from an exchange of set of cards
	static int numArmiesExchanged ;
	static int* exchangeCount; // number of exchanges player has done
    std::vector<Cards*> cardsInHand;
    
    // number of armies the player needs to place on the map when his turn starts
    std::unique_ptr<int> numOfArmiesToPlace;
};
