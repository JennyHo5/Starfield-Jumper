#include "stdafx.h"
#include "LevelMaker.h"

LevelMaker::LevelMaker() : width(MAP_WIDTH), height(MAP_HEIGHT)
{
}

std::vector<std::vector<int>> LevelMaker::GenerateMapData() const {
	// Create an 2D array, lay out the empty tiles first
	std::vector<std::vector<int>> mapData(MAP_WIDTH, std::vector<int>(MAP_HEIGHT, 0));

	// Column by column generate grounds
	for (int x = 0; x < width - 8; x++) {
		// Lay out the empty space (from the middle to the top of the screen)
		for (int y = GROUND_HEIGHT; y < height; y++) {
			mapData[x][y] = TILE_ID_EMPTY;
		}

		// Chance to just be emptyness for the column
		if (GetRandom(3) == 1) {
			for (int y = 0; y < GROUND_HEIGHT; y++) {
				mapData[x][y] = TILE_ID_EMPTY;
			}

		}
		// Chance to generate grounds
		else {
			for (int y = 0; y < GROUND_HEIGHT - 1; y++) {
				mapData[x][y] = TILE_ID_GROUND[GetRandom(GROUND_NUMBER) - 1];
			}
			mapData[x][GROUND_HEIGHT - 1] = TILE_ID_TOP[GetRandom(TOPS_NUMBER) - 1];
		}

		// Chance to generate a pillar
		if (GetRandom(7) == 1) {
			for (int y = 0; y < GROUND_HEIGHT - 1 + PILLAR_HEIGHT; y++) {
				mapData[x][y] = TILE_ID_GROUND[GetRandom(GROUND_NUMBER) - 1];
			}
			mapData[x][GROUND_HEIGHT - 1 + PILLAR_HEIGHT] = TILE_ID_TOP[GetRandom(TOPS_NUMBER) - 1];;
		}
		// Chance to generate a grass
		else if (GetRandom(6) == 1) {
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
	for (int x = MAP_WIDTH - 8; x < width; x++) {
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
	int startColumn = -1;
	int startRow = -1;
	for (int x = 0; x < MAP_WIDTH; x++) {
		if (mapData[x][0] != TILE_ID_EMPTY) {
			startColumn = x;
			for (int y = 0; y < MAP_HEIGHT; y++) {
				if (mapData[x][y] == TILE_ID_TOP[0] || mapData[x][y] == TILE_ID_TOP[1]) {
					startRow = y;
					break;
				}
			}
			break;
		}
	}

	std::unique_ptr<GameObject> sign = std::make_unique<GameObject>(startColumn * TILE_SIZE + TILE_SIZE / 2, startRow * TILE_SIZE + TILE_SIZE + SIGN_HEIGHT / 2, TILE_SIZE, TILE_SIZE, App::CreateSprite(".\\graphics\\decor\\sign.png", 1, 1));
	newLevel->AddGameObject(std::move(sign));


	// if there is a platform, might generate a platform decor
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (mapData[x][y] == TILE_ID_PLATFORM_LEFT || mapData[x][y] == TILE_ID_PLATFORM_MIDDLE || mapData[x][y] == TILE_ID_PLATFORM_RIGHT) {
				if (GetRandom(5) == 1) {
					std::unique_ptr<GameObject> newDecor = std::make_unique<GameObject>(x * TILE_SIZE + TILE_SIZE / 2, y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE, App::CreateSprite(".\\graphics\\decor\\platform_decor_small.png", 1, 1));
					newLevel->AddGameObject(std::move(newDecor));
				}
				else if (GetRandom(5) == 1) {
					std::unique_ptr<GameObject> newDecor = std::make_unique<GameObject>(x * TILE_SIZE + TILE_SIZE / 2, y * TILE_SIZE, TILE_SIZE, TILE_SIZE * 2, App::CreateSprite(".\\graphics\\decor\\platform_decor_middle.png", 1, 1));
					newLevel->AddGameObject(std::move(newDecor));
				}
				else if (GetRandom(5) == 1) {
					std::unique_ptr<GameObject> newDecor = std::make_unique<GameObject>(x * TILE_SIZE + TILE_SIZE / 2, y * TILE_SIZE - TILE_SIZE / 2, TILE_SIZE, TILE_SIZE * 3, App::CreateSprite(".\\graphics\\decor\\platform_decor_large.png", 1, 1));
					newLevel->AddGameObject(std::move(newDecor));
				}
			}
		}
	}

	// if there is a solid top with 2 tile width, might generate a rock
	for (int x = 1; x < width; x++) {
		if (mapData[x][GROUND_HEIGHT - 1] != TILE_ID_EMPTY && mapData[x - 1][GROUND_HEIGHT - 1] != TILE_ID_EMPTY
			&& mapData[x][GROUND_HEIGHT] == TILE_ID_EMPTY && mapData[x - 1][GROUND_HEIGHT] == TILE_ID_EMPTY)
			{
			if(GetRandom(8) == 1)
			{
				std::unique_ptr<GameObject> newRock = std::make_unique<GameObject>(TILE_SIZE * (x + 1 / 2), TILE_SIZE * (GROUND_HEIGHT + 1), ROCK_WIDTH, ROCK_HEIGHT, App::CreateSprite(".\\graphics\\decor\\rock.png", 1, 1));
				newLevel->AddGameObject(std::move(newRock));
			}
		}
	}

	// if there is a solid top with 4 tile width, might generate a small tree
	for (int x = 3; x < width; x++) {
		if (mapData[x][GROUND_HEIGHT - 1] != TILE_ID_EMPTY && mapData[x - 1][GROUND_HEIGHT - 1] != TILE_ID_EMPTY && mapData[x - 2][GROUND_HEIGHT - 1] != TILE_ID_EMPTY && mapData[x - 3][GROUND_HEIGHT - 1] != TILE_ID_EMPTY
			&& mapData[x][GROUND_HEIGHT] == TILE_ID_EMPTY && mapData[x - 1][GROUND_HEIGHT] == TILE_ID_EMPTY && mapData[x - 2][GROUND_HEIGHT] == TILE_ID_EMPTY && mapData[x - 3][GROUND_HEIGHT] == TILE_ID_EMPTY)
		{
			if (GetRandom(3) == 1)
			{
				std::unique_ptr<GameObject> newTree = std::make_unique<GameObject>(TILE_SIZE * (x - 2 + 1 + 1 / 2), TILE_SIZE * GROUND_HEIGHT + SMALL_TREE_HEIGHT / 2, SMALL_TREE_WIDTH, SMALL_TREE_HEIGHT, App::CreateSprite(".\\graphics\\decor\\small-tree.png", 1, 1));
				newLevel->AddGameObject(std::move(newTree));
			}
		}
	}

	// Add the big tree at the end
	std::unique_ptr<GameObject> newBigTree = std::make_unique<GameObject>(TILE_SIZE * MAP_WIDTH - BIG_TREE_WIDTH / 2, TILE_SIZE * (GROUND_HEIGHT + 1) + BIG_TREE_HEIGHT / 2, BIG_TREE_WIDTH, BIG_TREE_HEIGHT, App::CreateSprite(".\\graphics\\decor\\big-tree.png", 1, 1));
	newLevel->AddGameObject(std::move(newBigTree));

}

std::unique_ptr<GameLevel> LevelMaker::Generate() {
	tileMap = std::make_unique<TileMap>(MAP_WIDTH, MAP_HEIGHT); // Deallocated in GameLevel
	
	mapData = GenerateMapData();
	tileMap->loadMap(mapData);
	newLevel = std::make_unique<GameLevel>(std::move(tileMap));
	GenerateDecors(); // Adding gameObjects to newLevel

	return std::move(newLevel); // Deallocated in PlayState
}