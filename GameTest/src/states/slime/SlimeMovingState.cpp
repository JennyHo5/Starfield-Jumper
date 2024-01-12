#include "stdafx.h"
#include "SlimeMovingState.h"

SlimeMovingState::SlimeMovingState(TileMap* tm, Player* p, Slime* o):
	map(tm), player(p), slime(o), movingDirection(0)
{
	if (GetRandom(2) == 1) {
		movingDirection = 1;
	}

	slime->SetDirection(movingDirection);
	movingDuration = GetRandom(SLIME_MOVING_DURATION);
	movingTimer = 0;
}

void SlimeMovingState::Enter() {
	slime->GetSprite()->SetAnimation(SLIME_MOVING);
}

void SlimeMovingState::Update(float deltaTime) {
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
	else if (slime->GetDirection() == 0) {
		slime->SetX(slime->GetX() - SLIME_RUNNING_SPEED * deltaTime);

		// stop if there's a missing tile on the floor to the left or a solid tile directly left
		Tile* tileLeft = map->PointToTile(slime->GetX() - SLIME_WIDTH / 2, slime->GetY());
		Tile* tileBottomLeft = map->PointToTile(slime->GetX() - SLIME_WIDTH / 2, slime->GetY() - SLIME_WIDTH / 2);

		if (tileLeft == nullptr || tileBottomLeft == nullptr ||
			(tileLeft && tileBottomLeft && (tileLeft->Collidable() || !tileBottomLeft->Collidable()))) {
			slime->SetX(slime->GetX() + SLIME_RUNNING_SPEED * deltaTime);
			//Reset direction
			movingDirection = 1;
			slime->SetDirection(movingDirection);
			movingDuration = GetRandom(SLIME_MOVING_DURATION);
			movingTimer = 0;
		}

	}
	else {
		slime->SetX(slime->GetX() + SLIME_RUNNING_SPEED * deltaTime);

		// stop if there's a missing tile on the floor to the left or a solid tile directly left
		Tile* tileRight = map->PointToTile(slime->GetX() + SLIME_WIDTH / 2, slime->GetY());
		Tile* tileBottomRight = map->PointToTile(slime->GetX() + SLIME_WIDTH / 2, slime->GetY() - SLIME_WIDTH / 2);
		
		if (tileRight == nullptr || tileBottomRight == nullptr ||
			(tileRight && tileBottomRight && (tileRight->Collidable() || !tileBottomRight->Collidable()))) {
			slime->SetX(slime->GetX() - SLIME_RUNNING_SPEED * deltaTime);
			//Reset direction
			movingDirection = 0;
			slime->SetDirection(movingDirection);
			movingDuration = GetRandom(SLIME_MOVING_DURATION);
			movingTimer = 0;
		}
	}

	// Calculate difference between slime and player on X axis, only chase if <= 5 tiles
	int diff = std::abs(player->GetX() - slime->GetX());

	if (diff < TILE_SIZE * 5) {
		slime->ChangeState(State::SLIME_CHASING);
	}

}