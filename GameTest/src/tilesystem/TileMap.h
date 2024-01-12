#pragma once
#include "Tile.h"
#include <vector>

class TileMap {
public:
    TileMap(int width, int height);
    ~TileMap();

    // Load from bit reference to tiles 2D array
    void loadMap(const std::vector<std::vector<int>>& mapData);
    void Render();

    std::vector<std::vector<Tile*>>* GetTiles() { return &tiles; }

    Tile* PointToTile(float x, float y);

private:
    int width;
    int height;
    std::vector<std::vector<Tile*>> tiles; // 2D vector to store the tile pointers
};

