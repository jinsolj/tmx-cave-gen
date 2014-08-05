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

//Dimensions of each tile in pixels.
const int tileWidth = 32;
const int tileHeight = 32;

//Dimensions of the tileset image in pixels.
const int tilesetWidth = 416;
const int tilesetHeight = 32;

//Name of the tileset image.
const std::string tilesetName = "tileset2.png";

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
	saveMap(tilesetName, mapLayers, x, y, tileWidth, tileHeight, tilesetWidth,
		tilesetHeight, num);

	//clean up memory
	while (!randomMaps.empty()) {
		celAutoMap *map = *randomMaps.begin();
		delete map;
		randomMaps.pop_front();
	}

	return 0;
}