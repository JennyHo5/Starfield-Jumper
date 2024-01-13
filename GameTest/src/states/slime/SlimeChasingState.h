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
    SlimeChasingState(const TileMap*, Player*, Slime*);
    void Enter() override;
    void Update(float deltaTime) override;
    void HandleCollision();

private:
    const TileMap* map;
    Player* player;
    Slime* slime;
};

