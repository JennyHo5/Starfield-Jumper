#include "stdafx.h"
#include "Slime.h"

Slime::Slime(float x, float y, GameLevel& level) :
	Entity(x, y, SLIME_WIDTH, SLIME_HEIGHT,
		App::CreateSprite(".\\graphics\\enemies\\slime.png", 8, 6),
		level)
{
	sprite->CreateAnimation(SLIME_MOVING_LEFT, ANIMATION_SPEED, { 0, 1, 2, 3, 4, 5, 6, 7 });
	sprite->CreateAnimation(SLIME_DEAD_LEFT, ANIMATION_SPEED, {16, 17, 18, 19, 20 });
	sprite->CreateAnimation(SLIME_CHASING_LEFT, ANIMATION_SPEED, {8, 9, 10, 11, 12, 13, 14, 15 });
	sprite->CreateAnimation(SLIME_MOVING_RIGHT, ANIMATION_SPEED, { 31, 30, 29, 28, 27, 26, 25, 24 });
	sprite->CreateAnimation(SLIME_DEAD_RIGHT, ANIMATION_SPEED, {47, 46, 45, 44, 43 });
	sprite->CreateAnimation(SLIME_CHASING_RIGHT, ANIMATION_SPEED, {39, 38, 37, 36, 35, 34, 33, 32 });

}

