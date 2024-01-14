#include "stdafx.h"
#include "Bat.h"

Bat::Bat(float x, float y, GameLevel& level) :
	Entity(x, y, BAT_WIDTH, BAT_HEIGHT,
		App::CreateSprite(".\\graphics\\enemies\\bat.png", 8, 4),
		level)
{
	sprite->CreateAnimation(FLYING_RIGHT, ANIMATION_SPEED, { 0, 1, 2, 3, 4, 5, 6, 7 });
	sprite->CreateAnimation(FLYING_LEFT, ANIMATION_SPEED, { 8, 9, 10, 11, 12, 13, 14, 15 });
	sprite->CreateAnimation(BAT_DEAD_RIGHT, ANIMATION_SPEED, { 16, 17, 18, 19, 20, 21, 22, 23 });
	sprite->CreateAnimation(BAT_DEAD_LEFT, ANIMATION_SPEED, { 31, 30, 29, 28, 27, 26, 25, 24 });
}