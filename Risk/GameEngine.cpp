
#include <iostream>
#include <string>
#include "GameEngine.h"
#include "time.h"
#include <random>
//using std::cout;
//using std::endl;
//using std::cin;
using namespace std;
const int MIN_PLAYERS = 2;
const int MAX_PLAYERS = 6;


GameEngine:: GameEngine() {
    maploader = new MapLoader();
}

GameEngine:: ~GameEngine() {
    delete maploader;
    delete deck;
}


void GameEngine::askNumberOfPlayers() {
    int numPlayersEntered;

    cout << "\nPlease enter the number of players (between 2 and 6): " << endl;

	cin >> numPlayersEntered;

	while (numPlayersEntered<MIN_PLAYERS || numPlayersEntered > MAX_PLAYERS) {
		cout << "Invalid entry. Please enter a number between 2 and 6" << endl;
		cin >> numPlayersEntered;
	}

	//numberOfPlayers = &numPlayersEntered;
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

void GameEngine::setNumberOfArmiesPerPlayer() {
	int A;
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

	numberOfArmiesPerPlayer = make_unique<int>(A);

    //gives to each player a numberOfArmies at startup phase
    for(int i =0; i < allPlayers.size(); i++) {
        allPlayers.at(i)->setNumOfArmiesAtStartUpPhase(*numberOfArmiesPerPlayer);
    }
}

void GameEngine::setArmiesToCountries() {

    bool done = false;

    //put 1 army in each player country
     for (int i = 0; i < allPlayers.size(); i++) {

         int remainingArmies = this->getNumberOfArmiesPerPlayer();

         //place at least 1 armie on each player's countries
         for(int j =0; j < allPlayers.at(i)->getThisPlayerCountries().size(); j++) {
             allPlayers.at(i)->getThisPlayerCountries().at(j)->setNumberOfArmies(1);
             remainingArmies = remainingArmies -1;
         }

         //set the number of armies a player need to place to the remaining armies
        allPlayers.at(i)->setNumOfArmiesAtStartUpPhase(remainingArmies);
     }


    cout << "each country has 1 army now" << endl;

    while(done == false) {
    for (int i = 0; i < allPlayers.size(); i++) {

        bool isCountryChosenValid = false;
        string countryChosen;
        int indexOfCountryChosen =0;

        cout << "\n\nPlayer " << allPlayers.at(i)->getName() << " turn" << endl;
        cout << "This is your countries with their number of armies" << endl;

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

        cout << "You have place 1 more army on the country " << allPlayers.at(i)->getThisPlayerCountries().at(indexOfCountryChosen)->getCountryName()<< endl;

        cout << allPlayers.at(i)->getThisPlayerCountries().at(indexOfCountryChosen)->getCountryName() << " has now " << allPlayers.at(i)->getThisPlayerCountries().at(indexOfCountryChosen)->getNumberOfArmies() << " armies " << endl;


        if(allPlayers.at(i)->getNumOfArmiesAtStartUpPhase() == 0) {
            done = true;
        }
    }
        	}
}


void GameEngine::createPlayers() {

	string playerName;

	for (int i = 0; i < this->getNumberOfPlayers(); i++) {

		cout << "\nPlease enter the name of player " << i +1 << endl;
		cin >> playerName;

		//creates a player with name, dice, and hand
		Player* player = new Player(playerName);
		player->setName(playerName);

		setPlayer(player);

	}
}

void GameEngine::setPlayer(Player* player) {
	cout << "adding player to list of players" << endl;
	allPlayers.push_back(player);
}

vector<Player*> GameEngine::getAllPlayers() {
    return allPlayers;
}


void GameEngine::setPlayerOrder() {

    //get a time base seed to have a new random random generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();


    //shuffle the player's order
    shuffle(this->allPlayers.begin(), this->allPlayers.end(), default_random_engine(seed));


    }


void GameEngine::showPlayerOrder() {
	for (int i = 0; i<allPlayers.size(); i++) {
		cout << "Player " << allPlayers[i]->getName() << " is at position " << (i + 1) << endl;
	}

}


void GameEngine::assignCountriesToPlayers() {

	int numOfCountries = this->map->getCountries().size();
	int numOfPlayers = this->allPlayers.size();
	int countryNumberPushed = 0;
    int playerTurns = 0;
    //contains index of countries already assigned to a player
    vector<int> countriesAlreadyAssigned;
    // Resets the random
        srand(time(NULL));

    while(countryNumberPushed < numOfCountries) {

        int randomCountry = rand() % numOfCountries;

        //if the index of countries is not already assigned
        if(find(countriesAlreadyAssigned.begin(), countriesAlreadyAssigned.end(), randomCountry) == countriesAlreadyAssigned.end()) {

        //set the country to the player


            this-> allPlayers.at(playerTurns)->setThisPlayerCountry(map->getCountries().at(randomCountry));
            //set the owner id
             map->getCountries().at(randomCountry)->setCountryOwnerId(allPlayers.at(playerTurns)->getID());

            if(playerTurns < this->allPlayers.size()-1) {
            playerTurns ++;
            }

            else {
            playerTurns = 0;
            }

            countryNumberPushed ++;
            countriesAlreadyAssigned.push_back(randomCountry);
        }
    }

}

void GameEngine::displayCountriesOfPlayers() {
	for (int i = 0; i < allPlayers.size(); i++) {
		cout << "\n\nPlayer " << allPlayers.at(i)->getName() << " countries: " << endl;

		for (int j = 0; j < allPlayers.at(i)->getThisPlayerCountries().size(); j++) {
			cout << j+1 << " " << allPlayers.at(i)->getThisPlayerCountries().at(j)->getCountryName() << endl;
		}
	}
}

void GameEngine::createMap() {
	int mapChoice;
    string mapFile;


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

    maploader->readMapFile("maps/" + mapFile+ ".map");
    maploader->createMap();
    maploader->displayMap();

    map = maploader->getMap();

    //create a new deck
    deck = new Deck(map);

}


//part 3 main game loop, each player play turn by turn
void GameEngine:: mainGameLoop() {

    cout << "\n\n****** Main Game Loop *******" << endl;
    bool gameEnd = false;

    while (gameEnd == false) {

        for(int i = 0; i< this->getNumberOfPlayers(); i++) {
            
            //display which player is playing
            cout << "\n\nPlayer " <<  i+1 << ": " << this->getAllPlayers().at(i)->getName() << " turn" << endl;
            
            this->getAllPlayers().at(i)->reinforce();
            this->getAllPlayers().at(i)->attack();
            this->getAllPlayers().at(i)->fortify();
           
            
            //check if a player owns all the countries
            if(this->getAllPlayers().at(i)->getThisPlayerCountries().size() == this->map->getCountries().size()) {
                gameEnd = true;
            }
        }
        
       
        //Need to add an end, when one player controls all the countries
    //    gameEnd = true;

    }
}
