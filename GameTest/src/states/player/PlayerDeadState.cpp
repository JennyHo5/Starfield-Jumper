#include "stdafx.h"
#include "PlayerDeadState.h"

PlayerDeadState::PlayerDeadState(Player* player) : player(player) {
}

void PlayerDeadState::Enter() {
	player->SetAnimation(PlayerAnimation::DEAD);
	player->SetDead();
}

void PlayerDeadState::Update(float deltaTime) {
	if (App::IsKeyPressed(0x52))
		GameStateMachine::GetInstance()->ChangeState(State::START);
}
