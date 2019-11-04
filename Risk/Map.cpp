#include "Map.h"

#include<iostream>
#include <queue>
#include <memory>

using namespace std;
//map constructor
Map::Map() {
}

Map::~Map() {
}

//setter 

//pushes continent objects to continent vector

void Map::setContinent(Continent * continent) {
	continents.push_back(continent);
}

//pushes country objects to vector
void Map::setCountry(Country* country) {
	countries.push_back(country);
}

//returns vector of continent objects
vector<Continent*> Map::getContinents() {
	return continents;
}

//returns vector of country objects
vector<Country*> Map::getCountries() {
	return countries;
}


vector<Country*> Map::getOwnerCountries(int playerId) {
	for (unsigned int i = 0; i < countries.size(); i++) {
		if (countries.at(i)->getCountryOwnerId() == playerId) {
			ownerCountries.push_back(countries.at(i));
			cout << "Player " << playerId << " owns the country " << countries.at(i)->getCountryName() << " with " << countries.at(i)->getNumberOfArmies() << " armies." << endl;
		}
	}
	return ownerCountries;
}

//algorithm to search through continents
void Map::breadthFirstSearchContinents(vector<Continent*> continents, Continent* continent) {
	cout << "Beginning a Breadth First Search on continent subgraph." << endl;

	bool visitedContinents[100]; // Array to keep track of which continent we have visited
	for (unsigned int i = 0; i < getContinents().size(); i++) { // Initialize array with false (we have yet to visit these continents)
		visitedContinents[i] = false;
	}

	visitedContinentsQueue.push(continent);
	visitedContinents[0] = true; // Our search starts at the first continent

	while (!visitedContinentsQueue.empty()) {
		Continent* continentNode = visitedContinentsQueue.front(); // Get first continent from the queue
		visitedContinentsQueue.pop(); // Remove that continent from the queue
		cout << continentNode << endl;

		for (unsigned int i = 0; i < continents.size(); i++) {  // Loop through all continents
			Continent* adjacentContinent = continents.at(i)->getAdjacentContinents().at(i); // Get an adjacent continent
			if (visitedContinents[i] == false) { // If this continent has not been visited, we mark it as visited and add it to the queue
				visitedContinents[i] = true;
				visitedContinentsQueue.push(adjacentContinent);
			}
		}
	}
}

//Algorithm to search through countries 
void Map::breadthFirstSearchCountries(vector<Country*> countries, Country* country) {
	cout << "Beginning a Breadth First Search on country subgraph." << endl;

	bool visitedCountries[100]; // Array to keep track of which country we have visited
	for (unsigned int i = 0; i < getCountries().size(); i++) { // Initialize array with false (we have yet to visit these countries)
		visitedCountries[i] = false;
	}

	visitedCountriesQueue.push(country);
	visitedCountries[0] = true; // Our search starts at the first country

	while (!visitedCountriesQueue.empty()) {
		Country* countryNode = visitedCountriesQueue.front(); // Get first country from the queue
		visitedCountriesQueue.pop(); // Remove that country from the queue
		cout << countryNode << endl;

		for (unsigned int i = 0; i < countries.size(); i++) {  // Loop through all countries
			Country* adjacentCountry = countries.at(i)->getAdjacentCountries().at(i); // Get an adjacent country
			if (visitedCountries[i] == false) { // If this country has not been visited, we mark it as visited and add it to the queue
				visitedCountries[i] = true;
				visitedCountriesQueue.push(adjacentCountry);
			}
		}
	}
}

//checks if continent is a subgraph 
bool Map::isContinentSubgraph() {
	if (getContinents().size() == 0) {
		return false;
	}
	else {
		breadthFirstSearchContinents(getContinents(), getContinents().at(0));
		if (getContinents().size() == visitedContinentsQueue.size()) {
			cout << "Continents are connected subgraphs." << endl;
		}
	}
	return true;
}

//checks if country is subgraph 
bool Map::isCountrySubgraph() {
	if (getCountries().size() == 0) {
		return false;
	}
	else {
		breadthFirstSearchCountries(getCountries(), getCountries().at(0));
		if (getContinents().size() == visitedCountriesQueue.size()) {
			cout << "Map is a connected subgraphs." << endl;
		}
	}
	return true;
}

//checks if country is in one continent
bool Map::isCountryInOneContinent() {
	for (unsigned int i = 0; i < getCountries().size() - 1; i++) { // Loop through all continents
		for (unsigned int j = 0; j < continents.at(i)->getCountriesOfContinent().size() - 1; j++) { // Loop through all countries of a continent
			for (unsigned int k = 0; k < getCountries().size() - 1; k++) { // Loop through all continents
				for (unsigned int l = j + 1; l < continents.at(k)->getCountriesOfContinent().size() - 1; l++) { // Loop through all other countries of a continent
					if (continents.at(i)->getCountriesOfContinent().at(j)->getCountryName() == continents.at(k)->getCountriesOfContinent().at(l)->getCountryName()) { // Check if each country belongs to only 1 continent
						cout << "Country " << continents.at(i)->getCountriesOfContinent().at(j)->getCountryName() << " belongs to more than one continent." << endl;
						cout << "Map is invalid." << endl;
						return false;
					}
				}
			}
		}
	}
	cout << "All countries belong to only one continent." << endl;
	return true;
}

bool Map::isNotEmptyContinent() {
	for (unsigned int i = 0; i < continents.size() - 1; i++) { // Loop through all continents
		if (continents.at(i)->getCountriesOfContinent().size() - 1 < 1) { // Check if each continent has at least 1 country
			cout << "Continent " << continents.at(i)->getContinentName() << " does not have any countries." << endl;
			cout << "Map is invalid." << endl;
			return false;
		}
	}
	cout << "All continents have countries." << endl;
	return true;
}

bool Map::countryHasContinent() {
	for (unsigned int i = 0; i < countries.size() - 1; i++) { // Loop through all countries and check if they belong to a continent
		if (countries.at(i)->getContinentOfCountry() == NULL) {
			cout << "Country " << countries.at(i)->getCountryName() << " does not belong to a continent." << endl;
			cout << "Map is invalid." << endl;
			return false;
		}
	}
	cout << "All countries belong to a continent." << endl;
	return true;
}

bool Map::isValidMap() {
	return isContinentSubgraph() && isCountrySubgraph() && isCountryInOneContinent() && isNotEmptyContinent() && countryHasContinent();
}

int Map::controlContinent(vector<Country*> country) {
	int countryinContinent = 0;
	int numContinent = 0;
	for (int i = 0; i < continents.size(); i++) {
		for (int j = 0; j < countries.size(); j++) {
			for (int k = 0; k < countries.size(); k++) {
				if (countries.at(j) == countries.at(k)) { 
					countryinContinent += 1;
					break;
				}
				else {
					continue;
				}
			}

			if (countryinContinent == countries.size()) { // COME BACK THIS IS WRONG
				numContinent += 1;
			}
		}
	}

	return numContinent;
}


//continent constructor
Continent::Continent() {
}

Continent::~Continent() {
}

//setter and getter methods for continent class
string Continent::getContinentName() {
	return *continentName;
}

void Continent::setContinentName(string continentName) {
	this->continentName.reset(new string(continentName));
}

vector<Country*> Continent::getCountriesOfContinent() {
	return countriesOfContinent;
}

void Continent::setCountriesOfContinent(Country * country) {
	countriesOfContinent.push_back(country);
}

vector<Continent*> Continent::getAdjacentContinents() {
	return adjacentContinents;
}

void Continent::setAdjacentContinents(Continent * continent) {
	adjacentContinents.push_back(continent);
}

int Continent::getNumberOfArmies() {
    return *numberOfArmies;
}

void Continent::setNumberOfArmies(int numberOfArmies) {
    this->numberOfArmies = make_unique<int>(numberOfArmies);
}


//country constructors
Country::Country() {

}

Country::~Country() {
}

//setter and getter methods for country class
string Country::getCountryName() {
	return *countryName;
}

void Country::setCountryName(string countryName) {
	this->countryName.reset(new string(countryName));
}

int Country::getCountryNumber() {
	return *countryNumber;
}

void Country::setCountryNumber(int countryNumber) {
	this->countryNumber.reset(new int(countryNumber));
}

Continent* Country::getContinentOfCountry() {
	return continentOfCountry;
}

void Country::setContinentOfCountry(Continent * continentOfCountry) {
	this->continentOfCountry = continentOfCountry;
}


int Country::getCountryOwnerId() {
	return *countryOwnerId;
}

void Country::setCountryOwnerId(int countryOwnerId) {
	this->countryOwnerId.reset(new int(countryOwnerId));
}

int Country::getNumberOfArmies() {
	return *numberOfArmies;
}

void Country::setNumberOfArmies(int numberOfArmies) {
	this->numberOfArmies.reset(new int(numberOfArmies));
}

int Country::getCoordinateX() {
	return *coordinateX;
}

void Country::setCoordinateX(int coordinateX) {
	this->coordinateX.reset(new int(coordinateX));
}

int Country::getCoordinateY() {
	return *coordinateY;
}

void Country::setCoordinateY(int coordinateY) {
	this->coordinateY.reset(new int(coordinateY));
}

vector<Country*> Country::getAdjacentCountries() {
	return adjacentCountries;
}

void Country::setAdjacentCountries(Country * country) {
	adjacentCountries.push_back(country);
}

