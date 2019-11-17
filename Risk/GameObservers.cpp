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

	int i = subject->currentPlayerIndex;
	   
	int phaseR = 1;
	int phaseA = 2;
	int phaseF = 3;

	int phase = subject->getPhase();
	string playerName = subject->getAllPlayers().at(i)->getName();
	int id = subject->getAllPlayers().at(i)->getID();
	if (phase == phaseR) {
		int numArmy1 = subject->getAllPlayers().at(i)->getNumArmy1();
		int numArmy2 = subject->getAllPlayers().at(i)->getNumArmy2();
		int numArmy3 = subject->getAllPlayers().at(i)->getNumArmy3();
		int armyAdd = numArmy1 + numArmy2 + numArmy3;
		cout << "--------------------------------------------------------------" << endl;
		cout << "Player " << id << ", " << playerName << ": Reinfore Phase." << endl;
		cout << "Number of armies for controlled countries: " << numArmy1 << endl;
		cout << "Number of armies for controlled continents: " << numArmy2 << endl;
		cout << "Number of armies added by exchanging cards is " << numArmy3 << "." << endl;
		cout << "In total, " << armyAdd << " armies were added for reinforcement." << endl;
		cout << "--------------------------------------------------------------" << endl;
	}
	if (phase == phaseA) {
		cout << "--------------------------------------------------------------" << endl;
		cout << "Player " << id << ", " << playerName << ": Attack Phase." << endl;
		cout << "Player " << id << " is the attacker and  Player " << subject->getAllPlayers().at(i)->getDefenderId() << " is the defender." << endl;
		cout << "The Attacker used " << subject->getAllPlayers().at(i)->getStartA()<<  " army/ies from " << subject->getAllPlayers().at(i)->getAttackerCountry() << " to attack." << endl;
		cout << "The Defender had " << subject->getAllPlayers().at(i)->getStartD() << " army/ies on " << subject->getAllPlayers().at(i)->getDefenderCountry() << "." << endl;
		cout << "At the end of the attack:" << endl;
		cout << "The Attacker now has " << subject->getAllPlayers().at(i)->getEndA()<< " army/ies from " << subject->getAllPlayers().at(i)->getAttackerCountry() << " to attack." << endl;
		cout << "The Defender now has " << subject->getAllPlayers().at(i)->getEndD() << " army/ies on " << subject->getAllPlayers().at(i)->getDefenderCountry() << "." << endl;
		cout << "--------------------------------------------------------------" << endl;
	}

	if (phase == phaseF) {
		cout << "--------------------------------------------------------------" << endl;
		cout << "Player " << id << ", " << playerName << ": Fortify Phase." << endl;
		cout << subject->getAllPlayers().at(i)->getFortifySourceCountry() << " has now " << subject->getAllPlayers().at(i)->getSourceArmy() << " armies" << endl;
		cout << subject->getAllPlayers().at(i)->getFortifyTargetCountry() << " has now " << subject->getAllPlayers().at(i)->getTargetArmy() << " armies" << endl;
		cout << "--------------------------------------------------------------" << endl;
	}



}
