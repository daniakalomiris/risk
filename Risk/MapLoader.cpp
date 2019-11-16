#include <iostream>
#include <fstream>
#include "MapLoader.h"
#include <vector>
#include <string>
#include <sstream>


using namespace std;

//******************* Implementation for the MapLoader Class *******************

MapLoader::MapLoader() {
    map = new Map();
    
}

MapLoader:: ~MapLoader() {
    delete map;
}

//copy constructor
MapLoader:: MapLoader(const MapLoader &orig){
    this->continents_info = orig.continents_info;
    this->countries_info = orig.countries_info;
    this->borders_info = orig.borders_info;
    this->map = new Map();
    *map = *orig.map;
}

//assignment operator
const MapLoader& MapLoader:: operator=(const MapLoader& m){
    if(&m !=this) {
        delete map;
        Map* newMap = new Map();
        this->map = newMap;
    }
    
    return *this;
}


void MapLoader::readMapFile(string fileName) {
    
    
    //create mapFile stream
    ifstream mapFile;
    
    //tells if the map is valid or not
    bool isValidMapFile1 = false;
    bool isValidMapFile2 = false;
    bool isValidMapFile3 = false;
    
    string line;
    
    //open the file
    mapFile.open(fileName);
    
    
    //if i can't open the mapfile, display a error message and exit program
    if (mapFile.fail()) {
        cout << "Error: cannot open map" << endl;
        //exit the program
        exit(1);
    }
    
    cout << "Reading from " << fileName << endl;
    
    //while you can read a line and the file is not at the end
    while (getline(mapFile, line) && !mapFile.eof()) {
        
        
        //if line is equal to [continents]
        if (line.find("[continents]") != std::string::npos) {
            isValidMapFile1 = true;
            
            //start reading the continents until we reach an empty line
            //Be carefull the last element will be an empty line
            while (getline(mapFile, line) && line.find("[countries]") == std::string::npos) {
                //push the continents data into the vector
                continents_info.push_back(line);
            }
        }
        
        //if the line is equal to [countries]
        if (line.find("[countries]") != std::string::npos) {
            
            isValidMapFile2 = true;
            
            
            //start reading the countries until we reach an empty line
            //Be carefull the last element will be an empty line
            while (getline(mapFile, line) && line.find("[borders]") == std::string::npos) {
                //push the countries data into the vector
                countries_info.push_back(line);
            }
        }
        
        
        //if the line is equal to [borders]
        if (line.find("[borders]") != std::string::npos) {
            
            isValidMapFile3 = true;
            
            //start reading the borders until we reach an empty line
            
            while (getline(mapFile, line) && line != "") {
                //push the countries data into the vector
                borders_info.push_back(line);
            }
        }
    }
    
    if( (isValidMapFile1 && isValidMapFile2 && isValidMapFile3) == false) {
        cout << "This is not a valid map file, the program will terminate" <<endl;
        exit(1);
    }
    
    
    //delete the last empty line of the countries_info and continents_info
    countries_info.pop_back();
    continents_info.pop_back();
    mapFile.close();
    
}

void MapLoader::createMap() {
    
    
    //create continents
    for(int i = 0; i< continents_info.size(); i++) {
        
        //temp string array to store a continent info
        string temp[3];
        
        //create a continent and push it to map
        Continent* continent = new Continent();
        map->setContinent(continent);
        
        //put each line of the continents_info vector into a string
        string line_info = continents_info[i];
        
        //create a stringstream to separate each elements on the line
        stringstream elements_line(line_info);
        
        for(int i =0; i< 3; i++) {
            elements_line >> temp[i];
        }
        
        continent->setContinentName(temp[0]);
        continent->setNumberOfArmies(stoi(temp[1]));
    }
    
    //create countries
    for(int i = 0; i< countries_info.size(); i++) {
        
        //temp string array to store a continent info
        //temp[0] = countryNumber
        //temp[1] = countryName
        //temp[2] = continents it belongs to
        string temp[5];
        
        //put each line of the contients_info vector into a string
        string line_info = countries_info[i];
        
        //create a stringstream to separate each elements on the line
        stringstream elements_line(line_info);
        
        for(int i =0; i< 5; i++) {
            elements_line >> temp[i];
        }
        
        //create a country
        Country* country = new Country();
        
        //set all its data
        country->setCountryNumber(stoi(temp[0]));
        country->setCountryName(temp[1]);
        country->setCoordinateX(stoi(temp[3]));
        country->setCoordinateY(stoi(temp[4]));
        country->setContinentOfCountry(map->getContinents().at(stoi(temp[2])-1));
        
        //push the country in one continent
        map->getContinents().at(stoi(temp[2])-1)->setCountriesOfContinent(country);
        map->setCountry(country);
    }
    
    
    
    //create borders
    //create a temp vector containing the info of one line of the border_info
    //we can't use an array like for countries and continents because the number of elements per line change
    for(int i = 0; i < borders_info.size(); i++) {
        
        vector <string> temp;
        
        //put each line of the borders_info vector into a string
        string line_info = borders_info[i];
        
        //create a stringstream helper to find the number of elements on  each line
        stringstream helper(line_info);
        
        //we put -1 so we don't count the first number given because it is the country
        //int numBorders =-1;
        //string temp3;
        
        //number of elements on the line
        int numElements =0;
        
        string temp2;
        
        //while loop to calculate the number of element on 1 line
        while(helper >> temp2 ) {
            numElements++;
            
        }
        
        //create a stringstream to separate each elements on the line
        stringstream elements_line(line_info);
        
        //put each elements on the line in the vector temp
        for(int i = 0 ; i < numElements; i++) {
            elements_line >> temp2;
            temp.push_back(temp2);
        }
        
        
        
        for(int j = 1; j < temp.size(); j ++) {
            // cout << temp.at(j) << endl;
            
            for(int k = 0; k < map->getCountries().size(); k++) {
                
                if(this->map->getCountries().at(k)->getCountryNumber() == (stoi(temp.at(j)))) {
                    
                    //   cout << map->getCountries().at(k)->getCountryName() << endl;
                    map->getCountries().at(i)->setAdjacentCountries(map->getCountries().at(k));
                    
                }
                
                
            }
            
        }
    }
    
    //create adjacent continents
    
    //loop through all countries in the map
    for(int i = 0; i < map->getCountries().size(); i++) {
        
        //for each countries, loop through its adjacent countries
        for(int j = 0; j < map->getCountries().at(i)->getAdjacentCountries().size(); j++) {
            
            //name of the continent of the country
            string continentName = map->getCountries().at(i)->getContinentOfCountry()->getContinentName();
            
            //compare the continent of the country and the continent of the adjacent countries
            //if it is not the same, set new adjacent continents
            if( (continentName.compare(map->getCountries().at(i)->getAdjacentCountries().at(j)->getContinentOfCountry()->getContinentName())) != 0) {
                
                //vector of adjacent continents of the current continent of the country
                vector<Continent*> currentContinentOfCountry =  map->getCountries().at(i)->getContinentOfCountry()->getAdjacentContinents();
                
                vector<Continent*>::iterator it1 = find(currentContinentOfCountry.begin(), currentContinentOfCountry.end(), map->getCountries().at(i)->getAdjacentCountries().at(j)->getContinentOfCountry());
                
                // Check if continent has not been added already, if not add them as an adjacent continent
                if (it1 == currentContinentOfCountry.end()) {
                    
                    map->getCountries().at(i)->getContinentOfCountry()->setAdjacentContinents(map->getCountries().at(i)->getAdjacentCountries().at(j)->getContinentOfCountry());
                    
                }
                
            }
            
        }
        
    }
    
    //check if the map created is valid or not
    map->isValidMap();
}

Map* MapLoader::getMap() {
    return map;
}

void MapLoader::displayMap() {
    
    cout << "\nThese are the map's continents and their armies: " << endl;
    
    
    //display the continents
    for (int i = 0; i < map->getContinents().size(); i++) {
        
        cout << "\nContinent #" << i <<endl;
        cout<< map->getContinents().at(i)->getContinentName() << ": " << map->getContinents().at(i)->getNumberOfArmies() << " armies" << endl;
        
        //diplay the countries
        for(int j = 0; j<map->getContinents().at(i)->getCountriesOfContinent().size(); j++) {
            cout<< "\t" << map->getContinents().at(i)->getCountriesOfContinent().at(j)->getCountryName() << endl;
        }
    }
    
    //display the countries and adjacent countries
    cout << "\n\nThis is a list of each country and its adjacent countries: " << endl;
    for(int i = 0; i < map->getCountries().size(); i++) {
        cout << map->getCountries().at(i)->getCountryName() << " : " ;
        for(int j = 0 ; j < map->getCountries().at(i)->getAdjacentCountries().size(); j++) {
            cout << map->getCountries().at(i)->getAdjacentCountries().at(j)->getCountryName() << ", " ;
            
            
        }
        cout << " " << endl;
    }
    
    //display continents and adjacent continents
    cout << "\n\nThis is a list of each continent and its adjacent continents: " << endl;
    for(int i=0; i < map->getContinents().size(); i++) {
        cout << map->getContinents().at(i)->getContinentName() << " : ";
        for(int j=0; j < map->getContinents().at(i)->getAdjacentContinents().size(); j++) {
            cout << map->getContinents().at(i)->getAdjacentContinents().at(j)->getContinentName() << ", ";
            
            
        }
        cout << " " << endl;
    }
    
    
    
}



//******************* Implementation for the MapLoaderConquest Class *******************

//default constructor
ConquestMapLoader::ConquestMapLoader() {
    map = new Map();
}

//destructor
ConquestMapLoader:: ~ConquestMapLoader() {
    delete map;
}

//copy constructor
ConquestMapLoader:: ConquestMapLoader(const ConquestMapLoader &orig) {
    this->continents_info = orig.continents_info;
    this->territories_info = orig.territories_info;
      this->map = new Map();
      *map = *orig.map;
}

//assignment operator
const ConquestMapLoader& ConquestMapLoader::operator=(const ConquestMapLoader& c) {
    if(&c !=this) {
           delete map;
           Map* newMap = new Map();
           this->map = newMap;
       }
       
       return *this;
}

//read a conquest map file
void ConquestMapLoader::readConquestMapFile(string fileName) {
    
    //create mapFile stream
    ifstream mapFile;
    
    
    //tells if the map is valid or not
    bool isValidMapFile1 = false;
    bool isValidMapFile2 = false;
    
    string line;
    
    //open the file
    mapFile.open(fileName);
    
    
    //if i can't open the mapfile, display a error message and exit program
    if (mapFile.fail()) {
        cout << "Error: cannot open map" << endl;
        //exit the program
        exit(1);
    }
    
    cout << "Reading from " << fileName << endl;
    
    //while you can read a line and the file is not at the end
    while (getline(mapFile, line) && !mapFile.eof()) {
        
        //if line is equal to [Continents]
        if (line.find("[Continents]") != std::string::npos) {
            isValidMapFile1 = true;
            
            //start reading the continents until we reach an empty line
            //Be carefull the last element will be an empty line
            while (getline(mapFile, line) && line.find("[Territories]") == std::string::npos) {
                
                string* lineToPush = new string();
                
                *lineToPush = line;
                
                //push the continents data into the vector
                continents_info.push_back(lineToPush);
                
                
            }
        }
        
        
        
        //if the line is equal to [Territories]
        if (line.find("[Territories]") != std::string::npos) {
            
            isValidMapFile2 = true;
            
            
            //start reading the countries until we reach an empty line
            //Be carefull the last element will be an empty line
            while (getline(mapFile, line)) {
                
                string* lineToPush = new string;
                
                *lineToPush = line;
                
                //push the countries data into the vector
                territories_info.push_back(lineToPush);
                
            }
        }
    }
    
    
    
    //delete empty lines in territories_info vectors
    for(int i = territories_info.size()-1; i >= 0; i--) {
        
        //contains the line
        string temp = *territories_info.at(i);
        
        //if the length of the line is 1
        if(temp.length() == 1) {
            
            //char that contains the blank character
            char empty = temp.at(0);
            
            //if the char is a space character, erase that line
            if(isspace(empty)) {
                territories_info.erase(territories_info.begin() + i);
            }
        }
        else if(temp.length() == 0) {
                  territories_info.erase(territories_info.begin() + i);
              }
    }
    
    
    //delete empty lines in continent_info vectors
    for(int i = continents_info.size()-1; i >= 0; i--) {
        
        //contains the line
        string temp = *continents_info.at(i);
        
        //if the length of the line is 1
        if(temp.length() == 1) {
            
            //char that contains the blank character
            char empty = temp.at(0);
            
            //if the char is a space character, erase that line
            if(isspace(empty)) {
                continents_info.erase(continents_info.begin() + i);
            }
        }
        else if(temp.length() == 0) {
             continents_info.erase(continents_info.begin() + i);
        }
    }
    
    
    if( (isValidMapFile1 && isValidMapFile2) == false) {
        cout << "This is not a valid map file, the program will terminate" <<endl;
        exit(1);
    }
    
    //close the file
    mapFile.close();
    
}

//create the conquest map
void ConquestMapLoader::createConquestMap() {
    
    
    //create continents
     for(int i = 0; i< continents_info.size(); i++) {
    
    
    //temp string array to store a continent info
    string temp[2];
    
    //create a continent and push it to map
    Continent* continent = new Continent();
    map->setContinent(continent);
    
    //put each line of the continents_info vector into a string
    string line_info = *continents_info[i];
    
    //create a stringstream to separate each elements on the line
    stringstream elements_line(line_info);
    
    //will contains the important data on the line
    string data;
    
    //keeptrack of the index of the temp array string
    int indexTemp = 0;
    
    //separate the line in two string, don't care about the = sign
    while(getline(elements_line, data, '=')) {
        
        //put the data in the temp array string
        temp[indexTemp] = data;
        indexTemp++;
    }
    
    //sets the data from the map file to the continent object
    continent->setContinentName(temp[0]);

    continent->setNumberOfArmies(stoi (temp[1]));

    
}
    
    //create territories
    for(int i = 0; i< territories_info.size(); i++) {
        //temporary vector containing all the data of each territory
        vector<string> tempTerritoriesInfo;
        
        //put each line of the territories_info vector into a string
        string line_info = *territories_info[i];
        
        //create a stringstream to separate each elements on the line
        stringstream elements_line(line_info);
        
        //will contains the important data on the line
        string data;
        
        
        //separate the line in different string, use the coma as a delimiter
        while(getline(elements_line, data, ',')) {
            // put the data in the temp array string
            tempTerritoriesInfo.push_back(data);
        }
        
        
        //create a new country
        Country* country = new Country();
        
        //set all the country data
        country->setCountryNumber(i+1);
        country->setCountryName(tempTerritoriesInfo[0]);
        country->setCoordinateX(stoi (tempTerritoriesInfo[1]));
        country->setCoordinateY(stoi(tempTerritoriesInfo[2]));
        
        //look for the continent in the map
        for(int j=0; j <map->getContinents().size(); j++) {
            
            //the continent name we are looking for
            string continentName = tempTerritoriesInfo[3];
            
            if(continentName.compare(map->getContinents().at(j)->getContinentName()) == 0) {
                
                //set the continent of the country
                country->setContinentOfCountry(map->getContinents().at(j));
                map->getContinents().at(j)->setCountriesOfContinent(country);
            }
            
        }
       
        //set the country to the map
        map->setCountry(country);
        
    }
    
    //create adjacent territories
    for(int i = 0; i< territories_info.size(); i++) {
   
    //temporary vector containing all the data of each territory
    vector<string> tempTerritoriesInfo;
    
    //put each line of the territories_info vector into a string
    string line_info = *territories_info[i];
    
    //create a stringstream to separate each elements on the line
    stringstream elements_line(line_info);
    
    //will contains the important data on the line
    string data;
    
    
    //separate the line in different string, use the coma as a delimiter
    while(getline(elements_line, data, ',')) {
        
        //remove the ascii 13 at the end of a line, without removing the name won't compare
        data.erase(remove(data.begin(), data.end(), 13), data.end());
        
        // put the data in the temp array string
        tempTerritoriesInfo.push_back(data);
    }
    
   
        
        //loop throught the names of the adjacent countries in the tempTerritoriesInfo vector
        for(int j=4; j < tempTerritoriesInfo.size(); j++) {
           
            string countryName = tempTerritoriesInfo.at(j);
            
           // cout << countryName << endl;
            //not working with the length are not the same. there is an extra whitespace in the last element of the list
            //loop in the countries of the map to get the country with the right name
            for(int k = 0; k < map->getCountries().size(); k++) {
                
             
                //if we have the found the country with the righ name
                if(countryName.compare(map->getCountries().at(k)->getCountryName()) == 0) {
                 
                    //set that country as an adjacent country
                   map->getCountries().at(i)->setAdjacentCountries(map->getCountries().at(k));
                    break;
                }
                
            }
            
            
        }
       
    }
        
    
    //creates adjacent continents
    //loop through all countries in the map
     for(int i = 0; i < map->getCountries().size(); i++) {
         
         //for each countries, loop through its adjacent countries
         for(int j = 0; j < map->getCountries().at(i)->getAdjacentCountries().size(); j++) {
             
             //name of the continent of the country
             string continentName = map->getCountries().at(i)->getContinentOfCountry()->getContinentName();
             
             //compare the continent of the country and the continent of the adjacent countries
             //if it is not the same, set new adjacent continents
             if( (continentName.compare(map->getCountries().at(i)->getAdjacentCountries().at(j)->getContinentOfCountry()->getContinentName())) != 0) {
                 
                 //vector of adjacent continents of the current continent of the country
                 vector<Continent*> currentContinentOfCountry =  map->getCountries().at(i)->getContinentOfCountry()->getAdjacentContinents();
                 
                 vector<Continent*>::iterator it1 = find(currentContinentOfCountry.begin(), currentContinentOfCountry.end(), map->getCountries().at(i)->getAdjacentCountries().at(j)->getContinentOfCountry());
                 
                 // Check if continent has not been added already, if not add them as an adjacent continent
                 if (it1 == currentContinentOfCountry.end()) {
                     
                     map->getCountries().at(i)->getContinentOfCountry()->setAdjacentContinents(map->getCountries().at(i)->getAdjacentCountries().at(j)->getContinentOfCountry());
                     
                 }
                 
             }
             
         }
         
     }
        
               
        //check if the map created is valid or not
        map->isValidMap();
    

}

//get the map created
Map* ConquestMapLoader:: getMap() {
    return map;
}

//display the conquest map
void ConquestMapLoader:: displayConquestMap() {
    cout << "\nThese are the map's continents and their armies: " << endl;
    
    
    //display the continents
    for (int i = 0; i < map->getContinents().size(); i++) {
        
        cout << "\nContinent #" << i <<endl;
        cout<< map->getContinents().at(i)->getContinentName() << ": " << map->getContinents().at(i)->getNumberOfArmies() << " armies" << endl;
        
        //diplay the countries
        for(int j = 0; j<map->getContinents().at(i)->getCountriesOfContinent().size(); j++) {
            cout<< "\t" << map->getContinents().at(i)->getCountriesOfContinent().at(j)->getCountryName() << endl;
        }
    }
    
    //display the countries and adjacent countries
    cout << "\n\nThis is a list of each country and its adjacent countries: " << endl;
    for(int i = 0; i < map->getCountries().size(); i++) {
        cout << map->getCountries().at(i)->getCountryName() << " : " ;
        for(int j = 0 ; j < map->getCountries().at(i)->getAdjacentCountries().size(); j++) {
            cout << map->getCountries().at(i)->getAdjacentCountries().at(j)->getCountryName() << ", " ;
            
            
        }
        cout << " " << endl;
    }
    
    //display continents and adjacent continents
    cout << "\n\nThis is a list of each continent and its adjacent continents: " << endl;
    for(int i=0; i < map->getContinents().size(); i++) {
        cout << map->getContinents().at(i)->getContinentName() << " : ";
        for(int j=0; j < map->getContinents().at(i)->getAdjacentContinents().size(); j++) {
            cout << map->getContinents().at(i)->getAdjacentContinents().at(j)->getContinentName() << ", ";
            
            
        }
        cout << " " << endl;
    }
    
    
}


//******************* Implementation for the adapterMap Class *******************

//default constructor
AdapterConquestMaploader:: AdapterConquestMaploader() {
    
}

//constructor with 1 parameter
AdapterConquestMaploader:: AdapterConquestMaploader(ConquestMapLoader* conquestMap) {
    conquestMaploader = conquestMap;
}

//destructor
AdapterConquestMaploader:: ~AdapterConquestMaploader() {
    delete conquestMaploader;
}

//copy construstor
AdapterConquestMaploader:: AdapterConquestMaploader(const AdapterConquestMaploader &orig) {
    this->conquestMaploader = new ConquestMapLoader();
    
    *conquestMaploader = *orig.conquestMaploader;
    
}

//overloading assignment operator
const AdapterConquestMaploader& AdapterConquestMaploader:: operator=(const AdapterConquestMaploader &a) {
    if(&a !=this) {
        delete conquestMaploader;
        AdapterConquestMaploader* tempAdapter = new AdapterConquestMaploader(a);
        this->conquestMaploader = tempAdapter->conquestMaploader;
    }
    return *this;
}

//override function in Maploader to be able to call function in MapLoaderConquest
void AdapterConquestMaploader::readMapFile(string fileName) {
    conquestMaploader->readConquestMapFile(fileName);
}

void AdapterConquestMaploader::createMap() {
    conquestMaploader->createConquestMap();
}

void AdapterConquestMaploader::displayMap() {
    conquestMaploader->displayConquestMap();
}

Map* AdapterConquestMaploader::getMap() {
    return conquestMaploader->getMap();
}
