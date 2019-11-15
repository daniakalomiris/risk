#pragma once
#include "GameObservers.h"
#include "player.h"
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
//  The concrete Subjet is actually the Player class, slight modifications were done to notify the observers



//-------------- CONCRETE OBSERVERS ----------
//---------------------Concrete observer for reinforce phase 
RObs::RObs() {
}

RObs::RObs(Player* s) {
	//When object is instantiated, it attaches itself to a player
	subject = s;
	subject->Attach(this);
}

RObs::~RObs() {
	//When a player is destroyed, it must detache itself from it 
	subject->Detach(this);
}

void RObs::update() {
	//This methid is called by Notify from Subject when a state from Player changes
	display();
}

void RObs::display() {

}

//---------------------Concrete observer for attack phase 
AObs::AObs() {
}

AObs::AObs(Player* s) {
	//When object is instantiated, it attaches itself to a player
	subject = s;
	subject->Attach(this);
}

AObs::~AObs() {
	//When a player is destroyed, it must detache itself from it 
	subject->Detach(this);
}

void AObs::update() {
	//This methid is called by Notify from Subject when a state from Player changes
	display();
}

void AObs::display() {

}

//---------------------Concrete observer for fortify phase 
FObs::FObs() {
}

FObs::FObs(Player* s) {
	//When object is instantiated, it attaches itself to a player
	subject = s;
	subject->Attach(this);
}
FObs::~FObs() {
	//When a player is destroyed, it must detache itself from it 
	subject->Detach(this);
}
void FObs::update() {
	//This methid is called by Notify from Subject when a state from Player changes
	display();
}
void FObs::display() {

}