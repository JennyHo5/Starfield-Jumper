#pragma once
#include "states/BaseState.h"
#include "tilesystem/TileMap.h"
#include "Player.h"
#include "enemy/Bat.h"

class Bat;

class BatFlyingState :
    public BaseState
{
public:
    BatFlyingState(const TileMap*, Player*, Bat*);
    void Update(float deltaTime) override;

private:
    const TileMap* map;
    Player* player;
    Bat* bat;
    bool movingDirection; // 0 = left, 1 = right
    int movingDuration;
    float movingTimer;
};

