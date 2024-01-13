#include "stdafx.h"
#include "PlayerWinState.h"

PlayerWinState::PlayerWinState(Player* player) : player(player) {
}

void PlayerWinState::Enter() {
	player->SetAnimation(PlayerAnimation::IDLE);
	player->SetWin();
}

void PlayerWinState::Update(float deltaTime) {
	if (App::IsKeyPressed(0x52))
		GameStateMachine::GetInstance()->ChangeState(State::START);
}
