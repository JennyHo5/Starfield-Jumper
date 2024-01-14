#pragma once
#include "Entity.h"
#include "states/slime/SlimeMovingState.h"
#include "states/slime/SlimeDeadState.h"
#include "states/slime/SlimeChasingState.h"

class SlimeMovingState;
class SlimeDeadState;
class SlimeChasingState;


enum SlimeAnimation
{
    SLIME_MOVING_LEFT,
    SLIME_DEAD_LEFT,
    SLIME_CHASING_LEFT,
    SLIME_MOVING_RIGHT,
    SLIME_DEAD_RIGHT,
    SLIME_CHASING_RIGHT
};

class Slime :
    public Entity
{
public:
    Slime(float x, float y, GameLevel&);
};

