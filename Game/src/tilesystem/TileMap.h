#pragma once
#include "Tile.h"
#include <vector>

// Represents the layout of the game world
class TileMap {
public:
    TileMap(int width, int height);
    ~TileMap();

    // Load from bit reference to tiles 2D array
    void loadMap(const std::vector<std::vector<int>>& mapData);
    void Render();

    const std::vector<std::vector<Tile*>>* GetTiles() const { return &tiles; }

    const Tile* PointToTile(float x, float y) const;

private:
    int width;
    int height;
    std::vector<std::vector<Tile*>> tiles; // 2D vector to store the tile pointers
};

