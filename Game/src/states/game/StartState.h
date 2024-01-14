#pragma once
#include <string>
#include "states/BaseState.h"
#include "game.h"

class Game;

// Initial state when the game is launched
class StartState: public BaseState
{
public:
    StartState();

    ~StartState();

    void Enter() override;

    void Update(float deltaTime) override;

    void Render() override;

    void Exit() override {}

    int GetCurrentLevel() { return currentLevel; }

    State GetType() const { return State::START; }

private:
    CSimpleSprite* background1;
    CSimpleSprite* background2;
    CSimpleSprite* background3;
    int currentLevel;
};

