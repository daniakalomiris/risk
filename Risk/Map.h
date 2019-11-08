#pragma once

#include <string>
#include <vector>
#include <queue>
#include <memory>


class Continent;
class Country;

class Map {
public:
	Map();
	~Map();

	void setContinent(Continent* continent); // sets continents
	std::vector<Continent*> getContinents(); // returns continents

	void setCountry(Country* country);
	std::vector<Country*> getCountries(); // returns vector of countries

	bool isValidMap(); // checks if valid map
	bool isContinentSubgraph(); // checks continents subgraph
	bool isCountrySubgraph(); // checks if country subgraph
	bool isCountryInOneContinent(); //checks if country is on one continent
	bool isNotEmptyContinent(); // checks if continent is empty
	bool countryHasContinent(); // checks if country is on contient

	void getOwnerCountries(int playerId); //returns vector of owner countries

    //********************** PART added by Loujain **********************
	int controlContinent(std::vector<Country*> country);

private:
	std::vector<Continent*> continents;
    std::vector<Country*> countries;
	
    // for controlcontinent variables
	int countryinContinent;
	int numContinent;
    
	//Declare variables
	std::queue<Continent*> visitedContinentsQueue;
	std::queue<Country*> visitedCountriesQueue;
	std::vector<Country*> ownerCountries;
};

class Continent {
public:
	Continent(); // continent constructor
	~Continent();

	void setCountriesOfContinent(Country* country); // sets the countries on continents
	std::vector<Country*> getCountriesOfContinent(); // returns vector of countries on continent

	void setAdjacentContinents(Continent* continent); //sets adjacent continents
	std::vector<Continent*> getAdjacentContinents(); // returns vector of adjacent continents

	void setContinentName(std::string continentName); //sets continents name
	std::string getContinentName();

    void setNumberOfArmies(int numberOfArmies); //sets the number of armies
    int getNumberOfArmies(); // number of armies on a continent
    bool continentOwnByAPlayer();
private:
	//declare variables
	std::unique_ptr<std::string> continentName;
	std::vector<Country*> countriesOfContinent;
	std::vector<Continent*> adjacentContinents;
    std::unique_ptr<int> numberOfArmies;
	static int continentCounter;
};

class Country {
public:
	Country(); // contry constructor
	~Country(); // country deconstructor


	void setCountryName(std::string countryName); //setter method to set country name
	std::string getCountryName(); //getter method to get country name

	void setCountryNumber(int countryNumber); //set country id
	int getCountryNumber(); //country id

	void setContinentOfCountry(Continent* continentOfCountry);  //sets continent of country
	Continent* getContinentOfCountry(); //returns continent object

	void setCountryOwnerId(int countryOwnerId);  //sets owner of country
	int getCountryOwnerId(); //returns player id

	void setAdjacentCountries(Country* country);//sets adjacent countries
	std::vector<Country*> getAdjacentCountries(); //returns vector of adjacent countries

	void setNumberOfArmies(int numberOfArmies); //sets the number of armies
	int getNumberOfArmies(); // number of armies on a country

	//methods to potentially implement GUI
	void setCoordinateX(int coordinateX);
	int getCoordinateX();
	void setCoordinateY(int coordinateY);
	int getCoordinateY();

private:
	//declaring variables
	std::unique_ptr<std::string> countryName;
	std::unique_ptr<int> countryNumber;
	Continent* continentOfCountry;
	std::unique_ptr<int> coordinateX;
	std::unique_ptr<int> coordinateY;
	std::vector<Country*> adjacentCountries;
	std::unique_ptr<int> countryOwnerId;
	std::unique_ptr<int> numberOfArmies;
	static int countryCounter;

};
