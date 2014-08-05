#include <iostream>
#include <cstdio>
#include <string>
#include <time.h>
#include <list>

#include "celAutoMap.h"
#include "mapSaver.h"

//Dimensions of the map
const int x = 20;
const int y = 20;

//Number of map layers
const int num = 6;

using namespace std;

int main(int argc, char* argv[]) {
	srand(time(NULL));

	list<celAutoMap*> randomMaps;

	//create muliple maps
	for (int n = 0; n < num; ++n) {
		celAutoMap* map = new celAutoMap(x, y);
		map->generateMap();
		map->setWallIDs();
		randomMaps.push_back(map);
	}

	//store the map data of each map in an array of int**
	int*** mapLayers = new int**[randomMaps.size()];
	int n = 0;
	for (list<celAutoMap*>::iterator iter = randomMaps.begin(); iter != randomMaps.end(); iter++) {
		mapLayers[n] = (*iter)->getMap();
		++n;
	}

	//save map
	saveMap("tileset2.png", mapLayers, x, y, 32, 32, 416, 32, num);

	//clean up memory
	while (!randomMaps.empty()) {
		celAutoMap *map = *randomMaps.begin();
		delete map;
		randomMaps.pop_front();
	}

	return 0;
}