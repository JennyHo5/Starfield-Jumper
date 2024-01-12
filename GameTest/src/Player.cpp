#include "stdafx.h"
#include "Player.h"
#include "global/constants.h"

Player::Player(float x, float y, GameLevel& level):
	isDead(false),
	Entity(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, 
		App::CreateSprite(".\\graphics\\char_blue.png", 8, 7),
		StateMachine(), level)
{
	sprite->CreateAnimation(IDLE, ANIMATION_SPEED, { 0, 1, 2, 3, 4, 5 });
	sprite->CreateAnimation(WALKING, ANIMATION_SPEED, { 16, 17, 18, 19, 20, 21, 22, 23 });
	sprite->CreateAnimation(JUMP, ANIMATION_SPEED * 3, {24, 25, 26, 27, 28, 29, 30, 31});
	sprite->CreateAnimation(FALLING, ANIMATION_SPEED * 3, { 32, 33, 34, 35, 36, 37, 38, 39 });
	sprite->CreateAnimation(ATTACK, ANIMATION_SPEED, { 8, 9, 10, 11, 12, 13});
	sprite->CreateAnimation(DEAD, ANIMATION_SPEED, { 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51});
	stateMachine.AddState(State::IDLE, new PlayerIdleState(this));
	stateMachine.AddState(State::WALKING, new PlayerWalkingState(this));
	stateMachine.AddState(State::JUMP, new PlayerJumpState(this));
	stateMachine.AddState(State::FALLING, new PlayerFallingState(this));
	stateMachine.AddState(State::ATTACK, new PlayerAttackState(this));
	stateMachine.AddState(State::DEAD, new PlayerDeadState(this));
	stateMachine.ChangeState(State::FALLING);
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
	if (x >= MAP_WIDTH * (TILE_SIZE - 1) - width / 2) {
		x = MAP_WIDTH * (TILE_SIZE - 1) - width / 2;
		StateMachineManager::GetInstance()->ChangeState(State::START);
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
			SetDy(0);
			ChangeState(State::FALLING);
		}
	}
}

bool Player::InAttackRate(Entity* entity) const {
	return !(x - width > entity->GetX() + entity->GetWidth() / 2 || entity->GetX() - entity->GetWidth() / 2 > x + width ||
		y - height / 2 > entity->GetY() + entity->GetHeight() / 2 || entity->GetY() - entity->GetHeight() / 2 > y + height / 2);

}

