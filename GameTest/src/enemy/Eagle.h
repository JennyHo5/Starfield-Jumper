#pragma once
#include "Entity.h"
#include "states/eagle/EagleFlyingState.h"

class EagleFlyingState;


enum EagleAnimation
{
    FLYING_LEFT,
    FLYING_RIGHT
};

class Eagle :
    public Entity
{
public:
    Eagle(float x, float y, GameLevel&);
};
