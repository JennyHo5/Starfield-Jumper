#include "stdafx.h"
#include "LevelMaker.h"

LevelMaker::LevelMaker() : width(MAP_WIDTH), height(MAP_HEIGHT), tileMap(nullptr), entities(nullptr), gameObjects(nullptr)
{
}

std::vector<std::vector<int>> LevelMaker::GenerateMapData() const {
	printf("Generating Map Data from Level Maker\n");
	// Create an 2D array, lay out the empty tiles first
	std::vector<std::vector<int>> mapData(width, std::vector<int>(height, 0));

	// Column by column generate grounds
	for (int x = 0; x < width - 8; x++) {
		// Lay out the empty space (from the middle to the top of the screen)
		for (int y = GROUND_HEIGHT; y < height; y++) {
			mapData[x][y] = TILE_ID_EMPTY;
		}

		// Chance to just be emptyness for the column
		if (GetRandom(4) == 1) {
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
		if (GetRandom(6) == 1) {
			for (int y = 0; y < GROUND_HEIGHT - 1 + PILLAR_HEIGHT; y++) {
				mapData[x][y] = TILE_ID_GROUND[GetRandom(GROUND_NUMBER) - 1];
			}
			mapData[x][GROUND_HEIGHT - 1 + PILLAR_HEIGHT] = TILE_ID_TOP[GetRandom(TOPS_NUMBER) - 1];;
		}
		// Chance to generate a grass or rock
		else if (GetRandom(3) == 1) {
			if (mapData[x][0] != TILE_ID_EMPTY) // Is the column is not empty column
			{
				mapData[x][GROUND_HEIGHT] = TILE_ID_DECOR[GetRandom(DECOR_NUMBER) - 1];
			}
		}
	}

	// Row by row generate platforms
	for (int y = GROUND_HEIGHT + PILLAR_HEIGHT; y < height - 2; y++) {
		// For a continuing empty space with 3 tile width, there's a chance to generate a platform
		for (int x = 3; x < width; x++) {
			if (mapData[x][y] == TILE_ID_EMPTY && mapData[x - 1][y] == TILE_ID_EMPTY && mapData[x - 2][y] == TILE_ID_EMPTY) {
				if (GetRandom(15) == 1) {
					mapData[x][y] = TILE_ID_PLATFORM_RIGHT;
					mapData[x - 1][y] = TILE_ID_PLATFORM_MIDDLE;
					mapData[x - 2][y] = TILE_ID_PLATFORM_LEFT;
				}
			}
		}
	}

	// Leave 8 tile width ground to generate big tree
	for (int x = width - 8; x < width; x++) {
		// Lay out the empty space (from the middle to the top of the screen)
		for (int y = GROUND_HEIGHT; y < height; y++) {
			mapData[x][y] = TILE_ID_EMPTY;
		}

		for (int y = 0; y < GROUND_HEIGHT - 1; y++) {
			mapData[x][y] = TILE_ID_GROUND[GetRandom(GROUND_NUMBER) - 1];
		}
		mapData[x][GROUND_HEIGHT - 1] = TILE_ID_TOP[GetRandom(TOPS_NUMBER) - 1];
	}

	return mapData;
}

void LevelMaker::GenerateDecors() {
	// Add a sign at the start of the map
	if (mapData[0][GROUND_HEIGHT - 1] != TILE_ID_EMPTY)
	{
		if (mapData[0][GROUND_HEIGHT + 1] == TILE_ID_EMPTY)
		{
			GameObject* sign = new GameObject(TILE_SIZE / 2, TILE_SIZE * (GROUND_HEIGHT + 1 / 2) + SIGN_HEIGHT / 2, SIGN_WIDTH, SIGN_HEIGHT, App::CreateSprite(".\\graphics\\decor\\sign.png", 1, 1));
			gameObjects->push_back(sign);
		}
		else {
			GameObject* sign = new GameObject(TILE_SIZE / 2, TILE_SIZE * (GROUND_HEIGHT + PILLAR_HEIGHT + 1/2) + SIGN_HEIGHT / 2, SIGN_WIDTH, SIGN_HEIGHT, App::CreateSprite(".\\graphics\\decor\\sign.png", 1, 1));
			gameObjects->push_back(sign);
		}
	}

	// if there is a solid top with 2 tile width, might generate a rock
	for (int x = 1; x < width; x++) {
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

	// if there is a solid top with 4 tile width, might generate a small tree
	for (int x = 3; x < width; x++) {
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

	// Add the big tree at the end
	GameObject* newBigTree = new GameObject(TILE_SIZE * MAP_WIDTH - BIG_TREE_WIDTH / 2, TILE_SIZE * (GROUND_HEIGHT + 1) + BIG_TREE_HEIGHT / 2, BIG_TREE_WIDTH, BIG_TREE_HEIGHT, App::CreateSprite(".\\graphics\\decor\\big-tree.png", 1, 1));
	gameObjects->push_back(newBigTree);

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