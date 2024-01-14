#pragma once
#include "app/app.h"
#include "global/constants.h"
#include "global/Util.h"

class BaseState
{
public:

    // Define common methods that can be overridden by specific states
    virtual void Enter() {}
    virtual void Update(float deltaTime) {}
    virtual void Render() {}
    virtual void Exit() {}

    virtual State GetType() const = 0;
};

