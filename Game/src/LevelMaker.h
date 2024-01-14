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
	std::unique_ptr<GameLevel> Generate();

private:
	float width;
	float height;
	std::unique_ptr<TileMap> tileMap;
	std::vector<std::vector<int>> mapData;
	std::unique_ptr<GameLevel> newLevel;
};

