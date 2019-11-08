//Driver class to test the player object
#include <iostream>
#include "Player.h"
#include "Map.h"
using namespace std;


//declares function that will be the drivers for part4, part5 and part 6 of assignment 2
void part4();
void part5();
void part6();

<<<<<<< HEAD
int main() {
     part4();
    // part5();
    //part6();
}

=======
//main method that can call each driver for each part
//uncomment the part you want to test
//int main() {
//    part4();
//    //part5();
//    // part6();
//}
>>>>>>> 3b93e59236ab7bbecd2f341d0dcf0bf1fdcc17a3

//driver for part4: reinforce of assignment2
void part4() {
    char answer;
    string name;
    cout << "Do you want to create a new player Y/N ? " << endl;
    cin >> answer;
    if (answer == 'Y') {
        cout << "what is the players name ?" << endl;
        cin >> name;
        Player* player = new Player(name);
        player->setName(name);
        Map* map = new Map();
        Country* country1 = new Country();
        Country* country2 = new Country();
        Country* country3 = new Country();
        Country* country4 = new Country();
        Country* country5 = new Country();
        Country* country6 = new Country();
        Country* country7 = new Country();
        Country* country8 = new Country();
        Country* country9 = new Country();
        Country* country10 = new Country();
        Country* country11 = new Country();
        Country* country12 = new Country();
        
        
        country1->setCountryName("Canada");
        country2->setCountryName("USA");
        country3->setCountryName("Mexico");
        country4->setCountryName("Italy");
        country5->setCountryName("France");
        country6->setCountryName("Japan");
        country7->setCountryName("China");
<<<<<<< HEAD


        // TWO CASES FOR REINFORCE
        cout << endl;
        cout << "case 1 for reinforce" << endl;
        player->reinforce();
=======
        country8->setCountryName("Denmark");
        country9->setCountryName("Costa Rica");
        country10->setCountryName("Sweden");
        country11->setCountryName("Finland");
        country12->setCountryName("Crotia");
>>>>>>> 3b93e59236ab7bbecd2f341d0dcf0bf1fdcc17a3
        
        //ownership of new countries
        country8->setCountryOwnerId(player->getID());
        country9->setCountryOwnerId(player->getID());
        country10->setCountryOwnerId(player->getID());
        country11->setCountryOwnerId(player->getID());
        
        player->setThisPlayerCountry(country8);
        player->setThisPlayerCountry(country9);
        player->setThisPlayerCountry(country10);
        player->setThisPlayerCountry(country11);
        
        
        map->setCountry(country1);
        map->setCountry(country2);
        map->setCountry(country3);
        map->setCountry(country4);
        map->setCountry(country5);
        map->setCountry(country6);
        map->setCountry(country7);
        map->setCountry(country8);
        map->setCountry(country9);
        map->setCountry(country10);
        map->setCountry(country11);
        map->setCountry(country12);
        
        
        
        //new deck based on number of countries in map (size of deck should be 3)
        Deck* deck = new Deck(map);
        
        deck->draw(player->getHand(), player->getName());
        deck->draw(player->getHand(), player->getName());
        deck->draw(player->getHand(), player->getName());
        deck->draw(player->getHand(), player->getName());
        deck->draw(player->getHand(), player->getName());
        
        cout << "\nCards in hand of player : " << endl;
        for (int i = 0; i < player->getHand()->getCardsInHand().size(); i++) {
            cout << "Type of card " << i+1 << " is: " << player->getHand()->getCardsInHand().at(i)->getType() << endl;
        }
        
        cout << "\nCountries of player" << endl;
        for(int i = 0; i<player->getThisPlayerCountries().size(); i++) {
            cout << player->getThisPlayerCountries().at(i)->getCountryName() << endl;
        }
        
        
        
        //  int newArmy;
        
        //  newArmy = country4->getNumberOfArmies() + player->getNumOfArmiesAtStartUpPhase();
        //  country4->setNumberOfArmies(newArmy);
        //  cout << "number of armies in Italy is " << country4->getNumberOfArmies() << endl;
        
        
        // TWO CASES FOR REINFORCE
        // cout << endl;
        // cout << "case 1 for reinforce" << endl;
        player->reinforce();
        
        
        // player owns continents and has 5 cards for exchange
        // cout << endl;
        
        
        
        
        // adding extra countries that are all in the same continent in risk.map to demonstrate how a player gets extra points if conquers a continent
        
        
        
        
        // print all cards in player's hand
        //player->getHand()->getCardsInHand();
        
        // should show different armiy count, including an owned continent and a force card exchange
        // player->reinforce();
        
        // newArmy = country10->getNumberOfArmies() + player->getNumOfArmiesAdd();
        // country11->setNumberOfArmies(newArmy);
        // cout << "number of armies in Brazil is " << country10->getNumberOfArmies() << endl;
        
        delete player;
        player = NULL;
        delete map;
        map = NULL;
        delete country1;
        country2 = NULL;
        delete country2;
        country2 = NULL;
        delete country3;
        country3 = NULL;
        delete country4;
        country4 = NULL;
        delete country5;
        country5 = NULL;
        delete country6;
        country6 = NULL;
        delete country7;
        country7 = NULL;
        delete country8;
        country8 = NULL;
        delete country9;
        country9 = NULL;
        delete country10;
        country10 = NULL;
        delete country11;
        country11 = NULL;
        delete deck;
        deck = NULL;
    }
}

//driver for part 5: attack of assignment 2
void part5() {
    
    Map* map = new Map();
    Country* country1 = new Country();
    Country* country2 = new Country();
    Country* country3 = new Country();
    Country* country4 = new Country();
    Country* country5 = new Country();
    Country* country6 = new Country();
    Country* country7 = new Country();
    
    Player* player = new Player();
    Player* player2 = new Player();
    
    // add countries to map
    map->setCountry(country1);
    map->setCountry(country2);
    map->setCountry(country3);
    map->setCountry(country4);
    map->setCountry(country5);
    map->setCountry(country6);
    map->setCountry(country7);
    
    // setting country names
    country1->setCountryName("Canada");
    country2->setCountryName("USA");
    country3->setCountryName("Mexico");
    country4->setCountryName("Italy");
    country5->setCountryName("France");
    country6->setCountryName("Japan");
    country7->setCountryName("China");
    
    // setting neighbor countries
    country1->setAdjacentCountries(country2);
    country1->setAdjacentCountries(country3);
    country2->setAdjacentCountries(country1);
    country2->setAdjacentCountries(country3);
    country3->setAdjacentCountries(country1);
    country3->setAdjacentCountries(country2);
    country4->setAdjacentCountries(country5);
    country4->setAdjacentCountries(country6);
    country5->setAdjacentCountries(country4);
    country5->setAdjacentCountries(country6);
    country5->setAdjacentCountries(country7);
    country6->setAdjacentCountries(country4);
    country6->setAdjacentCountries(country5);
    country7->setAdjacentCountries(country5);
    
    // setting number of armies on each country
    country1->setNumberOfArmies(10);
    country2->setNumberOfArmies(5);
    country3->setNumberOfArmies(8);
    country4->setNumberOfArmies(1);
    country5->setNumberOfArmies(5);
    country6->setNumberOfArmies(3);
    country7->setNumberOfArmies(0);
    
    // setting owners of each country
    
    country1->setCountryOwnerId(player->getID());
    country2->setCountryOwnerId(player->getID());
    country4->setCountryOwnerId(player->getID());
    country6->setCountryOwnerId(player->getID());
    country3->setCountryOwnerId(player2->getID());
    country5->setCountryOwnerId(player2->getID());
    country7->setCountryOwnerId(player2->getID());
    player->setThisPlayerCountry(country1);
    player->setThisPlayerCountry(country2);
    player->setThisPlayerCountry(country4);
    player->setThisPlayerCountry(country6);
    player2->setThisPlayerCountry(country3);
    player2->setThisPlayerCountry(country5);
    player2->setThisPlayerCountry(country7);
    
    
    // initializing attack phase
    player->attack();
    
    delete country1;
    country1 = NULL;
    delete country2;
    country2 = NULL;
    delete country3;
    country3 = NULL;
    delete country4;
    country4 = NULL;
    delete country5;
    country5 = NULL;
    delete country6;
    country6 = NULL;
    delete country7;
    country7 = NULL;
    delete map;
    map = NULL;
    delete player;
    player = NULL;
    delete player2;
    player2 = NULL;
}

//driver for part 6: fortify of assignment 2
void part6() {
    
    char answer;
    string name;
    cout << "Do you want to create a new player Y/N ? " << endl;
    cin >> answer;
    
    Map* map = new Map();
    Country* country1 = new Country();
    Country* country2 = new Country();
    Country* country3 = new Country();
    Country* country4 = new Country();
    Country* country5 = new Country();
    Country* country6 = new Country();
    Country* country7 = new Country();
    
    
    if (answer == 'Y') {
        cout << "what is the players name ?" << endl;
        cin >> name;
        Player* player = new Player(name);
        player->setName(name);
        
        // COUNTRIES
        country1->setCountryName("Canada");
        country2->setCountryName("USA");
        country3->setCountryName("Mexico");
        country4->setCountryName("Italy");
        country5->setCountryName("France");
        country6->setCountryName("Japan");
        country7->setCountryName("China");
        
        
        country1->setAdjacentCountries(country2);
        country2->setAdjacentCountries(country1);
        country2->setAdjacentCountries(country3);
        country4->setAdjacentCountries(country5);
        country5->setAdjacentCountries(country4);
        country6->setAdjacentCountries(country7);
        country7->setAdjacentCountries(country6);
        
        country1->setNumberOfArmies(10);
        country2->setNumberOfArmies(5);
        country3->setNumberOfArmies(8);
        country4->setNumberOfArmies(4);
        country5->setNumberOfArmies(5);
        country6->setNumberOfArmies(3);
        country7->setNumberOfArmies(9);
        
        country1->setCountryOwnerId(player->getID());
        country2->setCountryOwnerId(player->getID());
        country3->setCountryOwnerId(player->getID());
        country4->setCountryOwnerId(player->getID());
        country5->setCountryOwnerId(player->getID());
        country6->setCountryOwnerId(player->getID());
        //  country7->setCountryOwnerId(player->getID());
        
        map->setCountry(country1);
        map->setCountry(country2);
        map->setCountry(country3);
        map->setCountry(country4);
        map->setCountry(country5);
        map->setCountry(country6);
        // map->setCountry(country7);
        
        player->setMap(map);
        
        int playerID = player->getID();
        
        map->getOwnerCountries(playerID);
        
        player->setThisPlayerCountry(country1);
        player->setThisPlayerCountry(country2);
        player->setThisPlayerCountry(country3);
        player->setThisPlayerCountry(country4);
        player->setThisPlayerCountry(country5);
        player->setThisPlayerCountry(country6);
        // player->setThisPlayerCountry(country7);
        
        // HAND
        Cards* card1 = new Cards(0, 1);
        Cards* card2 = new Cards(1, 5);
        Cards* card3 = new Cards(2, 10);
        
        Deck* deck = new Deck();
        deck->setCardInDeck(card1);
        deck->setCardInDeck(card2);
        deck->setCardInDeck(card3);
        
        //add card2 to player's hand
        player->getHand()->setCardInHand(card2);
        
        //print all cards in player's hand (should be card2)
        player->getHand()->getCardsInHand();
        
        // initializing fortify phase
        player->fortify();
        
        delete player;
        player = NULL;
        delete card1;
        card1 = NULL;
        delete card2;
        card2 = NULL;
        delete card3;
        card3 = NULL;
        delete deck;
        deck = NULL;
    }
    else {
        cout << "Thank you for playing, Have a good day" << endl;
    }
    
    delete country1;
    country1 = NULL;
    delete country2;
    country2 = NULL;
    delete country3;
    country3 = NULL;
    delete country4;
    country4 = NULL;
    delete country5;
    country5 = NULL;
    delete country6;
    country6 = NULL;
    delete country7;
    country7 = NULL;
    delete map;
    map = NULL;
}
