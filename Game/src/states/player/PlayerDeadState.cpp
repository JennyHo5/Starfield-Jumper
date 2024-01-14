#include "stdafx.h"
#include "PlayerDeadState.h"

PlayerDeadState::PlayerDeadState(Player* player) : player(player) {
}

void PlayerDeadState::Enter() {
	if (player->GetDirection() == 0)
	player->SetAnimation(PlayerAnimation::DEAD_LEFT);
	else
		player->SetAnimation(PlayerAnimation::DEAD_RIGHT);
	player->SetDead();
}

void PlayerDeadState::Update(float deltaTime) {
	if (App::IsKeyPressed(0x52))
		Game::GetInstance()->ChangeState(State::START);
}
