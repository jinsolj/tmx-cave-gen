#include <iostream>
#include <cstdio>
#include <string>
#include <time.h>
#include <list>

#include "celAutoMap.h"
#include "mapSaver.h"

//Dimensions of the map
const int x = 70;
const int y = 70;

//Number of map layers
const int num = 2;

//Dimensions of each tile in pixels.
const int tileWidth = 16;
const int tileHeight = 16;

//Dimensions of the tileset image in pixels.
const int tilesetWidth = 16*13;
const int tilesetHeight = 16*3;

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
		map->extrudeGeography(2);
		randomMaps.push_back(map);
	}

	//save map
	saveMap(tilesetName, randomMaps.front()->getMap(), x, y, tileWidth, tileHeight, tilesetWidth,
		tilesetHeight, num);

	//clean up memory
	randomMaps.clear();

	/*
	celAutoMap myMap(x, y);
	myMap.generateMap();

	celAutoMap myMap2(x * 2, y * 2);
	for (int j = 0; j < y; ++j) {
		for (int i = 0; i < x; ++i) {
			myMap2.getMap()[2 * j][2 * i] = myMap.getMap()[j][i];
			myMap2.getMap()[2*j][2*i + 1] = myMap.getMap()[j][i];
			myMap2.getMap()[2*j + 1][2*i] = myMap.getMap()[j][i];
			myMap2.getMap()[2*j + 1][2*i + 1] = myMap.getMap()[j][i];
		}
	}

	for (n = 0; n < DEFAULT_NUM_ITERATIONS/2; n++) {
		myMap2.celAutoIterate();
	}

	myMap2.setWallIDs();

	int** terk = myMap2.getMap();
	saveMap(tilesetName, &terk, x * 2, y * 2, tileWidth, tileHeight, tilesetWidth, tilesetHeight);
	*/

	return 0;
}