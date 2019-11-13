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
    
	void readMapFile(std::string fileName);
    void createMap();
    void displayMap();
	Map* getMap();
private:
    Map* map;
    
    //vectors of information from map file
    std::vector<std::string> continents_info;
    std::vector<std::string> countries_info;
    std::vector<std::string> borders_info;
    
};


class MapLoaderConquest {
    
public:
    //constructor
    MapLoaderConquest();
    
    //destructor
    ~MapLoaderConquest();
    
    void readConquestMapFile(std::string fileName);
    void createConquestMap();
    void displayConquestMap();
    Map* getMap();

    private:
    Map* map;
    
    //vectors of information from conquest map file
    std::vector<std::string*> continents_info;
    std::vector<std::string*> territories_info;
    
    
};


class AdapterMap: public MapLoader {
    
    public:
    //constructor with parameter
    AdapterMap(MapLoaderConquest* conquestMap);
    
    //default constructor
    AdapterMap();
    
    //destructor
    ~AdapterMap();
    
    void readMapFile(std::string fileName);
    void createMap();
    void displayMap();
    Map* getMap();
    
private:
    Map* map;
    MapLoaderConquest* conquestMaploader;


};
