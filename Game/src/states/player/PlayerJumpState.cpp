#include "stdafx.h"
#include "PlayerJumpState.h"

PlayerJumpState::PlayerJumpState(Player* p) : player(p) {
}

void PlayerJumpState::Enter() {
	player->SetDy(PLAYER_JUMP_VELOCITY);
	App::PlaySoundW(".\\sounds\\jumpland.wav");
}

void PlayerJumpState::Update(float deltaTime) {
	if (player->GetDirection() == 0)
		player->SetAnimation(PlayerAnimation::JUMP_LEFT);
	else
		player->SetAnimation(PlayerAnimation::JUMP_RIGHT);


	player->SetDy(player->GetDy() + GRAVITY);
	player->SetY(player->GetY() + player->GetDy() * deltaTime);

	// Go into the falling state when y velocity is positive
	if (player->GetDy() <= 0) {
		player->ChangeState(State::FALLING);
	}
	player->SetY(player->GetY() + player->GetDy() * deltaTime);
	
	if (App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed(0x41)) {
		player->SetX(player->GetX() - PlAYER_WALKING_SPEED * deltaTime);
		player->SetDirection(0);
		player->CheckLeftCollisions();
	}
	else if (App::IsKeyPressed(VK_RIGHT) || App::IsKeyPressed(0x44)) {
		player->SetX(player->GetX() + PlAYER_WALKING_SPEED * deltaTime);
		player->SetDirection(1);
		player->CheckRightCollisions();
	}

	player->CheckUpCollisions();
}