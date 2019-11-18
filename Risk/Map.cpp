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

void Map::setContinent(Continent* continent) {
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


void Map::getOwnerCountries(int playerId) {
	for (unsigned int i = 0; i < countries.size(); i++) {
		if (countries.at(i)->getCountryOwnerId() != NULL && countries.at(i)->getCountryOwnerId() == playerId) {
			cout << "Player " << playerId << " owns the country " << countries.at(i)->getCountryName() << " with " << countries.at(i)->getNumberOfArmies() << " armies." << endl;
		}
	}
}

//checks if continent is a subgraph 
bool Map::isContinentSubgraph() {
	if (continents.size() == 0) {
		return false;
	} 
	else {
		vector<Continent*> visited;
		visited.push_back(continents.at(0)); // Push first continent
		for (unsigned int i = 0; i < continents.size(); i++) {  // Loop through all continents
			for (unsigned int j = 0; j < continents.at(i)->getAdjacentContinents().size(); j++) { // Loop through all adjacent continents of a continent
				vector<Continent*>::iterator it = find(visited.begin(), visited.end(), continents.at(i)->getAdjacentContinents().at(j));
				if (it == visited.end()) { // Check if continent has not been visited
					visited.push_back(continents.at(i)->getAdjacentContinents().at(j)); // Add it to the list of visited continents
				}
			}
		}
		if (continents.size() == visited.size()) {
			cout << "Continents are connected subgraphs." << endl;
			return true;
		}
		else {
			cout << "Continents are not connected subgraphs." << endl;
			return false;
		}
	}
}

//checks if country is subgraph 
bool Map::isCountrySubgraph() {
	if (countries.size() == 0) {
		return false;
	}
	else {
		vector<Country*> visited;
		visited.push_back(countries.at(0)); // Push first country
		for (unsigned int i = 0; i < countries.size(); i++) {  // Loop through all countries
			for (unsigned int j = 0; j < countries.at(i)->getAdjacentCountries().size(); j++) { // Loop through all adjacent countries of a country
				vector<Country*>::iterator it = find(visited.begin(), visited.end(), countries.at(i)->getAdjacentCountries().at(j));
				if (it == visited.end()) { // Check if country has not been visited
					visited.push_back(countries.at(i)->getAdjacentCountries().at(j)); // Add it to the list of visited countries
				}
			}
		}
		if (countries.size() == visited.size()) {
			cout << "Map is a connected subgraph." << endl;
			return true;
		}
		else {
			cout << "Map is not a connected subgraph." << endl;
			return false;
		}
	}
}

//checks if country is in one continent
bool Map::isCountryInOneContinent() {
	for (unsigned int i = 0; i < countries.size(); i++) { // Loop through all countries
		Country* tempCountry = countries.at(i); // Country to find only once
		for (unsigned int j = 0; j < continents.size(); j++) { // Loop through all continents
			if (tempCountry->getContinentOfCountry() != continents.at(j)) { // If continent is the same as the continent of the country we are looking for, move to next continent
				for (unsigned int k = 0; k < continents.at(j)->getCountriesOfContinent().size(); k++) { // Loop through next continent's countries
					if (tempCountry->getCountryName() == continents.at(j)->getCountriesOfContinent().at(k)->getCountryName()) { // Check if each country belongs to only 1 continent
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
	for (unsigned int i = 0; i < continents.size(); i++) { // Loop through all continents
		if (continents.at(i)->getCountriesOfContinent().empty()) { // Check if each continent has at least 1 country
			cout << "Continent " << continents.at(i)->getContinentName() << " does not have any countries." << endl;
			cout << "Map is invalid." << endl;
			return false;
		}
	}
	cout << "All continents contain countries." << endl;
	return true;
}

bool Map::countryHasContinent() {
	for (unsigned int i = 0; i < countries.size(); i++) { // Loop through all countries and check if they belong to a continent
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
    
	if (isContinentSubgraph() && isCountrySubgraph() && isCountryInOneContinent() && isNotEmptyContinent() && countryHasContinent()) {
		cout << "Map is valid." << endl;
		return true;
	}
    
	return false;
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

//set the id to the player who owns the continent
void Continent:: setOwnerId(int playerId) {
    ownerId = make_unique<int>(playerId);
}
//get the id of the player who owns the continent
int Continent:: getOwnerId() {
    return *ownerId;
}

bool Continent::continentOwnByAPlayer() {
    
    //get the id of the country owner.
    int countryOwner = getCountriesOfContinent().at(0)->getCountryOwnerId();
    
    //check if the id of the first country in the continent is the same for the other countries in the continent
    for(int i = 0; i <getCountriesOfContinent().size(); i++) {
        if(countryOwner != getCountriesOfContinent().at(i)->getCountryOwnerId()) {
            return false;
        }
        
    }
    
    //set the owner ID
    setOwnerId(countryOwner);
    return true;
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

