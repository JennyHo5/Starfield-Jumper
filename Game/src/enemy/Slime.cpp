#include "stdafx.h"
#include "Slime.h"

Slime::Slime(float x, float y, GameLevel& level) :
	Entity(x, y, SLIME_WIDTH, SLIME_HEIGHT,
		App::CreateSprite(".\\graphics\\enemies\\slime.png", 8, 3),
		level)
{
	sprite->CreateAnimation(SLIME_MOVING, ANIMATION_SPEED, { 0, 1, 2, 3, 4, 5, 6, 7 });
	sprite->CreateAnimation(SLIME_DEAD, ANIMATION_SPEED, {16, 17, 18 });
	sprite->CreateAnimation(SLIME_CHASING, ANIMATION_SPEED, {8, 9, 10, 11, 12, 13, 14, 15 });

}

