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
