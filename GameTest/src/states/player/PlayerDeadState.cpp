#include "stdafx.h"
#include "PlayerDeadState.h"

PlayerDeadState::PlayerDeadState(Player* player) : player(player), animTimer(0) {
}

void PlayerDeadState::Enter() {
	animTimer = 0;
	player->SetAnimation(PlayerAnimation::DEAD);
	player->SetDead();
}

void PlayerDeadState::Update(float deltaTime) {
	// For the dead animation
	animTimer += 1;
	if (animTimer >= 12 * UPDATE_CALLS_PER_FRAME) {
		player->GetSprite()->SetAnimation(-1);
		player->GetSprite()->SetFrame(35);
	}
	if (App::IsKeyPressed(0x52))
		StateMachineManager::GetInstance()->ChangeState(State::START);
}
