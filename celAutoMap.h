/* Cellular Automata Map Generator
	Uses cellular automata to procedurally generate cave-like maps.
	
	This is a modified implementation of the method described here: 
	http://www.roguebasin.com/index.php?title=Cellular_Automata_Method_for_Generating_Random_Cave-Like_Levels
	
	IMPORTANT: remember to #include<time.h> and call srand(time(NULL)) before doing any map operations.
*/

#ifndef CELAUTOMAP_H
#define CELAUTOMAP_H

const int DEFAULT_WALL_CHANCE = 45;
const int DEFAULT_NUM_ITERATIONS = 40;

class celAutoMap {
public:
	celAutoMap(int width, int height, int wallChance = DEFAULT_WALL_CHANCE, 
				int numIterations = DEFAULT_NUM_ITERATIONS) {
		mWidth = width;
		mHeight = height;
		mWallChance = wallChance;
		mNumIterations = numIterations;

		//dynamically allocate 2d array of ints for map
		mMap = new int*[mHeight];
		for (int i = 0; i < mHeight; i++) {
			mMap[i] = new int[mWidth];
		}
	}

	~celAutoMap() {
		for (int i = 0; i < mHeight; i++) {
			delete[] mMap[i];
		}
		delete mMap;
	}

	//procedurally generates a map within celAutoMap.
	//this removes the previously generated map.
	void generateMap();

	//modifies mMap values so that specific ints map to specific wall types
	void setWallIDs();

	int** getMap() { return mMap; }
	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

private:
	//runs one iteration of cellular automata method.
	void celAutoIterate();

	//checks how many neighbors of a particular cell in the map are walls.
	int checkNeighbor(int row, int col);

	//sets the values in the map to random values depending on mWallChance.
	void initMap();

	//2d array of ints: 0 = floor, anything else is wall
	int** mMap;

	//width and height of map
	//wall chance = %chance of a random cell being a wall during initMap()
	//mNumIterations = number of iterations to run celAutoIterate during generateMap(); higher = less noisy
	int mWidth, mHeight, mWallChance, mNumIterations;

};

#endif