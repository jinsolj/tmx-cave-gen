#include <iostream>
#include "celAutoMap.h"

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

	WALL,
};

//check the amount of neighbors of a cell that are walls
int celAutoMap::checkNeighbor(int row, int col) {
	//0 1 2
	//3 X 5
	//6 7 8

	int** map = mMap;
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
			if ((mMap[i][j] > FLOOR && numWall >= 4) ||
				(mMap[i][j] == FLOOR && numWall >= 5))
				tempMap[i][j] = WALL;

			/*else if ((mapA[i][j] == WALL && numWall <= 1) ||
			(mapA[i][j] != WALL && numWall <= 2))
			mapB[i][j] = FLOOR;*/

			else
				tempMap[i][j] = FLOOR;// mapA[i][j];
		}
	}

	//delete old map and assign new one
	for (int i = 0; i < mHeight; i++) {
		delete[] mMap[i];
	}
	delete mMap;

	mMap = tempMap;
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
				mMap[i][j] = WALL;
			else
				mMap[i][j] = FLOOR;
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
			int** map = mMap;
			int height = mHeight;
			int width = mWidth;
			int row = i;
			int col = j;

			if(mMap[i][j] > FLOOR) {
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
					mMap[i][j] = TOP_LEFT_WALL;
				else if (!wall1 && wall3 && wall5 && wall7)
					mMap[i][j] = TOP_CENTER_WALL;
				else if (!wall1 && wall3 && !wall5 && wall7)
					mMap[i][j] = TOP_RIGHT_WALL;
				else if (wall1 && !wall3 && wall5 && wall7)
					mMap[i][j] = MID_LEFT_WALL;
				else if (wall1 && wall3 && wall5 && wall7)
					mMap[i][j] = MID_CENTER_WALL;
				else if (wall1 && wall3 && !wall5 && wall7)
					mMap[i][j] = MID_RIGHT_WALL;
				else if (wall1 && !wall3 && wall5 && !wall7)
					mMap[i][j] = BOT_LEFT_WALL;
				else if (wall1 && wall3 && wall5 && !wall7)
					mMap[i][j] = BOT_CENTER_WALL;
				else if (wall1 && wall3 && !wall5 && !wall7)
					mMap[i][j] = BOT_RIGHT_WALL;
				else if (wall1 && !wall3 && !wall5 && wall7)
					mMap[i][j] = VERTICAL_WALL;
				else if (!wall1 && wall3 && wall5 && !wall7)
					mMap[i][j] = HORIZONTAL_WALL;
				else if (!wall1 && !wall3 && !wall5 && !wall7)
					mMap[i][j] = SINGULAR_WALL;
			}

			//NOTE: Forgetting to check if a tile was a wall first
			//leads to some interesting procedurally generated vertical line patterns.
		}
	}
}