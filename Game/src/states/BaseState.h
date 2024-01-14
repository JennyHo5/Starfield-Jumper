#pragma once
#include "app/app.h"
#include "global/constants.h"
#include "global/Util.h"

// The Base State is an abstract base class for all State classes.
class BaseState
{
public:

    // Define common funtions that can be overridden by specific states
    virtual void Enter() {}
    virtual void Update(float deltaTime) {}
    virtual void Render() {}
    virtual void Exit() {}

    virtual State GetType() const = 0;
};

