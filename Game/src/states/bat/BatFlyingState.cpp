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
	HandleCollision();

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
		const Tile* tileLeft = map->PointToTile(bat->GetX() - BAT_WIDTH / 2, bat->GetY());

		if (tileLeft && tileLeft->IsTop()) {
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
		const Tile* tileRight = map->PointToTile(bat->GetX() + BAT_WIDTH / 2, bat->GetY());

		if (tileRight && tileRight->IsTop()) {
			bat->SetX(bat->GetX() - speed * deltaTime);
			//Reset direction
			movingDirection = 0;
			bat->SetDirection(movingDirection);
			movingDuration = GetRandom(BAT_MOVING_DURATION);
			movingTimer = 0;
		}
	}
}

void BatFlyingState::HandleCollision() {
	// If bat collides with player
	if (bat->Collides(player)) {
		// If player is falling on bat, set slime to dead
		if (player->GetStateMachine()->GetCurrentState()->GetType() == State::FALLING)
		{
			bat->ChangeState(State::BAT_DEAD);
			player->AddScore(200);
		}
		// Else set player to dead
		else
			player->ChangeState(State::DEAD);
	}
}