#include "stdafx.h"
#include "Oposum.h"

Oposum::Oposum(float x, float y, GameLevel& level) :
	Entity(x, y, OPOSUM_WIDTH, OPOSUM_HEIGHT,
		App::CreateSprite(".\\graphics\\oposum.png", 6, 2),
		StateMachine(), level)
{
	sprite->CreateAnimation(RUNNING_LEFT, ANIMATION_SPEED, { 0, 1, 2, 3, 4, 5 });
	sprite->CreateAnimation(RUNNING_RIGHT, ANIMATION_SPEED, { 6, 7, 8, 9, 10, 11 });
}
