#pragma once
#include <string>
#include <memory>
#include "Player.h"

class User;
class Aggressive;
class Benevolent;
class Random;
//class Cheater;

class Strategy {
public:
    Strategy();
    ~Strategy();
 
    /* methods for reinforcement phase */
    virtual std::string extraReinforcement() = 0;
    virtual int countryToReinforce(Player* player) = 0;
    virtual int armiesToPlace(Player* player) = 0;
    
    /* methods for attack phase */
    virtual std::string chooseAttack() = 0;
    virtual int attackFrom(Player* player) = 0;
    virtual int countryToAttack(Country* attackFrom) = 0;
    virtual int attackerRoll() = 0;
	virtual int defenderRoll() = 0;
    virtual int armiesToMove(int armiesCanMove) = 0;
    
    /* methods for fortify phase */
    virtual std::string chooseFortify() = 0;
    virtual std::string countryToFortifyFrom(Player* player) = 0;
    virtual int armiesToFortify(int sourceCounrtyArmies) = 0;
    virtual std::string countryToFortify(Player* player, Country* country) = 0;
    
    // determines how exchange is handled for each strategy
    virtual bool exchangeAutom() = 0;
};

class User : public Strategy {
public:
    User();
    ~User();
   
    std::string extraReinforcement();
    int countryToReinforce(Player* player);
    int armiesToPlace(Player* player);
    
    std::string chooseAttack();
    int attackFrom(Player* player);
    int countryToAttack(Country* attackFrom);
    int attackerRoll();
	int defenderRoll();
    int armiesToMove(int armiesCanMove);
    
    std::string chooseFortify();
    std::string countryToFortifyFrom(Player* player);
    int armiesToFortify(int sourceCounrtyArmies);
    std::string countryToFortify(Player* player, Country *);
    
    bool exchangeAutom();
};

class Aggressive : public Strategy {
public:
    Aggressive();
    ~Aggressive();
     
    std::string extraReinforcement();
    int countryToReinforce(Player* player);
    int armiesToPlace(Player* player);
    
    std::string chooseAttack();
    int attackFrom(Player* player);
    int countryToAttack(Country* attackFrom);
    int attackerRoll();
	int defenderRoll();
    int armiesToMove(int armiesCanMove);
    
    std::string chooseFortify();
    std::string countryToFortifyFrom(Player* player);
    int armiesToFortify(int sourceCounrtyArmies);
    std::string countryToFortify(Player* player, Country *);
    
    bool exchangeAutom();
};

class Benevolent : public Strategy {
public:
    Benevolent();
    ~Benevolent();
       
    std::string extraReinforcement();
    int countryToReinforce(Player* player);
    int armiesToPlace(Player* player);
    
    std::string chooseAttack();
    int attackFrom(Player* player);
    int countryToAttack(Country* attackFrom);
    int attackerRoll();
	int defenderRoll();
    int armiesToMove(int armiesCanMove);
    
    std::string chooseFortify();
    std::string countryToFortifyFrom(Player* player);
    int armiesToFortify(int sourceCounrtyArmies);
    std::string countryToFortify(Player* player, Country* country);
    
    bool exchangeAutom();
};

class Random : public Strategy {
public:
	Random();
	~Random();

	std::string extraReinforcement();
	int countryToReinforce(Player* player);
	int armiesToPlace(Player* player);

	std::string chooseAttack();
	int attackFrom(Player* player);
	int countryToAttack(Country* attackFrom);
	int attackerRoll();
	int defenderRoll();
	int armiesToMove(int armiesCanMove);

	std::string chooseFortify();
	std::string countryToFortifyFrom(Player* player);
	int armiesToFortify(int sourceCounrtyArmies);
	std::string countryToFortify(Player* player, Country* country);

	bool exchangeAutom();
};

class Cheater : public Strategy {
public:
	Cheater();
	~Cheater();

	//std::string extraReinforcement();
	int countryToReinforce(Player* player);
	//int armiesToPlace(Player* player);

	std::string chooseAttack();
	/*int attackFrom(Player* player);
	int countryToAttack(Country* attackFrom);
	int attackerRoll();
	int defenderRoll();*/
	//int armiesToMove(int armiesCanMove);
	void attackCheater(Player* player);
	std::string chooseFortify();
	std::string countryToFortifyFrom(Player* player);
	int armiesToFortify(int sourceCounrtyArmies);
	std::string countryToFortify(Player* player, Country* country);

	bool exchangeAutom();
private:
	vector<Country*> fortifyCountry;
};
