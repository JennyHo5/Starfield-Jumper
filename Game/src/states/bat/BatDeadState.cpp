#include "stdafx.h"
#include "BatDeadState.h"

BatDeadState::BatDeadState(Bat* bat) : bat(bat), animTimer(0) {
}

void BatDeadState::Enter() {
	App::PlaySoundW(".\\sounds\\bat.wav");
	animTimer = 0;
}

void BatDeadState::Update(float deltaTime) {
	if (bat->GetDirection() == 0)
		bat->GetSprite()->SetAnimation(BatAnimation::BAT_DEAD_LEFT);
	else
		bat->GetSprite()->SetAnimation(BatAnimation::BAT_DEAD_RIGHT);

	// For the dead animation
	animTimer += 1;
	if (animTimer >= 15 * UPDATE_CALLS_PER_FRAME) {
		bat->GetSprite()->SetAnimation(-1);
		bat->SetDead();
	}
}
