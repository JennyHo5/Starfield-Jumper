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
    SLIME_MOVING,
    SLIME_DEAD,
    SLIME_CHASING
};

class Slime :
    public Entity
{
public:
    Slime(float x, float y, GameLevel&);
};

