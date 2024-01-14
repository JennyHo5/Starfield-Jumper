#pragma once
#include "Entity.h"
#include "states/bat/BatFlyingState.h"
#include "states/bat/BatDeadState.h"

class BatFlyingState;
class BatDeadState;


enum BatAnimation
{
    FLYING_LEFT,
    FLYING_RIGHT,
    BAT_DEAD_LEFT,
    BAT_DEAD_RIGHT
};

class Bat :
    public Entity
{
public:
    Bat(float x, float y, GameLevel&);

};
