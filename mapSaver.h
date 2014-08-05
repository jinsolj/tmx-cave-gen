/* TMX Map Saver

	Original code by Jin Sol Jung (jinsol.jung@gmail.com)

	This source code is provided 'as-is', without any express or implied
	warranty. In no event will the author be held liable for any damages	
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this source code must not be misrepresented; you must not
	claim that you wrote the original source code. If you use this source code
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original source code.

	3. This notice may not be removed or altered from any source distribution.
	
	----------------------------------------------------------------------------
	
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
