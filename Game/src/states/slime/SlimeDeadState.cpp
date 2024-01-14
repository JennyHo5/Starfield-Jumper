#include "stdafx.h"
#include "SlimeDeadState.h"

SlimeDeadState::SlimeDeadState(Slime* slime) : slime(slime), animTimer(0) {
}

void SlimeDeadState::Enter() {
	App::PlaySoundW(".\\sounds\\slime.wav");
	animTimer = 0;
}

void SlimeDeadState::Update(float deltaTime) {
	if (slime->GetDirection() == 0)
		slime->GetSprite()->SetAnimation(SLIME_DEAD_LEFT);
	else
		slime->GetSprite()->SetAnimation(SLIME_DEAD_RIGHT);


	// For the dead animation
	animTimer += 1;
	if (animTimer >= 5 * UPDATE_CALLS_PER_FRAME) {
		slime->GetSprite()->SetAnimation(-1);
		slime->SetDead();
	}
}
