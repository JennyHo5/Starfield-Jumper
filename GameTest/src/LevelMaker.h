#pragma once
#include "tilesystem/TileMap.h"
#include "global/Util.h"
#include "GameLevel.h"

class LevelMaker
{

public:
	LevelMaker();
	std::vector<std::vector<int>> GenerateMapData() const;
	GameLevel* Generate();

private:
	float width;
	float height;
	TileMap* tileMap;
	std::vector<Entity*>* entities;
};

