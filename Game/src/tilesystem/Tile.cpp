#include "stdafx.h"
#include "Tile.h"

Tile::Tile(int t, float x, float y) :
	id(t),
	x(x),
	y(y),
	width(TILE_SIZE),
	height(TILE_SIZE)
{
	sprite = App::CreateSprite(".\\graphics\\stringstar_fields_sheet.png", 18, 11);
	sprite->SetFrame(id); // Set the til's sprite to tileset's id'th frame
}

Tile::~Tile() {
	delete sprite;
}

void Tile::Render() {
	sprite->Draw();
}

bool Tile::IsTop() const {
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
