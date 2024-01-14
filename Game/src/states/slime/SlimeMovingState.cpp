#include "stdafx.h"
#include "SlimeMovingState.h"

SlimeMovingState::SlimeMovingState(const TileMap* tm, Player* p, Slime* o):
	map(tm), player(p), slime(o), movingDirection(0)
{
	if (GetRandom(2) == 1) {
		movingDirection = 1;
	}

	slime->SetDirection(movingDirection);
	movingDuration = GetRandom(SLIME_MOVING_DURATION);
	movingTimer = 0;
}


void SlimeMovingState::Update(float deltaTime) {
	HandleCollision();

	movingTimer += deltaTime;
	// Reset movement direction and timer if timer is above duration
	if (movingTimer > movingDuration) {
		if (GetRandom(2) == 1) {
			movingDirection = 0;
		}
		else
			movingDirection = 1;

		slime->SetDirection(movingDirection);
		movingDuration = GetRandom(SLIME_MOVING_DURATION);
		movingTimer = 0;
	}
	// Slime is moving left
	else if (slime->GetDirection() == 0) {
		slime->GetSprite()->SetAnimation(SLIME_MOVING_LEFT);
		slime->SetX(slime->GetX() - SLIME_RUNNING_SPEED * deltaTime);

		// stop if there's a missing tile on the floor to the left or a solid tile directly left
		const Tile* tileLeft = map->PointToTile(slime->GetX() - SLIME_WIDTH / 2, slime->GetY());
		const Tile* tileBottomLeft = map->PointToTile(slime->GetX() - SLIME_WIDTH / 2, slime->GetY() - SLIME_WIDTH / 2);
		const Tile* tileBottom = map->PointToTile(slime->GetX(), slime->GetY() - TILE_SIZE);

		if (tileBottom && !tileBottom->IsPlatform()) {
			// Slime is on the ground
			if (!tileLeft || !tileBottomLeft ||
				(tileLeft && tileBottomLeft
					&& (tileLeft->IsTop() || !tileBottomLeft->IsTop()))) {
				slime->SetX(slime->GetX() + SLIME_RUNNING_SPEED * deltaTime);
				//Reset direction
				movingDirection = 1;
				slime->SetDirection(movingDirection);
				movingDuration = GetRandom(SLIME_MOVING_DURATION);
				movingTimer = 0;
			}
		}
		else if (tileBottom && tileBottom->IsPlatform()) {
			// Slime is on the platform
			if (!tileLeft || !tileBottomLeft ||
				!tileBottomLeft->IsPlatform())
			{
				slime->SetX(slime->GetX() + SLIME_RUNNING_SPEED * deltaTime);
				//Reset direction
				movingDirection = 1;
				slime->SetDirection(movingDirection);
				movingDuration = GetRandom(SLIME_MOVING_DURATION);
				movingTimer = 0;
			}
		}

	}
	// Slime is moving right
	else {
		slime->SetX(slime->GetX() + SLIME_RUNNING_SPEED * deltaTime);
		slime->GetSprite()->SetAnimation(SLIME_MOVING_RIGHT);

		// stop if there's a missing tile on the floor to the left or a solid tile directly left
		const Tile* tileRight = map->PointToTile(slime->GetX() + SLIME_WIDTH / 2, slime->GetY());
		const Tile* tileBottomRight = map->PointToTile(slime->GetX() + SLIME_WIDTH / 2, slime->GetY() - SLIME_WIDTH / 2);
		const Tile* tileBottom = map->PointToTile(slime->GetX(), slime->GetY() - TILE_SIZE);

		if (tileBottom && !tileBottom->IsPlatform()) {
			// Slime is on the ground
			if (!tileRight || !tileBottomRight ||
				(tileRight && tileBottomRight && (tileRight->IsTop() || !tileBottomRight->IsTop()))) {
				slime->SetX(slime->GetX() - SLIME_RUNNING_SPEED * deltaTime);
				//Reset direction
				movingDirection = 0;
				slime->SetDirection(movingDirection);
				movingDuration = GetRandom(SLIME_MOVING_DURATION);
				movingTimer = 0;
			}
		}
		// Slime is on the platform
		else if (tileBottom && tileBottom->IsPlatform()) {
			if (!tileRight || !tileBottomRight ||
				!tileBottomRight->IsPlatform())
			{
				slime->SetX(slime->GetX() - SLIME_RUNNING_SPEED * deltaTime);
				//Reset direction
				movingDirection = 0;
				slime->SetDirection(movingDirection);
				movingDuration = GetRandom(SLIME_MOVING_DURATION);
				movingTimer = 0;
			}
		}
	}

	// Calculate difference between slime and player on X axis, only chase if <= 5 tiles
	float diff = std::abs(player->GetX() - slime->GetX());

	if (diff <= TILE_SIZE * 5) {
		slime->ChangeState(State::SLIME_CHASING);
	}

}

void SlimeMovingState::HandleCollision() {
	// If slime collides with player
	if (slime->Collides(player)) {
		// If player is falling on slime, set slime to dead
		if (player->GetStateMachine()->GetCurrentState()->GetType() == State::FALLING)
		{
			slime->ChangeState(State::SLIME_DEAD);
			player->AddScore(100);
		}
		// Else if player is not in jump state, set player to dead
		else if (player->GetStateMachine()->GetCurrentState()->GetType() != State::JUMP)
			player->ChangeState(State::DEAD);
		// If player is in jump state, player should still be alive even if their boxes collide with each other
	}

}