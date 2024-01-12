#include "stdafx.h"
#include "PlayerIdleState.h"

PlayerIdleState::PlayerIdleState(Player* player) : player(player) {
}

void PlayerIdleState::Enter() {
	player->SetAnimation(PlayerAnimation::IDLE);
}

void PlayerIdleState::Update(float deltaTime) {

	player->CheckBottomCollisions();

	if (App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed(VK_RIGHT) || App::IsKeyPressed(0x41) || App::IsKeyPressed(0x44)) {
		player->ChangeState(State::WALKING);
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