#include "stdafx.h"
#include "Tile.h"

Tile::Tile(int t, float x, float y) :
	id(t),
	x(x),
	y(y),
	width(TILE_SIZE),
	height(TILE_SIZE)
{
	tileset = App::CreateSprite(".\\graphics\\tileset_og.png", 14, 12);
	tileset->SetFrame(id); // Set the til's sprite to tileset's id'th frame
}

Tile::~Tile() {
	delete tileset;
}

void Tile::Render() {
	tileset->Draw();
}

bool Tile::Collidable() const {
	return (id == TILE_ID_TOP || id == TILE_ID_TOPLEFT || id == TILE_ID_PILLAR_TOP);
}
