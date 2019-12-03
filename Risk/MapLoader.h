#include <iostream>
#include "Map.h"
#include <vector>
#include <string>

class MapLoader {
public:
    MapLoader(); //constructor
    ~MapLoader(); //destructor
    MapLoader(const MapLoader &orig); //copy constructor
    void readMapFile(std::string fileName);
    void createMap();
    void displayMap();
    Map* getMap();
    const MapLoader& operator=(const MapLoader& m);
private:
    Map* map;
    std::vector<std::string> continents_info; //vector of information from map file
    std::vector<std::string> countries_info; //vector of information from map file
    std::vector<std::string> borders_info; //vector of information from map file
};

class ConquestMapLoader {
public:
    ConquestMapLoader(); //constructor
    ~ConquestMapLoader(); //destructor
    ConquestMapLoader(const ConquestMapLoader &orig); //copy constructor
    void readConquestMapFile(std::string fileName);
    void createConquestMap();
    void displayConquestMap();
    Map* getMap();
    const ConquestMapLoader& operator=(const ConquestMapLoader& c);
private:
    Map* map;
    std::vector<std::string*> continents_info; //vector of information from conquest map file
    std::vector<std::string*> territories_info; //vector of information from conquest map file
};

class AdapterConquestMaploader: public MapLoader {
public:
    AdapterConquestMaploader(ConquestMapLoader* conquestMap); //constructor with parameter
    AdapterConquestMaploader(); //default constructor
    ~AdapterConquestMaploader(); //destructor
    AdapterConquestMaploader(const AdapterConquestMaploader &orig); //copy constructor
    const AdapterConquestMaploader &operator=(const AdapterConquestMaploader &a);
    void readMapFile(std::string fileName);
    void createMap();
    void displayMap();
    Map* getMap();
private:
    ConquestMapLoader* conquestMaploader;
};
