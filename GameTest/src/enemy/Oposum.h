#pragma once
#include "Entity.h"
#include "states/oposum/OposumRunningState.h"

class OposumRunningState;


enum OposumAnimation
{
    RUNNING_LEFT,
    RUNNING_RIGHT
};

class Oposum :
    public Entity
{
public:
    Oposum(float x, float y, GameLevel&);
};

