
#include <iostream>
#include <string>
#include "GameEngine.h"
#include "PlayerStrategies.h"
#include "time.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
using namespace std;

//maximum and minimum number of players that can play the game
const int MIN_PLAYERS = 2;
const int MAX_PLAYERS = 6;
std::string phase;
class Tournament;


//constructor
GameEngine:: GameEngine() {
    maploader = new MapLoader();
    endGame = make_unique<bool>(false);
    gameMode = make_unique<bool>(false);
    winner = make_unique<string>("Draw");
}


//copy constructor
GameEngine::GameEngine(const GameEngine& orig) {
    
    this->maploader = new MapLoader();
    *maploader = *orig.maploader;
    this->endGame = make_unique<bool>(false);
    this->gameMode = make_unique<bool>(false);
    
}

//assignment operator
const GameEngine& GameEngine::operator=(const GameEngine& g){
    
    if(&g != this) {
        this->maploader = new MapLoader();
        *maploader = *g.maploader;
        this->endGame = make_unique<bool>(false);
        this->gameMode = make_unique<bool>(false);
    }
    
    return *this;
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

// phase == 1 is for reinforce, phase == 2 is for attack, phase == 3 is for fortify
void GameEngine::setPhase(int phase) {
    this->phase = make_unique<int>(phase);
}
int GameEngine::getPhase() {
    return *phase;
}

int GameEngine::getMaxNumTurn() {
    return *maxNumTurn;
}

void GameEngine::setMaxNumTurn(int max) {
    maxNumTurn.reset(new int(max));
}

void GameEngine::setGameMode(bool mode){
    *gameMode = mode;
}

bool GameEngine::getGamemode(){
    return *gameMode;
}

string GameEngine::getWinner() {
    return *winner;
}

void GameEngine::setWinner(string name) {
    this->winner.reset(new string(name));
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
    srand(time(NULL)); // reset randomize
    
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
            
 
           //it means we have a user player
            if( allPlayers.at(i)->getStrategyNum() == 5) {
                //use this if we the user chose it himself
                cin >> countryChosen;
            }
            
            //else it is a computer player
            else {
                //pick randomly a country to put armies on
                int temp = rand() % (allPlayers.at(i)->getThisPlayerCountries().size());
                
                //assign the country name of the random chosen country to the countryChosen string varialbe.
                countryChosen = allPlayers.at(i)->getThisPlayerCountries().at(temp)->getCountryName();
                
                cout << "You chose the country " << countryChosen << endl;
            }
            
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
    int strategy =0;
    for (int i = 0; i < this->getNumberOfPlayers(); i++) {
        
        
        int strategy;
        cout << "\nWhich strategy would you like to use for player #" << i+1 << "? Please enter the number of the strategy to make your choice." << endl;
        cout << "(1) Aggressive Strategy" << endl;
        cout << "(2) Benevolent Strategy" << endl;
        cout << "(3) Cheater Strategy" << endl;
        cout << "(4) Random Strategy" << endl;
        cout << "(5) User Strategy" << endl;
        cin >> strategy;
        
        while (strategy < 0 || strategy > 5) {
            cout << "Please select a valid strategy from the list of strategies." << endl;
            cin >> strategy;
        }
        
        
        Aggressive* aggressive = new Aggressive();
        Benevolent* benevolent = new Benevolent();
        User* user = new User();
        //WILL NEED TO CREATE A RANDOM AND CHEATER TOO
        //Random random = new Random();
        //Cheater cheater = new Cheater;
        switch (strategy) {
            case 1: {
                Player *aPlayer = new Player("Aggressive", getMap());
                cout << "The player #" << i+1 << " will play as an Aggressive computer player" << endl;
                aPlayer->setStrategy(aggressive);
                aPlayer->setStrategyNum(1);
                setPlayer(aPlayer);
                break;
            }
            case 2: {
                Player *bPlayer = new Player("Benevolant", getMap());
                cout << "The player #" << i+1 << " will play as an Benevolant computer player" << endl;
                bPlayer->setStrategy(benevolent);
                bPlayer->setStrategyNum(2);
                setPlayer(bPlayer);
                break;
            }
            case 3: {
                Player *cPlayer = new Player("Cheater", getMap());
                cout << "The player #" << i+1 << " will play as an Cheater computer player" << endl;
                //  cPlayer->setStrategy(cheater);
                //cPlayer->setStrategyNum(3);
                setPlayer(cPlayer);
                break;
            }
            case 4: {
                Player *rPlayer = new Player("Random", getMap());
                cout << "The player #" << i+1 << " will play as an Random computer player" << endl;
                //  rPlayer->setStrategy(random);
                //rPlayer->setStrategyNum(4);
                setPlayer(rPlayer);
                break;
            }
            case 5: {
                Player *hPlayer = new Player("User", getMap());
                cout << "The player #" << i+1 << " will play as an User human player" << endl;
                hPlayer->setStrategy(user);
                hPlayer->setStrategyNum(5);
                setPlayer(hPlayer);
                break;
            }
            default: {
                break;
            }
        }
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
void GameEngine::createMap(string mapFile) {
    
    //calls methods from maploader to open the file selected, create it, and display it
    maploader->readMapFile("maps/domination/" + mapFile+ ".map");
    maploader->createMap();
    maploader->displayMap();
    
    //assign the map to maploader
    map = maploader->getMap();
    
    //create a new deck based on the map selected
    deck = new Deck(map);
    
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
    maploader->readMapFile("maps/domination/" + mapFile+ ".map");
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
    int numTurnsPlayed = 0;
    cout << "\n\n****** Main Game Loop *******" << endl;
    
    //while the game is still playing
    cout << "END GAME: " << boolalpha << getEndGame() << endl;
    while (getEndGame() == false) {
        
        //increment the number of turns played
        numTurnsPlayed++;
        
        //vector of the country owner id before the attack
        vector<int> OldCountryOwnerId;
        
        for(int i = 0; i< this->getNumberOfPlayers(); i++) {
            
            //if the player doesn't own any countries, skip his turn
            if(this->getAllPlayers().at(i)->getThisPlayerCountries().size() ==0) {
                continue;
            }
            
            //display which player is playing
            cout << "\n\n************** Player " << this->getAllPlayers().at(i)->getName() << "'s turn **************\n" << endl;
            
            
            currentPlayerIndex = i;
            //make the player reinforce, attack and fortify
            setPhase(1);
            Notify();
            
            this->getAllPlayers().at(i)->reinforce();
            Notify();
            
            //make the phaseStart back to false, so we don't display data that we didn't enter yet
            this->getAllPlayers().at(i)->setPhaseStart(false);
            
            //get the countryOwnerId for all countries before the attack
            for(int j=0; j < map->getCountries().size(); j++) {
                OldCountryOwnerId.push_back(map->getCountries().at(j)->getCountryOwnerId());
            }
            
            setPhase(2);
            Notify();
            this->getAllPlayers().at(i)->attack();
            
            //compare the old owner ID with the new owner Id if a player won a country
            for(int j = 0; j < map->getCountries().size(); j++) {
                
                int indexPlayerLostCountry =0;
                
                //if the owner id has changed delete the country from the old owner player
                if(OldCountryOwnerId.at(j) != map->getCountries().at(j)->getCountryOwnerId()) {
                    
                    
                    //get the index of player that lost a country
                    for(int k=0; k< getAllPlayers().size(); k++) {
                        
                        if(OldCountryOwnerId.at(j) == getAllPlayers().at(k)->getID()) {
                            indexPlayerLostCountry = k;
                        }
                    }
                    
                    this->getAllPlayers().at(indexPlayerLostCountry)->deleteThisPlayerCountry(map->getCountries().at(j));
                }
            }
            
            //check if a player owns a continent
            this->getAllPlayers().at(i)->checkControlContinents();
            
            //reset the countryOwnerId
            OldCountryOwnerId.clear();
            
            
            Notify();
            //make the phaseStart back to false, so we don't display data that we didn't enter yet
            this->getAllPlayers().at(i)->setPhaseStart(false);
            
            setPhase(3);
            Notify();
            this->getAllPlayers().at(i)->fortify();
            
            Notify();
            //make the phaseStart back to false, so we don't display data that we didn't enter yet
            this->getAllPlayers().at(i)->setPhaseStart(false);
            
            
            
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
        
        //check if the number of turns played is greater than the max number of turns
        //if we are playing a tournament end the game
        if(numTurnsPlayed == getMaxNumTurn() && *gameMode == true) {
             cout << "\n\n ************** The Game is a draw **************\n End of the game" << endl;
            this->setEndGame(true);
        }
        
        //if countries are own by same player, set the game to end. There is a winner.
        if(allCountriesOwnByPlayer == true) {
            this->setEndGame(true);
            string winner = getAllPlayers().at(indexOfWinningPlayer)->getName();
            this->setWinner(winner);
             cout << "\n\n **************Player " << indexOfWinningPlayer +1 << " wins the game **************\n End of the game" << endl;
        }
    }
    
   
}



//**********Implementation for Tournament class**********

Tournament::Tournament() {
    
}

Tournament::Tournament(const Tournament& orig) {
    this->numMaps = make_unique<int>(*orig.numMaps);
    this->numGames = make_unique<int>(*orig.numGames);
    this->numTurns = make_unique<int>(*orig.numTurns);
    this->numComps = make_unique<int>(*orig.numComps);
    
    this->games = orig.games;
}

Tournament:: ~Tournament() {
    
}


//selecting different maps to play on
void Tournament::mapSelection(){
    int mapChoice; //choice of user
    string mapFile; //name of map
    //vector<string> mapsSelected;
    
    for(int i=0; i<this->getNumMaps(); i++){
        cout << "\nPlease select map #" << i+1 <<endl;
        cout << "Please enter the number associated with the map you would like to play on: \n"
        "Select 1 for Big Europe \n"
        "Select 2 for Geoscape \n"
        "Select 3 for LOTR \n"
        "Select 4 for Risk \n"
        "Select 5 for Solar \n"
        "Select 6 for notvalid2 \n" << endl;
        
        cin >> mapChoice;
        
        //checks if input corresponds to a map
              while(mapChoice<1 || mapChoice >6){
                  cout << "Invalid map. Please select one from the choices below: " << endl;
                  cout << "Please enter the number associated with the map you would like to play on: \n"
                  "Select 1 for Big Europe \n"
                  "Select 2 for Geoscape \n"
                  "Select 3 for LOTR \n"
                  "Select 4 for Risk \n"
                  "Select 5 for Solar \n"
                  "Select 6 for notvalid2 \n" << endl;
                  
                  cin>>mapChoice;
              }
              
        
        switch(mapChoice){
            case 1: mapFile = "bigeurope";
                break;
            case 2: mapFile = "geoscape";
                break;
            case 3: mapFile = "lotr";
                break;
            case 4: mapFile = "risk";
                break;
            case 5: mapFile = "solar";
                break;
            case 6: mapFile = "notvalid2";
                break;
        }
        
        //checks if map was not already selected
        while(find(tournamentMaps.begin(), tournamentMaps.end(), mapFile) !=tournamentMaps.end()){
            cout << "you have already selected that map, please pick another one!" << endl;
            cin >> mapChoice;
            
            switch(mapChoice){
                case 1: mapFile = "bigeurope";
                    break;
                case 2: mapFile = "geoscape";
                    break;
                case 3: mapFile = "lotr";
                    break;
                case 4: mapFile = "risk";
                    break;
                case 5: mapFile = "solar";
                    break;
                case 6: mapFile = "notvalid2";
                    break;
            }
            
        }
        
        
        tournamentMaps.push_back(mapFile);
        
        cout << "You chose the map " << mapFile << " to play" << endl;
        
    }
    
}

void Tournament:: playerSelection() {
    
    //for each computer players create a new player and make the user choose its strategy
    for(int i=0; i < *numComps; i++) {
        
        int strategy;
        cout << "\nWhich strategy would you like to use for player #" << i+1 << "? Please enter the number of the strategy to make your choice." << endl;
        cout << "(1) Aggressive Strategy" << endl;
        cout << "(2) Benevolent Strategy" << endl;
        cout << "(3) Cheater Strategy" << endl;
        cout << "(4) Random Strategy" << endl;
        cin >> strategy;
        
        while (strategy < 0 || strategy > 4) {
            cout << "Please select a valid strategy from the list of strategies." << endl;
            cin >> strategy;
        }
        
        
        Aggressive* aggressive = new Aggressive();
        Benevolent* benevolent = new Benevolent();
        //WILL NEED TO CREATE A RANDOM AND CHEATER TOO
        //Random random = new Random();
        //Cheater cheater = new Cheater;
        switch (strategy) {
            case 1: {
                Player *aPlayer = new Player("Aggressive");
                cout << "The player #" << i+1 << " will play as an Aggressive computer player" << endl;
                aPlayer->setStrategy(aggressive);
                aPlayer->setStrategyNum(1);
                allCompPlayers.push_back(aPlayer); //push the created player in the vector allComPlayers
                break;
            }
            case 2: {
                Player *bPlayer = new Player("Benevolant");
                cout << "The player #" << i+1 << " will play as an Benevolant computer player" << endl;
                bPlayer->setStrategy(benevolent);
                bPlayer->setStrategyNum(2);
                allCompPlayers.push_back(bPlayer); //push the created player in the vector allComPlayers
                break;
            }
            case 3: {
                Player *cPlayer = new Player("Cheater");
                cout << "The player #" << i+1 << " will play as an Cheater computer player" << endl;
                //  cPlayer->setStrategy(cheater);
                //cPlayer->setStrategyNum(3);
                allCompPlayers.push_back(cPlayer); //push the created player in the vector allComPlayers
                break;
            }
            case 4: {
                Player *rPlayer = new Player("Random");
                cout << "The player #" << i+1 << " will play as an Random computer player" << endl;
                //  rPlayer->setStrategy(random);
                  //rPlayer->setStrategyNum(4);
                allCompPlayers.push_back(rPlayer); //push the created player in the vector allComPlayers
                break;
            }
            default: {
                break;
            }
        }
    }
    
    
}





//displays the menu that prompts the user for information to set up the tournament
void Tournament::tournamentSettings(){
    
    
    int numComps; //number of computers to partake in the tournament
    int numMaps; //number of maps to play on
    int numGames; //number of games per map
    int numTurns; //number of turns per player
    
    //sets number of maps based on user input.
    cout << "Please enter the number of maps to play on (1 to 5): " << endl;
    cin >> numMaps;
    while(numMaps<1 || numMaps > 5){
        cout << "Invalid entry. Please enter a number between 1 and 5." << endl;
        cin >> numMaps;
    }
    
    cout << "There will be games on " << numMaps << " maps." << endl;
    
    this->setNumMaps(numMaps);
    
    
    cout << "You now have to select " << numMaps << " from this list: " << endl;
    
    //calls method to select the maps that will be played on
    mapSelection();

    
    //sets number of players based on input
    cout << "\nPlease enter the number of computer players that will participate in the tournament (2 to 4): " << endl;
    cin >> numComps;
    
    while(numComps<2 || numComps > 4){
        cout << "Invalid entry. Please enter a number between 2 and 4." << endl;
        cin >> numComps;
    }
    
    cout << "There will be " << numComps << " computer players" << endl;
    //set the number of computer players
    this->setNumComps(numComps);
    
    //calls playerSelection
    playerSelection();
    
    //sets number of games per map
    cout << "\nPlease enter the number of games that will be played on each map (1 to 5): " << endl;
    cin >> numGames;
    while(numGames<1 || numGames > 5){
        cout << "Invalid entry. Please enter a number between 1 and 5." << endl;
        cin >> numGames;
    }
    
    
    cout << "There will be " << numGames << " games played on each map." << endl;
    
    this->setNumGames(numGames);
    
    //sets maximum number of turns based on input
    cout << "\nPlease enter the maximum number of turns per game (10 to 50):  " << endl;
    cin >> numTurns;
    
    while(numTurns<10 || numTurns > 50){
        cout << "Invalid entry. Please enter a number between 10 and 50." << endl;
        cin >> numTurns;
    }
    
    cout << "There will be a maximum of " << numTurns << " turns per game" << endl;
    //set the number of computer players
    this->setNumTurns(numTurns);
    
    
    
}


//create games based on user input
void Tournament::createGames(bool isTournamentOn){
    
    //for each maps
    for(int i = 0; i <*numMaps; i++) {
        
        //create the number of games the user input
        for(int j=0; j < *numGames; j++) {
            
            cout << "\n\n*************Creating the Game " << j+1 << " on map " << i+1 << "*************\n\n" << endl;
            GameEngine* aGame = new GameEngine();
            aGame->createMap(tournamentMaps.at(i));
            
            //create the players in the games with the players created in tournament
            for(int k=0; k < *numComps; k++ ) {
                
                //we need to pass a map to the player
                Player *temp = new Player(*allCompPlayers.at(k));
                
                temp->setMap(aGame->getMap());
                aGame->setNumberOfPlayers(*numComps);
                aGame->setPlayer(temp);
            }
            
            aGame->setNumberOfPlayers(*numComps);
            aGame->assignCountriesToPlayers();
            aGame->displayCountriesOfPlayers();
            aGame->setNumberOfArmiesPerPlayer();
            aGame->setArmiesToCountries();
            aGame->setGameMode(true); //set the game mode to tournament game
            aGame->setMaxNumTurn(*numTurns);
            //add the game we just create to the games vector
            games.push_back(aGame);
            
        }
    }
}


void Tournament::displayGamesResults() {
    
    cout << "\n\n**** GAMES RESULTS ****" << endl;
    cout << "Number of maps: " << *numMaps << endl;
    cout << "Players playing: ";
    for(int i=0 ; i <allCompPlayers.size(); i++) {
        cout << allCompPlayers.at(i)->getName() << ", ";
    }
    
    cout << "\nNumber of games played: " << *numGames << endl;
    cout << "Maximum number of turns: " << *numTurns << endl;
    
    int gameId = 0;
    
    //printing the outcome on each map
    for(int i=0; i<*numMaps; i++){

        cout << "\n***** MAP " << i+1 << " *****" << endl;

        //printing each game
        for(int j =0; j <*numGames; j++) {

            cout << "\n\tGame " << j+1 << endl;
            cout << "\tWinner: " << games.at(gameId)->getWinner() << endl;

            if(gameId < games.size()) {
                           gameId++;
                       }
        }

    }
    
    
    
//
//    games.at(0)->setWinner("Aggressive");
//    games.at(1)->setWinner("Random");
//    games.at(2)->setWinner("Cheater");
//    cout << "\n\n|\t\t\t\t";
//    for(int i=0; i < *numGames; i++) {
//        cout << "|\t\tGame " << i+1 << "\t\t" ;
//    }
//    cout<< "|" << endl;
//
//        int gameId = 0;
//
//       //printing the outcome on each map
//        for(int i=0; i<*numMaps; i++){
//
//            cout  << "|MAP " << i+1 << "\t\t\t";
//
//            //printing each game
//           for(int j =0; j <*numGames; j++) {
//
//
//                cout  << "|\t\t" << games.at(gameId)->getWinner() << "\t\t";
//
//                if(gameId < games.size()) {
//                               gameId++;
//                           }
//            }
//
//            cout << "\n"; //change line for the other map
//        }
    
    
    
}
int Tournament::getNumMaps() {
    return *numMaps;
}

void Tournament::setNumMaps(int num){
    this->numMaps.reset(new int(num));
}

int Tournament::getNumGames() {
    return *numGames;
}

void Tournament::setNumGames(int num) {
    this->numGames.reset(new int(num));
}

int Tournament::getNumTurns() {
    return *numTurns;
}

void Tournament::setNumTurns(int num) {
    this->numTurns.reset(new int(num));
}

int Tournament::getNumComps(){
    return *numComps;
}


void Tournament::setNumComps(int num){
    this->numComps.reset(new int(num));
}

vector<string> Tournament::getTournamentMaps(){
    return tournamentMaps;
}

void Tournament::setTournamentMaps(string map){
    tournamentMaps.push_back(map);
}

vector<GameEngine*> Tournament::getGames() {
    return games;
}
