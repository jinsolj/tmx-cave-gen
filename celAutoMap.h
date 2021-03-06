/* Cellular Automata Map Generator
	
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
	
	Uses cellular automata to procedurally generate cave-like maps.
	
	This is a modified implementation of the method described here: 
	http://www.roguebasin.com/index.php?title=Cellular_Automata_Method_for_Generating_Random_Cave-Like_Levels
	
	IMPORTANT: remember to #include<time.h> and call srand(time(NULL)) before doing any map operations.
*/

#ifndef CELAUTOMAP_H
#define CELAUTOMAP_H

const int DEFAULT_WALL_CHANCE = 45;
const int DEFAULT_NUM_ITERATIONS = 40;
const int NUM_MAP_LAYERS = 2;

class celAutoMap {
public:
	celAutoMap(int width, int height, int wallChance = DEFAULT_WALL_CHANCE,
		int numIterations = DEFAULT_NUM_ITERATIONS) {
		mWidth = width;
		mHeight = height;
		mWallChance = wallChance;
		mNumIterations = numIterations;


		mMap = new int**[NUM_MAP_LAYERS];

		//dynamically allocate 2d array of ints for map
		for (int j = 0; j < NUM_MAP_LAYERS; ++j) {
			mMap[j] = new int*[mHeight];
			for (int i = 0; i < mHeight; i++) {
				mMap[j][i] = new int[mWidth];
			}
		}
	}

	~celAutoMap() {
		for (int j = 0; j < NUM_MAP_LAYERS; ++j) {
			for (int i = 0; i < mHeight; i++) {
				delete[] mMap[j][i];
			}
			delete mMap[j];
		}
		delete mMap;
	}

	//procedurally generates a map within celAutoMap.
	//this removes the previously generated map.
	void generateMap();

	//modifies mMap values so that specific ints map to specific wall types
	void setWallIDs();

	//adds second layer that gives depth to scene.
	void extrudeGeography(int wallHeight);

	int*** getMap() { return mMap; }
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
	int*** mMap;

	//width and height of map
	//wall chance = %chance of a random cell being a wall during initMap()
	//mNumIterations = number of iterations to run celAutoIterate during generateMap(); higher = less noisy
	int mWidth, mHeight, mWallChance, mNumIterations;

};

#endif
