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
    Cards(const Cards& orig); //copy constructor
    ~Cards();
    std::string getType(); //type of card
    void setType(int typeNum);
    int getWorth(); //worth in armies
    void setWorth(int worth);
private:
    std::unique_ptr<int> typeNum; // //Type of card 0 -> infrantry, 1 -> artillery, 2 -> cavalry
    std::unique_ptr<int> worth; // //Worth of each card in terms of armies infantry -> 1 army, cavalry -> 5 armies, artillery -> 10 armies
    std::unique_ptr<std::string> type; 
};

class Deck {
public:
    Deck();
    Deck(Map* map);
    ~Deck();
    Cards* card;
    std::vector<Cards*> getCardsInDeck(); //returns vector of cards objects
    void setCardInDeck(Cards* card);
    int getNumOfCardsInDeck();
    void draw(Hand* hand, std::string playerName); //draw method that allows player to draw a card from the cards remaining in the deck
private:
    std::unique_ptr<int> numOfCardsInDeck; //number of cards (= number of countries in the map)
    std::unique_ptr<int> cardsPerType; //Same number of cards per each type (infantry, cava, art)
    std::vector<Cards*> cardsInDeck; //declare vectors of card objects in deck
};

class Hand {
public:
    Hand();
    Hand(const Hand& orig);
    const Hand& operator=(const Hand& h);
    Hand(int id);
    ~Hand();
    void exchange(); //exchange cards in hand in returns of armies
    void removeCard(int index);
    void setCardInHand(Cards* card);
    std::vector<Cards*> getCardsInHand();
    int getNumberOfArmiesToPlace();
    void setNumberOfArmiesToPlace(int num);
    void addNumberOfArmies(int num);
    void deleteNumberOfArmies(int num);
    void setAutom(bool autom);
    bool getAutom();
private:
    int id;
    static int numArmiesExchanged; //number of armies a player will get from an exchange of set of cards
    static int* exchangeCount; // number of exchanges player has done
    std::vector<Cards*> cardsInHand;
    std::unique_ptr<int> numOfArmiesToPlace; // number of armies the player needs to place on the map when his turn starts
    bool autom; // determines exchange (false if user, true if computer player)
};
