#include "stdafx.h"
#include "LevelMaker.h"

LevelMaker::LevelMaker() : width(MAP_WIDTH), height(MAP_HEIGHT), tileMap(nullptr), entities(nullptr), gameObjects(nullptr)
{
}

std::vector<std::vector<int>> LevelMaker::GenerateMapData() const {
	printf("Generating Map Data from Level Maker\n");
	// Create an 2D array, lay out the empty tiles first
	std::vector<std::vector<int>> mapData(width, std::vector<int>(height, 0));

	int groundHeight = height * 1 / 5;
	// Column by column generation
	for (int x = 0; x < width; x++) {
		// Lay out the empty space (from the middle to the top of the screen)
		for (int y = groundHeight; y < height; y++) {
			mapData[x][y] = TILE_ID_EMPTY;
		}

		// Chance to just be emptyness for the column
		if (GetRandom(7) == 1) {
			for (int y = 0; y < groundHeight; y++) {
				mapData[x][y] = TILE_ID_EMPTY;
			}

		}
		else {
			for (int y = 0; y < groundHeight - 1; y++) {
				mapData[x][y] = TILE_ID_GROUND[GetRandom(GROUND_NUMBER) - 1];
			}
			mapData[x][groundHeight - 1] = TILE_ID_TOP[GetRandom(TOPS_NUMBER) - 1];
		}

		// Chance to generate a pillar
		int pillarHeight = 2;
		if (GetRandom(8) == 1) {
			for (int y = 0; y < groundHeight - 1 + pillarHeight; y++) {
				mapData[x][y] = TILE_ID_GROUND[GetRandom(GROUND_NUMBER) - 1];
			}
			mapData[x][groundHeight - 1 + pillarHeight] = TILE_ID_TOP[GetRandom(TOPS_NUMBER) - 1];;
		}
		// Chance to generate a grass or rock
		else if (GetRandom(3) == 1) {
			if (mapData[x][0] != TILE_ID_EMPTY) // Is the column is not empty column
			{
				mapData[x][groundHeight] = TILE_ID_DECOR[GetRandom(DECOR_NUMBER) - 1];
			}
		}
	}

	// Change the tile's style based on it's position
	// For 0st column
	// if 0st column is a pillar, change it to pillar style


	// For 1 to width -1 column
	for (int x = 1; x < width; x++) {
		// TODO:
		// If x column is a gap and x-1 column is a flat ground, then change the x-1 column to right style
		// If x column is flat ground and x-1 column is a gap, then change x column to left style
		// If x column is a pillar, then change x column to pillar style
	}
	

	return mapData;
}

GameLevel* LevelMaker::Generate() {
	entities = new std::vector<Entity*>(); // Deallocated in GameLevel
	gameObjects = new std::vector<GameObject*>(); // Deallocated in GameLevel
	tileMap = new TileMap(MAP_WIDTH, MAP_HEIGHT); // Deallocated in GameLevel
	printf("Generating tileMap at address %p\n", tileMap);
	tileMap->loadMap(GenerateMapData());
	return new GameLevel(tileMap, entities, gameObjects); // Deallocated in PlayState
}