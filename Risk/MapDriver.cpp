#include "Map.h"
#include <iostream>
#include <memory>

using namespace std;

int main() {

	/* Create maps */
	
	Map map;
	Country canada;
	string canadaName = "Canada";
	canada.setCountryName(canadaName);

	cout << "COUNTRY NAME IS: " << canada.getCountryName() << endl;
	

	/* Valid map */

	/* Invalid map (some countries do not belong to any continents) */

	/* Invalid map (some continents have 0 countries) */

	/* Invalid map (some countries belong to more than 1 continent) */

	/* Show that each country is only in one continent */

	/* Shpw that map is connected graph (BFS or DFS) */

	/* Show that continents are connected subgraphs (BFS or DFS) */

	/* Show that each country is owned by a player and contain a number of armies */
}