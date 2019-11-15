#include <iostream>
#include "Map.h"
#include <vector>
#include <string>
class MapLoader {
public:
    
    //constructor
	MapLoader();
    
    //destructor
    ~MapLoader();
    
    //copy constructor
    MapLoader(const MapLoader &orig);
    
	void readMapFile(std::string fileName);
    void createMap();
    void displayMap();
	Map* getMap();
    
    const MapLoader& operator=(const MapLoader& m);
    
private:
    Map* map;
    
    //vectors of information from map file
    std::vector<std::string> continents_info;
    std::vector<std::string> countries_info;
    std::vector<std::string> borders_info;    
};


class ConquestMapLoader {
    
public:
    //constructor
    ConquestMapLoader();
    
    //destructor
    ~ConquestMapLoader();
    
    //copy constructor
    ConquestMapLoader(const ConquestMapLoader &orig);
    
    void readConquestMapFile(std::string fileName);
    void createConquestMap();
    void displayConquestMap();
    Map* getMap();
    
    const ConquestMapLoader& operator=(const ConquestMapLoader& c);
    private:
    Map* map;
    
    //vectors of information from conquest map file
    std::vector<std::string*> continents_info;
    std::vector<std::string*> territories_info;
    
    
};


class AdapterConquestMaploader: public MapLoader {
    
    public:
    //constructor with parameter
    AdapterConquestMaploader(ConquestMapLoader* conquestMap);
    
    //default constructor
    AdapterConquestMaploader();
    
    //destructor
    ~AdapterConquestMaploader();
    
    //copy constructor
    AdapterConquestMaploader(const AdapterConquestMaploader &orig);
    
    const AdapterConquestMaploader &operator=(const AdapterConquestMaploader &a);
    
    void readMapFile(std::string fileName);
    void createMap();
    void displayMap();
    Map* getMap();
    
private:
    ConquestMapLoader* conquestMaploader;


};
