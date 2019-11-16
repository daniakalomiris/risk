
#include <iostream>
#include <string>
#include "GameEngine.h"
#include "time.h"
#include <random>
#include <chrono>

using namespace std;

//maximum and minimum number of players that can play the game
const int MIN_PLAYERS = 2;
const int MAX_PLAYERS = 6;


//constructor
GameEngine:: GameEngine() {
    maploader = new MapLoader();
    endGame = make_unique<bool>(false);
}

//destructor
GameEngine:: ~GameEngine() {
    delete maploader;
    delete deck;
}

//ask user the number of players playing
void GameEngine::askNumberOfPlayers() {
    
    //variable to store user input
    int numPlayersEntered;
    
    cout << "Please enter the number of players (between 2 and 6): " << endl;
    
    cin >> numPlayersEntered;
    
    //verifies that user input a valid number of players and asks them to input again if not
    while (numPlayersEntered<MIN_PLAYERS || numPlayersEntered > MAX_PLAYERS) {
        cout << "Invalid entry. Please enter a number between 2 and 6" << endl;
        cin >> numPlayersEntered;
    }
    
    cout << "Ok, there will be " << numPlayersEntered << " players" << endl;
    
    
    //sets the numberOfPlayers
    this->setNumberOfPlayers(numPlayersEntered);
    
}


void GameEngine::setNumberOfPlayers(int numberOfPlayers) {
    this->numberOfPlayers = make_unique<int>(numberOfPlayers);
}

int GameEngine::getNumberOfPlayers() {
    return *numberOfPlayers;
}

int GameEngine::getNumberOfArmiesPerPlayer() {
    return *numberOfArmiesPerPlayer;
}

Map* GameEngine:: getMap() {
    return map;
}

void GameEngine::setMap(Map *newMap) {
    this->map = new Map();
    *map = *newMap;
}
bool GameEngine::getEndGame() {
    return *endGame;
}

void GameEngine::setEndGame(bool value) {
    *endGame = value;
}

//sets the number of armies per player depending of the number of players
void GameEngine::setNumberOfArmiesPerPlayer() {
    
    //number of armies per player
    int A;
    
    //number of armies depends on the number of players
    if (this->allPlayers.size() == 2) {
        A = 40;
    }
    else if(this->allPlayers.size() == 3) {
        A = 35;
    }
    
    else if(this->allPlayers.size() == 4){
        A = 30;
    }
    
    else if(this->allPlayers.size() == 5) {
        A = 25;
    }
    
    else if(this->allPlayers.size() == 6) {
        A = 20;
    }
    else {
        cout << "The number of players must be between 2 and 6. The program will terminate. " << endl;
        exit(1);
    }
    
    //set the number of armies per player pointer variable
    numberOfArmiesPerPlayer = make_unique<int>(A);
    
    //gives to each player a numberOfArmies at startup phase
    for(int i =0; i < allPlayers.size(); i++) {
        allPlayers.at(i)->setNumOfArmiesAtStartUpPhase(*numberOfArmiesPerPlayer);
    }
}

//placing armies on countries
void GameEngine::setArmiesToCountries() {
    
    //tells if the placement of armies is done
    bool done = false;
    
    //puts 1 army in each player country
    for (int i = 0; i < allPlayers.size(); i++) {
        
        //tells the number of remaining armies to place on the map per player
        int remainingArmies = this->getNumberOfArmiesPerPlayer();
        
        //place at least 1 army on each player's countries and decrease the remaining armies
        for(int j =0; j < allPlayers.at(i)->getThisPlayerCountries().size(); j++) {
            allPlayers.at(i)->getThisPlayerCountries().at(j)->setNumberOfArmies(1);
            remainingArmies = remainingArmies -1;
        }
        
        //set the number of armies a player need to place to the remaining armies
        allPlayers.at(i)->setNumOfArmiesAtStartUpPhase(remainingArmies);
    }
    
    
    cout << "each country has 1 army now" << endl;
    
    //while we are done placing armies
    while(done == false) {
        
        //players can place remainder of armies on country of their choice
        for (int i = 0; i < allPlayers.size(); i++) {
            
            bool isCountryChosenValid = false;
            
            //country chosen by player to place an army on and its index
            string countryChosen;
            int indexOfCountryChosen = 0;
            
            cout << "\n\nPlayer " << allPlayers.at(i)->getName() << " turn" << endl;
            cout << "This is your countries with their number of armies" << endl;
            
            //loops through all countries of the player which is set to play
            for(int j = 0; j < allPlayers.at(i)->getThisPlayerCountries().size(); j++ ) {
                cout << allPlayers.at(i)->getThisPlayerCountries().at(j)->getCountryName() << " " << allPlayers.at(i)->getThisPlayerCountries().at(j)->getNumberOfArmies() << endl;
            }
            
            cout << "You have " << allPlayers.at(i)->getNumOfArmiesAtStartUpPhase() << " armies left to place" << endl;
            cout << "Enter the name of the country you would like to place one army" << endl;
            
            
            cin >> countryChosen;
            
            
            //check if the country enter is valid
            for(int j = 0; j < allPlayers.at(i)->getThisPlayerCountries().size(); j++ ) {
                
                //if the country is own by the player, the country is valid
                if(countryChosen.compare(allPlayers.at(i)->getThisPlayerCountries().at(j)->getCountryName()) == 0 ) {
                    isCountryChosenValid = true;
                    indexOfCountryChosen = j;
                }
            }
            
            //ask to enter another country if the one enter is not valid
            while(isCountryChosenValid == false) {
                
                cout << "You have enter the name of an invalid country" << endl;
                cout << "Enter the name of the country you would like to place one army" << endl;
                
                cin >> countryChosen;
                
                //check if the country enter is valid
                for(int j = 0; j < allPlayers.at(i)->getThisPlayerCountries().size(); j++ ) {
                    
                    //if the country is own by the player, the country is valid
                    if(countryChosen.compare(allPlayers.at(i)->getThisPlayerCountries().at(j)->getCountryName()) == 0 ) {
                        isCountryChosenValid = true;
                        indexOfCountryChosen = j;
                    }
                }
            }
            
            
            //if country chosen is valid put 1 armie in that country
            int numOfAmrmiesInCountry = allPlayers.at(i)->getThisPlayerCountries().at(indexOfCountryChosen)->getNumberOfArmies();
            numOfAmrmiesInCountry = numOfAmrmiesInCountry +1;
            allPlayers.at(i)->getThisPlayerCountries().at(indexOfCountryChosen)->setNumberOfArmies(numOfAmrmiesInCountry);
            
            //delete the number of armies to place for the player
            int numOfArmiesToPlace = allPlayers.at(i)->getNumOfArmiesAtStartUpPhase();
            numOfArmiesToPlace = numOfArmiesToPlace -1;
            allPlayers.at(i)->setNumOfArmiesAtStartUpPhase(numOfArmiesToPlace);
            
            
            //Display the new number of armies on the country chosen
            cout << "You have place 1 more army on the country " << allPlayers.at(i)->getThisPlayerCountries().at(indexOfCountryChosen)->getCountryName()<< endl;
            cout << allPlayers.at(i)->getThisPlayerCountries().at(indexOfCountryChosen)->getCountryName() << " has now " << allPlayers.at(i)->getThisPlayerCountries().at(indexOfCountryChosen)->getNumberOfArmies() << " armies " << endl;
            
            //checks if all armies have been placed
            if(allPlayers.at(i)->getNumOfArmiesAtStartUpPhase() == 0) {
                done = true;
            }
        }
    }
}

//creates players
void GameEngine::createPlayers() {
    
    string playerName;
    
    for (int i = 0; i < this->getNumberOfPlayers(); i++) {
        
        cout << "\nPlease enter the name of player " << i +1 << endl;
        cin >> playerName;
        
        //creates a player with name, dice, and hand
        Player* player = new Player(playerName, getMap());
        player->setName(playerName);
        
        //sets the player
        setPlayer(player);
        
    }
    Notify(); //displays when players are created even if they do not have countries yet
}

//adds players to vector of players
void GameEngine::setPlayer(Player* player) {
    cout << "adding player to list of players" << endl;
    allPlayers.push_back(player);
}

//returns unordered vector of players
vector<Player*> GameEngine::getAllPlayers() {
    return allPlayers;
}

//randomly set players' turns
void GameEngine::setPlayerOrder() {
    
    //get a time base seed to have a new random random generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    
    //shuffle the player's order
    shuffle(this->allPlayers.begin(), this->allPlayers.end(), default_random_engine(seed));
    
    
}

//displays order of players
void GameEngine::showPlayerOrder() {
    for (int i = 0; i<allPlayers.size(); i++) {
        cout << "Player " << allPlayers[i]->getName() << " is at position " << (i + 1) << endl;
    }
    
}

//assigning countries to each player
void GameEngine::assignCountriesToPlayers() {
    
    int numOfCountries = this->map->getCountries().size(); //number of countries in the map
    int numOfPlayers = this->allPlayers.size();
    
    //number of countries assigned to players
    int countryNumberPushed = 0;
    
    //index of the player who's playing
    int playerTurns = 0;
    
    //contains index of countries already assigned to a player
    vector<int> countriesAlreadyAssigned;
    
    // Resets the random
    srand(time(NULL));
    
    //checks that there are still countries to assign
    while(countryNumberPushed < numOfCountries) {
        
        int randomCountry = rand() % numOfCountries;
        
        //if the index of countries is not already assigned
        if(find(countriesAlreadyAssigned.begin(), countriesAlreadyAssigned.end(), randomCountry) == countriesAlreadyAssigned.end()) {
            
            //set the country to the player
            this-> allPlayers.at(playerTurns)->setThisPlayerCountry(map->getCountries().at(randomCountry));
            //set the owner id
            map->getCountries().at(randomCountry)->setCountryOwnerId(allPlayers.at(playerTurns)->getID());
            
            //loops through all players once
            if(playerTurns < this->allPlayers.size()-1) {
                playerTurns ++;
            }
            //resets playerTurns to go through the loop again with the first player
            else {
                playerTurns = 0;
            }
            
            countryNumberPushed ++;
            countriesAlreadyAssigned.push_back(randomCountry);
        }
    }
    Notify(); //Notify PlayerDomination when countries are initially assigned to players to display original stats
    
}

//displays countries of a player
void GameEngine::displayCountriesOfPlayers() {
    for (int i = 0; i < allPlayers.size(); i++) {
        cout << "\n\nPlayer " << allPlayers.at(i)->getName() << "(ID: "<< allPlayers.at(i)->getID() << ") countries: " << endl;
        
        for (int j = 0; j < allPlayers.at(i)->getThisPlayerCountries().size(); j++) {
            cout << j+1 << " " << allPlayers.at(i)->getThisPlayerCountries().at(j)->getCountryName() << endl;
        }
    }
    Notify();
}

//creates a map based on the choice of the user
void GameEngine::createMap() {
    int mapChoice;
    string mapFile; //input of user
    
    
    cout << "\nPlease enter the number associated with the map you would like to play on: \n"
    "Select 1 for Big Europe \n"
    "Select 2 for Geoscape \n"
    "Select 3 for LOTR \n"
    "Select 4 for Risk \n"
    "Select 5 for Solar \n"
    "Select 6 for notvalid2 \n" << endl;
    
    cin >> mapChoice;
    
    //checks if entry is valid
    while(mapChoice<1 || mapChoice>6){
        cout << "Invalid entry please nter a valid choice: \n"
        "Select 1 for Big Europe \n"
        "Select 2 for Geoscape \n"
        "Select 3 for LOTR \n"
        "Select 4 for Risk \n"
        "Select 5 for Solar \n"
        "Select 6 for notvalid2 \n"<< endl;
        
        cin >> mapChoice;
    }
    
    //associated choice of user with a map that is available
    if (mapChoice == 1) {
        cout << "You selected Big Europe. We will load that up for you" << endl;
        mapFile = "bigeurope";
    }
    else if (mapChoice == 2) {
        cout << "You selected Geoscape. We will load that up for you" << endl;
        mapFile = "geoscape";
    }
    else if (mapChoice == 3) {
        cout << "You selected LOTR. We will load that up for you" << endl;
        mapFile = "lotr";
    }
    else if (mapChoice == 4) {
        cout << "You selected Risk. We will load that up for you" << endl;
        mapFile = "risk";
    }
    else if (mapChoice == 5) {
        cout << "You selected Solar. We will load that up for you" << endl;
        mapFile = "solar";
    }
    
    else if (mapChoice == 6) {
        cout << "You selected notvalid2. We will load that up for you" << endl;
        mapFile = "notvalid2";
    }
    
    //calls methods from maploader to open the file selected, create it, and display it
    maploader->readMapFile("maps/" + mapFile+ ".map");
    maploader->createMap();
    maploader->displayMap();
    
    //assign the map to maploader
    map = maploader->getMap();
    
    //create a new deck based on the map selected
    deck = new Deck(map);
    
}


//part 3: main game loop, each player play turn by turn
void GameEngine:: mainGameLoop() {
    
    bool allCountriesOwnByPlayer = false;
    int indexOfWinningPlayer = 0;
    
    
  
    
    
    cout << "\n\n****** Main Game Loop *******" << endl;
    
    //while the game is still playing
    while (getEndGame() == false) {
        
        //vector of the country owner id before the attack
          vector<int> OldCountryOwnerId;
        
        for(int i = 0; i< this->getNumberOfPlayers(); i++) {
            
            //if the player doesn't own any countries, skip his turn
            if(this->getAllPlayers().at(i)->getThisPlayerCountries().size() ==0) {
                continue;
            }
            
            //display which player is playing
            cout << "\n\n************** Player " << this->getAllPlayers().at(i)->getName() << "'s turn **************\n" << endl;
            
            //make the player reinforce, attack and fortify
            this->getAllPlayers().at(i)->reinforce();
			Notify();
            
            
            //get the countryOwnerId for all countries before the attack
            for(int j=0; j < map->getCountries().size(); j++) {
                OldCountryOwnerId.push_back(map->getCountries().at(j)->getCountryOwnerId());
            }
            
            this->getAllPlayers().at(i)->attack();
            
            //compare the old owner ID with the new owner Id if a player won a country
            
            for(int j = 0; j < map->getCountries().size(); j++) {
                
                int indexPlayerLostCountry;
                
                //if the owner id has changed delete the country from the old owner player
                if(OldCountryOwnerId.at(j) != map->getCountries().at(j)->getCountryOwnerId()) {
                    
                    //code for debug, i will erase it before submitting
                   // cout << "the country that the player wins " << map->getCountries().at(j)->getCountryName() << endl;
                   // cout << "ID of the player who lost a country " << OldCountryOwnerId.at(j) << endl;
                    
                    
                    
                    //get the index of player that lost a country
                    for(int k=0; k< getAllPlayers().size(); k++) {
                        
                        if(OldCountryOwnerId.at(j) == getAllPlayers().at(k)->getID()) {
                            indexPlayerLostCountry = k;
                        }
                        
                        
                    }
                    //code for debug, i will erase it before submitting
                   // cout << "index of player what lost a country" << indexPlayerLostCountry << endl;
                    this->getAllPlayers().at(indexPlayerLostCountry)->deleteThisPlayerCountry(map->getCountries().at(j));
                }
            }
            
            //reset the countryOwnerId
            OldCountryOwnerId.clear();
            
                        
			Notify();
            this->getAllPlayers().at(i)->fortify();
			Notify();
            
            
            //check if a player owns all the countries
            if(this->getAllPlayers().at(i)->getThisPlayerCountries().size() == this->map->getCountries().size()) {
                this->setEndGame(true);
                Notify();
            }
            
            
        }
        
        //check if countries are own by same player"
        for(int j =0; j < this->getMap()->getCountries().size()-1; j++) {
            
            //compare the index of the country owner with the next one, if they are not the same then the countries are not own byt the player
            if(getMap()->getCountries().at(j)->getCountryOwnerId() != getMap()->getCountries().at(j+1)->getCountryOwnerId()) {
                allCountriesOwnByPlayer = false;
                break;
            }
            
            else {
                allCountriesOwnByPlayer = true;
                indexOfWinningPlayer = getMap()->getCountries().at(0)->getCountryOwnerId();
            }
            
        }
        
        //if countries are own by same player, set the game to end. There is a winner.
        if(allCountriesOwnByPlayer == true) {
            this->setEndGame(true);
        }
    }
    
    cout << "\n\n **************Player " << indexOfWinningPlayer +1 << " wins the game **************\n End of the game" << endl;
}
