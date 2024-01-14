#pragma once
#include "states\BaseState.h"
#include "Player.h"
#include "tilesystem\Tile.h"
#include "states\slime\SlimeDeadState.h"

class Player;

class PlayerFallingState : public BaseState
{
public:
	PlayerFallingState(Player* player);
	void Enter() override;
	void Update(float deltaTime) override;
	State GetType() const { return State::FALLING; }


private:
	Player* player;
};

