#pragma once
#include <list>
using namespace std;

class Player;

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

//Concrete subject is the player class, please go see player.h

//Concrete observer for reinforce phase 
class RObs : public Observer {

public:
	RObs();
	RObs(Player* s);
	~RObs();
	void Update();
	void display();

private:
	Player* subject;
};

//Concrete observer for attack phase 
class AObs : public Observer {

public:
	AObs();
	AObs(Player* s);
	~AObs();
	void Update();
	void display();

private:
	Player* subject;
};

//Concrete observer for fortify phase 
class FObs : public Observer {
public:
	FObs();
	FObs(Player* s);
	~FObs();
	void Update();
	void display();

private:
	Player* subject;
};
