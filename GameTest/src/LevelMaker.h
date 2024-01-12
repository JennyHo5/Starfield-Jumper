#pragma once
#include "tilesystem/TileMap.h"
#include "global/Util.h"
#include "GameLevel.h"

class LevelMaker
{

public:
	LevelMaker();
	std::vector<std::vector<int>> GenerateMapData() const;
	void GenerateDecors();
	GameLevel* Generate();

private:
	float width;
	float height;
	TileMap* tileMap;
	std::vector<std::vector<int>> mapData;
	std::vector<Entity*>* entities;
	std::vector<GameObject*>* gameObjects;
};

