#include "stdafx.h"
#include "PlayerWalkingState.h"

PlayerWalkingState::PlayerWalkingState(Player* player) : player(player) {
}

void PlayerWalkingState::Enter() {
	player->SetAnimation(PlayerAnimation::WALKING);
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
		if (e->Collides(player)) {
			printf("Enemy collides with Player\n");
			player->ChangeState(State::DEAD);
			break;
		}
	}

}
