#include "stdafx.h"
#include "PlayerWalkingState.h"

PlayerWalkingState::PlayerWalkingState(Player* player) : player(player) {
}

void PlayerWalkingState::Enter() {
	App::PlaySoundW(".\\sounds\\stepdirt.wav", true);
}

void PlayerWalkingState::Update(float deltaTime) {
	if (player->GetDirection() == 0)
		player->SetAnimation(PlayerAnimation::WALKING_LEFT);
	else
		player->SetAnimation(PlayerAnimation::WALKING_RIGHT);


	if (!(App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed(VK_RIGHT) || App::IsKeyPressed(0x41) || App::IsKeyPressed(0x44))) {
		player->ChangeState(State::IDLE);
	}
	else {
		player->CheckBottomCollisions();

		if (App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed(0x41)) {
			printf("player walking left\n");
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

	if (App::IsKeyPressed(VK_SPACE)) {
		player->ChangeState(State::JUMP);
	}
}

void PlayerWalkingState::Exit() {
	App::StopSound(".\\sounds\\stepdirt.wav");
}
