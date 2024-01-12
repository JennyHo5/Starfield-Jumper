#include "stdafx.h"
#include "EagleFlyingState.h"

EagleFlyingState::EagleFlyingState(TileMap* tm, Player* p, Eagle* e) :
	map(tm), player(p), eagle(e), movingDirection(0)
{
	if (GetRandom(2) == 1) {
		movingDirection = 1;
	}

	eagle->SetDirection(movingDirection);
	movingDuration = GetRandom(EAGLE_MOVING_DURATION);
	movingTimer = 0;
}

void EagleFlyingState::Update(float deltaTime) {
	movingTimer += deltaTime;
	// Reset movement direction and timer if timer is above duration
	if (movingTimer > movingDuration) {
		if (GetRandom(2) == 1) {
			movingDirection = 0;
		}
		else
			movingDirection = 1;

		eagle->SetDirection(movingDirection);
		movingDuration = GetRandom(EAGLE_MOVING_DURATION);
		movingTimer = 0;
	}
	else if (eagle->GetDirection() == 0) {
		eagle->GetSprite()->SetAnimation(FLYING_LEFT);
		eagle->SetX(eagle->GetX() - EAGLE_FLYING_SPEED * deltaTime);

		// stop if there's a solid tile directly left
		Tile* tileLeft = map->PointToTile(eagle->GetX() - EAGLE_WIDTH / 2, eagle->GetY());

		if (tileLeft && tileLeft->Collidable()) {
			eagle->SetX(eagle->GetX() + EAGLE_FLYING_SPEED * deltaTime);
			//Reset direction
			movingDirection = 1;
			eagle->SetDirection(movingDirection);
			movingDuration = GetRandom(EAGLE_MOVING_DURATION);
			movingTimer = 0;
		}

	}
	else {
		eagle->GetSprite()->SetAnimation(FLYING_RIGHT);
		eagle->SetX(eagle->GetX() + EAGLE_FLYING_SPEED * deltaTime);

		// stop if there's a solid tile directly right
		Tile* tileRight = map->PointToTile(eagle->GetX() + EAGLE_WIDTH / 2, eagle->GetY());

		if (tileRight && tileRight->Collidable()) {
			eagle->SetX(eagle->GetX() - EAGLE_FLYING_SPEED * deltaTime);
			//Reset direction
			movingDirection = 0;
			eagle->SetDirection(movingDirection);
			movingDuration = GetRandom(EAGLE_MOVING_DURATION);
			movingTimer = 0;
		}
	}
}