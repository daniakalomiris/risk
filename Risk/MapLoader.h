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
    
    void readConquestMapFile();
    void createConquestMap();
    void displayConquestMap();
    Map* getMap();

    private:
    Map* map;
    
    //vectors of information from conquest map file
    std::vector<std::string*> continents_info;
    std::vector<std::string*> territories_info;
    
    
};


class adapterMap: public MapLoader {
    
    public:
    //constructor with parameter
    adapterMap(MapLoaderConquest* conquestMap);
    
    //default constructor
    adapterMap();
    
    //destructor
    ~adapterMap();
    
    void readMapFile(std::string fileName);
    void createMap();
    void displayMap();
    Map* getMap();
    
private:
    Map* map;
    MapLoaderConquest* conquestMaploader;


};
