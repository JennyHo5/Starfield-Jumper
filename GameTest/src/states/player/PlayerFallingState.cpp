#include "stdafx.h"
#include "PlayerFallingState.h"

PlayerFallingState::PlayerFallingState(Player* player) : player(player) {
}

void PlayerFallingState::Enter() {
	player->SetAnimation(PlayerAnimation::FALLING);
}

void PlayerFallingState::Update(float deltaTime) {
	// Update by gravity
	player->SetDy(player->GetDy() + GRAVITY);
	player->SetY(player->GetY() + player->GetDy() * deltaTime);

	Tile* tileBottomLeft = player->GetGameLevel()->GetTileMap()->PointToTile(player->GetX() - PLAYER_WIDTH / 2, player->GetY() - PLAYER_HEIGHT / 2);
	Tile* tileBottomRight = player->GetGameLevel()->GetTileMap()->PointToTile(player->GetX() + PLAYER_WIDTH / 2, player->GetY() - PLAYER_HEIGHT / 2);

	// If we get a collision or platform beneath us, go into either walking or idle
	if (tileBottomLeft && tileBottomRight 
		&& ((tileBottomLeft->Collidable() || tileBottomRight->Collidable()) ||
			(tileBottomLeft->IsPlatform() || tileBottomRight->IsPlatform())
			)) {
			player->SetDy(0);

			// Set the player to walking or idle
			if (App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed(0x41) || App::IsKeyPressed(VK_RIGHT) || App::IsKeyPressed(0x44))
				player->ChangeState(State::WALKING);
			else player->ChangeState(State::IDLE);

			player->SetY(tileBottomLeft->GetY() + TILE_SIZE / 2 + PLAYER_HEIGHT / 2);

	}
	// Go to game over state if player falls below the boundary
	else if (player->GetY() < 0) {
		player->ChangeState(State::DEAD);
	}
	// Check side colllisions and reset positions
	else if (App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed(0x41)) {
		player->SetX(player->GetX() - PlAYER_WALKING_SPEED * deltaTime);
		player->SetDirection(0);
		player->CheckLeftCollisions();
	}
	else if (App::IsKeyPressed(VK_RIGHT) || App::IsKeyPressed(0x44)) {
		player->SetX(player->GetX() + PlAYER_WALKING_SPEED * deltaTime);
		player->SetDirection(1);
		player->CheckRightCollisions();
	}

	// Check if we've collided with any entities and kill them if so
	for (Entity* e : *player->GetGameLevel()->GetEntities()) {
		if (player->Collides(e) &&
			!dynamic_cast<SlimeDeadState*>(e->GetStateMachine()->GetCurrentState())) {
			printf("Player jumped on and slime is not dead yet\n");
			e->ChangeState(State::SLIME_DEAD);
			player->AddScore(100);
		}
	}
}
