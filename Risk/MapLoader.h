#include <iostream>
#include "Map.h"

class MapLoader {
public:
	MapLoader();
	void readMapFile(std::string fileName);
	void createMap();
	Map* getMap();
private:
	Map* map;
};
