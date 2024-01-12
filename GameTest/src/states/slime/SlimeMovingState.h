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
    SlimeMovingState(TileMap*, Player*, Slime *);
    void Update(float deltaTime) override;

private:
    TileMap* map;
    Player* player;
    Slime* slime;
    bool movingDirection; // 0 = left, 1 = right
    int movingDuration;
    float movingTimer;
};

