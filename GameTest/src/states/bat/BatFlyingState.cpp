#include "stdafx.h"
#include "BatFlyingState.h"

BatFlyingState::BatFlyingState(const TileMap* tm, Player* p, Bat* e) :
	map(tm), player(p), bat(e), movingDirection(0)
{
	if (GetRandom(2) == 1) {
		movingDirection = 1;
	}

	bat->SetDirection(movingDirection);
	movingDuration = GetRandom(BAT_MOVING_DURATION);
	movingTimer = 0;
}

void BatFlyingState::Update(float deltaTime) {
	movingTimer += deltaTime;
	// Reset movement direction and timer if timer is above duration
	if (movingTimer > movingDuration) {
		if (GetRandom(2) == 1) {
			movingDirection = 0;
		}
		else
			movingDirection = 1;

		bat->SetDirection(movingDirection);
		movingDuration = GetRandom(BAT_MOVING_DURATION);
		movingTimer = 0;
	}
	else if (bat->GetDirection() == 0) {
		bat->GetSprite()->SetAnimation(FLYING_LEFT);
		float speed = GetRandom(2) * BAT_FLYING_SPEED;
		bat->SetX(bat->GetX() - speed * deltaTime);

		// stop if there's a solid tile directly left
		Tile* tileLeft = map->PointToTile(bat->GetX() - BAT_WIDTH / 2, bat->GetY());

		if (tileLeft && tileLeft->Collidable()) {
			bat->SetX(bat->GetX() + speed * deltaTime);
			//Reset direction
			movingDirection = 1;
			bat->SetDirection(movingDirection);
			movingDuration = GetRandom(BAT_MOVING_DURATION);
			movingTimer = 0;
		}

	}
	else {
		bat->GetSprite()->SetAnimation(FLYING_RIGHT);
		float speed = GetRandom(2) * BAT_FLYING_SPEED;
		bat->SetX(bat->GetX() + speed * deltaTime);

		// stop if there's a solid tile directly right
		Tile* tileRight = map->PointToTile(bat->GetX() + BAT_WIDTH / 2, bat->GetY());

		if (tileRight && tileRight->Collidable()) {
			bat->SetX(bat->GetX() - speed * deltaTime);
			//Reset direction
			movingDirection = 0;
			bat->SetDirection(movingDirection);
			movingDuration = GetRandom(BAT_MOVING_DURATION);
			movingTimer = 0;
		}
	}
}