#pragma once
#include "states/BaseState.h"
#include "tilesystem/TileMap.h"
#include "Player.h"
#include "enemy/Slime.h"

class Slime;

class SlimeMovingState :
    public BaseState
{
public:
    SlimeMovingState(const TileMap*, Player*, Slime *);
    void Enter() override;
    void Update(float deltaTime) override;

private:
    const TileMap* map;
    Player* player;
    Slime* slime;
    bool movingDirection; // 0 = left, 1 = right
    int movingDuration;
    float movingTimer;
};

