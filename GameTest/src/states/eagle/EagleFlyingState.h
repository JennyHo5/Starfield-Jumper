#pragma once
#include "states/BaseState.h"
#include "tilesystem/TileMap.h"
#include "Player.h"
#include "enemy/Eagle.h"

class Eagle;

class EagleFlyingState :
    public BaseState
{
public:
    EagleFlyingState(TileMap*, Player*, Eagle*);
    void Update(float deltaTime) override;

private:
    TileMap* map;
    Player* player;
    Eagle* eagle;
    bool movingDirection; // 0 = left, 1 = right
    int movingDuration;
    float movingTimer;
};

