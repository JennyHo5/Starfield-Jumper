#pragma once
#include "Entity.h"
#include "states/slime/SlimeMovingState.h"

class SlimeMovingState;


enum SlimeAnimation
{
    MOVING
};

class Slime :
    public Entity
{
public:
    Slime(float x, float y, GameLevel&);
};

