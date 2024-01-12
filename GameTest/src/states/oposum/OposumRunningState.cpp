#include "stdafx.h"
#include "OposumRunningState.h"

OposumRunningState::OposumRunningState(TileMap* tm, Player* p, Oposum* o):
	map(tm), player(p), oposum(o), movingDirection(0)
{
	if (GetRandom(2) == 1) {
		movingDirection = 1;
	}

	oposum->SetDirection(movingDirection);
	movingDuration = GetRandom(OPOSUM_MOVING_DURATION);
	movingTimer = 0;
}

void OposumRunningState::Update(float deltaTime) {
	movingTimer += deltaTime;
	// Reset movement direction and timer if timer is above duration
	if (movingTimer > movingDuration) {
		if (GetRandom(2) == 1) {
			movingDirection = 0;
		}
		else
			movingDirection = 1;

		oposum->SetDirection(movingDirection);
		movingDuration = GetRandom(OPOSUM_MOVING_DURATION);
		movingTimer = 0;
	}
	else if (oposum->GetDirection() == 0) {
		oposum->GetSprite()->SetAnimation(RUNNING_LEFT);
		oposum->SetX(oposum->GetX() - OPOSUM_RUNNING_SPEED * deltaTime);

		// stop if there's a missing tile on the floor to the left or a solid tile directly left
		Tile* tileLeft = map->PointToTile(oposum->GetX() - OPOSUM_WIDTH / 2, oposum->GetY());
		Tile* tileBottomLeft = map->PointToTile(oposum->GetX() - OPOSUM_WIDTH / 2, oposum->GetY() - OPOSUM_WIDTH / 2);

		if (tileLeft == nullptr || tileBottomLeft == nullptr ||
			(tileLeft && tileBottomLeft && (tileLeft->Collidable() || !tileBottomLeft->Collidable()))) {
			oposum->SetX(oposum->GetX() + OPOSUM_RUNNING_SPEED * deltaTime);
			//Reset direction
			movingDirection = 1;
			oposum->SetDirection(movingDirection);
			movingDuration = GetRandom(OPOSUM_MOVING_DURATION);
			movingTimer = 0;
		}

	}
	else {
		oposum->GetSprite()->SetAnimation(RUNNING_RIGHT);
		oposum->SetX(oposum->GetX() + OPOSUM_RUNNING_SPEED * deltaTime);

		// stop if there's a missing tile on the floor to the left or a solid tile directly left
		Tile* tileRight = map->PointToTile(oposum->GetX() + OPOSUM_WIDTH / 2, oposum->GetY());
		Tile* tileBottomRight = map->PointToTile(oposum->GetX() + OPOSUM_WIDTH / 2, oposum->GetY() - OPOSUM_WIDTH / 2);
		
		if (tileRight == nullptr || tileBottomRight == nullptr ||
			(tileRight && tileBottomRight && (tileRight->Collidable() || !tileBottomRight->Collidable()))) {
			oposum->SetX(oposum->GetX() - OPOSUM_RUNNING_SPEED * deltaTime);
			//Reset direction
			movingDirection = 0;
			oposum->SetDirection(movingDirection);
			movingDuration = GetRandom(OPOSUM_MOVING_DURATION);
			movingTimer = 0;
		}
	}
}