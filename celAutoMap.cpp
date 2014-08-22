#include <iostream>
#include <stack>
#include "celAutoMap.h"

const int NUM_WALL_TYPES = 13;
const int NUM_EDGE_TYPES = 3;

const int FLOOR_LAYER = 0;
const int WALL_LAYER = 1;

//NOTE: Each generic type should be the highest of its subtypes.
enum TileType {
	//floor types
	FLOOR = 1,

	//wall types
	TOP_LEFT_WALL,
	TOP_CENTER_WALL,
	TOP_RIGHT_WALL,

	MID_LEFT_WALL,
	MID_CENTER_WALL,
	MID_RIGHT_WALL,

	BOT_LEFT_WALL,
	BOT_CENTER_WALL,
	BOT_RIGHT_WALL,

	VERTICAL_WALL,
	HORIZONTAL_WALL,
	SINGULAR_WALL,

	//mid wall types
	BLANK0,

	TOP_LEFT_WALL_ZMID,
	TOP_CENTER_WALL_ZMID,
	TOP_RIGHT_WALL_ZMID,

	MID_LEFT_WALL_ZMID,
	MID_CENTER_WALL_ZMID,
	MID_RIGHT_WALL_ZMID,

	BOT_LEFT_WALL_ZMID,
	BOT_CENTER_WALL_ZMID,
	BOT_RIGHT_WALL_ZMID,

	VERTICAL_WALL_ZMID,
	HORIZONTAL_WALL_ZMID,
	SINGULAR_WALL_ZMID,

	//high wall types
	BLANK1,

	TOP_LEFT_WALL_ZHIGH,
	TOP_CENTER_WALL_ZHIGH,
	TOP_RIGHT_WALL_ZHIGH,

	MID_LEFT_WALL_ZHIGH,
	MID_CENTER_WALL_ZHIGH,
	MID_RIGHT_WALL_ZHIGH,

	BOT_LEFT_WALL_ZHIGH,
	BOT_CENTER_WALL_ZHIGH,
	BOT_RIGHT_WALL_ZHIGH,

	VERTICAL_WALL_ZHIGH,
	HORIZONTAL_WALL_ZHIGH,
	SINGULAR_WALL_ZHIGH,

	//building types
	BLANK2,

	TOP_LEFT_BUILDING,
	TOP_CENTER_BUILDING,
	TOP_RIGHT_BUILDING,

	MID_LEFT_BUILDING,
	MID_CENTER_BUILDING,
	MID_RIGHT_BUILDING,

	BOT_LEFT_BUILDING,
	BOT_CENTER_BUILDING,
	BOT_RIGHT_BUILDING,

	VERTICAL_BUILDING,
	HORIZONTAL_BUILDING,
	SINGULAR_BUILDING,

	//mid BUILDING types
	BLANK3,

	TOP_LEFT_BUILDING_ZMID,
	TOP_CENTER_BUILDING_ZMID,
	TOP_RIGHT_BUILDING_ZMID,

	MID_LEFT_BUILDING_ZMID,
	MID_CENTER_BUILDING_ZMID,
	MID_RIGHT_BUILDING_ZMID,

	BOT_LEFT_BUILDING_ZMID,
	BOT_CENTER_BUILDING_ZMID,
	BOT_RIGHT_BUILDING_ZMID,

	VERTICAL_BUILDING_ZMID,
	HORIZONTAL_BUILDING_ZMID,
	SINGULAR_BUILDING_ZMID,

	//high BUILDING types
	BLANK4,

	TOP_LEFT_BUILDING_ZHIGH,
	TOP_CENTER_BUILDING_ZHIGH,
	TOP_RIGHT_BUILDING_ZHIGH,

	MID_LEFT_BUILDING_ZHIGH,
	MID_CENTER_BUILDING_ZHIGH,
	MID_RIGHT_BUILDING_ZHIGH,

	BOT_LEFT_BUILDING_ZHIGH,
	BOT_CENTER_BUILDING_ZHIGH,
	BOT_RIGHT_BUILDING_ZHIGH,

	VERTICAL_BUILDING_ZHIGH,
	HORIZONTAL_BUILDING_ZHIGH,
	SINGULAR_BUILDING_ZHIGH,
};

//check the amount of neighbors of a cell that are walls
int celAutoMap::checkNeighbor(int row, int col) {
	//0 1 2
	//3 X 5
	//6 7 8

	//generation starts on the bottom-most layer
	int** map = mMap[FLOOR_LAYER];
	int height = mHeight;
	int width = mWidth;

	int count = 0;

	if (row < 0 || col < 0 || row >= height || col >= width) {
		std::cerr << "ERROR: passing invalid values to checkNeighbor().";
		abort();
	}


	//check 0
	if ((row == 0 || col == 0) ||
		(map[row - 1][col - 1] > FLOOR))
		count++;

	//check 1
	if (row == 0 || map[row - 1][col] > FLOOR)
		count++;

	//check 2
	if ((row == 0 || col == width - 1) ||
		map[row - 1][col + 1] > FLOOR)
		count++;

	//check 3
	if (col == 0 || map[row][col - 1] > FLOOR)
		count++;

	//check 5
	if (col == width - 1 || map[row][col + 1]  > FLOOR)
		count++;

	//check 6
	if ((row == height - 1 || col == 0) ||
		(map[row + 1][col - 1]  > FLOOR))
		count++;

	//check 7
	if (row == height - 1 || map[row + 1][col] > FLOOR)
		count++;

	//check 8
	if ((row == height - 1 || col == width - 1) ||
		map[row + 1][col + 1] > FLOOR)
		count++;

	return count;
}

//runs the cellular automata method for each cell
void celAutoMap::celAutoIterate() {

	//create a temporary map to store new values
	int** tempMap = new int*[mHeight];
	for (int i = 0; i < mHeight; i++) {
		tempMap[i] = new int[mWidth];
	}

	for (int i = 0; i < mHeight; i++) {
		for (int j = 0; j < mWidth; j++) {

			int numWall = checkNeighbor(i, j);

			//4-5 rule: makes a specific cell more like its neighbors
			if ((mMap[FLOOR_LAYER][i][j] > FLOOR && numWall >= 4) ||
				(mMap[FLOOR_LAYER][i][j] == FLOOR && numWall >= 5))
				tempMap[i][j] = TOP_LEFT_WALL;

			/*else if ((mapA[i][j] == WALL && numWall <= 1) ||
			(mapA[i][j] != WALL && numWall <= 2))
			mapB[i][j] = FLOOR;*/

			else
				tempMap[i][j] = FLOOR;// mapA[i][j];
		}
	}

	//delete old map and assign new one
	for (int i = 0; i < mHeight; i++) {
		delete[] mMap[FLOOR_LAYER][i];
	}
	delete mMap[FLOOR_LAYER];

	mMap[FLOOR_LAYER] = tempMap;
}

//fills map randomly with floors or walls
void celAutoMap::initMap() {
	//generate random value from 0-99
	int value = rand() % 100;

	//fill map with randomly walls or spaces
	for (int i = 0; i < mHeight; i++) {
		for (int j = 0; j < mWidth; j++) {
			value = rand() % 100;
			if (value < mWallChance)
				mMap[FLOOR_LAYER][i][j] = TOP_LEFT_WALL;
			else
				mMap[FLOOR_LAYER][i][j] = FLOOR;
		}
	}
}

void celAutoMap::generateMap() {
	//init map
	initMap();

	//run cellular automata method for mNumIterations iterations
	int n;
	for (n = 0; n < mNumIterations; n++) {
		celAutoIterate();
	}
}

//set IDs of wall tiles to be used in map editor.
void celAutoMap::setWallIDs() {
	for (int i = 0; i < mHeight; i++) {
		for (int j = 0; j < mWidth; j++) {
			int** map = mMap[FLOOR_LAYER];
			int height = mHeight;
			int width = mWidth;
			int row = i;
			int col = j;

			if(mMap[FLOOR_LAYER][i][j] > FLOOR) {
				//0 1 2
				//3 X 5
				//6 7 8
	
				//where X is our current cell
	

				//bool wall0 = (row == 0 || col == 0) ||
				//	(map[row - 1][col - 1] > 0);
	
				bool wall1 = (row == 0 || map[row - 1][col] > FLOOR);
	
				//bool wall2 = (row == 0 || col == width - 1) ||
				//	map[row - 1][col + 1] > 0;
	
				bool wall3 = (col == 0 || map[row][col - 1] > FLOOR);
	
				bool wall5 = (col == width - 1 || map[row][col + 1] > FLOOR);
	
				//bool wall6 = (row == height - 1 || col == 0) ||
				//	(map[row + 1][col - 1] > 0);
	
				bool wall7 = (row == height - 1 || map[row + 1][col] > FLOOR);
	
				//bool wall8 = (row == height - 1 || col == width - 1) ||
				//	map[row + 1][col + 1] > 0;
	
	

				//These are the following block types:
	
				//+-----+
				//|1 2 3|
				//|4 5 5|
				//|7 8 9|
				//+-----+
	
				//|10|
	
	
				//--
				//11
				//--
	
				//+--+
				//|12|
				//+--+
	
				if (!wall1 && !wall3 && wall5 && wall7)
					mMap[FLOOR_LAYER][i][j] = TOP_LEFT_WALL;
				else if (!wall1 && wall3 && wall5 && wall7)
					mMap[FLOOR_LAYER][i][j] = TOP_CENTER_WALL;
				else if (!wall1 && wall3 && !wall5 && wall7)
					mMap[FLOOR_LAYER][i][j] = TOP_RIGHT_WALL;
				else if (wall1 && !wall3 && wall5 && wall7)
					mMap[FLOOR_LAYER][i][j] = MID_LEFT_WALL;
				else if (wall1 && wall3 && wall5 && wall7)
					mMap[FLOOR_LAYER][i][j] = MID_CENTER_WALL;
				else if (wall1 && wall3 && !wall5 && wall7)
					mMap[FLOOR_LAYER][i][j] = MID_RIGHT_WALL;
				else if (wall1 && !wall3 && wall5 && !wall7)
					mMap[FLOOR_LAYER][i][j] = BOT_LEFT_WALL;
				else if (wall1 && wall3 && wall5 && !wall7)
					mMap[FLOOR_LAYER][i][j] = BOT_CENTER_WALL;
				else if (wall1 && wall3 && !wall5 && !wall7)
					mMap[FLOOR_LAYER][i][j] = BOT_RIGHT_WALL;
				else if (wall1 && !wall3 && !wall5 && wall7)
					mMap[FLOOR_LAYER][i][j] = VERTICAL_WALL;
				else if (!wall1 && wall3 && wall5 && !wall7)
					mMap[FLOOR_LAYER][i][j] = HORIZONTAL_WALL;
				else if (!wall1 && !wall3 && !wall5 && !wall7)
					mMap[FLOOR_LAYER][i][j] = SINGULAR_WALL;
			}

			//NOTE: Forgetting to check if a tile was a wall first
			//leads to some interesting procedurally generated vertical line patterns.
		}
	}
}

void celAutoMap::extrudeGeography(int wallHeight) {
	for (int j = 0; j < mHeight; ++j) {
		for (int i = 0; i < mWidth; ++i) {
			if (mMap[FLOOR_LAYER][j][i] > FLOOR) {

				//extrude geometry for intermediate walls
				for (int n = 1; n < wallHeight; ++n) {
					if (j - n >= 0) {
						mMap[WALL_LAYER][j - n][i] = mMap[FLOOR_LAYER][j][i] + NUM_WALL_TYPES;
					}
				}
				//extrude for top of walls
				if (j - (wallHeight) >= 0) {
					mMap[WALL_LAYER][j - (wallHeight)][i] = mMap[FLOOR_LAYER][j][i] + NUM_WALL_TYPES * 2;
				}
			}
		}
	}

	// if at the bottom of the map, extend tiles downward
	//in order to cover off map walls
	for (int i = 0; i < mWidth; ++i) {
		for (int n = 0; n < wallHeight; ++n) {
			if (mMap[FLOOR_LAYER][mHeight - 1][i] != FLOOR) {
				if (mMap[FLOOR_LAYER][mHeight - 1][i] != MID_CENTER_WALL)
					mMap[WALL_LAYER][mHeight - 1 - n][i] = mMap[FLOOR_LAYER][mHeight - 1][i] + NUM_EDGE_TYPES + NUM_WALL_TYPES * 2;
				else
					mMap[WALL_LAYER][mHeight - 1 - n][i] = MID_CENTER_WALL_ZHIGH;
			}
		}
	}
	
}

