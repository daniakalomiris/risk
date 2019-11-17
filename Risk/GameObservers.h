#pragma once
#include <list>
using namespace std;

class GameEngine;

class Observer {

public:

	~Observer();
	virtual void Update() = 0;

protected:

	Observer();

};

class Subject {
public:

	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();

	Subject();
	~Subject();

private:

	list<Observer*>* observers;

};

//Concrete subject is the GameEngine class, please go see GameEngine.h

//Concrete observer for reinforce phase 
class PhaseObs : public Observer {

public:
	PhaseObs();
	PhaseObs(GameEngine* s);
	~PhaseObs();
	void Update();
	void display();

private:
	GameEngine* subject;
};
