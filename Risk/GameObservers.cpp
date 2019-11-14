#include "GameObservers.h"
//-------------- OBSERVER CLASS ----------------
Observer::Observer() {

}

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