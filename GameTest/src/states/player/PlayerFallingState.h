#pragma once
#include "states\BaseState.h"
#include "Player.h"
#include "tilesystem\Tile.h"

class Player;

class PlayerFallingState : public BaseState
{
public:
	PlayerFallingState(Player* player);
	void Enter() override;
	void Update(float deltaTime) override;

private:
	Player* player;
};

