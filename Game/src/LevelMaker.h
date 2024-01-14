#pragma once
#include "tilesystem/TileMap.h"
#include "global/Util.h"
#include "GameLevel.h"

class LevelMaker
{

public:
	LevelMaker();
	//  Generating MapData using algorithms that loop through the whole map and generate different tile's ID at the 2D vector randomly.
	std::vector<std::vector<int>> GenerateMapData() const;
	
	// Adding decorations (rock, grass, tree, etc) as Game Objects using algorithms that loop through the whole map and add them to different locations randomly.
	void GenerateDecors();
	
	// Based on the return values of GenerateData and GenerateDecor during runtime, generate a new Game Level and return it.
	std::unique_ptr<GameLevel> Generate();

private:
	float width;
	float height;
	std::unique_ptr<TileMap> tileMap;
	std::vector<std::vector<int>> mapData; // A 2D vector including ID representation of the tilemap.
	std::unique_ptr<GameLevel> newLevel;
};

