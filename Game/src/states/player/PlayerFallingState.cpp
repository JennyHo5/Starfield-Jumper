#include "stdafx.h"
#include "PlayerFallingState.h"

PlayerFallingState::PlayerFallingState(Player* player) : player(player) {
}

void PlayerFallingState::Enter() {
}

void PlayerFallingState::Update(float deltaTime) {
	if (player->GetDirection() == 0)
		player->SetAnimation(PlayerAnimation::FALLING_LEFT);
	else
		player->SetAnimation(PlayerAnimation::FALLING_RIGHT);

	// Update by gravity
	player->SetDy(player->GetDy() + GRAVITY);
	player->SetY(player->GetY() + player->GetDy() * deltaTime);

	const Tile* tileBottomLeft = player->GetGameLevel()->GetTileMap()->PointToTile(player->GetX() - PLAYER_WIDTH / 2, player->GetY() - PLAYER_HEIGHT / 2);
	const Tile* tileBottomRight = player->GetGameLevel()->GetTileMap()->PointToTile(player->GetX() + PLAYER_WIDTH / 2, player->GetY() - PLAYER_HEIGHT / 2);

	// If we get a collision or platform beneath us, go into either walking or idle
	if (tileBottomLeft && tileBottomRight 
		&& ((tileBottomLeft->IsTop() || tileBottomRight->IsTop()) ||
			(tileBottomLeft->IsPlatform() || tileBottomRight->IsPlatform())
			)) {
			player->SetDy(0);

			// Set the player to walking or idle
			if (App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed(0x41) || App::IsKeyPressed(VK_RIGHT) || App::IsKeyPressed(0x44))
				player->ChangeState(State::WALKING);
			else 
			{
				App::PlaySoundW(".\\sounds\\stepdirt_1.wav");
				player->ChangeState(State::IDLE);
			}
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
}
