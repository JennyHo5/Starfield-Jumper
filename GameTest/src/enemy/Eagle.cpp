#include "stdafx.h"
#include "Eagle.h"

Eagle::Eagle(float x, float y, GameLevel& level) :
	Entity(x, y, OPOSUM_WIDTH, OPOSUM_HEIGHT,
		App::CreateSprite(".\\graphics\\eagle.png", 4, 2),
		StateMachine(), level)
{
	sprite->CreateAnimation(FLYING_LEFT, ANIMATION_SPEED, { 0, 1, 2, 3 });
	sprite->CreateAnimation(FLYING_RIGHT, ANIMATION_SPEED, { 4, 5, 6, 7 });
}