#include "stdafx.h"
#include "LevelMaker.h"

LevelMaker::LevelMaker() : width(MAP_WIDTH), height(MAP_HEIGHT), tileMap(nullptr), entities(nullptr), gameObjects(nullptr)
{
}

std::vector<std::vector<int>> LevelMaker::GenerateMapData() const {
	printf("Generating Map Data from Level Maker\n");
	// Create an 2D array, lay out the empty tiles first
	std::vector<std::vector<int>> mapData(width, std::vector<int>(height, 0));

	// Column by column generation
	for (int x = 0; x < width; x++) {
		// Lay out the empty space (from the middle to the top of the screen)
		for (int y = GROUND_HEIGHT; y < height; y++) {
			mapData[x][y] = TILE_ID_EMPTY;
		}

		// Chance to just be emptyness for the column
		if (GetRandom(7) == 1) {
			for (int y = 0; y < GROUND_HEIGHT; y++) {
				mapData[x][y] = TILE_ID_EMPTY;
			}

		}
		else {
			for (int y = 0; y < GROUND_HEIGHT - 1; y++) {
				mapData[x][y] = TILE_ID_GROUND[GetRandom(GROUND_NUMBER) - 1];
			}
			mapData[x][GROUND_HEIGHT - 1] = TILE_ID_TOP[GetRandom(TOPS_NUMBER) - 1];
		}

		// Chance to generate a pillar
		int pillarHeight = 2;
		if (GetRandom(8) == 1) {
			for (int y = 0; y < GROUND_HEIGHT - 1 + pillarHeight; y++) {
				mapData[x][y] = TILE_ID_GROUND[GetRandom(GROUND_NUMBER) - 1];
			}
			mapData[x][GROUND_HEIGHT - 1 + pillarHeight] = TILE_ID_TOP[GetRandom(TOPS_NUMBER) - 1];;
		}
		// Chance to generate a grass or rock
		else if (GetRandom(3) == 1) {
			if (mapData[x][0] != TILE_ID_EMPTY) // Is the column is not empty column
			{
				mapData[x][GROUND_HEIGHT] = TILE_ID_DECOR[GetRandom(DECOR_NUMBER) - 1];
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

void LevelMaker::GenerateDecors() {
	for (int x = 1; x < width; x++) {
		// if there is a solid top with 2 tile width, might generate a rock
		if (mapData[x][GROUND_HEIGHT - 1] != TILE_ID_EMPTY && mapData[x - 1][GROUND_HEIGHT - 1] != TILE_ID_EMPTY
			&& mapData[x][GROUND_HEIGHT] == TILE_ID_EMPTY && mapData[x - 1][GROUND_HEIGHT] == TILE_ID_EMPTY)
			{
			if(GetRandom(5) == 1)
			{
				GameObject* newRock = new GameObject(TILE_SIZE * (x + 1 / 2), TILE_SIZE * (GROUND_HEIGHT + 1), ROCK_WIDTH, ROCK_HEIGHT, App::CreateSprite(".\\graphics\\decor\\rock.png", 1, 1));
				gameObjects->push_back(newRock);
			}
		}
	}

	for (int x = 3; x < width; x++) {
		// if there is a solid top with 4 tile width, might generate a small tree
		if (mapData[x][GROUND_HEIGHT - 1] != TILE_ID_EMPTY && mapData[x - 1][GROUND_HEIGHT - 1] != TILE_ID_EMPTY && mapData[x - 2][GROUND_HEIGHT - 1] != TILE_ID_EMPTY && mapData[x - 3][GROUND_HEIGHT - 1] != TILE_ID_EMPTY
			&& mapData[x][GROUND_HEIGHT] == TILE_ID_EMPTY && mapData[x - 1][GROUND_HEIGHT] == TILE_ID_EMPTY && mapData[x - 2][GROUND_HEIGHT] == TILE_ID_EMPTY && mapData[x - 3][GROUND_HEIGHT] == TILE_ID_EMPTY)
		{
			if (GetRandom(2) == 1)
			{
				GameObject* newTree = new GameObject(TILE_SIZE * (x - 2 + 1 + 1 / 2), TILE_SIZE * GROUND_HEIGHT + SMALL_TREE_HEIGHT / 2, SMALL_TREE_WIDTH, SMALL_TREE_HEIGHT, App::CreateSprite(".\\graphics\\decor\\small-tree.png", 1, 1));
				gameObjects->push_back(newTree);
			}
		}
	}
}

GameLevel* LevelMaker::Generate() {
	entities = new std::vector<Entity*>(); // Deallocated in GameLevel
	gameObjects = new std::vector<GameObject*>(); // Deallocated in GameLevel
	tileMap = new TileMap(MAP_WIDTH, MAP_HEIGHT); // Deallocated in GameLevel
	
	mapData = GenerateMapData();
	tileMap->loadMap(mapData);
	GenerateDecors();
	return new GameLevel(tileMap, entities, gameObjects); // Deallocated in PlayState
}