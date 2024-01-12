#pragma once
#include "states/BaseState.h"
#include "tilesystem/TileMap.h"
#include "Player.h"
#include "enemy/Oposum.h"

class Oposum;

class OposumRunningState :
    public BaseState
{
public:
    OposumRunningState(TileMap*, Player*, Oposum*);
    void Update(float deltaTime) override;

private:
    TileMap* map;
    Player* player;
    Oposum* oposum;
    bool movingDirection; // 0 = left, 1 = right
    int movingDuration;
    float movingTimer;
};

