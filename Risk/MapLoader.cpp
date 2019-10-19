#include <iostream>
#include <fstream>
#include "MapLoader.h"
#include <vector>
#include <string>
using namespace std;

MapLoader::MapLoader() {

}

void MapLoader::readMapFile(string fileName) {

	vector<string> continents_info;
	vector<string> countries_info;
	vector<string> borders_info;

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
	cout << "\n**the Continents**" << endl;
	for (int i = 0; i < continents_info.size(); i++) {
		cout << continents_info[i] << endl;
	}


	//code to help debugging
		// bool lineIsEmpty;
		// lineIsEmpty =continents_info[10].empty();
		// cout << continents_info[10] << endl;
	   // cout << continents_info[9].length() << endl;



		//outputs country info
	cout << "\n**the Countries**" << endl;
	for (int i = 0; i < countries_info.size(); i++) {
		cout << countries_info[i] << endl;
	}

	//outputs border info
	cout << "\n**the Borders**" << endl;
	for (int i = 0; i < borders_info.size(); i++) {
		cout << borders_info[i] << endl;
	}


	mapFile.close();

}


