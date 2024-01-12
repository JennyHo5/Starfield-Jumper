#pragma once
#include "Entity.h"
#include "states/slime/SlimeMovingState.h"
#include "states/slime/SlimeDeadState.h"

class SlimeMovingState;
class SlimeDeadState;


enum SlimeAnimation
{
    SLIME_MOVING,
    SLIME_DEAD
};

class Slime :
    public Entity
{
public:
    Slime(float x, float y, GameLevel&);
};

