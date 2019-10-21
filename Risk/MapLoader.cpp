#include <iostream>
#include <fstream>
#include "MapLoader.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

static vector<string> continents_info;
static vector<string> countries_info;
static vector<string> borders_info;

MapLoader::MapLoader() {
     map = new Map();
}

void MapLoader::readMapFile(string fileName) {


	//create mapFile stream
	ifstream mapFile;

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

	// while(getline(mapFile, line) && line !="[continents]") {};

	// while(getline(mapFile, line) && line != "") {
	//     cout << line << endl;
	// }

	//while you can read a line and the file is not at the end
	while (getline(mapFile, line) && !mapFile.eof()) {

		//if line is equal to [continents]
		if (line.find("[continents]") != std::string::npos) {

			//start reading the continents until we reach an empty line
			//Be carefull the last element will be an empty line
			while (getline(mapFile, line) && line.find("[countries]") == std::string::npos) {
				//push the continents data into the vector
				continents_info.push_back(line);
			}
		}

		//if the line is equal to [countries]
		if (line.find("[countries]") != std::string::npos) {

			//start reading the countries until we reach an empty line
			//Be carefull the last element will be an empty line
			while (getline(mapFile, line) && line.find("[borders]") == std::string::npos) {
				//push the countries data into the vector
				countries_info.push_back(line);
			}
		}

		//if the line is equal to [borders]
		if (line.find("[borders]") != std::string::npos) {

			//start reading the borders until we reach an empty line

			while (getline(mapFile, line) && line != "") {
				//push the countries data into the vector
				borders_info.push_back(line);
			}
		}
	}


	//delete the last empty line of the countries_info and continents_info
	countries_info.pop_back();
	continents_info.pop_back();


	//outputs continent info
//	cout << "\n**the Continents**" << endl;
//	for (int i = 0; i < continents_info.size(); i++) {
//		cout << continents_info[i] << endl;
//	}
//
//
//	//code to help debugging
//		// bool lineIsEmpty;
//		// lineIsEmpty =continents_info[10].empty();
//		// cout << continents_info[10] << endl;
//	   // cout << continents_info[9].length() << endl;
//
//
//
//		//outputs country info
//	cout << "\n**the Countries**" << endl;
//	for (int i = 0; i < countries_info.size(); i++) {
//		cout << countries_info[i] << endl;
//	}
//
//	//outputs border info
//	cout << "\n**the Borders**" << endl;
//	for (int i = 0; i < borders_info.size(); i++) {
//		cout << borders_info[i] << endl;
//	}


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
        
        //put each line of the contients_info vector into a string
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
         country->setCountryNumber(stoi(temp[0]));
         country->setCountryName(temp[1]);
         country->setCoordinateX(stoi(temp[3]));
         country->setCoordinateY(stoi(temp[4]));
         country->setContinentOfCountry(map->getContinents().at(stoi(temp[2])-1));
         //push the country in one continent
         map->getContinents().at(stoi(temp[2])-1)->setCountriesOfContinent(country);

     }
    
    
    
    
    //create a temp variable the size of the continents (worst case, all countries are adjacent to one country)
    //temp[0] is the number of the country
    string temp[map->getContinents().size()-1];
    
    //put each line of the contients_info vector into a string
    string line_info = borders_info[0];
    
    //create a stringstream to separate each elements on the line
    stringstream elements_line(line_info);
    
    //we put -1 so we don't count the first number given because it is the country
    int numBorders =-1;
          for(int i =0; i< borders_info.size(); i++) {
              string temp2;
              elements_line >> temp2;
              if(temp2.empty()) {
                  continue;
              }
              numBorders++;
              temp[i] = temp2;
              }
    
  //  cout << "numOfBorders: " <<numBorders <<endl;
    
//    for(int i = 0; i <numBorders+1; i++) {
//        cout << temp[i] <<endl;
//    }
    
        //we need to get the countries through the continents.
        //HERE
    
    
     //   map->getContinents().at(i)->getCountriesOfContinent().at(stoi(temp[0])-1);
    
    
    //  map->getCountries().at(stoi(temp[0])-1)->setAdjacentCountries(map->getCountries().at(1));
    
//    for(int i = 1; i < numBorders; i++) {
//        map->getCountries().at(stoi(temp[0])-1)->setAdjacentCountries(map->getCountries().at(stoi(temp[i])-1));
//    }
    
    
    
    
    //create borders
//    for(int i = 0; i< borders_info.size(); i++) {
//
//        //create a temp variable the size of the continents (worst case, all countries are adjacent to one country)
//        //temp[0] is the number of the country
//        string temp[map->getContinents().size()-1];
//
//        //put each line of the contients_info vector into a string
//        string line_info = borders_info[i];
//
//        //create a stringstream to separate each elements on the line
//               stringstream elements_line(line_info);
//
//        int numBorders;
//              for(int i =0; i< borders_info.size(); i++) {
//
//                  if(elements_line.str() == "") {
//                      continue;
//                  }
//                  numBorders++;
//                  elements_line >> temp[i];
//                  }
//
//        for(int i = 1; i < numBorders; i++) {
//            map->getCountries().at(stoi(temp[0]))->setAdjacentCountries(map->getCountries().at(stoi(temp[i])));
//        }
//       // map->getCountries().at(stoi(temp[0]));
//
//
//    }
    
    
    
}

Map* MapLoader::getMap() {
	return map;
}

void MapLoader::displayMap() {
    
cout << "\nThese are the map's continents and their armies: " << endl;
  for (int i = 0; i < map->getContinents().size(); i++) {
      
      cout << "\nContinent #" << i <<endl;
      cout<< map->getContinents().at(i)->getContinentName() << ": " << map->getContinents().at(i)->getNumberOfArmies() << " armies" << endl;
    
//      cout << "Countries:" << endl;
      
      for(int j = 0; j<map->getContinents().at(i)->getCountriesOfContinent().size(); j++) {
      cout<< "\t" << map->getContinents().at(i)->getCountriesOfContinent().at(j)->getCountryName() << endl;
      }
  }
    
  
    
}
