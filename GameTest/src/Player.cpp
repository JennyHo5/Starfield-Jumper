#include "stdafx.h"
#include "Player.h"
#include "global/constants.h"

Player::Player(float x, float y, GameLevel& level):
	Entity(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, 
		App::CreateSprite(".\\graphics\\player.png", 9, 10),
		level)
{
	sprite->CreateAnimation(IDLE_RIGHT, ANIMATION_SPEED, { 0, 1, 2, 3, 4, 5 });
	sprite->CreateAnimation(WALKING_RIGHT, ANIMATION_SPEED, { 9, 10, 11, 12, 13, 14, 15, 16 });
	sprite->CreateAnimation(JUMP_RIGHT, ANIMATION_SPEED * 3, {18, 19, 20});
	sprite->CreateAnimation(FALLING_RIGHT, ANIMATION_SPEED * 3, { 22, 23, 24, 27 });
	sprite->CreateAnimation(DEAD_RIGHT, ANIMATION_SPEED * 2, { 28, 29, 30, 31, 32, 33, 34, 35});
	sprite->CreateAnimation(IDLE_LEFT, ANIMATION_SPEED, { 53, 52, 51, 50, 49, 48 });
	sprite->CreateAnimation(WALKING_LEFT, ANIMATION_SPEED, { 62, 61, 60, 59, 58, 57, 56, 55 });
	sprite->CreateAnimation(JUMP_LEFT, ANIMATION_SPEED * 3, {71, 70, 69});
	sprite->CreateAnimation(FALLING_LEFT, ANIMATION_SPEED * 3, { 67, 66, 65, 80 });
	sprite->CreateAnimation(DEAD_LEFT, ANIMATION_SPEED * 2, {79, 78, 76, 75, 74, 73, 72});
	stateMachine.AddState(State::IDLE, std::make_unique<PlayerIdleState>(this));
	stateMachine.AddState(State::WALKING, std::make_unique<PlayerWalkingState>(this));
	stateMachine.AddState(State::JUMP, std::make_unique<PlayerJumpState>(this));
	stateMachine.AddState(State::FALLING, std::make_unique<PlayerFallingState>(this));
	stateMachine.AddState(State::DEAD, std::make_unique<PlayerDeadState>(this));
	stateMachine.AddState(State::WIN, std::make_unique<PlayerWinState>(this));
	stateMachine.ChangeState(State::FALLING);

	score = 0;
	isWin = false;
}

void Player::SetAnimation(PlayerAnimation anim) {
	sprite->SetAnimation(anim);
}

void Player::SetFrame(int id) {
	sprite->SetFrame(id);
}

void Player::CheckLeftCollisions() {
	// Check if player trying to walk outside of the map width
	if (x <= width / 2)
		x = width / 2;

	// Check for two tiles collision
	Tile* tileTopLeft = level.GetTileMap()->PointToTile(x - width / 2, y + height / 2);
	Tile* tileBottomLeft = level.GetTileMap()->PointToTile(x - width / 2, y - height / 2);

	// Place player outside the x bounds on one of the tiles to reset the overlap
	if (tileTopLeft && tileBottomLeft) {
		if (tileTopLeft->Collidable() || tileBottomLeft->Collidable()) {
			SetX(tileTopLeft->GetX() + TILE_SIZE / 2 + PLAYER_WIDTH / 2);
		}
	}
}

void Player::CheckRightCollisions() {
	// Check if player reachs the right of the map
	if (x >= MAP_WIDTH * (TILE_SIZE - 2)) {
		x = MAP_WIDTH * (TILE_SIZE - 2);
		ChangeState(State::WIN);
	}


	// Check for two tiles collision
	Tile* tileTopRight = level.GetTileMap()->PointToTile(x + width / 2, y + height / 2);
	Tile* tileBottomRight = level.GetTileMap()->PointToTile(x + width / 2, y - height / 2);

	// Place player outside the x bounds on one of the tiles to reset the overlap
	if (tileTopRight && tileBottomRight) {
		if (tileTopRight->Collidable() || tileBottomRight->Collidable()) {
			SetX(tileTopRight->GetX() - TILE_SIZE / 2 - PLAYER_WIDTH / 2);
		}
	}
}

void Player::CheckBottomCollisions() {
	// Check for two tiles collision
	y--; // Temprarliy shift player down one pixel to test if there is collisions at bottom
	Tile* tileBottomLeft = level.GetTileMap()->PointToTile(x - width / 2, y - height / 2);
	Tile* tileBottomRight = level.GetTileMap()->PointToTile(x + width / 2, y - height / 2);
	y++;


	if (tileBottomLeft && tileBottomRight) {
		if (!tileBottomLeft->Collidable() && !tileBottomRight->Collidable()) {
			if (!tileBottomLeft->IsPlatform() && !tileBottomRight->IsPlatform()) {
				SetDy(0);
				ChangeState(State::FALLING);
			}
		}
	}
}

void Player::CheckUpCollisions() {
	// Check if player reachs the top of the map
	if (y >= MAP_HEIGHT * TILE_SIZE - PLAYER_HEIGHT / 2) {
		y = MAP_HEIGHT * TILE_SIZE - PLAYER_HEIGHT / 2;
	}

}
