#pragma once
#include "states/BaseState.h"
#include "Player.h"
#include "LevelMaker.h"
#include "enemy/Slime.h"
#include "enemy/Bat.h"

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

private:
    CSimpleSprite* background1;
    CSimpleSprite* background2;
    CSimpleSprite* background3;
    float camX;
    float backgroundX;
    float backgroundY;

    LevelMaker levelMaker;
    GameLevel* gameLevel;
    std::unique_ptr<Player> player;

    // Move every sprite in the scene by -camX
    void Translate();
};

