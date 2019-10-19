#include <iostream>
#include "MapLoader.h"
using namespace std;

int main() {
	string mapName;
	MapLoader myMapLoader;
	cout << "Please enter the name of the map you would like to load" << endl;
	cin >> mapName;

	myMapLoader.readMapFile("maps/" + mapName + ".map");

	cout << "End file" << endl;
}