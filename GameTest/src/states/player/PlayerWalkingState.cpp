#include "stdafx.h"
#include "PlayerWalkingState.h"

PlayerWalkingState::PlayerWalkingState(Player* player) : player(player) {
}

void PlayerWalkingState::Enter() {
	player->SetAnimation(PlayerAnimation::WALKING);
	App::PlaySoundW(".\\sounds\\stepdirt.wav", true);
}

void PlayerWalkingState::Update(float deltaTime) {


	if (!(App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed(VK_RIGHT) || App::IsKeyPressed(0x41) || App::IsKeyPressed(0x44))) {
		player->ChangeState(State::IDLE);
	}
	else {
		player->CheckBottomCollisions();

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
	}

	if (App::IsKeyPressed(VK_SPACE)) {
		player->ChangeState(State::JUMP);
	}

	// Check if collide with enemies
	for (Entity* e : *player->GetGameLevel()->GetEntities()) {
		if (player->Collides(e) &&
			!dynamic_cast<SlimeDeadState*>(e->GetStateMachine()->GetCurrentState())) {
			printf("Enemy collides with Player and slime is not dead yet\n");
			player->ChangeState(State::DEAD);
			break;
		}
	}
}

void PlayerWalkingState::Exit() {
	App::StopSound(".\\sounds\\stepdirt.wav");
}
