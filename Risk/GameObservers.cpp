#include "GameEngine.h"
#include "GameObservers.h"
#include <iostream>
#include <string>
using namespace std;

//-------------- OBSERVER CLASS ----------------
Observer::Observer() {
};

Observer::~Observer() {
}

// ------------------ SUBJECT CLASS -----------
Subject::Subject() {
    observers = new list<Observer*>;
}
Subject::~Subject() {
    delete observers;
}
void Subject::Attach(Observer* o) {
    observers->push_back(o);
}

void Subject::Detach(Observer* o) {
    observers->remove(o);
}
void Subject::Notify() {
    list<Observer*>::iterator i = observers->begin();

    for (; i != observers->end(); ++i) {
        (*i)->Update();
    }
}




// ------------- Concrete Subject ------------
//  The concrete Subjet is actually the GameEngine class, slight modifications were done to notify the observers



//-------------- CONCRETE OBSERVERS ----------
//---------------------Concrete observer for PlayerDominationView observer
PlayerDominationView::PlayerDominationView(){
    
}
PlayerDominationView::PlayerDominationView(GameEngine* s) {
    //When object is instantiated, it attaches itself to a GameEngine
    subject = s;
    subject->Attach(this);
}

PlayerDominationView::~PlayerDominationView() {
    //When a GameEngine is destroyed, it must detache itself from it
    subject->Detach(this);
}

void PlayerDominationView::Update() {
    //This methid is called by Notify from Subject when a state from GameEngine changes
    display();
}

void PlayerDominationView::display() {
    
    //total number of players
    int numPlayers = subject->getNumberOfPlayers();
    
//    //vector of all player names
//    vector<string> playerNames;
//
//    //vector of number of countries owned by each player
//    vector<int> countriesPlayers;
    
   //total number of countries
    int numOfCountries = subject->getMap()->getCountries().size();
    
    //dislpays table
    cout << "There are a total of " << numOfCountries << " countries" << endl;
    cout << "Player Name \t Countries owned\t % of wordl owned" << endl;
  
    
    //iterates through all players
    for(int i=0; i<numPlayers; i++){
        
        //players names
        string playerName = subject->getAllPlayers().at(i)->getName();
    
       
        //number of countries per player
        int playerNumCountries = subject->getAllPlayers().at(i)->getThisPlayerCountries().size();
        
        //if the player doesn't own countries, don't show him
        if(playerNumCountries == 0) {
            continue;
        }
        
        //percentage of world owned per player
        double percentageOwned = static_cast<double>(playerNumCountries)/numOfCountries*100;
        
        //output data of each player
        cout << playerName <<"\t\t\t" << playerNumCountries << "\t\t\t" <<  percentageOwned <<"%"<< endl;
        
//        //push names and countries
//        playerNames.push_back(playerName);
//        countriesPlayers.push_back(playerNumCountries);
        if(subject->getAllPlayers().at(i)->getThisPlayerCountries().size() == subject->getMap()->getCountries().size()){
            cout << "Congratulations! " << subject->getAllPlayers().at(i) << " has 100% of the countries!" <<endl;
        }
        
    }
    
   
    
    

}








