#include "stdafx.h"
#include "PlayerAttackState.h"

PlayerAttackState::PlayerAttackState(Player* p):
	player(p), animTimer(0)
{}

void PlayerAttackState::Enter() {
	animTimer = 0;
	player->SetAnimation(PlayerAnimation::ATTACK);
	App::PlaySoundW(".\\sounds\\sword-unsheathe.wav", false);
}

void PlayerAttackState::Update(float deltaTime) {
	// For the dead animation
	animTimer += 1;
	if (animTimer > 6 * UPDATE_CALLS_PER_FRAME) {
		player->GetSprite()->SetAnimation(-1);
		player->GetSprite()->SetFrame(13);
		player->ChangeState(State::IDLE);
	}

	// Check if collide with enemies
	for (Entity* e : *player->GetGameLevel()->GetEntities()) {
		if (player->InAttackRate(e)) {
			printf("Player attacked enemy\n");
			player->GetGameLevel()->RemoveEntity(e);
		}
	}


	if (App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed(VK_RIGHT) || App::IsKeyPressed(0x41) || App::IsKeyPressed(0x44)) {
		player->ChangeState(State::WALKING);
	}

	if (App::IsKeyPressed(VK_SPACE)) {
		player->ChangeState(State::JUMP);
	}


}