#include <iostream>
#include "MapLoader.h"
#include "Map.h"
using namespace std;


int main() {
        string mapName;
    MapLoaderConquest* myMapLoaderConquest = new MapLoaderConquest();;
        cout << "Please enter the name of the map you would like to load" << endl;
        
        //use getlines so we can enter file names with spaces
        getline(cin, mapName);
   
        myMapLoaderConquest->readConquestMapFile("maps/conquest/" + mapName + ".map");
    myMapLoaderConquest->createConquestMap();
    myMapLoaderConquest->displayConquestMap();

        cout << "End file" << endl;
    
    delete myMapLoaderConquest;
    myMapLoaderConquest = NULL;
    
}




//Driver for A1
//int main(){
//	string mapName;
//	MapLoader myMapLoader;
//	cout << "Please enter the name of the map you would like to load" << endl;
//	cin >> mapName;
//
//	myMapLoader.readMapFile("maps/" + mapName + ".map");
//    myMapLoader.createMap();
//    myMapLoader.displayMap();
//	cout << "End file" << endl;
//
//
//}


