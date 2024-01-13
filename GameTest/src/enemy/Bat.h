#pragma once
#include "Entity.h"
#include "states/bat/BatFlyingState.h"

class BatFlyingState;


enum BatAnimation
{
    FLYING_LEFT,
    FLYING_RIGHT,
};

class Bat :
    public Entity
{
public:
    Bat(float x, float y, GameLevel&);

};
