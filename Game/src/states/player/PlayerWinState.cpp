#include "stdafx.h"
#include "PlayerWinState.h"

PlayerWinState::PlayerWinState(Player* player) : player(player) {
}

void PlayerWinState::Enter() {
	if (player->GetDirection() == 0)
		player->SetAnimation(PlayerAnimation::IDLE_LEFT);
	else
		player->SetAnimation(PlayerAnimation::IDLE_RIGHT);
	player->SetWin();
}

void PlayerWinState::Update(float deltaTime) {
	if (App::IsKeyPressed(0x52))
		Game::GetStateMachine()->ChangeState(State::START);
}
