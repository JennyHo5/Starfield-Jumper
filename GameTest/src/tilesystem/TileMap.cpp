#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(int width, int height) : width(width), height(height) {
    tiles.resize(width, std::vector<Tile*>(height, new Tile(0, 0, 0))); // Initialize the 2D vector with default tiles
}

TileMap::~TileMap() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            delete tiles[i][j];
        }
    }
}

void TileMap::loadMap(const std::vector<std::vector<int>>& mapData) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tiles[j][i] = new Tile(mapData[j][i], j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2);
        }
    }
}

void TileMap::Render() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tiles[j][i]->Render();
        }
    }
}

Tile* TileMap::PointToTile(float x, float y) {
    if (x < 0 || x >(width - 1) * TILE_SIZE || y < 0 || y > (height - 1) * TILE_SIZE)
        return nullptr;
    return tiles[floor(x / TILE_SIZE)][floor(y / TILE_SIZE)];
}