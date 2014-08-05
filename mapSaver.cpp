#include "mapSaver.h"

std::string base64EncodeMap(int** mapLayer, int width, int height) {

	//this is usually 4, since int is 4 bytes and char is 1 bytes.
	int chars_in_int = sizeof(int) / sizeof(char);

	//copy mapLayer data into a single buffer
	unsigned char* data = (unsigned char*)malloc(width * height * chars_in_int);

	for (int y = 0; y < height; ++y) {
		memcpy(data + y * width * chars_in_int, mapLayer[y], width * chars_in_int);
	}

	//return encoded data
	return base64_encode((const unsigned char*)data, chars_in_int * width * height);
}

void addImageElement(tinyxml2::XMLElement* tilesetElement, std::string tilesetName, int tilesetWidth, int tilesetHeight) {

	tinyxml2::XMLElement* imageElement = tilesetElement->GetDocument()->NewElement("image");
	imageElement->SetAttribute("source", tilesetName.c_str());
	imageElement->SetAttribute("width", tilesetWidth);
	imageElement->SetAttribute("height", tilesetHeight);

	tilesetElement->LinkEndChild(imageElement);
	return;
}

void addPropertiesElement(tinyxml2::XMLElement* mapElement) {

	tinyxml2::XMLElement* propertyElement = mapElement->GetDocument()->NewElement("properties");
	mapElement->LinkEndChild(propertyElement);
	return;
}

void addTilesetElement(tinyxml2::XMLElement* mapElement,
	int tileWidth, int tileHeight, int tilesetWidth, int tilesetHeight,
	std::string tilesetName) {

	tinyxml2::XMLElement* tilesetElement = mapElement->GetDocument()->NewElement("tileset");
	tilesetElement->SetAttribute("firstgid", 1);
		//No support for multiple tilesets
		//Single tileset means firstgid is always 1
	tilesetElement->SetAttribute("name", "Map Tileset");
		//Name shouldn't matter too much, set to a default value
	tilesetElement->SetAttribute("tilewidth", tileWidth);
	tilesetElement->SetAttribute("tileheight", tileHeight);

	addImageElement(tilesetElement, tilesetName, tilesetWidth, tilesetHeight);

	mapElement->LinkEndChild(tilesetElement);
	return;
}

void addDataElement(tinyxml2::XMLElement* layerElement, int** mapLayer, int width, int height) {

	tinyxml2::XMLElement* dataElement = layerElement->GetDocument()->NewElement("data");
	dataElement->SetAttribute("encoding", "base64");
		//Only supports uncompressed base64 encoding

	std::string base64EncodedMap = base64EncodeMap(mapLayer, width, height);
	dataElement->SetText(base64EncodedMap.c_str());

	layerElement->LinkEndChild(dataElement);
	return;
}

void addLayerElement(tinyxml2::XMLElement* mapElement, int** mapLayer, int width, int height, std::string layerName) {
	
	tinyxml2::XMLElement* layerElement = mapElement->GetDocument()->NewElement("layer");
	layerElement->SetAttribute("name", layerName.c_str());
	layerElement->SetAttribute("width", width);
	layerElement->SetAttribute("height", height);

	addDataElement(layerElement, mapLayer, width, height);

	mapElement->LinkEndChild(layerElement);
	return;
}

void saveMap(std::string tilesetName, int*** map, int width,
	int height, int tileWidth, int tileHeight, int tilesetWidth,
	int tilesetHeight, int numLayers, std::string mapName) {

	//Create an XML document with default declaration
	tinyxml2::XMLDocument mapDoc;
	mapDoc.LinkEndChild(mapDoc.NewDeclaration());

	//Add map element with attributes
	tinyxml2::XMLElement* mapElement = mapDoc.NewElement("map");
	mapElement->SetAttribute("version", 1.0);
	mapElement->SetAttribute("orientation", "orthogonal");
		//Only supports orthogonal maps
	mapElement->SetAttribute("width", width);
	mapElement->SetAttribute("height", height);
	mapElement->SetAttribute("tilewidth", tileWidth);
	mapElement->SetAttribute("tileheight", tileHeight);

	//Add property element
	//Properties are not supported
	addPropertiesElement(mapElement);

	//Add tileset element with attributes
	addTilesetElement(mapElement, tileWidth, tileHeight, tilesetWidth, tilesetHeight, tilesetName);

	//Add multiple layer elements
	for (int n = 0; n < numLayers; ++n) {
		std::ostringstream layerName;
		layerName << "Layer " << n;
		addLayerElement(mapElement, map[n], width, height, layerName.str());
	}

	//Link everything to XML document
	mapDoc.LinkEndChild(mapElement);

	//Save to TMX file
	mapDoc.SaveFile(mapName.c_str());

	return;
}