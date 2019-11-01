#include <iostream>
#include "MapLoader.h"
#include "Map.h"
using namespace std;


<<<<<<< HEAD
int main() {
	string mapName;
	MapLoader myMapLoader;
	cout << "Please enter the name of the map you would like to load" << endl;
	cin >> mapName;

	myMapLoader.readMapFile("maps/" + mapName + ".map");
    myMapLoader.createMap();
    myMapLoader.displayMap();
	cout << "End file" << endl;


}
=======
//int main() {
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

>>>>>>> dca3588b34152b4352c87f0e44a20441699da17d
