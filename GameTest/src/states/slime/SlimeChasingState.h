#pragma once
#include "states/BaseState.h"
#include "tilesystem/TileMap.h"
#include "Player.h"
#include "enemy/Slime.h"

class Slime;

class SlimeChasingState :
    public BaseState
{
public:
    SlimeChasingState(TileMap*, Player*, Slime*);
    void Enter() override;
    void Update(float deltaTime) override;

private:
    TileMap* map;
    Player* player;
    Slime* slime;
};

