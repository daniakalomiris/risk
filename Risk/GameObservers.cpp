#include "GameEngine.h"
#include "GameObservers.h"
#include <iostream>
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
//---------------------Concrete observer for reinforce phase 
PhaseObs::PhaseObs() {
}

PhaseObs::PhaseObs(GameEngine* s) {
	//When object is instantiated, it attaches itself to a GameEngine
	subject = s;
	subject->Attach(this);
}

PhaseObs::~PhaseObs() {
	//When a GameEngine is destroyed, it must detache itself from it 
	subject->Detach(this);
}

void PhaseObs::Update() {
	//This methid is called by Notify from Subject when a state from GameEngine changes
	display();
}

void PhaseObs::display() {

	int numPlayers = subject->getNumberOfPlayers();
	
	int phaseR = 1;
	int phaseA = 2;
	int phaseF = 3;

	for (int i = 0; i <numPlayers; i++) {
		int phase = subject->getPhase();
		string playerName = subject->getAllPlayers().at(i)->getName();
		int id = subject->getAllPlayers().at(i)->getID();
		if (phase == phaseR) {
			int numArmy1 = subject->getAllPlayers().at(i)->getNumArmy1();
			int numArmy2 = subject->getAllPlayers().at(i)->getNumArmy2();
			int numArmy3 = subject->getAllPlayers().at(i)->getNumArmy3();
			int armyAdd = numArmy1 + numArmy2 + numArmy3;
			cout << "Player " << id << ", " << playerName << ": Reinfore Phase." << endl;
			cout << "Number of armies for controlled countries: " << numArmy1 << endl;
			cout << "Number of armies for controlled continents: " << numArmy2 << endl;
			cout << "Number of armies added by exchanging cards is " << numArmy3 << "." << endl;
			cout << "In total, " << armyAdd << " armies were added for reinforcement." << endl;
		}
		if (phase == phaseA) {
			cout << "Player " << id << ", " << playerName << ": Attack Phase." << endl;
			//cout << "Player " << id << "attacked" << subject->getAllPlayers().at(i)->
			
		}

		if (phase == phaseF) {
			cout << "Player " << id << ", " << playerName << ": Fortify Phase." << endl;
		}
		

	}
}
