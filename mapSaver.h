/* TMX Map Saver
Takes map data in memory and saves it to disk in the TMX format (i.e. XML).
Mostly used to save procedurally generated maps to a file.

More information on Tiled Map Editor: https://github.com/bjorn/tiled/wiki

NOTE: saveMap() is the only function necessary to understand.
*/

#ifndef MAPSAVER_H
#define MAPSAVER_H

#include <string>
#include <fstream>
#include <sstream>
#include "tinyxml2.h"
#include "base64.h"

//encode a 2d-array of integers into a base-64 encoded string
std::string base64EncodeMap(int** mapLayer, int width, int height);

//add an image element to tileset element
void addImageElement(tinyxml2::XMLElement* tilesetElement, std::string tilesetName, int tilesetWidth, int tilesetHeight);

//add a properties element to map element
void addPropertiesElement(tinyxml2::XMLElement* mapElement);

//add a tileset element to mapElement
void addTilesetElement(tinyxml2::XMLElement* mapElement,
	int tileWidth, int tileHeight, int tilesetWidth, int tilesetHeight,
	std::string tilesetName);

//add data element to layer element
void addDataElement(tinyxml2::XMLElement* layerElement, int** mapLayer, int width, int height);

//add layer element to map element
void addLayerElement(tinyxml2::XMLElement* mapElement, int** mapLayer, int width, int height, std::string layerName);

//Takes map data and metadata as arguments, and saves everything to a TMX file to be used with Tiled Map Editor.
void saveMap(std::string tilesetName, int*** map, int width, 
	int height, int tileWidth, int tileHeight, int tilesetWidth, 
	int tilesetHeight, int numLayers = 1, std::string mapName = "map.tmx");

#endif