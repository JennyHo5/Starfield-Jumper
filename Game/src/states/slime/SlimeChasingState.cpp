#include "stdafx.h"
#include "SlimeChasingState.h"

SlimeChasingState::SlimeChasingState(const TileMap* tm, Player* p, Slime* o) :
	map(tm), player(p), slime(o)
{
}

void SlimeChasingState::Update(float deltaTime) {
	HandleCollision();

	if (slime->GetDirection() == 0)
		slime->GetSprite()->SetAnimation(SLIME_CHASING_LEFT);
	else
		slime->GetSprite()->SetAnimation(SLIME_CHASING_RIGHT);

	// Calculate difference between slime and player on X axis, only chase if <= 5 tiles
	float diff = std::abs(player->GetX() - slime->GetX());

	if (diff >= TILE_SIZE * 5) {
		slime->ChangeState(State::SLIME_MOVING);
	}
	// If slime is at the right of the player
	else if (player->GetX() < slime->GetX()) {
		slime->SetDirection(0);
		slime->SetX(slime->GetX() - SLIME_RUNNING_SPEED * deltaTime);

		// Stop the slime is there is a missing tile on the floor to the left or a solid tile directly left
		Tile* tileLeft = map->PointToTile(slime->GetX() - SLIME_WIDTH / 2, slime->GetY());
		Tile* tileBottomLeft = map->PointToTile(slime->GetX() - SLIME_WIDTH / 2, slime->GetY() - SLIME_WIDTH / 2);
		Tile* tileBottom = map->PointToTile(slime->GetX(), slime->GetY() - TILE_SIZE);
		
		if (tileBottom && !tileBottom->IsPlatform()) {
			if (!tileLeft || !tileBottomLeft ||
				(tileLeft && tileBottomLeft
					&& (tileLeft->IsTop() || !tileBottomLeft->IsTop()))) {
				slime->SetX(slime->GetX() + SLIME_RUNNING_SPEED * deltaTime);
			}

		}
		else {
			// Slime is on the platform
			if (!tileLeft || !tileBottomLeft ||
				!tileBottomLeft->IsPlatform())
			{
				slime->SetX(slime->GetX() + SLIME_RUNNING_SPEED * deltaTime);
			}
		}
	}
	// If slime is at the left of the player
	else {
		slime->SetDirection(1);
		slime->SetX(slime->GetX() + SLIME_RUNNING_SPEED * deltaTime);

		// stop if there's a missing tile on the floor to the right or a solid tile directly right
		Tile* tileRight = map->PointToTile(slime->GetX() + SLIME_WIDTH / 2, slime->GetY());
		Tile* tileBottomRight = map->PointToTile(slime->GetX() + SLIME_WIDTH / 2, slime->GetY() - SLIME_WIDTH / 2);
		Tile* tileBottom = map->PointToTile(slime->GetX(), slime->GetY() - TILE_SIZE);
		
		if (tileBottom && !tileBottom->IsPlatform()) {
			if (!tileRight || !tileBottomRight ||
				(tileRight && tileBottomRight && (tileRight->IsTop() || !tileBottomRight->IsTop()))) {
				slime->SetX(slime->GetX() - SLIME_RUNNING_SPEED * deltaTime);
			}
		}
		else {
			// Slime is on the platform
			if (!tileRight || !tileBottomRight ||
				!tileBottomRight->IsPlatform())
			{
				slime->SetX(slime->GetX() - SLIME_RUNNING_SPEED * deltaTime);
			}
		}
	}
}

void SlimeChasingState::HandleCollision() {
	// If slime collides with player
	if (slime->Collides(player)) {
		// If player is falling on slime, set slime to dead
		if (dynamic_cast<PlayerFallingState*>(player->GetStateMachine()->GetCurrentState()))
		{
			slime->ChangeState(State::SLIME_DEAD);
			player->AddScore(100);
		}
		// Else, set player to dead
		else if (!dynamic_cast<PlayerJumpState*>(player->GetStateMachine()->GetCurrentState()))
			player->ChangeState(State::DEAD);
	}
}
