#pragma once
#include "states/BaseState.h"
#include "Player.h"
#include "LevelMaker.h"
#include "enemy/Slime.h"
#include "enemy/Bat.h"

// The main state where the game is actively played
class PlayState: public BaseState
{
public:
    PlayState();
    ~PlayState();

    void Enter() override;

    void Update(float deltaTime) override;

    void Render() override;

    void Exit() override;

    void SpawnEnemies();

    State GetType() const { return State::PLAY; }

private:
    CSimpleSprite* background1;
    CSimpleSprite* background2;
    CSimpleSprite* background3;
    float camX; // the X axis of the camera
    float backgroundX;
    float backgroundY;

    LevelMaker levelMaker;
    std::unique_ptr<GameLevel> gameLevel;
    std::unique_ptr<Player> player;

    // Move every sprite in the scene by -camX
    void Translate();
};

