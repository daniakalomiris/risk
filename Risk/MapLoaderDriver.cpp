#include <iostream>
#include "MapLoader.h"
#include "Map.h"
using namespace std;


int main() {
    
    //answer of user
    int answer;
    
    //answer to load another map
    string anotherMap = "y";
    
    string mapName;
   
    while(anotherMap == "y") {
    //do-while loop to make sure the user enter a correct prompt
    do {
    cout << "Do you want to read a (1)Domination map file or (2)Conquest map file?" << endl;
         cin >> answer;
    } while (answer != 1 && answer !=2 );
   
    cin.ignore();
    if(answer == 1) {
        
        //create a normal MapLoader object
        MapLoader* maploader = new MapLoader();
        
        //prompts the user for the name of the map
        //the user need to enter only the name with the same name as the map file (this is case sensitive)
        cout << "Please enter the name of the map you would like to load" << endl;
        
        //use getlines so we can enter file names with spaces
        getline(cin, mapName);
        
        maploader->readMapFile("maps/domination/" + mapName + ".map");
        maploader->createMap();
        maploader->displayMap();
        
        delete maploader;
        maploader = NULL;
    }
    
    else if(answer ==2) {
        
        //create a conquest maploader object
        ConquestMapLoader* conquestMaploader = new ConquestMapLoader();
        
        //create a maploader adapter to "convert" a conquest map into a domination map
        AdapterConquestMaploader* conquestadapter = new AdapterConquestMaploader(conquestMaploader);
        
        //prompts the user for the name of the map
        //the user need to enter only the name with the same name as the map file (this is case sensitive)
        cout << "Please enter the name of the map you would like to load" << endl;
        
        //use getlines so we can enter file names with spaces
        getline(cin, mapName);
        
        
        //call the same methods as the normal maploader
        conquestadapter->readMapFile("maps/conquest/" + mapName + ".map");
        conquestadapter->createMap();
        conquestadapter->displayMap();
        
        delete conquestadapter;
        conquestadapter = NULL;
       
    }
    
    cout << "\n\nDo you want to load another map? (y/n)" << endl;
    cin >> anotherMap;
    }
}



