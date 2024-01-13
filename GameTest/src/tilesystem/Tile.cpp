#include "stdafx.h"
#include "Tile.h"

Tile::Tile(int t, float x, float y) :
	id(t),
	x(x),
	y(y),
	width(TILE_SIZE),
	height(TILE_SIZE)
{
	tileset = App::CreateSprite(".\\graphics\\stringstar_fields_sheet.png", 18, 11);
	tileset->SetFrame(id); // Set the til's sprite to tileset's id'th frame
}

Tile::~Tile() {
	delete tileset;
}

void Tile::Render() {
	tileset->Draw();
}

bool Tile::Collidable() const {
	for (size_t i = 0; i < COLLIDABLE_SIZE; ++i) {
		if (id == COLLIDABLE[i]) {
			return true;
		}
	}
	return false;
}

bool Tile::IsPlatform() const {
	for (size_t i = 0; i < PLATFORMS_SIZE; ++i) {
		if (id == PLATFORMS[i]) {
			return true;
		}
	}
	return false;
}
